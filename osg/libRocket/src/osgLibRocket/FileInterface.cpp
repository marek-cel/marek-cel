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

#include <osgLibRocket/FileInterface.h>

////////////////////////////////////////////////////////////////////////////////

using namespace osgLibRocket;

////////////////////////////////////////////////////////////////////////////////

Rocket::Core::FileHandle FileInterface::Open( const Rocket::Core::String &path )
{
    std::string abspath = osgDB::findDataFile( path.CString() );

    if ( !osgDB::fileExists( abspath ) )
    {
        return 0;
    }

    FILE* fp = fopen( abspath.c_str(), "rb" );
    return ( Rocket::Core::FileHandle )fp;
}

////////////////////////////////////////////////////////////////////////////////

void FileInterface::Close( Rocket::Core::FileHandle file )
{
    fclose( ( FILE* )file );
}

////////////////////////////////////////////////////////////////////////////////

size_t FileInterface::Read( void *buffer, size_t size, Rocket::Core::FileHandle file )
{
    return fread( buffer, 1, size, (FILE*)file );
}

////////////////////////////////////////////////////////////////////////////////

bool FileInterface::Seek( Rocket::Core::FileHandle file, long offset, int origin )
{
    return fseek( (FILE*)file, offset, origin ) == 0;
}

////////////////////////////////////////////////////////////////////////////////

size_t FileInterface::Tell( Rocket::Core::FileHandle file )
{
    return ftell( (FILE*)file );
}
