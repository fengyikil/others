#include "test.h"
#include "memory"
extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <lualib.h>
#include <math.h>
}

#define lua_print(...) do{\
    printf(__VA_ARGS__);\
    fflush(stdout);\
    }while(0)

int add(lua_State* L);
int sub(lua_State* L);
int table(lua_State* L);
int table_look(lua_State* L);
int metatable(lua_State* L);

static const luaL_Reg testlib[] = {
    {"add",add},
    {"sub",sub},
    {"table",table},
    {"table_look",table_look},
    {"metatable",metatable},
    {NULL,NULL}
};


//打印栈信息的函数
void printLuaStack(lua_State* lua) {

    lua_print("========= content of stack from top to bottom: ===========\n");

    int stackSize = lua_gettop(lua);                    // 获得栈中元素个数
    for (int i=stackSize; i>0; --i) {
        lua_print("%d [%d]\t", i, -1 - (stackSize - i));
        int t = lua_type(lua, i);                       // 判断当前元素类型
        switch (t) {
        case LUA_TNUMBER:
            lua_print("%s: \t%.2f\n", lua_typename(lua, t), lua_tonumber(lua, i));     // 打印类型名称和值
            break;
        case LUA_TBOOLEAN:
            lua_print("%s: \t%d\n", lua_typename(lua, t), lua_toboolean(lua, i));
            break;
        case LUA_TSTRING:
            lua_print("%s: \t%s\n", lua_typename(lua, t), lua_tostring(lua, i));
            break;
        default:
            // LUA_TTABLE
            // LUA_TTHREAD
            // LUA_TFUNCTION
            // LUA_TLIGHTUSERDATA
            // LUA_TUSERDATA
            // LUA_TNIL
            lua_print("%s\n", lua_typename(lua, t));                                   // 不好打印的类型，暂时仅打印类型名称
            break;
        }
    }
    lua_print("stackSize is %d\n",stackSize);
}
//遍历table的函数
void traverse_table(lua_State *L, int index)
{
    lua_pushnil(L);

    // 现在的栈：-1 => nil; index => table
    while (lua_next(L, index-1))
    {

        lua_pushvalue(L, -1);
        lua_pushvalue(L, -3);
        const char* key = lua_tostring(L, -1);
        const char* value = lua_tostring(L, -2);

        if(lua_type(L,-1)==LUA_TTABLE)
        {
            lua_print("{");
            traverse_table(L, -1);
            lua_print("}");
            lua_print("=>",key);
        }
        else
        {
            lua_print(" %s=>",key);
        }
        lua_pop(L, 1);
        if(lua_type(L,-1)==LUA_TTABLE)
        {
            lua_print("{");
            traverse_table(L, -1);
            lua_print("} ");
        }
        else
        {
            lua_print("%s ",value);
        }
        lua_pop(L, 2);
    }
}

//普通的操作函数
int add(lua_State* L)
{
    printLuaStack(L);

    double op1 = lua_tonumber(L, 1);
    lua_print("op1 res is %f\n",op1);
    double op2 = lua_tonumber(L, 2);
    lua_print("op2 res is %f\n",op2);

    double op3 = op1 + op2;
    lua_print("op3 res is %f\n",op3);

    lua_pushnumber(L,op3);
    printLuaStack(L);
    return 1;
}
int sub(lua_State* L)
{
    double op1 = lua_tonumber(L, 1);
    double op2 = lua_tonumber(L, 2);
    double op3 = op1 - op2;

    lua_pushnumber(L,op3);
    return 1;
}
//操作table函数
int table(lua_State* L)
{

    // 创建一个新的table，并压入栈
    lua_newtable(L);

    // 往table中设置值
    lua_pushstring(L,"xjp"); // 先将值压入栈
    printLuaStack(L);
    lua_setfield(L, -2, "name"); // 将值设置到table中
    printLuaStack(L);
    //再设置一个值
    lua_pushstring(L,"man");
    printLuaStack(L);

    lua_setfield(L,-2,"sex");
    return 1;
}

int table_look(lua_State* L)
{
    //    printLuaStack(L);
    if(lua_istable(L, -1))
    {
        traverse_table(L,-1);
        //        lua_pushnil(L);  /* 第一个键 */
        //        printLuaStack(L);
        //        lua_next(L,1);
        //        printLuaStack(L);
        //        lua_pop(L, 1);
        //        printLuaStack(L);
        //        lua_next(L,1);
        //        printLuaStack(L);
    }
    return 0;
}
//操作metatable函数
int metatable(lua_State* L)
{
    //创建一个原表 取名 My_name 放入lua注册表
    luaL_newmetatable(L,"My_name");
    printLuaStack(L);
    lua_getfield(L, -1, "__name"); // 将__name压栈
    printLuaStack(L);

    lua_remove(L,-1);//删除刚刚压栈的字符串

    //创建一张函数表压栈
    luaL_newlib(L, testlib);
    printLuaStack(L);
    //设置原表的__index为刚刚创建的表
    lua_setfield(L,1,"__index");
    printLuaStack(L);
    return 1;
}
//操作metatable
int createtable_meta(lua_State* L)
{


    return 1;
}




extern "C" int __declspec(dllexport) luaopen_test(lua_State *L)
{

    //写法一
    //    lua_register(L, "t_add", t_add);
    //    lua_register(L, "t_sub", t_sub);

    //写法二
    luaL_newlib(L, testlib);
    return 1;
}
