#ifndef SCHEMAPLUGIN_H
#define SCHEMAPLUGIN_H

#include <optional>
#include <vector>
#include <string>

class SchemaPlugin
{
public:
    struct FetchInfo{
        std::string content;
        std::string contentType;
    };

    SchemaPlugin() = default;
    virtual ~SchemaPlugin() = default;

    virtual std::vector<std::string> schemaSupported()
    { return {}; }
    virtual std::optional<FetchInfo> fetchUrl(const std::string &url)
    { return {}; }
    virtual std::optional<std::vector<std::string>> parse(SchemaPlugin::FetchInfo &info)
    { return {}; }
};


extern "C" SchemaPlugin *loadPlugin();


#endif // SCHEMAPLUGIN_H
