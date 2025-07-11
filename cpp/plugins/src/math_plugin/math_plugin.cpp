#include <plugin_interface.h>
#include <iostream>
#include <cmath>

class MathPlugin : public IPlugin {
public:
    std::string getName() const override {
        return "Math Plugin";
    }

    void execute() override {
        std::cout << "  Math Plugin: sqrt(16) = " << sqrt(16) << std::endl;
        std::cout << "  Math Plugin: 2^3 = " << pow(2, 3) << std::endl;
    }

    int getVersion() const override {
        return 2;
    }
};

// Plugin factory functions
PLUGIN_API IPlugin* createPlugin() {
        return new MathPlugin();
    }

PLUGIN_API void destroyPlugin(IPlugin* plugin) {
        delete plugin;
    }
