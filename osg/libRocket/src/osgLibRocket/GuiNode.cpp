/****************************************************************************//*
 * osgLibRocket, an interface for OpenSceneGraph to use LibRocket
 *
 * This code is copyright (c) 2011 Martin Scheffler martin.scheffler@googlemail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <sstream>

#include <OpenThreads/ScopedLock>

#include <osg/Notify>
#include <osg/TexMat>
#include <osg/TextureRectangle>
#include <osgGA/EventVisitor>
#include <osgViewer/View>
#include <osg/ShapeDrawable>

#include <osgLibRocket/GuiNode.h>

////////////////////////////////////////////////////////////////////////////////

using namespace osgLibRocket;

////////////////////////////////////////////////////////////////////////////////

GuiNode::GuiNode( const std::string &contextname, bool debug ) :
    m_previousTraversalNumber( osg::UNINITIALIZED_FRAME_NUMBER ),
    m_camera(NULL)
{
    m_renderer = dynamic_cast< osgLibRocket::RenderInterface* >( Rocket::Core::GetRenderInterface() );
    if( m_renderer == NULL )
    {
        OSG_FATAL << "Please set libRocket render interface!\n";
    }

    setDataVariance( osg::Object::DYNAMIC );

    // if this is not set, osgViewer does not know how to set up initial camera transform:
    setInitialBound( osg::BoundingSphere( osg::Vec3( 500, 500, 0 ), 500 ) );

    // register for update traversal
    setNumChildrenRequiringUpdateTraversal( getNumChildrenRequiringUpdateTraversal() + 1 );

    // register for update traversal
    setNumChildrenRequiringEventTraversal( getNumChildrenRequiringEventTraversal() + 1 );

    // create libRocket context for this gui
    m_context = Rocket::Core::CreateContext( contextname.c_str(), Rocket::Core::Vector2i( 1024, 768 ) );
    if( m_context != NULL )
    {
        // add error and other debug stuff to this gui. only one gui at a time may have the
        // debug view
        if ( debug )
        {
            Rocket::Debugger::Initialise( m_context );
        }
    }

    getOrCreateStateSet()->setRenderBinDetails( 1000, "TraversalOrderBin" );
}

////////////////////////////////////////////////////////////////////////////////

GuiNode::~GuiNode()
{
    if ( m_context )
    {
        m_context->RemoveReference();
    }
}

////////////////////////////////////////////////////////////////////////////////

void GuiNode::setCamera( osg::Camera *cam )
{
    m_camera = cam;

    osgViewer::GraphicsWindow* win = dynamic_cast< osgViewer::GraphicsWindow* >( cam->getGraphicsContext() );

    if ( win )
    {
        int x, y, w, h;
        win->getWindowRectangle( x, y, w, h );
        setScreenSize( w, h );
    }
}

////////////////////////////////////////////////////////////////////////////////

void GuiNode::traverse(osg::NodeVisitor& nv)
{
    switch( nv.getVisitorType() )
    {
    case osg::NodeVisitor::UPDATE_VISITOR:
    {
        // ensure that we do not operate on this node more than
        // once during this traversal.  This is an issue since node
        // can be shared between multiple parents.
        if ( ( nv.getTraversalNumber() != m_previousTraversalNumber ) && nv.getFrameStamp() )
        {
            if( m_context != 0 )
            {
                //_toLocal =  osg::computeWorldToLocal(nv.getNodePath());
                m_renderer->setRenderTarget(this);

                m_context->Update();


                removeChildren(0, getNumChildren());
                m_context->Render();

            }
        }
    }
        break;

    case osg::NodeVisitor::EVENT_VISITOR:
    {
        osgGA::EventVisitor* ev = static_cast< osgGA::EventVisitor* >( &nv );
        for ( osgGA::EventQueue::Events::iterator itr = ev->getEvents().begin();
              itr != ev->getEvents().end();
              ++itr )
        {
#           ifdef __ANDROID__
            osgGA::GUIEventAdapter *ea = (*itr)->asGUIEventAdapter();
#           else
            osgGA::GUIEventAdapter *ea = (*itr).get();
#           endif

            if ( handle( *ea, *ev, *( ev->getActionAdapter() ) ) ) ea->setHandled( true );
        }
        
    }
        break;

    default: break;
    }

    osg::Group::traverse( nv );
}

////////////////////////////////////////////////////////////////////////////////

Rocket::Core::Input::KeyIdentifier GuiNode::GetKeyCode( int osgkey )
{
    switch ( osgkey )
    {
        case osgGA::GUIEventAdapter::KEY_Space: return Rocket::Core::Input::KI_SPACE;

        case osgGA::GUIEventAdapter::KEY_0: return Rocket::Core::Input::KI_0;
        case osgGA::GUIEventAdapter::KEY_1: return Rocket::Core::Input::KI_1;
        case osgGA::GUIEventAdapter::KEY_2: return Rocket::Core::Input::KI_2;
        case osgGA::GUIEventAdapter::KEY_3: return Rocket::Core::Input::KI_3;
        case osgGA::GUIEventAdapter::KEY_4: return Rocket::Core::Input::KI_4;
        case osgGA::GUIEventAdapter::KEY_5: return Rocket::Core::Input::KI_5;
        case osgGA::GUIEventAdapter::KEY_6: return Rocket::Core::Input::KI_6;
        case osgGA::GUIEventAdapter::KEY_7: return Rocket::Core::Input::KI_7;
        case osgGA::GUIEventAdapter::KEY_8: return Rocket::Core::Input::KI_8;
        case osgGA::GUIEventAdapter::KEY_9: return Rocket::Core::Input::KI_9;
        case osgGA::GUIEventAdapter::KEY_A: return Rocket::Core::Input::KI_A;
        case osgGA::GUIEventAdapter::KEY_B: return Rocket::Core::Input::KI_B;
        case osgGA::GUIEventAdapter::KEY_C: return Rocket::Core::Input::KI_C;
        case osgGA::GUIEventAdapter::KEY_D: return Rocket::Core::Input::KI_D;
        case osgGA::GUIEventAdapter::KEY_E: return Rocket::Core::Input::KI_E;
        case osgGA::GUIEventAdapter::KEY_F: return Rocket::Core::Input::KI_F;
        case osgGA::GUIEventAdapter::KEY_G: return Rocket::Core::Input::KI_G;
        case osgGA::GUIEventAdapter::KEY_H: return Rocket::Core::Input::KI_H;
        case osgGA::GUIEventAdapter::KEY_I: return Rocket::Core::Input::KI_I;
        case osgGA::GUIEventAdapter::KEY_J: return Rocket::Core::Input::KI_J;
        case osgGA::GUIEventAdapter::KEY_K: return Rocket::Core::Input::KI_K;
        case osgGA::GUIEventAdapter::KEY_L: return Rocket::Core::Input::KI_L;
        case osgGA::GUIEventAdapter::KEY_M: return Rocket::Core::Input::KI_M;
        case osgGA::GUIEventAdapter::KEY_N: return Rocket::Core::Input::KI_N;
        case osgGA::GUIEventAdapter::KEY_O: return Rocket::Core::Input::KI_O;
        case osgGA::GUIEventAdapter::KEY_P: return Rocket::Core::Input::KI_P;
        case osgGA::GUIEventAdapter::KEY_Q: return Rocket::Core::Input::KI_Q;
        case osgGA::GUIEventAdapter::KEY_R: return Rocket::Core::Input::KI_R;
        case osgGA::GUIEventAdapter::KEY_S: return Rocket::Core::Input::KI_S;
        case osgGA::GUIEventAdapter::KEY_T: return Rocket::Core::Input::KI_T;
        case osgGA::GUIEventAdapter::KEY_U: return Rocket::Core::Input::KI_U;
        case osgGA::GUIEventAdapter::KEY_V: return Rocket::Core::Input::KI_V;
        case osgGA::GUIEventAdapter::KEY_W: return Rocket::Core::Input::KI_W;
        case osgGA::GUIEventAdapter::KEY_X: return Rocket::Core::Input::KI_X;
        case osgGA::GUIEventAdapter::KEY_Y: return Rocket::Core::Input::KI_Y;
        case osgGA::GUIEventAdapter::KEY_Z: return Rocket::Core::Input::KI_Z;

        case osgGA::GUIEventAdapter::KEY_F1  : return Rocket::Core::Input::KI_F1;
        case osgGA::GUIEventAdapter::KEY_F2  : return Rocket::Core::Input::KI_F2;
        case osgGA::GUIEventAdapter::KEY_F3  : return Rocket::Core::Input::KI_F3;
        case osgGA::GUIEventAdapter::KEY_F4  : return Rocket::Core::Input::KI_F4;
        case osgGA::GUIEventAdapter::KEY_F5  : return Rocket::Core::Input::KI_F5;
        case osgGA::GUIEventAdapter::KEY_F6  : return Rocket::Core::Input::KI_F6;
        case osgGA::GUIEventAdapter::KEY_F7  : return Rocket::Core::Input::KI_F7;
        case osgGA::GUIEventAdapter::KEY_F8  : return Rocket::Core::Input::KI_F8;
        case osgGA::GUIEventAdapter::KEY_F9  : return Rocket::Core::Input::KI_F9;
        case osgGA::GUIEventAdapter::KEY_F10 : return Rocket::Core::Input::KI_F10;
        case osgGA::GUIEventAdapter::KEY_F11 : return Rocket::Core::Input::KI_F11;
        case osgGA::GUIEventAdapter::KEY_F12 : return Rocket::Core::Input::KI_F12;
        case osgGA::GUIEventAdapter::KEY_F13 : return Rocket::Core::Input::KI_F13;
        case osgGA::GUIEventAdapter::KEY_F14 : return Rocket::Core::Input::KI_F14;
        case osgGA::GUIEventAdapter::KEY_F15 : return Rocket::Core::Input::KI_F15;
        case osgGA::GUIEventAdapter::KEY_F16 : return Rocket::Core::Input::KI_F16;
        case osgGA::GUIEventAdapter::KEY_F17 : return Rocket::Core::Input::KI_F17;
        case osgGA::GUIEventAdapter::KEY_F18 : return Rocket::Core::Input::KI_F18;
        case osgGA::GUIEventAdapter::KEY_F19 : return Rocket::Core::Input::KI_F19;
        case osgGA::GUIEventAdapter::KEY_F20 : return Rocket::Core::Input::KI_F20;
        case osgGA::GUIEventAdapter::KEY_F21 : return Rocket::Core::Input::KI_F21;
        case osgGA::GUIEventAdapter::KEY_F22 : return Rocket::Core::Input::KI_F22;
        case osgGA::GUIEventAdapter::KEY_F23 : return Rocket::Core::Input::KI_F23;
        case osgGA::GUIEventAdapter::KEY_F24 : return Rocket::Core::Input::KI_F24;


        case osgGA::GUIEventAdapter::KEY_Plus: return Rocket::Core::Input::KI_ADD;

        case osgGA::GUIEventAdapter::KEY_Home:      return Rocket::Core::Input::KI_HOME;
        case osgGA::GUIEventAdapter::KEY_Left:      return Rocket::Core::Input::KI_LEFT;
        case osgGA::GUIEventAdapter::KEY_Up:        return Rocket::Core::Input::KI_UP;
        case osgGA::GUIEventAdapter::KEY_Right:     return Rocket::Core::Input::KI_RIGHT;
        case osgGA::GUIEventAdapter::KEY_Down:      return Rocket::Core::Input::KI_DOWN;
        case osgGA::GUIEventAdapter::KEY_Page_Up:   return Rocket::Core::Input::KI_PRIOR;
        case osgGA::GUIEventAdapter::KEY_Page_Down: return Rocket::Core::Input::KI_NEXT;
        case osgGA::GUIEventAdapter::KEY_End:       return Rocket::Core::Input::KI_END;
        case osgGA::GUIEventAdapter::KEY_Begin:     return Rocket::Core::Input::KI_HOME;

        case osgGA::GUIEventAdapter::KEY_BackSpace:   return Rocket::Core::Input::KI_BACK;
        case osgGA::GUIEventAdapter::KEY_Tab:         return Rocket::Core::Input::KI_TAB;
        case osgGA::GUIEventAdapter::KEY_Clear:       return Rocket::Core::Input::KI_CLEAR;
        case osgGA::GUIEventAdapter::KEY_Return:      return Rocket::Core::Input::KI_RETURN;
        case osgGA::GUIEventAdapter::KEY_Pause:       return Rocket::Core::Input::KI_PAUSE;
        case osgGA::GUIEventAdapter::KEY_Scroll_Lock: return Rocket::Core::Input::KI_SCROLL;
        case osgGA::GUIEventAdapter::KEY_Escape:      return Rocket::Core::Input::KI_ESCAPE;
        case osgGA::GUIEventAdapter::KEY_Delete:      return Rocket::Core::Input::KI_DELETE;

        case osgGA::GUIEventAdapter::KEY_KP_0: return Rocket::Core::Input::KI_NUMPAD0;
        case osgGA::GUIEventAdapter::KEY_KP_1: return Rocket::Core::Input::KI_NUMPAD1;
        case osgGA::GUIEventAdapter::KEY_KP_2: return Rocket::Core::Input::KI_NUMPAD2;
        case osgGA::GUIEventAdapter::KEY_KP_3: return Rocket::Core::Input::KI_NUMPAD3;
        case osgGA::GUIEventAdapter::KEY_KP_4: return Rocket::Core::Input::KI_NUMPAD4;
        case osgGA::GUIEventAdapter::KEY_KP_5: return Rocket::Core::Input::KI_NUMPAD5;
        case osgGA::GUIEventAdapter::KEY_KP_6: return Rocket::Core::Input::KI_NUMPAD6;
        case osgGA::GUIEventAdapter::KEY_KP_7: return Rocket::Core::Input::KI_NUMPAD7;
        case osgGA::GUIEventAdapter::KEY_KP_8: return Rocket::Core::Input::KI_NUMPAD8;
        case osgGA::GUIEventAdapter::KEY_KP_9: return Rocket::Core::Input::KI_NUMPAD9;

        case osgGA::GUIEventAdapter::KEY_Shift_L:   return Rocket::Core::Input::KI_LSHIFT;
        case osgGA::GUIEventAdapter::KEY_Shift_R:   return Rocket::Core::Input::KI_RSHIFT;
        case osgGA::GUIEventAdapter::KEY_Control_L: return Rocket::Core::Input::KI_LCONTROL;
        case osgGA::GUIEventAdapter::KEY_Control_R: return Rocket::Core::Input::KI_RCONTROL;

        default : return Rocket::Core::Input::KI_UNKNOWN;
    }

    /*
    Not (yet) mapped:

    KEY_Alt_L           = 0xFFE9,
    KEY_Alt_R           = 0xFFEA,

    KEY_Linefeed        = 0xFF0A,
    KEY_Sys_Req         = 0xFF15,

    KEY_Exclaim         = 0x21,
    KEY_Quotedbl        = 0x22,
    KEY_Hash            = 0x23,
    KEY_Dollar          = 0x24,
    KEY_Ampersand       = 0x26,
    KEY_Quote           = 0x27,
    KEY_Leftparen       = 0x28,
    KEY_Rightparen      = 0x29,
    KEY_Asterisk        = 0x2A,
    KEY_Comma           = 0x2C,
    KEY_Minus           = 0x2D,
    KEY_Period          = 0x2E,
    KEY_Slash           = 0x2F,
    KEY_Colon           = 0x3A,
    KEY_Semicolon       = 0x3B,
    KEY_Less            = 0x3C,
    KEY_Equals          = 0x3D,
    KEY_Greater         = 0x3E,
    KEY_Question        = 0x3F,
    KEY_At              = 0x40,
    KEY_Leftbracket     = 0x5B,
    KEY_Backslash       = 0x5C,
    KEY_Rightbracket    = 0x5D,
    KEY_Caret           = 0x5E,
    KEY_Underscore      = 0x5F,
    KEY_Backquote       = 0x60,

      KEY_F25             = 0xFFD6,
      KEY_F26             = 0xFFD7,
      KEY_F27             = 0xFFD8,
      KEY_F28             = 0xFFD9,
      KEY_F29             = 0xFFDA,
      KEY_F30             = 0xFFDB,
      KEY_F31             = 0xFFDC,
      KEY_F32             = 0xFFDD,
      KEY_F33             = 0xFFDE,
      KEY_F34             = 0xFFDF,
      KEY_F35             = 0xFFE0,






    KEY_Select          = 0xFF60,
    KEY_Print           = 0xFF61,
    KEY_Execute         = 0xFF62,
    KEY_Insert          = 0xFF63,
    KEY_Undo            = 0xFF65,
    KEY_Redo            = 0xFF66,
    KEY_Menu            = 0xFF67,
    KEY_Find            = 0xFF68,
    KEY_Cancel          = 0xFF69,
    KEY_Help            = 0xFF6A,
    KEY_Break           = 0xFF6B,
    KEY_Mode_switch     = 0xFF7E,
    KEY_Script_switch   = 0xFF7E,
    KEY_Num_Lock        = 0xFF7F,


    KEY_KP_Space        = 0xFF80,
    KEY_KP_Tab          = 0xFF89,
    KEY_KP_Enter        = 0xFF8D,
    KEY_KP_F1           = 0xFF91,
    KEY_KP_F2           = 0xFF92,
    KEY_KP_F3           = 0xFF93,
    KEY_KP_F4           = 0xFF94,
    KEY_KP_Home         = 0xFF95,
    KEY_KP_Left         = 0xFF96,
    KEY_KP_Up           = 0xFF97,
    KEY_KP_Right        = 0xFF98,
    KEY_KP_Down         = 0xFF99,
    KEY_KP_Prior        = 0xFF9A,
    KEY_KP_Page_Up      = 0xFF9A,
    KEY_KP_Next         = 0xFF9B,
    KEY_KP_Page_Down    = 0xFF9B,
    KEY_KP_End          = 0xFF9C,
    KEY_KP_Begin        = 0xFF9D,
    KEY_KP_Insert       = 0xFF9E,
    KEY_KP_Delete       = 0xFF9F,
    KEY_KP_Equal        = 0xFFBD,
    KEY_KP_Multiply     = 0xFFAA,
    KEY_KP_Add          = 0xFFAB,
    KEY_KP_Separator    = 0xFFAC,
    KEY_KP_Subtract     = 0xFFAD,
    KEY_KP_Decimal      = 0xFFAE,
    KEY_KP_Divide       = 0xFFAF,


    KEY_Caps_Lock       = 0xFFE5,
    KEY_Shift_Lock      = 0xFFE6,

    KEY_Meta_L          = 0xFFE7,
    KEY_Meta_R          = 0xFFE8,
     KEY_Super_L         = 0xFFEB,
    KEY_Super_R         = 0xFFEC,
    KEY_Hyper_L         = 0xFFED,
    KEY_Hyper_R         = 0xFFEE  */
}

////////////////////////////////////////////////////////////////////////////////

int GuiNode::GetKeyModifiers( int osgModKeyMask )
{
    int ret = 0;

    if ( ( osgModKeyMask & osgGA::GUIEventAdapter::MODKEY_SHIFT     ) != 0 ) ret |= Rocket::Core::Input::KM_SHIFT;
    if ( ( osgModKeyMask & osgGA::GUIEventAdapter::MODKEY_ALT       ) != 0 ) ret |= Rocket::Core::Input::KM_ALT;
    if ( ( osgModKeyMask & osgGA::GUIEventAdapter::MODKEY_META      ) != 0 ) ret |= Rocket::Core::Input::KM_META;
    if ( ( osgModKeyMask & osgGA::GUIEventAdapter::MODKEY_CAPS_LOCK ) != 0 ) ret |= Rocket::Core::Input::KM_CAPSLOCK;
    if ( ( osgModKeyMask & osgGA::GUIEventAdapter::MODKEY_NUM_LOCK  ) != 0 ) ret |= Rocket::Core::Input::KM_NUMLOCK;

    return ret;
}

////////////////////////////////////////////////////////////////////////////////

int GuiNode::GetButtonId(int button)
{
    switch ( button )
    {
        case osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON   : return 0;
        case osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON  : return 1;
        case osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON : return 2;
        default: return button;
    }
}

////////////////////////////////////////////////////////////////////////////////

void GuiNode::mousePosition( osgViewer::View *view,
                             const osgGA::GUIEventAdapter &ea,
                             osgGA::EventVisitor &ev,
                             int &x, int &y )
{
    if ( m_camera.valid() )
    {
        // fullscreen

        Rocket::Core::Vector2i dims = m_context->GetDimensions();
        x = ea.getX();
        y = dims.y - ea.getY();
    }
    else
    {
        // in-scene

        osg::NodePath& nodePath = ev.getNodePath();

        if ( !view->getCamera() || nodePath.empty() )
        {
            x = ea.getX();
            y = ea.getY();
            return;
        }

        float local_x, local_y;
        const osg::Camera* camera = view->getCameraContainingPosition( ea.getX(), ea.getY(), local_x, local_y );
        if ( !camera )
        {
            camera = view->getCamera();
        }

        osg::Matrixd matrix;
        matrix.makeIdentity();
        if( nodePath.size() > 1 )
        {
            osg::NodePath prunedNodePath( nodePath.begin(), nodePath.end() - 1 );
            matrix = osg::computeLocalToWorld( prunedNodePath );
        };

        matrix.postMult( camera->getViewMatrix() );
        matrix.postMult( camera->getProjectionMatrix() );

        double zNear = -1.0;
        double zFar  =  1.0;

        if ( camera->getViewport() )
        {
            matrix.postMult( camera->getViewport()->computeWindowMatrix() );
            zNear = 0.0;
            zFar  = 1.0;
        }

        osg::Matrixd inverse;
        inverse.invert( matrix );

        osg::Vec3d startVertex = osg::Vec3d( local_x, local_y, zNear ) * inverse;
        osg::Vec3d endVertex   = osg::Vec3d( local_x, local_y, zFar  ) * inverse;

        osg::Vec3 pick = endVertex - startVertex;
        pick.normalize();

        // project pick ray to z-plane at z=0
        float dist = - startVertex[ 2 ] / pick[ 2 ];
        osg::Vec3 projected( startVertex[ 0 ] + pick[ 0 ] * dist, startVertex[ 1 ] + pick[ 1 ] * dist, 0 );

        x = projected[ 0 ];
        y = projected[ 1 ];
    }
}

////////////////////////////////////////////////////////////////////////////////

void GuiNode::setScreenSize( int w, int h )
{
    if ( m_camera != NULL )
    {
        // tell libRocket about new size
        m_context->SetDimensions( Rocket::Core::Vector2i( w, h ) );

        // resize gui camera projection for new screen size
        m_camera->setProjectionMatrix( osg::Matrix::ortho2D( 0, w, 0, h ) );

        // libRocket gui seems to stand on its head, not sure why. Flip the view matrix.
        // If anyone has a more elegant solution for this then please contact me
        m_camera->setViewMatrix( osg::Matrix::translate( 0, -h, 0 ) * osg::Matrix::scale( 1, -1, 1 ) * osg::Matrix::identity() );
        m_camera->setViewport( 0, 0, w, h );
    }
}

////////////////////////////////////////////////////////////////////////////////

bool GuiNode::handle( const osgGA::GUIEventAdapter &ea,
                      osgGA::EventVisitor &ev,
                      osgGA::GUIActionAdapter &aa )
{
    switch( ea.getEventType() )
    {
    case osgGA::GUIEventAdapter::KEYDOWN:
    {
        Rocket::Core::Input::KeyIdentifier key = GetKeyCode( ea.getKey() );
        int modifiers = GetKeyModifiers( ea.getModKeyMask() );
        m_context->ProcessTextInput( (char)ea.getKey() );
        m_context->ProcessKeyDown( key, modifiers );
        Rocket::Core::Element *hover = m_context->GetHoverElement();
        return ( hover != NULL && hover != m_context->GetRootElement() );
    }

    case osgGA::GUIEventAdapter::KEYUP:
    {
        Rocket::Core::Input::KeyIdentifier key = GetKeyCode( ea.getKey() );
        int modifiers = GetKeyModifiers( ea.getModKeyMask() );
        m_context->ProcessKeyUp( key, modifiers );
        Rocket::Core::Element *hover = m_context->GetHoverElement();
        return ( hover != NULL && hover != m_context->GetRootElement() );
    }

    case osgGA::GUIEventAdapter::MOVE:
    case osgGA::GUIEventAdapter::DRAG:
    {
        int x, y;
        osgViewer::View *view = dynamic_cast< osgViewer::View* >( &aa );
        mousePosition( view, ea, ev, x, y );
        m_context->ProcessMouseMove( x, y, GetKeyModifiers( ea.getModKeyMask() ) );

        Rocket::Core::Element *hover = m_context->GetHoverElement();

        return ( hover != NULL && hover != m_context->GetRootElement() );
    }

    case osgGA::GUIEventAdapter::PUSH:
    {
        if ( ea.getHandled() ) return false;

        m_context->ProcessMouseButtonDown( GetButtonId( ea.getButton() ), GetKeyModifiers( ea.getModKeyMask() ) );
        osgViewer::View *view = dynamic_cast< osgViewer::View* >( &aa );
        int x, y;
        mousePosition( view, ea, ev, x, y );

        Rocket::Core::Element *hover = m_context->GetHoverElement();

        return ( hover != NULL && hover != m_context->GetRootElement() );
    }

    case osgGA::GUIEventAdapter::RELEASE:
    {
        m_context->ProcessMouseButtonUp( GetButtonId( ea.getButton() ), GetKeyModifiers( ea.getModKeyMask() ) );
        return false;
    }

    case osgGA::GUIEventAdapter::SCROLL:
    {
        return m_context->ProcessMouseWheel( (int)ea.getScrollingDeltaY(), GetKeyModifiers( ea.getModKeyMask() ) );
    }

    case osgGA::GUIEventAdapter::RESIZE:
    {
        setScreenSize( ea.getWindowWidth(), ea.getWindowHeight() );
        return true;
    }

    default: break;
    }

    return false;
}
