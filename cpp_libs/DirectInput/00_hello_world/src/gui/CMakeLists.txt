set(MODULE_NAME gui)

################################################################################

set(CPP_FILES
    MainWindow.cpp
)

set(MOC_SRC_FILES
    MainWindow.h
)

set(UIC_SRC_FILES
    MainWindow.ui
)

################################################################################

add_library(${MODULE_NAME} STATIC ${CPP_FILES} ${MOC_SRC_FILES} ${UIC_SRC_FILES})

################################################################################

qt5_use_modules(${MODULE_NAME} Core OpenGL Widgets)
