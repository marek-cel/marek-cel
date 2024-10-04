#pragma once

#include <osgGA/GUIEventAdapter>
#include <SDL.h>

osgGA::GUIEventAdapter::KeySymbol convertKeyFromSdlToOsg(SDL_Keysym key);