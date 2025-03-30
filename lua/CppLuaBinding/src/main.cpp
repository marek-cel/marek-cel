#include <iostream>

#include <lua.hpp>

int main()
{
    std::cout << "Hello, Lua!" << std::endl;

    lua_State* L = luaL_newstate(); // Create a new Lua state
    luaL_openlibs(L);               // Load Lua standard libraries

    // Load and run a Lua script
    if (luaL_dofile(L, "../scripts/hello.lua") != LUA_OK)
    {
        std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // Remove error message
    }

    lua_close(L); // Close Lua state

    return 0;
}
