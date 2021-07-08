#ifndef HTTPFETCHPLUGIN_H
#define HTTPFETCHPLUGIN_H

#include <vector>
#include <string>

extern "C"
{

#ifndef _cplusplus
struct HttpFetchPluginC
{
  char **(*supportedSchema)(HttpFetchPluginC *plugin);
  char **(*fetchUrl)(HttpFetchPluginC *plugin, const char *url);
};
#else
class HttpFetchPlugin;
#endif

HttpFetchPluginC *makeHttpFetchPlugin();


//char** supportedSchema(HttpFetchPluginC *plugin);

//char** fetchUrl(HttpFetchPluginC *plugin, const char* url);

void destroyHttpFetchPlugin(HttpFetchPluginC *plugin);

}

#endif // HTTPFETCHPLUGIN_H
