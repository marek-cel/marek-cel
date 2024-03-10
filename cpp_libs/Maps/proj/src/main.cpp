#include <iostream>
#include <proj.h>

////////////////////////////////////////////////////////////////////////////////

void PressEnterToContinue();

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    std::cout << "Hello PROJ4" << std::endl;

    PressEnterToContinue();

    // Initialize Proj library
    PJ_CONTEXT *ctx = proj_context_create();
    
    // Create a PJ object representing a WGS84 coordinate system
    PJ *wgs84 = proj_create(ctx, "+proj=longlat +datum=WGS84");
    
    // Define a coordinate point in WGS84 (longitude, latitude)
    double lon = -73.935242;
    double lat = 40.730610;
    
    // Transform the WGS84 coordinates to another coordinate system
    PJ *targetCoordSystem = proj_create(ctx, "+proj=utm +zone=33 +datum=WGS84");
    PJ_COORD inputCoord = proj_coord(lon, lat, 0, 0);
    PJ_COORD outputCoord = proj_trans(wgs84, targetCoordSystem, 1, &inputCoord);
    
    // Print the transformed coordinates
    std::cout << "Transformed coordinates: "
              << outputCoord.xy.x << ", " << outputCoord.xy.y << std::endl;
    
    // Clean up and free resources
    proj_destroy(wgs84);
    proj_destroy(targetCoordSystem);
    proj_context_destroy(ctx);

    PressEnterToContinue();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void PressEnterToContinue()
{
    std::cout << "Press enter to continue..." << std::endl; 
    std::cin.ignore();
}
