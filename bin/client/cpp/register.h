#ifndef REGISTER_ME
#define REGISTER_ME
/*
    C����ע���lua
    @auther:    ����
    @date:      2022.7.3
    @alter:     2022.7.3
*/

#include <lua.hpp>

/*��Ҫ���õĺ�����ʽ*/ //��׼��ʽ    ��������Ǳ���???
extern int C_Func_Child(lua_State* L);

/*����һ���¿�*/  //��׼��ʽ
extern int luaopen_C_Func_Name(lua_State* L);





#endif