#ifndef DATABUF_H
#define DATABUF_H

#pragma pack(push)
#pragma pack(8)

struct XPLANE_TO_GUI
{
    int tick = 0;
};

struct GUI_TO_XPLANE
{
    int tick = 0;
    double lat = 0.0;
    double lon = 0.0;
    double alt = 0.0;
};

#pragma pack(pop)

#endif // DATABUF_H
