#ifndef REMAPKEYSFROMSDLTOOSG_H
#define REMAPKEYSFROMSDLTOOSG_H

#include <osgGA/GUIEventAdapter>
#include <SDL.h>

osgGA::GUIEventAdapter::KeySymbol remapKeysFromSdlToOsg(SDL_Keysym key);

#endif // REMAPKEYSFROMSDLTOOSG_H
