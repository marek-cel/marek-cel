#pragma once

#include <osgGA/GUIEventAdapter>
#include <SFML/Window/Keyboard.hpp>

osgGA::GUIEventAdapter::KeySymbol convertKeyFromSfmlToOsg(sf::Keyboard::Key key);