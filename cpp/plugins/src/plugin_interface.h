#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <string>

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
