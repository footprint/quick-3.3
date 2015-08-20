
#ifndef __LUA_OBJC_BRIDGE_H_
#define __LUA_OBJC_BRIDGE_H_

#include "CCLuaBridge.h"

NS_CC_BEGIN

class LuaObjcBridge : public LuaBridge
{
public:
    static void luaopen_luaoc(lua_State *L);
    
protected:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    static void* lua_table_to_dict(lua_State *L);
#endif
    static int callObjcStaticMethod(lua_State *L);
    
    static void pushValue(lua_State *L, void *val);
};

NS_CC_END

#endif // __LUA_OBJC_BRIDGE_H_
