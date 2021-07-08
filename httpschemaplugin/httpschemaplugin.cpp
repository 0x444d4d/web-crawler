#include <curl/curl.h>
#include "httpschemaplugin.h"
#include <Document.h>
#include <Node.h>



std::atomic_int HttpSchemaPlugin::instanceCounter_ = 0;

HttpSchemaPlugin::HttpSchemaPlugin()
{
    if (instanceCounter_.fetch_add(1, std::memory_order_acquire) == 0)
        curl_global_init(CURL_GLOBAL_ALL);

    ++instanceCounter_;
}

HttpSchemaPlugin::~HttpSchemaPlugin()
{
    if (instanceCounter_.fetch_sub(1, std::memory_order_acquire) == 1)
        curl_global_cleanup();
}

std::vector<std::string> HttpSchemaPlugin::schemaSupported()
{
    static std::vector<std::string> schemas = {
        "http",
        "https"
    };
    return schemas;
}

std::optional<SchemaPlugin::FetchInfo> HttpSchemaPlugin::fetchUrl(const std::string &url)
{
    FetchInfo info;

    CURL* curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, curlWriteCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &info);

    auto result = curl_easy_perform(curl_handle);
    if (result != CURLE_OK && result != CURLE_WRITE_ERROR)
        return {};

    char* contentType = nullptr;
    curl_easy_getinfo(curl_handle, CURLINFO_CONTENT_TYPE, &contentType);
    info.contentType = contentType;

    curl_easy_cleanup(curl_handle);

    return info;

}

std::optional<std::vector<std::string>> HttpSchemaPlugin::parse(SchemaPlugin::FetchInfo &info)
{
    std::vector<std::string> urls;

    auto content = info.content;
    CDocument doc;
    doc.parse(content);
    CSelection elements = doc.find("[href], [src]");
    for (int i = 0; i < elements.nodeNum(); ++i)
    {
        auto node = elements.nodeAt(i);
        auto hrefAttribute = node.attribute("href");
        auto srcAttribute = node.attribute("src");
        if (!hrefAttribute.empty())
            urls.push_back(hrefAttribute);
        if (!srcAttribute.empty())
            urls.push_back(srcAttribute);

    }

    return urls;
}

size_t HttpSchemaPlugin::curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto info = static_cast<FetchInfo*>(userdata);
    if (nmemb != 0)
        info->content.insert(info->content.end(), ptr, ptr + nmemb);

    return nmemb; //TODO: Return a value smaller than nmemb to limit
    //download size. 12-05-20 2:0:0
}

SchemaPlugin *loadPlugin()
{
    return new HttpSchemaPlugin;
}
