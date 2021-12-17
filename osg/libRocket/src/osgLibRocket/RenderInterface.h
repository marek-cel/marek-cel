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
#ifndef RENDERINTERFACE_H
#define RENDERINTERFACE_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>
#include <osg/Scissor>
#include <osg/Texture2D>
#include <osg/Geometry>

#include <Rocket/Core/Core.h>
#include <Rocket/Debugger/Debugger.h>

////////////////////////////////////////////////////////////////////////////////

namespace osgLibRocket
{

/** */
class RenderInterface : public Rocket::Core::RenderInterface
{
public:

    RenderInterface();

    void setRenderTarget( osg::Group *grp );

    osg::Group* getRenderTarget() const;

    /**
     * Called by Rocket when it wants to render geometry that the application does not wish to optimise. Note that
     * Rocket renders everything as triangles.
     * @param[in] vertices The geometry's vertex data.
     * @param[in] num_vertices The number of vertices passed to the function.
     * @param[in] indices The geometry's index data.
     * @param[in] num_indices The number of indices passed to the function. This will always be a multiple of three.
     * @param[in] texture The texture to be applied to the geometry. This may be NULL, in which case the geometry is untextured.
     * @param[in] translation The translation to apply to the geometry.
     */
    virtual void RenderGeometry( Rocket::Core::Vertex *vertices,
                                 int num_vertices,
                                 int *indices,
                                 int num_indices,
                                 Rocket::Core::TextureHandle texture,
                                 const Rocket::Core::Vector2f &translation );

    /**
     * Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
     * If supported, this should be return a pointer to an optimised, application-specific version of the data. If
     * not, do not override the function or return NULL; the simpler RenderGeometry() will be called instead.
     * @param[in] vertices The geometry's vertex data.
     * @param[in] num_vertices The number of vertices passed to the function.
     * @param[in] indices The geometry's index data.
     * @param[in] num_indices The number of indices passed to the function. This will always be a multiple of three.
     * @param[in] texture The texture to be applied to the geometry. This may be NULL, in which case the geometry is untextured.
     * @return The application-specific compiled geometry. Compiled geometry will be stored and rendered using RenderCompiledGeometry() in future calls, and released with ReleaseCompiledGeometry() when it is no longer needed.
     */
    virtual Rocket::Core::CompiledGeometryHandle CompileGeometry( Rocket::Core::Vertex *vertices,
                                                                  int num_vertices,
                                                                  int *indices,
                                                                  int num_indices,
                                                                  Rocket::Core::TextureHandle texture );

    /**
     * Called by Rocket when it wants to render application-compiled geometry.
     * @param[in] geometry The application-specific compiled geometry to render.
     * @param[in] translation The translation to apply to the geometry.
     */
    virtual void RenderCompiledGeometry( Rocket::Core::CompiledGeometryHandle geometry,
                                         const Rocket::Core::Vector2f &translation );

    /**
     * Called by Rocket when it wants to release application-compiled geometry.
     * @param[in] geometry The application-specific compiled geometry to release.
     */
    virtual void ReleaseCompiledGeometry( Rocket::Core::CompiledGeometryHandle geometry );

    /**
     * Called by Rocket when it wants to enable or disable scissoring to clip content.
     * @param[in] enable True if scissoring is to enabled, false if it is to be disabled.
     */
    virtual void EnableScissorRegion( bool enable );

    /**
     * Called by Rocket when it wants to change the scissor region.
     * @param[in] x The left-most pixel to be rendered. All pixels to the left of this should be clipped.
     * @param[in] y The top-most pixel to be rendered. All pixels to the top of this should be clipped.
     * @param[in] width The width of the scissored region. All pixels to the right of (x + width) should be clipped.
     * @param[in] height The height of the scissored region. All pixels to below (y + height) should be clipped.
     */
    virtual void SetScissorRegion( int x, int y, int width, int height );

    void AddTexture(Rocket::Core::TextureHandle& texture_handle, osg::Image* image);

    /**
     * Called by Rocket when a texture is required by the library.
     * @param[out] texture_handle The handle to write the texture handle for the loaded texture to.
     * @param[out] texture_dimensions The variable to write the dimensions of the loaded texture.
     * @param[in] source The application-defined image source, joined with the path of the referencing document.
     * @return True if the load attempt succeeded and the handle and dimensions are valid, false if not.
     */
    virtual bool LoadTexture( Rocket::Core::TextureHandle &texture_handle,
                              Rocket::Core::Vector2i &texture_dimensions,
                              const Rocket::Core::String &source );

    /**
     * Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
     * @param[out] texture_handle The handle to write the texture handle for the generated texture to.
     * @param[in] source The raw 8-bit texture data. Each pixel is made up of four 8-bit values, indicating red, green, blue and alpha in that order.
     * @param[in] source_dimensions The dimensions, in pixels, of the source data.
     * @return True if the texture generation succeeded and the handle is valid, false if not.
     */
    virtual bool GenerateTexture( Rocket::Core::TextureHandle &texture_handle,
                                  const Rocket::Core::byte *source,
                                  const Rocket::Core::Vector2i &source_dimensions );


    /**
     * Called by Rocket when a loaded texture is no longer required.
     * @param texture The texture handle to release.
     */
    virtual void ReleaseTexture( Rocket::Core::TextureHandle texture );

    /** Called when this render interface is released. */
    virtual void Release();

private:

    osg::ref_ptr< osg::Group >    _renderTarget;
    osg::ref_ptr< osg::StateSet > _renderTargetStateSet;
    osg::ref_ptr< osg::Scissor >  _scissorTest;

    unsigned int _nextTextureId;
    unsigned int _nextGeometryId;

    typedef std::map< Rocket::Core::CompiledGeometryHandle, osg::ref_ptr< osg::Node > > CompiledGeometryMap;
    CompiledGeometryMap _compiledGeometryMap;

    typedef std::list< osg::ref_ptr< osg::Node > > InstantGeometryMap;
    InstantGeometryMap _instantGeometryMap;

    typedef std::map< Rocket::Core::TextureHandle, osg::ref_ptr< osg::Texture2D > > TextureMap;
    TextureMap _textureMap;

    osg::Node* createGeometry( Rocket::Core::Vertex *vertices,
                               int num_vertices,
                               int *indices,
                               int num_indices,
                               Rocket::Core::TextureHandle texture,
                               bool useDisplayList );
};

} // end of osgLibRocket namespace

////////////////////////////////////////////////////////////////////////////////

#endif // RENDERINTERFACE_H
