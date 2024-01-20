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
#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H

////////////////////////////////////////////////////////////////////////////////

#include <osgDB/FileUtils>

#include <Rocket/Core/Core.h>
#include <Rocket/Debugger/Debugger.h>

////////////////////////////////////////////////////////////////////////////////

namespace osgLibRocket
{

/** */
class FileInterface : public Rocket::Core::FileInterface
{
    virtual Rocket::Core::FileHandle Open( const Rocket::Core::String &path );

    /**
     * Closes a previously opened file.
     * @param file The file handle previously opened through Open().
     */
    virtual void Close( Rocket::Core::FileHandle file );

    /**
     * Reads data from a previously opened file.
     * @param buffer The buffer to be read into.
     * @param size The number of bytes to read into the buffer.
     * @param file The handle of the file.
     * @return The total number of bytes read into the buffer.
     */
    virtual size_t Read( void *buffer, size_t size, Rocket::Core::FileHandle file );

    /**
     * Seeks to a point in a previously opened file.
     * @param file The handle of the file to seek.
     * @param offset The number of bytes to seek.
     * @param origin One of either SEEK_SET (seek from the beginning of the file), SEEK_END (seek from the end of the file) or SEEK_CUR (seek from the current file position).
     * @return True if the operation completed successfully, false otherwise.
     */
    virtual bool Seek( Rocket::Core::FileHandle file, long offset, int origin );

    /**
     * Returns the current position of the file pointer.
     * @param file The handle of the file to be queried.
     * @return The number of bytes from the origin of the file.
     */
    virtual size_t Tell( Rocket::Core::FileHandle file );
};

} // end of osgLibRocket namespace

////////////////////////////////////////////////////////////////////////////////

#endif // FILEINTERFACE_H
