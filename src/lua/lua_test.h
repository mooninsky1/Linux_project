#include <iostream>
using namespace std;


extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
};


class CLuaTest
{
public:
	static void Test();
	//初始化LUA
	static void LuaInit();
	static void CloseLua();
	//open lua source
	static void OpenLuaFile();
	//c push value to lua
	static void C_Push_value();
	//c push function
	static void C_Push_Fun();
	//c call lua's fun
	static void C_Call_Lua();
private:
	//求两数和，lua调用
	static int AddSum(lua_State* L);
private:
	static lua_State* L;
};
