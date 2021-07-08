#ifndef HTTPSCHEMAPLUGIN_H
#define HTTPSCHEMAPLUGIN_H

#include <schemaplugin.h>
#include <atomic>
#include <optional>

class HttpSchemaPlugin : public SchemaPlugin
{
public:
    HttpSchemaPlugin();
    virtual ~HttpSchemaPlugin() override;

    virtual std::vector<std::string> schemaSupported() override;
    virtual std::optional<FetchInfo> fetchUrl(const std::string &url) override;
    virtual std::optional<std::vector<std::string>> parse(SchemaPlugin::FetchInfo &info) override;

private:
    static std::atomic_int instanceCounter_;

    static size_t curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
};

#endif // HTTPSCHEMAPLUGIN_H
