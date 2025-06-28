#include <iostream>
#include <vector>
#include <memory>
#ifdef __linux__
#   include <dlfcn.h>  // For Linux/Mac. Use LoadLibrary on Windows
#elif defined(WIN32)
#   include <windows.h>  // For Windows
#endif

#include <plugin_interface.h>

class PluginManager
{
private:

    struct LoadedPlugin
    {
        void* handle;
        std::unique_ptr<IPlugin> plugin;
        DestroyPluginFunc destroyFunc;
    };

    std::vector<LoadedPlugin> plugins;

public:

    ~PluginManager()
    {
        // Clean up all loaded plugins
        for (auto& p : plugins)
        {
            if (p.destroyFunc && p.plugin) {
                p.destroyFunc(p.plugin.release());
            }
            if (p.handle) {
#               ifdef __linux__
                dlclose(p.handle);
#               elif defined(WIN32)
                FreeLibrary((HMODULE)p.handle);
#               endif
            }
        }
    }

    bool loadPlugin(const std::string& filename)
    {
        // Load the shared library
#       ifdef __linux__
        void* handle = dlopen(filename.c_str(), RTLD_LAZY);
#       elif defined(WIN32)
        void* handle = LoadLibrary(filename.c_str());
#       endif
        if (!handle)
        {
#           ifdef __linux__
            std::cerr << "Cannot load plugin: " << dlerror() << std::endl;
#           elif defined(WIN32)
            std::cerr << "Cannot load plugin: " << GetLastError() << std::endl;
#           endif
            return false;
        }

#       ifdef __linux__
        // Get the create and destroy functions
        dlerror(); // Clear any existing error
#       endif

#       ifdef __linux__
        CreatePluginFunc createPlugin = (CreatePluginFunc) dlsym(handle, "createPlugin");
        const char* dlsym_error = dlerror();
        if (dlsym_error)
        {
            std::cerr << "Cannot find createPlugin function: " << dlsym_error << std::endl;
            dlclose(handle);
            return false;
        }

        DestroyPluginFunc destroyPlugin = (DestroyPluginFunc) dlsym(handle, "destroyPlugin");
        dlsym_error = dlerror();
        if (dlsym_error)
        {
            std::cerr << "Cannot find destroyPlugin function: " << dlsym_error << std::endl;
            dlclose(handle);
            return false;
        }
#       elif defined(WIN32)
        CreatePluginFunc createPlugin = (CreatePluginFunc) GetProcAddress((HMODULE)handle, "createPlugin");
        if (!createPlugin)
        {
            std::cerr << "Cannot find createPlugin function: " << GetLastError() << std::endl;
            FreeLibrary((HMODULE)handle);
            return false;
        }

        DestroyPluginFunc destroyPlugin = (DestroyPluginFunc) GetProcAddress((HMODULE)handle, "destroyPlugin");
        if (!destroyPlugin)
        {
            std::cerr << "Cannot find destroyPlugin function: " << GetLastError() << std::endl;
            FreeLibrary((HMODULE)handle);
            return false;
        }
#       endif

        // Create plugin instance
        IPlugin* plugin = createPlugin();
        if (!plugin)
        {
            std::cerr << "Failed to create plugin instance" << std::endl;
#           ifdef __linux__
            dlclose(handle);
#           elif defined(WIN32)
            FreeLibrary((HMODULE)handle);
#           endif
            return false;
        }

        // Store the loaded plugin
        LoadedPlugin loadedPlugin;
        loadedPlugin.handle = handle;
        loadedPlugin.plugin = std::unique_ptr<IPlugin>(plugin);
        loadedPlugin.destroyFunc = destroyPlugin;
        plugins.push_back(std::move(loadedPlugin));

        std::cout << "Loaded plugin: " << plugin->getName()
                  << " (v" << plugin->getVersion() << ")" << std::endl;
        return true;
    }

    void executeAllPlugins()
    {
        std::cout << "\nExecuting all loaded plugins:" << std::endl;
        for (const auto& p : plugins)
        {
            if (p.plugin)
            {
                std::cout << "Running " << p.plugin->getName() << "..." << std::endl;
                p.plugin->execute();
            }
        }
    }

    void listPlugins()
    {
        std::cout << "\nLoaded plugins:" << std::endl;
        for (const auto& p : plugins)
        {
            if (p.plugin)
            {
                std::cout << "- " << p.plugin->getName()
                          << " (v" << p.plugin->getVersion() << ")" << std::endl;
            }
        }
    }
};

int main()
{
    std::cout << "Simple Plugin System Demo" << std::endl;
    std::cout << "=========================" << std::endl;

    PluginManager manager;

    // Try to load some example plugins
    // These would be compiled as separate shared libraries
#   ifdef __linux__
    manager.loadPlugin("../lib/libhello_plugin.so");
    manager.loadPlugin("../lib/libmath_plugin.so");
#   elif defined(WIN32)
    manager.loadPlugin("./hello_plugin.dll");
    manager.loadPlugin("./math_plugin.dll");
#   endif

    // List all loaded plugins
    manager.listPlugins();

    // Execute all plugins
    manager.executeAllPlugins();

    return 0;
}
