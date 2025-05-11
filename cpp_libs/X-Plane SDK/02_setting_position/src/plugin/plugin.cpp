#include <stdio.h>
#include <string.h>

#include <XPLMDataAccess.h>

#include <XplaneToGUI.h>

XplaneToGUI g_xplane_to_gui;

int g_tick = 0;

PLUGIN_API int XPluginStart(
    char *		outName,
    char *		outSig,
    char *		outDesc)
{
    strcpy(outName, "Setting Position");
    strcpy(outSig, "xplanesdk.examples.setting_position");
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