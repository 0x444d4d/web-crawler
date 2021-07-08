#include "httpfetchpluginimpl.h"
#include "httpfetchplugin.h"

HttpFetchPlugin::HttpFetchPlugin()
{

}

std::vector<std::string> HttpFetchPlugin::supportedSchema()
{

}

std::vector<uint8_t> HttpFetchPlugin::fetchUrl(const std::string &url)
{

}

char **supportedSchema(HttpFetchPluginC *plugin)
{
    auto list = plugin->supportedSchema(plugin);
    //TODO: convert list to char**
}

char **fetchUrl(HttpFetchPluginC *plugin, const char *url)
{
    auto bytes = plugin->fetchUrl(plugin, url);
    //TODO: convert bytes tochar**
}

HttpFetchPluginC *makeHttpFetchPlugin()
{
    auto C =  new HttpFetchPluginC();
    C->fetchUrl = &fetchUrl;
    C->supportedSchema = &supportedSchema;
}


void destroyHttpFetchPlugin(HttpFetchPlugin *plugin)
{
    delete plugin;
}
