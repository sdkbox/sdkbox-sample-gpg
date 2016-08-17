//
//  SnapshotMetadataLuaHelper.h
//  SnapshotMetadataLuaHelper
//
//  Created by Justin Graham on 8/10/16.
//  Copyright © 2016 SDKBOX. All rights reserved.
//

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

TOLUA_API int lua_register_PluginSdkboxGooglePlayLua_SnapshotMetadata(lua_State* L);


