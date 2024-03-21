#include <iostream>

#include <WindowGL.h>

int main(int argc, char* argv[])
{
    WindowGL window;
    if (!window.Init())
    {
        std::cerr << "Error initializing GL Window" << std::endl;
        return -1;
    }

    window.Run();

    return 0;
}
