#include "lua_interface.h"
#include <stdio.h>

//lua call c 单返回
int lua_test(lua_State* L)
{
    int a = lua_tointeger(L, 1);
    double b = lua_tointeger(L, 2);
    int res = a * b ;
    lua_pushinteger(L, res);
    return 1;
}
//lua call c 多返回
int lua_test2(lua_State* L)
{
    int a = lua_tointeger(L, 1);
    double b = lua_tointeger(L, 2);
    int res = a * b ;
    lua_pushinteger(L, res);
    lua_pushstring(L,"world1");
    lua_pushinteger(L,88);
    lua_pushstring(L,"world2");

    return 4;
}
//lua call c 测试返回lua table
int lua_res_table(lua_State* L)
{
    lua_newtable(L);
     int table_index = lua_gettop(L);

     lua_pushboolean(L, true);
     lua_setfield(L, table_index, "result");
     lua_pushstring(L, "hello");
     lua_setfield(L, table_index, "data");

     return 1;
}
void my_regist_callback(lua_State* L)
{
    lua_register(L, "lua_test", lua_test);
    lua_register(L, "lua_test2", lua_test2);
    lua_register(L, "lua_res_table", lua_res_table);
}

int main(int argc, char *argv[])
{
    bool res;
    int a=0;

    res = lw_open_file("test.lua",my_regist_callback);
//    printf("lw_open_file return %d\n",res);
//    //test

//    lw_call_lua_func("test_add","ii>i",5,6,&a);
//    printf("lua test_add return %d\n",a);

//    lw_call_lua_func("test_c_lua_multi","ii>i",6,6,&a);
//    printf("lua test_c_lua_multi return %d\n",a);

    while(1)
    {
        a =1;
    }
    return 1;
}
