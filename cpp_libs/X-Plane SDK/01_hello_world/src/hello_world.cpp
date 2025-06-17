#include <stdio.h>
#include <string.h>

#include <XPLMUtilities.h>

#define SUCCESS 1
#define FAILURE 0

/**
 * This is called when the plugin is first loaded. You can use it to allocate
 * any permanent resources and register any other callbacks you need.
 * This is a good time to set up the user interface. This callback also returns
 * the plugin’s name, signature, and a description to the XPLM.
 */
PLUGIN_API int XPluginStart(
    char *		outName,
    char *		outSig,
    char *		outDesc)
{
    XPLMDebugString("XXX Hello World XXX XPluginStart\n");

    strcpy(outName, "HelloWorld");
    strcpy(outSig, "xplanesdk.examples.hello_world");
    strcpy(outDesc, "A test plugin.");

    return SUCCESS; // returns true to indicate success, if it returns false, the plugin would be unloaded immediately
}

/**
 * This is called right before the plugin is unloaded. You should unregister all
 * of the callbacks, release all resources, close all files, and generally clean up.
 */
PLUGIN_API void	XPluginStop(void)
{
    XPLMDebugString("XXX Hello World XXX XPluginStop\n");
}

/**
 * This is called when the plugin is enabled. You do not need to do anything in
 * this callback, but if you want, we can allocate resources that we only need
 * while enabled.
 */
PLUGIN_API int XPluginEnable(void)
{
    XPLMDebugString("XXX Hello World XXX XPluginEnable\n");

	return SUCCESS;
}

/**
 * This is called when the plugin is disabled. You do not need to do anything
 * in this callback, but if we want, you can deallocate resources that are only
 * needed while enabled. Once disabled, the plugin may not run again for a very
 * long time, so you should close any network connections that might time out
 * otherwise.
 */
PLUGIN_API void XPluginDisable(void)
{
    XPLMDebugString("XXX Hello World XXX XPluginDisable\n");
}

/**
 * This is called when a plugin or X-Plane sends the plugin a message.
 * See the article on “Interplugin communication and messaging” for more information.
 * The XPLM notifies you when events happen in the simulator (such as the user
 * crashing the plane or selecting a new aircraft model) by calling this function.
 */
PLUGIN_API void XPluginReceiveMessage(
					XPLMPluginID	inFromWho,
					int				inMessage,
					void *			inParam)
{
    XPLMDebugString("XXX Hello World XXX XPluginReceiveMessage\n");
}