add_library( gui
    STATIC
    
    MainWindow.h
    MainWindow.cpp
    MainWindow.ui )

qt5_use_modules( gui Widgets )