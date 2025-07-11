#include <plugin_interface.h>
#include <iostream>

class HelloPlugin : public IPlugin {
public:
    std::string getName() const override {
        return "Hello Plugin";
    }

    void execute() override {
        std::cout << "  Hello from the Hello Plugin!" << std::endl;
    }

    int getVersion() const override {
        return 1;
    }
};

// Plugin factory functions
PLUGIN_API IPlugin* createPlugin()
{
    return new HelloPlugin();
}

PLUGIN_API void destroyPlugin(IPlugin* plugin)
{
    delete plugin;
}



