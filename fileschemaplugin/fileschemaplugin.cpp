#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

#include "fileschemaplugin.h"

std::atomic_int FileSchemaPlugin::instanceCounter_ = 0;

FileSchemaPlugin::FileSchemaPlugin()
{
}

FileSchemaPlugin::~FileSchemaPlugin()
{}

std::vector<std::string> FileSchemaPlugin::schemaSupported()
{
    static std::vector<std::string> schemas = {
        "file",
    };
    return schemas;
}

std::optional<SchemaPlugin::FetchInfo> FileSchemaPlugin::fetchUrl(const std::string &url)
{
    FetchInfo info;

    std::string real_url = url.substr(7);

    std::string contentType;
    std::string content = "";

    try {
    auto path = std::filesystem::path(real_url);
    auto status = std::filesystem::status(path);
    auto perms = status.permissions();

    auto owRPerms = (perms & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? 1 : 0;
    auto gRPerms = (perms & std::filesystem::perms::group_read) != std::filesystem::perms::none ? 1 : 0;
    auto oRPerms = (perms & std::filesystem::perms::others_read) != std::filesystem::perms::none ? 1 : 0;
    auto owXRPerms = (perms & std::filesystem::perms::owner_exec) != std::filesystem::perms::none? 1 : 0;
    auto gXRPerms = (perms & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? 1 : 0;
    auto gXPerms = (perms & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? 1 : 0;


        if ((owRPerms || gRPerms || oRPerms) && !std::filesystem::is_symlink(real_url))
            if (std::filesystem::exists(real_url))
            {
                if(std::filesystem::is_directory(real_url))
                {

                    contentType = "inode/directory";

                    if (owXRPerms || gXPerms || owXRPerms)
                    {
                        std::ifstream ifs(real_url);
                        std::string test;

                        auto subdir = std::filesystem::directory_iterator(std::filesystem::path(real_url), std::filesystem::directory_options::skip_permission_denied);
                        if (subdir != std::filesystem::directory_iterator()) {


                            try {
                                for(auto& p: subdir)
                                {
                                    content += p.path();
                                    content += ' ';
                                }

                            }  catch (std::runtime_error& e) {
                                return {};
                            }

                        }
                    }

                }
                else
                {
                    contentType = std::filesystem::path(real_url).extension();
                    std::ifstream ifs(real_url);

                    if (ifs)
                    {
                        std::getline(ifs, content);
                    }

                }

        }

    }  catch (std::runtime_error& e) {
    }

    info.content = content;
    info.contentType = contentType;

    return info;

}

std::optional<std::vector<std::string>> FileSchemaPlugin::parse(SchemaPlugin::FetchInfo &info)
{
    std::vector<std::string> urls;

    auto content = info.content;

    std::istringstream iss(info.content);
    std::string line;


    try {
        if (info.contentType == "inode/directory") {
            while(std::getline(iss, line, ' '))
            {
                if (std::filesystem::exists(line))
                    urls.push_back(line);
            }
        }
        else {
            urls.push_back(info.content);
        }

    }  catch (std::runtime_error& e) {

    }

    return urls;

}

size_t FileSchemaPlugin::curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto info = static_cast<FetchInfo*>(userdata);
    if (nmemb != 0)
        info->content.insert(info->content.end(), ptr, ptr + nmemb);

    return nmemb; //TODO: Return a value smaller than nmemb to limit
    //download size. 12-05-20 2:0:0
}

SchemaPlugin *loadPlugin()
{
    return new FileSchemaPlugin;
}
