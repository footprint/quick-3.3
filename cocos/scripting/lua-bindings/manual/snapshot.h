//
//  snapshot.h
//  cocos2d_lua_bindings
//
//  Created by footprint on 8/31/15.
//
//

#ifdef __cplusplus
extern "C" {
#endif
    
#include "lua.h"
#include "lauxlib.h"
    
    extern int luaopen_snapshot(lua_State *L);
    
#ifdef __cplusplus
}
#endif