#ifndef TILED_EXTENSIONS_LUA_HPP
#define TILED_EXTENSIONS_LUA_HPP
#include "tiled/tiled.hpp"

extern "C"
{
    #include "lua/lua.h"
    #include "lua/lualib.h"
    #include "lua/lauxlib.h"
}

namespace tiled
{
namespace lua
{
void load(Map& map, lua_State* L);
} /* lua */
} /* tiled */

#endif /* ifndef TILED_EXTENSIONS_LUA_HPP */
