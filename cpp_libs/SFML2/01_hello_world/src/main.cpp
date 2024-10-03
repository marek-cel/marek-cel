#include <iostream>

#include <SFML/Window.hpp>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    sf::Window window(sf::VideoMode(800, 600), "Hello, World!", sf::Style::Default);
    window.setFramerateLimit(60); // call it once, after creating the window

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "Closing window..." << std::endl;
                window.close();
            }
        }
    }

    return 0;
}