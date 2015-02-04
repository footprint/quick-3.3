#include "base/ccConfig.h"
#ifndef __updater_h__
#define __updater_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_updater(lua_State* tolua_S);

#endif // __updater_h__
