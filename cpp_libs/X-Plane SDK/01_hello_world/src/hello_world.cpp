#include <stdio.h>
#include <string.h>

#include <XPLMDataAccess.h>

PLUGIN_API int XPluginStart(
    char *		outName,
    char *		outSig,
    char *		outDesc)
{
    strcpy(outName, "HelloWorld");
    strcpy(outSig, "xplanesdk.examples.hello_world");
    strcpy(outDesc, "A test plugin.");

    return 1;
}

PLUGIN_API void	XPluginStop(void)
{
}

PLUGIN_API void XPluginDisable(void)
{
}

PLUGIN_API int XPluginEnable(void)
{
	return 1;
}

PLUGIN_API void XPluginReceiveMessage(
					XPLMPluginID	inFromWho,
					int				inMessage,
					void *			inParam)
{
}