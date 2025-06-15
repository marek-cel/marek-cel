#include <cstdio>
#include <cstring>

#include <filesystem>
#include <fstream>
#include <string>

#include <UdpSocket.h>

#include <XPLMDataAccess.h>
#include <XPLMUtilities.h>
#include <XPLMProcessing.h>

#include <databuf.h>

XPLMFlightLoopID flight_loop_id = nullptr;
float flight_loop(float since_last, float since_last_fl, int count, void* refcon);

UdpSocket g_socket;
XPLANE_TO_GUI g_xplane_to_gui;
GUI_TO_XPLANE g_gui_to_xplane;

int g_tick = -1;

std::ofstream g_log_file;

XPLMDataRef g_ref_force_x = nullptr;
XPLMDataRef g_ref_force_y = nullptr;
XPLMDataRef g_ref_force_z = nullptr;

PLUGIN_API int XPluginStart(
    char *		outName,
    char *		outSig,
    char *		outDesc)
{
    strcpy(outName, "Extra Forces");
    strcpy(outSig, "xplanesdk.examples.extra_forces");
    strcpy(outDesc, "A test plugin.");

    XPLMDebugString("XXX Extra Forces XXX\n");

    // std::filesystem::path file = std::filesystem::path(getenv("HOME")) / "xplane_to_gui.log";
#   ifdef __linux__
    std::filesystem::path file = "/home/cel/xplane_to_gui.log";
#   elif defined(WIN32)
    std::filesystem::path file = "D:\\xplane_to_gui.log";
#   endif // __linux__
    g_log_file.open(file, std::ios::out | std::ios::trunc);
    if (!g_log_file.is_open())
    {
        std::string msg = "Error: log file open failed: " + file.string() + "\n";
        XPLMDebugString(msg.c_str());
        return 0;
    }
    std::string msg = "Log file opened: " + file.string() + "\n";
    XPLMDebugString(msg.c_str());
    g_log_file << "Plugin started" << std::endl;
    g_log_file.flush();

    if ( !g_socket.bind("", 5500) )
    {
        XPLMDebugString("Error: bind failed\n");
        return 0;
    }

    if ( !g_socket.connect("127.0.0.1", 5501) )
    {
        XPLMDebugString("Error: connect failed\n");
        return 0;
    }

    if ( !g_socket.setNonBlocking(true) )
    {
        XPLMDebugString("Error: setNonBlocking failed\n");
        return 0;
    }

    XPLMDebugString("Connected to GUI\n");

    g_ref_force_x = XPLMFindDataRef("sim/flightmodel/forces/faxil_plug_acf");
    g_ref_force_y = XPLMFindDataRef("sim/flightmodel/forces/fside_plug_acf");
    g_ref_force_z = XPLMFindDataRef("sim/flightmodel/forces/fnrml_plug_acf");
    if (g_ref_force_x == nullptr || g_ref_force_y == nullptr || g_ref_force_z == nullptr)
    {
        XPLMDebugString("Error: DataRefs not found\n");
        return 0;
    }

    g_xplane_to_gui.tick = g_tick;
    g_socket.sendto((char*)(&g_xplane_to_gui), sizeof(g_xplane_to_gui), "127.0.0.1", 5501);

	XPLMCreateFlightLoop_t params;
	params.callbackFunc = flight_loop;
	params.phase = 1;
	params.refcon = nullptr;
	params.structSize = sizeof(params);
	flight_loop_id = XPLMCreateFlightLoop(&params);
    XPLMScheduleFlightLoop(flight_loop_id, .1f, 1);

    return 1;
}

PLUGIN_API void	XPluginStop(void)
{
    XPLMDebugString("XXX Extra Forces XXX: XPluginStop\n");

    // Stop the flight loop
    if (flight_loop_id != nullptr)
    {
        XPLMDebugString("Stopping flight loop\n");
        XPLMDestroyFlightLoop(flight_loop_id);
        flight_loop_id = nullptr;
    }

    if (g_log_file.is_open())
    {
        g_log_file << "Plugin stopped" << std::endl;
        g_log_file.flush();
        g_log_file.close();
    }
}

PLUGIN_API void XPluginDisable(void)
{
    XPLMDebugString("XXX Extra Forces XXX: XPluginDisable\n");
}

PLUGIN_API int XPluginEnable(void)
{
    XPLMDebugString("XXX Extra Forces XXX: XPluginEnable\n");
	return 1;
}

PLUGIN_API void XPluginReceiveMessage(
					XPLMPluginID	inFromWho,
					int				inMessage,
					void *			inParam)
{
    XPLMDebugString("XXX Extra Forces XXX: XPluginReceiveMessage\n");
}

float flight_loop(float since_last, float since_last_fl, int count, void* refcon)
{
    g_tick++;

    // if (g_log_file.is_open())
    // {
    //     g_log_file << "Tick: " << g_tick << std::endl;
    //     g_log_file.flush();
    // }

    g_xplane_to_gui.tick = g_tick;
    g_socket.sendto((char*)(&g_xplane_to_gui), sizeof(g_xplane_to_gui), "127.0.0.1", 5501);

    while ( g_socket.hasPendingDatagrams() )
    {
        int size = g_socket.recv((char*)(&g_gui_to_xplane), sizeof(g_gui_to_xplane));
        if ( size == sizeof(g_gui_to_xplane) )
        {
            if (g_log_file.is_open())
            {
                g_log_file << "Current: " << g_tick << " Received: " << g_gui_to_xplane.tick << std::endl;
                g_log_file.flush();
            }
        }
    }

    if ( g_gui_to_xplane.tick > 0 )
    {
        double force_x = 0.0; //XPLMGetDataf(g_ref_force_x);
        double force_y = 0.0; //XPLMGetDataf(g_ref_force_y);
        double force_z = 0.0; //XPLMGetDataf(g_ref_force_z);
        force_x += g_gui_to_xplane.force_x;
        force_y += g_gui_to_xplane.force_y;
        force_z += g_gui_to_xplane.force_z;
        XPLMSetDataf(g_ref_force_x, static_cast<float>(force_x));
        XPLMSetDataf(g_ref_force_y, static_cast<float>(force_y));
        XPLMSetDataf(g_ref_force_z, static_cast<float>(force_z));
    }

	return -1;
}