#include<lua.hpp>
#include<iostream>
#include<windows.h>
#include"register.h"

int main()
{

    
    lua_State *lua = luaL_newstate(); 
    if(lua == nullptr)
    {
        return 0;
    }
    luaL_requiref(lua, "CFuncName", luaopen_C_Func_Name, 1);/*��C���Ժ�����ע�ᵽLua������*/
    
    luaL_openlibs(lua);
    luaL_dofile(lua, "../bin/client/lua/debugPrint.lua");
	lua_close(lua);
    
    SetConsoleTitle("My Life");
    system("pause");

    return 0;
}