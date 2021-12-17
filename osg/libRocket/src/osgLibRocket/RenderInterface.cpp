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

#include <assert.h>

#include <osg/BlendFunc>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osgDB/FileUtils>
#include <osgDB/ReadFile>

#include <osgLibRocket/RenderInterface.h>

////////////////////////////////////////////////////////////////////////////////

using namespace osgLibRocket;

////////////////////////////////////////////////////////////////////////////////

RenderInterface::RenderInterface() :
    _nextTextureId  ( 1 ),
    _nextGeometryId ( 1 )
{
    setRenderTarget( new osg::Group() );
}

////////////////////////////////////////////////////////////////////////////////

void RenderInterface::setRenderTarget( osg::Group *grp )
{
    if ( _renderTarget != grp )
    {
        _renderTarget = grp;
        _renderTargetStateSet = grp->getOrCreateStateSet();
        _scissorTest = dynamic_cast< osg::Scissor* >( _renderTargetStateSet->getAttribute( osg::StateAttribute::SCISSOR ) );

        if ( !_scissorTest )
        {
            _scissorTest = new osg::Scissor( 0, 0, 0, 0 );

            _renderTargetStateSet->setAttributeAndModes( _scissorTest, osg::StateAttribute::OFF );

            _renderTargetStateSet->setMode( GL_LIGHTING   , osg::StateAttribute::OFF );
            _renderTargetStateSet->setMode( GL_BLEND      , osg::StateAttribute::ON  );
            _renderTargetStateSet->setMode( GL_DEPTH_TEST , osg::StateAttribute::OFF );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

osg::Group* RenderInterface::getRenderTarget() const
{
    return _renderTarget;
}

////////////////////////////////////////////////////////////////////////////////

osg::Node* RenderInterface::createGeometry( Rocket::Core::Vertex *vertices,
                                            int num_vertices,
                                            int *indices,
                                            int num_indices,
                                            Rocket::Core::TextureHandle texture,
                                            bool useDisplayList )
{

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
    geometry->setUseDisplayList( useDisplayList );
    geometry->setDataVariance( osg::Object::DYNAMIC );

    osg::ref_ptr<osg::Vec3Array> vertarray  = new osg::Vec3Array( num_vertices );
    osg::ref_ptr<osg::Vec4Array> colorarray = new osg::Vec4Array( num_vertices );
    osg::ref_ptr<osg::Vec2Array> texcoords  = new osg::Vec2Array( num_vertices );

    for( int i = 0; i < num_vertices; ++i )
    {
        Rocket::Core::Vertex *vert = &vertices[ i ];
        Rocket::Core::Colourb c = vert->colour;
        (*vertarray)  [ i ].set( vert->position.x, vert->position.y, 0 );
        (*colorarray) [ i ].set( c.red / 255.0f, c.green / 255.0f, c.blue / 255.0f, c.alpha / 255.0f );
        (*texcoords)  [ i ].set( vert->tex_coord.x, vert->tex_coord.y );
    }

    osg::ref_ptr<osg::DrawElementsUInt> elements = new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES, num_indices );

    for ( int i = 0; i < num_indices; ++i )
    {
        elements->setElement( i, indices[ i ] );
    }

    geometry->setVertexArray( vertarray );
    geometry->setColorArray( colorarray );
    geometry->setColorBinding( osg::Geometry::BIND_PER_VERTEX );

    geometry->addPrimitiveSet( elements );

    if ( texture != 0 )
    {
        geometry->setTexCoordArray( 0, texcoords );
        TextureMap::iterator i = _textureMap.find( texture );
        assert( i != _textureMap.end() );
        osg::StateSet* ss = geometry->getOrCreateStateSet();
        ss->setTextureAttributeAndModes( 0, i->second, osg::StateAttribute::ON );
    }


    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    geode->setDataVariance( osg::Object::DYNAMIC );
    geode->addDrawable( geometry );

    return geode.release();
}

////////////////////////////////////////////////////////////////////////////////

void RenderInterface::RenderGeometry( Rocket::Core::Vertex *vertices,
                                      int num_vertices,
                                      int *indices,
                                      int num_indices,
                                      Rocket::Core::TextureHandle texture,
                                      const Rocket::Core::Vector2f &translation )
{

    osg::ref_ptr<osg::Node> node = createGeometry( vertices, num_vertices, indices, num_indices, texture, false );

    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform();

    trans->setMatrix( osg::Matrix::translate( osg::Vec3( translation.x, translation.y, 0 ) ) );
    trans->addChild( node );
    trans->setDataVariance( osg::Object::DYNAMIC );

    _renderTarget->addChild( trans );
    _renderTarget->dirtyBound();

    _instantGeometryMap.push_back( trans );
}

////////////////////////////////////////////////////////////////////////////////

Rocket::Core::CompiledGeometryHandle RenderInterface::CompileGeometry( Rocket::Core::Vertex *vertices,
                                                                       int num_vertices,
                                                                       int *indices,
                                                                       int num_indices,
                                                                       Rocket::Core::TextureHandle texture )
{
    osg::Node *node = createGeometry( vertices, num_vertices, indices, num_indices, texture, true );

    _compiledGeometryMap[ _nextGeometryId ] = node;
    //_compiledGeometryMap.insert( std::pair< Rocket::Core::CompiledGeometryHandle, osg::ref_ptr< osg::Node > >( _nextGeometryId, node ) );

    return _nextGeometryId++;
}

////////////////////////////////////////////////////////////////////////////////

void RenderInterface::RenderCompiledGeometry( Rocket::Core::CompiledGeometryHandle geometry,
                                              const Rocket::Core::Vector2f &translation )
{
    CompiledGeometryMap::iterator i = _compiledGeometryMap.find( geometry );

    if ( i != _compiledGeometryMap.end() )
    {
        osg::ref_ptr< osg::MatrixTransform > trans = new osg::MatrixTransform();
        //osg::MatrixTransform *trans = new osg::MatrixTransform();

        trans->setMatrix( osg::Matrix::translate( osg::Vec3( translation.x, translation.y, 0 ) ) );

        if ( trans.valid() )
        {
            if ( i->second.valid() )
            {
                trans->addChild( i->second );
            }
            else
            {
                osg::notify(osg::ALWAYS) << "Error in " << __FILE__ << "(" << __LINE__ << ")" << std::endl;
            }
        }
        else
        {
            osg::notify(osg::ALWAYS) << "Error in " << __FILE__ << "(" << __LINE__ << ")" << std::endl;
        }

        _renderTarget->addChild( trans );
        _renderTarget->dirtyBound();
    }
}

////////////////////////////////////////////////////////////////////////////////

void RenderInterface::ReleaseCompiledGeometry( Rocket::Core::CompiledGeometryHandle geometry )
{
    CompiledGeometryMap::iterator i = _compiledGeometryMap.find( geometry );

    if ( i != _compiledGeometryMap.end() )
    {
        _compiledGeometryMap.erase( i );
    }
}

////////////////////////////////////////////////////////////////////////////////

void RenderInterface::EnableScissorRegion( bool enable )
{
    _renderTargetStateSet->setAttributeAndModes( _scissorTest, enable ? osg::StateAttribute::ON : osg::StateAttribute::OFF );
}

////////////////////////////////////////////////////////////////////////////////

void RenderInterface::SetScissorRegion( int x, int y, int width, int height )
{
    _scissorTest->setScissor( x, y, width, height );
}

////////////////////////////////////////////////////////////////////////////////

void RenderInterface::AddTexture( Rocket::Core::TextureHandle &texture_handle,
                                  osg::Image *image )
{
    texture_handle = _nextTextureId++;

    osg::ref_ptr< osg::Texture2D > texture = new osg::Texture2D();

    texture->setImage( image );

    texture->setWrap( osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE );
    texture->setWrap( osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE );

    texture->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR );
    texture->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );

    _textureMap[ texture_handle ] = texture;
}

////////////////////////////////////////////////////////////////////////////////

bool RenderInterface::LoadTexture( Rocket::Core::TextureHandle &texture_handle,
                                   Rocket::Core::Vector2i &texture_dimensions,
                                   const Rocket::Core::String &source )
{

    std::string src = source.CString();

    std::string path = osgDB::findDataFile( src );
    if ( path.empty() )
    {
        return false;
    }

    osg::ref_ptr<osg::Image> img = osgDB::readImageFile( path );
    if( !img.valid() )
    {
        return false;
    }

    img->flipVertical();

    if ( img == NULL ) return false;

    texture_dimensions.x = img->s();
    texture_dimensions.y = img->t();

    AddTexture( texture_handle, img );

    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool RenderInterface::GenerateTexture( Rocket::Core::TextureHandle &texture_handle,
                                       const Rocket::Core::byte *source,
                                       const Rocket::Core::Vector2i &source_dimensions )
{
    osg::ref_ptr<osg::Image> img = new osg::Image();

    int w = source_dimensions.x;
    int h = source_dimensions.y;

    img->allocateImage( w, h, 1, GL_RGBA, GL_UNSIGNED_BYTE );

    memcpy( img->data(), source, w * h * 4 * sizeof( Rocket::Core::byte ) );

    AddTexture( texture_handle, img );

    return true;
}

////////////////////////////////////////////////////////////////////////////////

void RenderInterface::ReleaseTexture( Rocket::Core::TextureHandle texture )
{
    TextureMap::iterator i = _textureMap.find( texture );

    if ( i != _textureMap.end() )
    {
        _textureMap.erase( i );
    }
}

////////////////////////////////////////////////////////////////////////////////

void RenderInterface::Release() {}
