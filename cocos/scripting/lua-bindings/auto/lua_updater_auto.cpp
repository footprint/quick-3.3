#include "lua_updater_auto.hpp"
#include "cocos-ext.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_updater_Updater_registerScriptHandler(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Updater* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Updater",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::extension::Updater*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_updater_Updater_registerScriptHandler'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        int arg0;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Updater:registerScriptHandler");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_updater_Updater_registerScriptHandler'", nullptr);
            return 0;
        }
        cobj->registerScriptHandler(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Updater:registerScriptHandler",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_updater_Updater_registerScriptHandler'.",&tolua_err);
#endif
    
    return 0;
}
int lua_updater_Updater_removeDirectory(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Updater* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Updater",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::extension::Updater*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_updater_Updater_removeDirectory'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Updater:removeDirectory"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_updater_Updater_removeDirectory'", nullptr);
            return 0;
        }
        bool ret = cobj->removeDirectory(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Updater:removeDirectory",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_updater_Updater_removeDirectory'.",&tolua_err);
#endif
    
    return 0;
}
int lua_updater_Updater_update(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Updater* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Updater",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::extension::Updater*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_updater_Updater_update'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::__Array* arg0;
            ok &= luaval_to_object<cocos2d::__Array>(tolua_S, 2, "cc.__Array",&arg0);
            
            if (!ok) { break; }
            cobj->update(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Updater:update"); arg0 = arg0_tmp.c_str();
            
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.Updater:update"); arg1 = arg1_tmp.c_str();
            
            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.Updater:update"); arg2 = arg2_tmp.c_str();
            
            if (!ok) { break; }
            cobj->update(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Updater:update"); arg0 = arg0_tmp.c_str();
            
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.Updater:update"); arg1 = arg1_tmp.c_str();
            
            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.Updater:update"); arg2 = arg2_tmp.c_str();
            
            if (!ok) { break; }
            bool arg3;
            ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.Updater:update");
            
            if (!ok) { break; }
            cobj->update(arg0, arg1, arg2, arg3);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Updater:update"); arg0 = arg0_tmp.c_str();
            
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.Updater:update"); arg1 = arg1_tmp.c_str();
            
            if (!ok) { break; }
            cobj->update(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Updater:update"); arg0 = arg0_tmp.c_str();
            
            if (!ok) { break; }
            cobj->update(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Updater:update",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_updater_Updater_update'.",&tolua_err);
#endif
    
    return 0;
}
int lua_updater_Updater_unregisterScriptHandler(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Updater* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Updater",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::extension::Updater*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_updater_Updater_unregisterScriptHandler'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_updater_Updater_unregisterScriptHandler'", nullptr);
            return 0;
        }
        cobj->unregisterScriptHandler();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Updater:unregisterScriptHandler",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_updater_Updater_unregisterScriptHandler'.",&tolua_err);
#endif
    
    return 0;
}
int lua_updater_Updater_query(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Updater* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Updater",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::extension::Updater*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_updater_Updater_query'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Updater:query"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_updater_Updater_query'", nullptr);
            return 0;
        }
        cobj->query(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Updater:query",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_updater_Updater_query'.",&tolua_err);
#endif
    
    return 0;
}
int lua_updater_Updater_createDirectory(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Updater* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Updater",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::extension::Updater*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_updater_Updater_createDirectory'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Updater:createDirectory"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_updater_Updater_createDirectory'", nullptr);
            return 0;
        }
        bool ret = cobj->createDirectory(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Updater:createDirectory",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_updater_Updater_createDirectory'.",&tolua_err);
#endif
    
    return 0;
}
int lua_updater_Updater_setConnectionTimeout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Updater* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Updater",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::extension::Updater*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_updater_Updater_setConnectionTimeout'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        unsigned int arg0;
        
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.Updater:setConnectionTimeout");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_updater_Updater_setConnectionTimeout'", nullptr);
            return 0;
        }
        cobj->setConnectionTimeout(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Updater:setConnectionTimeout",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_updater_Updater_setConnectionTimeout'.",&tolua_err);
#endif
    
    return 0;
}
int lua_updater_Updater_getConnectionTimeout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Updater* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Updater",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::extension::Updater*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_updater_Updater_getConnectionTimeout'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_updater_Updater_getConnectionTimeout'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getConnectionTimeout();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Updater:getConnectionTimeout",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_updater_Updater_getConnectionTimeout'.",&tolua_err);
#endif
    
    return 0;
}
int lua_updater_Updater_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Updater* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_updater_Updater_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::Updater();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Updater");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Updater:Updater",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_updater_Updater_constructor'.",&tolua_err);
#endif
    
    return 0;
}

static int lua_updater_Updater_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Updater)");
    return 0;
}

int lua_register_updater_Updater(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Updater");
    tolua_cclass(tolua_S,"Updater","cc.Updater","cc.Ref",nullptr);
    
    tolua_beginmodule(tolua_S,"Updater");
    tolua_function(tolua_S,"new",lua_updater_Updater_constructor);
    tolua_function(tolua_S,"registerScriptHandler",lua_updater_Updater_registerScriptHandler);
    tolua_function(tolua_S,"removeDirectory",lua_updater_Updater_removeDirectory);
    tolua_function(tolua_S,"update",lua_updater_Updater_update);
    tolua_function(tolua_S,"unregisterScriptHandler",lua_updater_Updater_unregisterScriptHandler);
    tolua_function(tolua_S,"query",lua_updater_Updater_query);
    tolua_function(tolua_S,"createDirectory",lua_updater_Updater_createDirectory);
    tolua_function(tolua_S,"setConnectionTimeout",lua_updater_Updater_setConnectionTimeout);
    tolua_function(tolua_S,"getConnectionTimeout",lua_updater_Updater_getConnectionTimeout);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::Updater).name();
    g_luaType[typeName] = "cc.Updater";
    g_typeCast["Updater"] = "cc.Updater";
    return 1;
}
TOLUA_API int register_all_updater(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    
    tolua_module(tolua_S,"cc",0);
    tolua_beginmodule(tolua_S,"cc");
    
    lua_register_updater_Updater(tolua_S);
    
    tolua_endmodule(tolua_S);
    return 1;
}

