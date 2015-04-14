#include "base/ccConfig.h"
#ifndef __gaf_main_h__
#define __gaf_main_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int append_gaf_scripts(lua_State* tolua_S);

#endif