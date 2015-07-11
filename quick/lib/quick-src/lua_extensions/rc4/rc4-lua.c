//
//  rc4-lua.c
//  sg
//
//  Created by footprint on 7/11/15.
//
//
#include <memory.h>
#include <stdlib.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "rc4.h"
#include "rc4-lua.h"

static struct rc4_state state;

static int rc4_init_lua(lua_State *L)
{
    const char *key = luaL_checkstring(L, 1);
    int length = luaL_checkint(L, 2);
    
    rc4_init(&state, key, length);
    
    return 0; /* number of results */
}

static int rc4_crypt_lua(lua_State *L)
{
    const char *input = luaL_checkstring(L, 1);
    int length = luaL_checkint(L, 2);
    unsigned char *output = (unsigned char*)malloc(sizeof(unsigned char)*length);

    rc4_crypt(&state, input, output, length);
    
    lua_pushlstring(L, (const char*)output, length);
    
    free(output);
    
    return 1; /* number of results */
}

int luaopen_rc4_c(lua_State *L)
{
    lua_register(L,"rc4_init", rc4_init_lua);
    lua_register(L,"rc4_crypt", rc4_crypt_lua);
    return 0;
}
