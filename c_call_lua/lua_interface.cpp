#include "stdio.h"
#include <string>
#include <stdarg.h>
#include "lua_interface.h"
//#include "//qDebug"
lua_State *mState;
bool mStatus;




/************************************************************************/
/*         wrap_module interface                                                        */
/************************************************************************/


lua_State* get_luaState()
{
    return mState;
}
//加载lua文件，并注册 C 函数到 lua 供 lua 调用
bool lw_open_file(const char* file,regist_callback rcfun)
{
    if (mState != NULL)
        lua_close(mState);
    mState = luaL_newstate();
    if (NULL != mState)
    {
        luaL_openlibs(mState);
        mStatus = true;
        if(rcfun!=NULL)
            (*rcfun)(mState);
    }
    else
    {
        mStatus = false;
        return false;
    }
    int bRet = luaL_loadfile(mState, file);
    if (bRet)
    {
        lua_close(mState);
        return false;
    }
    bRet = lua_pcall(mState, 0, 0, 0);
    if (bRet)
    {
        lua_close(mState);
        return false;
    }
    return true;
}
void lw_close()
{
    lua_close(mState);
}


/*不清栈调用lua函数*/
void lw_nc_call_lua_func(const char *func, const char *sig, ...) {
    va_list vl;
    int narg, nres;   /* number of arguments and results */
    //	//qDebug() << "lua_gettop is" << lua_gettop(mState);
    va_start(vl, sig);
    lua_getglobal(mState, func);  /* get function */

    /* push arguments */
    narg = 0;
    while (*sig) {    /* push arguments */
        switch (*sig++) {
        case 'b':/* boolean argument*/
            lua_pushboolean(mState, va_arg(vl, bool));
            break;

        case 'i':  /* int argument */
            lua_pushinteger(mState, va_arg(vl, int));
            break;

        case 'd':  /* double argument */
            lua_pushnumber(mState, va_arg(vl, double));
            break;

        case 's':  /* string argument */
            lua_pushstring(mState, va_arg(vl, char *));
            break;
        case 'l': /*light userdata*/
            lua_pushlightuserdata(mState, va_arg(vl, void *));
            break;
        case '>':
            goto endwhile;

        default:
            break;
            //error(mState, "invalid option (%c)", *(sig - 1));
        }
        narg++;
        luaL_checkstack(mState, 1, "too many arguments");
    }
endwhile:

    /* do the call */
    nres = strlen(sig);  /* number of expected results */
    if (lua_pcall(mState, narg, nres, 0) != 0)  /* do the call */
    {
        //qDebug() << "lua_pcal erro";
    }
    //error(mState, "error running function `%s': %s",func, lua_tostring(mState, -1));

    /* retrieve results */
    nres = -nres;     /* stack index of first result */

    while (*sig) {    /* get results */
        ////qDebug() <<"nres is"  <<nres<<"type is"<<lua_type(mState, nres);
        switch (*sig++) {

        case 'b':/* boolean argument*/
            if (!lua_isboolean(mState, nres))
            {
             //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(mState, "wrong result type");
            *va_arg(vl, bool *) = lua_tonumber(mState, nres);
            break;

        case 'i':  /* int result */
            if (!lua_isinteger(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }

            //error(L, "wrong result type");
            *va_arg(vl, int *) = (int)lua_tointeger(mState, nres);
            break;

        case 'd':  /* double result */
            if (!lua_isnumber(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(mState, "wrong result type");
            *va_arg(vl, double *) = lua_tonumber(mState, nres);
            break;

        case 's':  /* string result */
            if (!lua_isstring(mState, nres))
            {
                //qDebug() << "wrong result type"<< lua_type(mState, nres);
            }
            //error(L, "wrong result type");
            *va_arg(vl, const char **) = lua_tostring(mState, nres);
            break;
        case  'l':
            if (!lua_islightuserdata(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);

            }
            //error(L, "wrong result type");
            *va_arg(vl, void **) = lua_touserdata(mState, nres);
            break;

        default:
            //error(mState, "invalid option (%c)", *(sig - 1));
            break;
        }
        nres++;
    }
    va_end(vl);
}

/*手动清理栈*/
void lw_clear_lua_stack()
{
    lua_settop(mState, 0);
}

/*清栈、调用lua函数*/
void lw_call_lua_func(const char *func, const char *sig, ...)
{
    lua_settop(mState, 0);
    va_list vl;
    int narg, nres;   /* number of arguments and results */
    //	//qDebug() << "lua_gettop is" << lua_gettop(mState);
    va_start(vl, sig);
    lua_getglobal(mState, func);  /* get function */

    /* push arguments */
    narg = 0;
    while (*sig) {    /* push arguments */
        switch (*sig++) {
        case 'b':/* boolean argument*/
            lua_pushboolean(mState, va_arg(vl, bool));
            break;

        case 'i':  /* int argument */
            lua_pushinteger(mState, va_arg(vl, int));
            break;

        case 'd':  /* double argument */
            lua_pushnumber(mState, va_arg(vl, double));
            break;

        case 's':  /* string argument */
            lua_pushstring(mState, va_arg(vl, char *));
            break;
        case 'l': /*light userdata*/
            lua_pushlightuserdata(mState, va_arg(vl, void *));
            break;
        case '>':
            goto endwhile;

        default:
            break;
            //error(mState, "invalid option (%c)", *(sig - 1));
        }
        narg++;
        luaL_checkstack(mState, 1, "too many arguments");
    }
endwhile:

    /* do the call */
    nres = strlen(sig);  /* number of expected results */
    if (lua_pcall(mState, narg, nres, 0) != 0)  /* do the call */
    {
        //qDebug() << "lua_pcal erro";
    }
    //error(mState, "error running function `%s': %s",func, lua_tostring(mState, -1));

    /* retrieve results */
    nres = -nres;     /* stack index of first result */

    while (*sig) {    /* get results */
        ////qDebug() <<"nres is"  <<nres<<"type is"<<lua_type(mState, nres);
        switch (*sig++) {

        case 'b':/* boolean argument*/
            if (!lua_isboolean(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(mState, "wrong result type");
            *va_arg(vl, bool *) = lua_tonumber(mState, nres);
            break;

        case 'i':  /* int result */
            if (!lua_isinteger(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(L, "wrong result type");
            *va_arg(vl, int *) = (int)lua_tointeger(mState, nres);
            break;

        case 'd':  /* double result */
            if (!lua_isnumber(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(mState, "wrong result type");
            *va_arg(vl, double *) = lua_tonumber(mState, nres);
            break;

        case 's':  /* string result */
            if (!lua_isstring(mState, nres))
            {
                //qDebug() << "wrong result type"<< lua_type(mState, nres);
            }
            //error(L, "wrong result type");
            *va_arg(vl, const char **) = lua_tostring(mState, nres);
            break;
        case  'l':
            if (!lua_islightuserdata(mState, nres))
            {
                //qDebug() << "wrong result type" << lua_type(mState, nres);
            }
            //error(L, "wrong result type");
            *va_arg(vl, void **) = lua_touserdata(mState, nres);
            break;

        default:
            //error(mState, "invalid option (%c)", *(sig - 1));
            break;
        }
        nres++;
    }
    va_end(vl);
}
