#include <iostream>

#include <QApplication>

#include "GUI.h"

int main(int argc, char* argv[])
{
    std::cout << "Starting..." << std::endl;
    QApplication app(argc, argv);
    GUI gui;
    gui.show();
    int result = app.exec();
    std::cout << "Exiting..." << std::endl;
    return result;
}
