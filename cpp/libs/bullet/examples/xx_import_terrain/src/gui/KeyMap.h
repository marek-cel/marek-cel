#ifndef KEYMAP_H
#define KEYMAP_H

////////////////////////////////////////////////////////////////////////////////

#include <osgGA/GUIEventAdapter>

////////////////////////////////////////////////////////////////////////////////

/** */
class KeyMap
{
public:

    static osgGA::GUIEventAdapter::KeySymbol remapOSG( int key_qt );
};

////////////////////////////////////////////////////////////////////////////////

#endif // KEYMAP_H