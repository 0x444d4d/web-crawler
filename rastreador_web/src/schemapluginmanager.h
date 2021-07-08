#ifndef SCHEMAPLUGINMANAGER_H
#define SCHEMAPLUGINMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <map>

#include <schemaplugin.h>
#include "dynamiclibrary.h"

class SchemaPluginManager
{
public:
    using LoadPluginFunctionPtr = decltype (&loadPlugin);

    static const SchemaPluginManager &instance();

    std::unique_ptr<SchemaPlugin> getSchemaPlugin(const std::string &schema) const;


private:
    std::map<std::string, LoadPluginFunctionPtr> schemas_;
    std::vector<DynamicLibrary> libraries_;

    SchemaPluginManager();
    SchemaPluginManager(const SchemaPluginManager&) = delete;
    SchemaPluginManager& operator=(const SchemaPluginManager&) = delete;

};

#endif // SCHEMAPLUGINMANAGER_H
