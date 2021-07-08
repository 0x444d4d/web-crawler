#ifndef HTTPFETCHPLUGINIMPL_H
#define HTTPFETCHPLUGINIMPL_H

#include <vector>
#include <string>

#include "httpfetchplugin_global.h"

class HttpFetchPlugin
{
public:
    HttpFetchPlugin();

    std::vector<std::string> supportedSchema();

    std::vector<uint8_t> fetchUrl(const std::string &url);
};

#endif // HTTPFETCHPLUGINIMPL_H
