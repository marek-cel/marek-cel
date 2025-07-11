#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <string>

#ifdef __linux__
#   define PLUGIN_API extern "C" __attribute__((visibility("default")))
#elif defined(WIN32)
#   define PLUGIN_API extern "C" __declspec(dllexport)
#endif

// Abstract base class that all plugins must implement
class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual std::string getName() const = 0;
    virtual void execute() = 0;
    virtual int getVersion() const = 0;
};

// Plugin factory function signature
typedef IPlugin* (*CreatePluginFunc)();
typedef void (*DestroyPluginFunc)(IPlugin*);

#endif // PLUGIN_INTERFACE_H
