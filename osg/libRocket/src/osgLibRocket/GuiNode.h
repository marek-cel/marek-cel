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
#ifndef GUINODE_H
#define GUINODE_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>
#include <osgViewer/View>

#include <Rocket/Core/Core.h>
#include <Rocket/Debugger/Debugger.h>

#include <osgLibRocket/RenderInterface.h>

////////////////////////////////////////////////////////////////////////////////

namespace osgLibRocket
{

/** A node for rendering a libRocket GUI in OpenSceneGraph. */
class GuiNode : public osg::Group
{
    typedef osg::Group BaseClass;

public:

    /**
     * @param contextname Unique string identifying the gui node context
     * @param renderer Access to renderer interface singleton
     * @param debug Set to true to add libRocket debug gui
     */
    GuiNode( const std::string &contextname, bool debug = false );

    ~GuiNode();

    /** get libRocket context of this gui */
    Rocket::Core::Context* getContext() { return m_context; }

    /** traversal handler for injecting time into libRocket */
    virtual void traverse( osg::NodeVisitor& nv );

    /** handle osg events. */
    virtual bool handle( const osgGA::GUIEventAdapter &ea,
                         osgGA::EventVisitor &ev,
                         osgGA::GUIActionAdapter &aa );

    /** transform osg key to libRocket key */
    Rocket::Core::Input::KeyIdentifier GetKeyCode( int osgkey );

    /** transform key modifiers from osg to libRocket */
    int GetKeyModifiers( int osgModKeyMask );

    /** transform from osg button to libRocket button */
    int GetButtonId( int button );

    /** Set this if libRocket gui should render to a fullscreen camera. */
    void setCamera( osg::Camera *cam );

private:

    /** update view matrix and resize libRocket screen dimensions */
    void setScreenSize( int w, int h );

    /** Transform osg mouse position into libRocket screen coordinates */
    void mousePosition( osgViewer::View* view,
                        const osgGA::GUIEventAdapter &ea,
                        osgGA::EventVisitor &ev,
                        int &x, int &y );


    unsigned int m_previousTraversalNumber; ///< number of last frame so we don't update multiple times per frame
    RenderInterface* m_renderer;            ///< osgLibRocket render interface singleton
    Rocket::Core::Context* m_context;       ///< context of this gui (one per gui)
    osg::ref_ptr<osg::Camera> m_camera;     ///< camera to render to (can be NULL)
};

} // end of osgLibRocket namespace

////////////////////////////////////////////////////////////////////////////////

#endif // GUINODE_H
