#include "dynamiclibrary.h"

DynamicLibrary::DynamicLibrary(const std::string &path)
    :handle_(nullptr, dlclose)
{
     handle_.reset(dlopen(path.c_str(), RTLD_LAZY));
     if (!handle_)
     {
         std::string message("Dynamic Library: ");
         message += dlerror();
         throw std::runtime_error(std::string(message));
     }
}
