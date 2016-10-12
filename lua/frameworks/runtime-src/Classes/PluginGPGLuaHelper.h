//
//  PluginSdkboxGooglePlayLuaHelper.h
//  PluginSdkboxGooglePlayLuaHelper
//
//  Created by Justin Graham on 8/10/16.
//  Copyright © 2016 SDKBOX. All rights reserved.
//

#pragma once

#include <string>
#include "cocos2d.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

TOLUA_API int register_all_PluginGPGLua_helper(lua_State* L);

class NativeLuaNotifierScheduler
	: public cocos2d::Ref
{
public:

    NativeLuaNotifierScheduler(int id, const std::string& json);
    void schedule();
    void notity(float dt);

protected:
    int _id;
    std::string _json;
};
