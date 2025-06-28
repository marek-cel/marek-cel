#include <iostream>
#include <vector>
#include <memory>
#include <dlfcn.h>  // For Linux/Mac. Use LoadLibrary on Windows

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
                dlclose(p.handle);
            }
        }
    }

    bool loadPlugin(const std::string& filename)
    {
        // Load the shared library
        void* handle = dlopen(filename.c_str(), RTLD_LAZY);
        if (!handle)
        {
            std::cerr << "Cannot load plugin: " << dlerror() << std::endl;
            return false;
        }

        // Get the create and destroy functions
        dlerror(); // Clear any existing error

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

        // Create plugin instance
        IPlugin* plugin = createPlugin();
        if (!plugin)
        {
            std::cerr << "Failed to create plugin instance" << std::endl;
            dlclose(handle);
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
    manager.loadPlugin("../lib/hello_plugin.dll");
    manager.loadPlugin("../lib/math_plugin.dll");
#   endif

    // List all loaded plugins
    manager.listPlugins();

    // Execute all plugins
    manager.executeAllPlugins();

    return 0;
}
