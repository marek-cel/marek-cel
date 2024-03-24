#include <KeyMap.h>

#include <qnamespace.h>

osgGA::GUIEventAdapter::KeySymbol remapKeysFromQtToOSG(int key_qt)
{
    switch ( key_qt )
    {
    case Qt::Key_0:
        return osgGA::GUIEventAdapter::KEY_0;

    case Qt::Key_1:
        return osgGA::GUIEventAdapter::KEY_1;

    case Qt::Key_2:
        return osgGA::GUIEventAdapter::KEY_2;

    case Qt::Key_3:
        return osgGA::GUIEventAdapter::KEY_3;

    case Qt::Key_4:
        return osgGA::GUIEventAdapter::KEY_4;

    case Qt::Key_5:
        return osgGA::GUIEventAdapter::KEY_5;

    case Qt::Key_6:
        return osgGA::GUIEventAdapter::KEY_6;

    case Qt::Key_7:
        return osgGA::GUIEventAdapter::KEY_7;

    case Qt::Key_8:
        return osgGA::GUIEventAdapter::KEY_8;

    case Qt::Key_9:
        return osgGA::GUIEventAdapter::KEY_9;

    case Qt::Key_A:
        return osgGA::GUIEventAdapter::KEY_A;

    case Qt::Key_B:
        return osgGA::GUIEventAdapter::KEY_B;

    case Qt::Key_C:
        return osgGA::GUIEventAdapter::KEY_C;

    case Qt::Key_D:
        return osgGA::GUIEventAdapter::KEY_D;

    case Qt::Key_E:
        return osgGA::GUIEventAdapter::KEY_E;

    case Qt::Key_F:
        return osgGA::GUIEventAdapter::KEY_F;

    case Qt::Key_G:
        return osgGA::GUIEventAdapter::KEY_G;

    case Qt::Key_H:
        return osgGA::GUIEventAdapter::KEY_H;

    case Qt::Key_I:
        return osgGA::GUIEventAdapter::KEY_I;

    case Qt::Key_J:
        return osgGA::GUIEventAdapter::KEY_J;

    case Qt::Key_K:
        return osgGA::GUIEventAdapter::KEY_K;

    case Qt::Key_L:
        return osgGA::GUIEventAdapter::KEY_L;

    case Qt::Key_M:
        return osgGA::GUIEventAdapter::KEY_M;

    case Qt::Key_N:
        return osgGA::GUIEventAdapter::KEY_N;

    case Qt::Key_O:
        return osgGA::GUIEventAdapter::KEY_O;

    case Qt::Key_P:
        return osgGA::GUIEventAdapter::KEY_P;

    case Qt::Key_Q:
        return osgGA::GUIEventAdapter::KEY_Q;

    case Qt::Key_R:
        return osgGA::GUIEventAdapter::KEY_R;

    case Qt::Key_S:
        return osgGA::GUIEventAdapter::KEY_S;

    case Qt::Key_T:
        return osgGA::GUIEventAdapter::KEY_T;

    case Qt::Key_U:
        return osgGA::GUIEventAdapter::KEY_U;

    case Qt::Key_V:
        return osgGA::GUIEventAdapter::KEY_V;

    case Qt::Key_W:
        return osgGA::GUIEventAdapter::KEY_W;

    case Qt::Key_X:
        return osgGA::GUIEventAdapter::KEY_X;

    case Qt::Key_Y:
        return osgGA::GUIEventAdapter::KEY_Y;

    case Qt::Key_Z:
        return osgGA::GUIEventAdapter::KEY_Z;

    case Qt::Key_Escape:
        return osgGA::GUIEventAdapter::KEY_Escape;

    case Qt::Key_Tab:
        return osgGA::GUIEventAdapter::KEY_Tab;

    case Qt::Key_Backspace:
        return osgGA::GUIEventAdapter::KEY_BackSpace;

    case Qt::Key_Return:
        return osgGA::GUIEventAdapter::KEY_Return;

    case Qt::Key_Enter:
        return osgGA::GUIEventAdapter::KEY_KP_Enter;

    case Qt::Key_QuoteLeft:
        return osgGA::GUIEventAdapter::KEY_Backquote;

    case Qt::Key_Minus:
        return osgGA::GUIEventAdapter::KEY_Minus;

    case Qt::Key_Equal:
        return osgGA::GUIEventAdapter::KEY_Equals;

    case Qt::Key_BracketLeft:
        return osgGA::GUIEventAdapter::KEY_Leftbracket;

    case Qt::Key_BracketRight:
        return osgGA::GUIEventAdapter::KEY_Rightbracket;

    case Qt::Key_Semicolon:
        return osgGA::GUIEventAdapter::KEY_Semicolon;

    case Qt::Key_Apostrophe:
        return osgGA::GUIEventAdapter::KEY_Quote;

    case Qt::Key_Comma:
        return osgGA::GUIEventAdapter::KEY_Comma;

    case Qt::Key_Period:
        return osgGA::GUIEventAdapter::KEY_Period;

    case Qt::Key_Slash:
        return osgGA::GUIEventAdapter::KEY_Slash;

    case Qt::Key_Space:
        return osgGA::GUIEventAdapter::KEY_Space;

    case Qt::Key_Left:
        return osgGA::GUIEventAdapter::KEY_Left;

    case Qt::Key_Right:
        return osgGA::GUIEventAdapter::KEY_Right;

    case Qt::Key_Up:
        return osgGA::GUIEventAdapter::KEY_Up;

    case Qt::Key_Down:
        return osgGA::GUIEventAdapter::KEY_Down;

    case Qt::Key_Insert:
        return osgGA::GUIEventAdapter::KEY_Insert;

    case Qt::Key_Delete:
        return osgGA::GUIEventAdapter::KEY_Delete;

    case Qt::Key_Home:
        return osgGA::GUIEventAdapter::KEY_Home;

    case Qt::Key_End:
        return osgGA::GUIEventAdapter::KEY_End;

    case Qt::Key_PageUp:
        return osgGA::GUIEventAdapter::KEY_Page_Up;

    case Qt::Key_PageDown:
        return osgGA::GUIEventAdapter::KEY_Page_Down;

    case Qt::Key_Shift:
        return osgGA::GUIEventAdapter::KEY_Shift_L;

    case Qt::Key_Control:
        return osgGA::GUIEventAdapter::KEY_Control_L;

    case Qt::Key_Meta:
        return osgGA::GUIEventAdapter::KEY_Meta_L;

    case Qt::Key_Alt:
        return osgGA::GUIEventAdapter::KEY_Alt_L;

    case Qt::Key_F1:
        return osgGA::GUIEventAdapter::KEY_F1;

    case Qt::Key_F2:
        return osgGA::GUIEventAdapter::KEY_F2;

    case Qt::Key_F3:
        return osgGA::GUIEventAdapter::KEY_F3;

    case Qt::Key_F4:
        return osgGA::GUIEventAdapter::KEY_F4;

    case Qt::Key_F5:
        return osgGA::GUIEventAdapter::KEY_F5;

    case Qt::Key_F6:
        return osgGA::GUIEventAdapter::KEY_F6;

    case Qt::Key_F7:
        return osgGA::GUIEventAdapter::KEY_F7;

    case Qt::Key_F8:
        return osgGA::GUIEventAdapter::KEY_F8;

    case Qt::Key_F9:
        return osgGA::GUIEventAdapter::KEY_F9;

    case Qt::Key_F10:
        return osgGA::GUIEventAdapter::KEY_F10;

    case Qt::Key_F11:
        return osgGA::GUIEventAdapter::KEY_F11;

    case Qt::Key_F12:
        return osgGA::GUIEventAdapter::KEY_F12;
    }

    return (osgGA::GUIEventAdapter::KeySymbol)(-1);
}

