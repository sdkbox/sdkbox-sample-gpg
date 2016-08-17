#include "PluginSdkboxGooglePlayLua.hpp"
#include "PluginSdkboxGooglePlay/PluginSdkboxGooglePlay.h"
#include "SDKBoxLuaHelper.h"
#include "sdkbox/Sdkbox.h"


TOLUA_API int register_all_PluginSdkboxGooglePlayLua(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"sdkbox",0);
	tolua_beginmodule(tolua_S,"sdkbox");


	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}

