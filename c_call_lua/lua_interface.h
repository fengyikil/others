#ifndef LUA_WRAP_H
#define LUA_WRAP_H
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

typedef void(*regist_callback)(lua_State*);
//接口
bool lw_open_file(const char* file, regist_callback rcfun);
extern lua_State* get_luaState();
extern void lw_nc_call_lua_func(const char *func, const char *sig, ...);
extern void lw_clear_lua_stack();
extern void lw_call_lua_func(const char *func, const char *sig, ...);
#endif // !LUA_WRAP_H
