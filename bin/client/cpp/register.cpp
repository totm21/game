#include"register.h"

/*���庯����*/   //��׼��ʽ

/*��Ҫ���õĺ�����ʽ*/ //��׼��ʽ
int C_Func_Child(lua_State* L)
{
	printf("it's standard\n");
	return 0;
}

/*����һ���¿�*/  //��׼��ʽ
int luaopen_C_Func_Name(lua_State* L) {
	
	/*����һ����׼��*/ 
	luaL_Reg C_Fun_Table[] = {
		{"C_Func_Child",C_Func_Child},
		{NULL,NULL}
	};

	luaL_newlib(L, C_Fun_Table);
	return 1;
}