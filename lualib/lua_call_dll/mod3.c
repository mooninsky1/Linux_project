#include <stdio.h>
#include <string.h>
//#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include <lua.hpp>

extern "C" int add(lua_State* L)
{
	double op1 = luaL_checknumber(L,1);
     double op2 = luaL_checknumber(L,2);
     lua_pushnumber(L,op1 + op2);
     return 1;
}

extern "C" int sub(lua_State* L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1 - op2);
    return 1;
}

static luaL_Reg mylibs[] = 
{
	{"add", add},
	{"sub", sub},
	{NULL, NULL}
};


int luaopen_mytestlib(lua_State* L)
{
	const char* libName = "mytestlib";
	luaL_register(L, libName, mylibs);
	//luaL_openlib(L, libName, mylibs, 0);

	return 1;
}


