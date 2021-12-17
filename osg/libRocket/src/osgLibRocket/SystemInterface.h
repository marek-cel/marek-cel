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
#ifndef SYSTEMINTERFACE_H
#define SYSTEMINTERFACE_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Notify>

#include <Rocket/Core/Core.h>

////////////////////////////////////////////////////////////////////////////////

namespace osgLibRocket
{

/** */
class SystemInterface : public Rocket::Core::SystemInterface
{
public:

    virtual float GetElapsedTime()
    {
        return 0;
    }

    /**
     * Translate the input string into the translated string.
     * @param[out] translated Translated string ready for display.
     * @param[in] input String as received from XML.
     * @return Number of translations that occured.
     */
    virtual int TranslateString( Rocket::Core::String &translated,
                                 const Rocket::Core::String &input )
    {
        translated = input;
        return 0;
    }

    /**
     * Joins the path of an RML or RCSS file with the path of a resource specified within the file.
     * @param[out] translated_path The joined path.
     * @param[in] document_path The path of the source document (including the file name).
     * @param[in] path The path of the resource specified in the document.
     */
    virtual void JoinPath( Rocket::Core::String &translated_path,
                           const Rocket::Core::String &document_path,
                           const Rocket::Core::String &path )
    {}

    /**
     * Log the specified message.
     * @param[in] type Type of log message, ERROR, WARNING, etc.
     * @param[in] message Message to log.
     * @return True to continue execution, false to break into the debugger.
     */
    virtual bool LogMessage( Rocket::Core::Log::Type type,
                             const Rocket::Core::String &message )
    {
        std::string str = message.CString();

        switch(type)
        {
            case Rocket::Core::Log::LT_ALWAYS  : OSG_ALWAYS << str << "\n"; break;
            case Rocket::Core::Log::LT_ERROR   : OSG_FATAL  << str << "\n"; break;
            case Rocket::Core::Log::LT_ASSERT  : OSG_FATAL  << str << "\n"; break;
            case Rocket::Core::Log::LT_WARNING : OSG_WARN   << str << "\n"; break;
            case Rocket::Core::Log::LT_INFO    : OSG_INFO   << str << "\n"; break;
            case Rocket::Core::Log::LT_DEBUG   : OSG_DEBUG  << str << "\n"; break;
            case Rocket::Core::Log::LT_MAX     : OSG_ALWAYS << str << "\n"; break;
        }

        return true;
    }

    /** Called when this system interface is no longer required. */
    virtual void Release() {}

};

} // end of osgLibRocket namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SYSTEMINTERFACE_H
