set(MODULE_NAME gui)

################################################################################

set(CPP_FILES
    ImGuiApp.cpp
    ImGuiEventHandler.cpp
)

################################################################################

add_library(${MODULE_NAME} STATIC ${CPP_FILES})