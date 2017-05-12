#include "lua_interface.h"
#include <stdio.h>

//注册到lua的 c 函数
int lua_test(lua_State* L)
{
    int a = lua_tointeger(L, 1);
    double b = lua_tointeger(L, 2);
    int res = a * b ;
    lua_pushinteger(L, res);
    return 1;
}
void my_regist_callback(lua_State* L)
{
    lua_register(L, "lua_test", lua_test);
}

int main(int argc, char *argv[])
{
    bool res;
    int a=0;

    res = lw_open_file("test.lua",my_regist_callback);
    printf("lw_open_file return %d\n",res);
    //test

    lw_call_lua_func("test_add","ii>i",5,6,&a);
    printf("lua test_add return %d\n",a);

    lw_call_lua_func("test_c_lua_multi","ii>i",6,6,&a);
    printf("lua test_c_lua_multi return %d\n",a);

    while(1)
    {
        a =1;
    }
    return 1;
}
