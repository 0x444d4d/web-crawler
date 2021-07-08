#include "schemapluginmanager.h"

using namespace std::literals;

const auto LOADPLUGIN_SYMBOL_NAME = "loadPlugin";

SchemaPluginManager::SchemaPluginManager()
{
    //TODO: iterar sobre los *.so encontrados para:
    try{
        libraries_.emplace_back("../httpschemaplugin/libhttpschemaplugin.so");
        libraries_.emplace_back("../fileschemaplugin/libfileschemaplugin.so");
    }
    catch(std::runtime_error& e)
    {
        return;
    }

    for (uint8_t i = 0; i < libraries_.size(); ++i)
    {
        auto loadPlugin = libraries_[i].resolve<LoadPluginFunctionPtr>(LOADPLUGIN_SYMBOL_NAME);
        if (!loadPlugin)
        {
            libraries_.pop_back();
            return;
        }

        auto schemaPlugin = (loadPlugin.value())();
        for (auto schema : schemaPlugin->schemaSupported())
        {
            schemas_.emplace(schema, loadPlugin.value());
        }
    }

}

const SchemaPluginManager &SchemaPluginManager::instance()
{
    static SchemaPluginManager instance;
    return instance;
}

std::unique_ptr<SchemaPlugin> SchemaPluginManager::getSchemaPlugin(const std::string &schema) const
{
    auto iter = schemas_.find(schema);
    if (iter == schemas_.end())
    {
        return nullptr;
    }
    else {
        return std::unique_ptr<SchemaPlugin>((iter->second)());
    }
}
