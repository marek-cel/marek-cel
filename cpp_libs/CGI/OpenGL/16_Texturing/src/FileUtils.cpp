#include <FileUtils.h>

#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

bool DoesFileExists(const char* filepath)
{
    std::ifstream f(filepath);
    return f.good();
}