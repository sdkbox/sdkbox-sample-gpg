#include "PluginSdkboxGooglePlayLua.hpp"
#include "PluginSdkboxGooglePlay/SdkboxGooglePlayWrappedObjects.h"
#include "SDKBoxLuaHelper.h"
#include "sdkbox/Sdkbox.h"



int lua_PluginSdkboxGooglePlayLua_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGRealTimeMultiplayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGRealTimeMultiplayerWrapper:CreateRealTimeRoom");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGRealTimeMultiplayerWrapper:CreateRealTimeRoom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom'", nullptr);
            return 0;
        }
        sdkbox::GPGRealTimeMultiplayerWrapper::CreateRealTimeRoom(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGRealTimeMultiplayerWrapper:CreateRealTimeRoom",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGRealTimeMultiplayerWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGRealTimeMultiplayerWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGRealTimeMultiplayerWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGRealTimeMultiplayerWrapper");
    tolua_cclass(tolua_S,"GPGRealTimeMultiplayerWrapper","sdkbox.GPGRealTimeMultiplayerWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGRealTimeMultiplayerWrapper");
        tolua_function(tolua_S,"CreateRealTimeRoom", lua_PluginSdkboxGooglePlayLua_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGRealTimeMultiplayerWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGRealTimeMultiplayerWrapper";
    g_typeCast["GPGRealTimeMultiplayerWrapper"] = "sdkbox.GPGRealTimeMultiplayerWrapper";
    return 1;
}

int lua_PluginSdkboxGooglePlayLua_GPGWrapper_NotifyToScripting(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGWrapper:NotifyToScripting");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGWrapper:NotifyToScripting");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_NotifyToScripting'", nullptr);
            return 0;
        }
        sdkbox::GPGWrapper::NotifyToScripting(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGWrapper:NotifyToScripting",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_NotifyToScripting'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGWrapper_IsAuthorized(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_IsAuthorized'", nullptr);
            return 0;
        }
        bool ret = sdkbox::GPGWrapper::IsAuthorized();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGWrapper:IsAuthorized",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_IsAuthorized'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGWrapper_CreateGameServices(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.GPGWrapper:CreateGameServices");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_CreateGameServices'", nullptr);
            return 0;
        }
        sdkbox::GPGWrapper::CreateGameServices(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGWrapper:CreateGameServices",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_CreateGameServices'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGWrapper_StartAuthorizationUI(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_StartAuthorizationUI'", nullptr);
            return 0;
        }
        sdkbox::GPGWrapper::StartAuthorizationUI();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGWrapper:StartAuthorizationUI",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_StartAuthorizationUI'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGWrapper_SignOut(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_SignOut'", nullptr);
            return 0;
        }
        sdkbox::GPGWrapper::SignOut();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGWrapper:SignOut",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_SignOut'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGWrapper");
    tolua_cclass(tolua_S,"GPGWrapper","sdkbox.GPGWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGWrapper");
        tolua_function(tolua_S,"NotifyToScripting", lua_PluginSdkboxGooglePlayLua_GPGWrapper_NotifyToScripting);
        tolua_function(tolua_S,"IsAuthorized", lua_PluginSdkboxGooglePlayLua_GPGWrapper_IsAuthorized);
        tolua_function(tolua_S,"CreateGameServices", lua_PluginSdkboxGooglePlayLua_GPGWrapper_CreateGameServices);
        tolua_function(tolua_S,"StartAuthorizationUI", lua_PluginSdkboxGooglePlayLua_GPGWrapper_StartAuthorizationUI);
        tolua_function(tolua_S,"SignOut", lua_PluginSdkboxGooglePlayLua_GPGWrapper_SignOut);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGWrapper";
    g_typeCast["GPGWrapper"] = "sdkbox.GPGWrapper";
    return 1;
}

int lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyConnected(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGPlayerWrapper:FetchRecentlyConnected");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGPlayerWrapper:FetchRecentlyConnected");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyConnected'", nullptr);
            return 0;
        }
        sdkbox::GPGPlayerWrapper::FetchRecentlyConnected(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGPlayerWrapper:FetchRecentlyConnected",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyConnected'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyInvitable(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGPlayerWrapper:FetchRecentlyInvitable");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGPlayerWrapper:FetchRecentlyInvitable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyInvitable'", nullptr);
            return 0;
        }
        sdkbox::GPGPlayerWrapper::FetchRecentlyInvitable(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGPlayerWrapper:FetchRecentlyInvitable",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyInvitable'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_Fetch(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        std::string arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGPlayerWrapper:Fetch");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGPlayerWrapper:Fetch");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "sdkbox.GPGPlayerWrapper:Fetch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_Fetch'", nullptr);
            return 0;
        }
        sdkbox::GPGPlayerWrapper::Fetch(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGPlayerWrapper:Fetch",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_Fetch'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyPlayed(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGPlayerWrapper:FetchRecentlyPlayed");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGPlayerWrapper:FetchRecentlyPlayed");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyPlayed'", nullptr);
            return 0;
        }
        sdkbox::GPGPlayerWrapper::FetchRecentlyPlayed(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGPlayerWrapper:FetchRecentlyPlayed",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyPlayed'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchSelf(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGPlayerWrapper:FetchSelf");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGPlayerWrapper:FetchSelf");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchSelf'", nullptr);
            return 0;
        }
        sdkbox::GPGPlayerWrapper::FetchSelf(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGPlayerWrapper:FetchSelf",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchSelf'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGPlayerWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGPlayerWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGPlayerWrapper");
    tolua_cclass(tolua_S,"GPGPlayerWrapper","sdkbox.GPGPlayerWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGPlayerWrapper");
        tolua_function(tolua_S,"FetchRecentlyConnected", lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyConnected);
        tolua_function(tolua_S,"FetchRecentlyInvitable", lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyInvitable);
        tolua_function(tolua_S,"Fetch", lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_Fetch);
        tolua_function(tolua_S,"FetchRecentlyPlayed", lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchRecentlyPlayed);
        tolua_function(tolua_S,"FetchSelf", lua_PluginSdkboxGooglePlayLua_GPGPlayerWrapper_FetchSelf);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGPlayerWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGPlayerWrapper";
    g_typeCast["GPGPlayerWrapper"] = "sdkbox.GPGPlayerWrapper";
    return 1;
}

int lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Load(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGSnapshotWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        int arg0;
        std::string arg1;
        int arg2;
        int arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGSnapshotWrapper:Load");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGSnapshotWrapper:Load");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "sdkbox.GPGSnapshotWrapper:Load");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "sdkbox.GPGSnapshotWrapper:Load");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Load'", nullptr);
            return 0;
        }
        sdkbox::GPGSnapshotWrapper::Load(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGSnapshotWrapper:Load",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Load'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_ShowSelectUIOperation(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGSnapshotWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGSnapshotWrapper:ShowSelectUIOperation");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGSnapshotWrapper:ShowSelectUIOperation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_ShowSelectUIOperation'", nullptr);
            return 0;
        }
        sdkbox::GPGSnapshotWrapper::ShowSelectUIOperation(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGSnapshotWrapper:ShowSelectUIOperation",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_ShowSelectUIOperation'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Save(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGSnapshotWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGSnapshotWrapper:Save");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGSnapshotWrapper:Save");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Save'", nullptr);
            return 0;
        }
        sdkbox::GPGSnapshotWrapper::Save(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGSnapshotWrapper:Save",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Save'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Delete(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGSnapshotWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGSnapshotWrapper:Delete");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGSnapshotWrapper:Delete");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Delete'", nullptr);
            return 0;
        }
        sdkbox::GPGSnapshotWrapper::Delete(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGSnapshotWrapper:Delete",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Delete'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_FetchAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGSnapshotWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGSnapshotWrapper:FetchAll");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGSnapshotWrapper:FetchAll");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_FetchAll'", nullptr);
            return 0;
        }
        sdkbox::GPGSnapshotWrapper::FetchAll(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGSnapshotWrapper:FetchAll",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_FetchAll'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGSnapshotWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGSnapshotWrapper");
    tolua_cclass(tolua_S,"GPGSnapshotWrapper","sdkbox.GPGSnapshotWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGSnapshotWrapper");
        tolua_function(tolua_S,"Load", lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Load);
        tolua_function(tolua_S,"ShowSelectUIOperation", lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_ShowSelectUIOperation);
        tolua_function(tolua_S,"Save", lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Save);
        tolua_function(tolua_S,"Delete", lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_Delete);
        tolua_function(tolua_S,"FetchAll", lua_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper_FetchAll);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGSnapshotWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGSnapshotWrapper";
    g_typeCast["GPGSnapshotWrapper"] = "sdkbox.GPGSnapshotWrapper";
    return 1;
}

int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:FetchAll");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGLeaderboardWrapper:FetchAll");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchAll'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::FetchAll(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:FetchAll",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchAll'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchScoreSummary(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 5)
    {
        int arg0;
        int arg1;
        std::string arg2;
        int arg3;
        int arg4;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:FetchScoreSummary");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGLeaderboardWrapper:FetchScoreSummary");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "sdkbox.GPGLeaderboardWrapper:FetchScoreSummary");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "sdkbox.GPGLeaderboardWrapper:FetchScoreSummary");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "sdkbox.GPGLeaderboardWrapper:FetchScoreSummary");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchScoreSummary'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::FetchScoreSummary(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:FetchScoreSummary",argc, 5);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchScoreSummary'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchPreviousScorePage(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:FetchPreviousScorePage");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGLeaderboardWrapper:FetchPreviousScorePage");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "sdkbox.GPGLeaderboardWrapper:FetchPreviousScorePage");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchPreviousScorePage'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::FetchPreviousScorePage(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:FetchPreviousScorePage",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchPreviousScorePage'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_ShowAllUI(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:ShowAllUI");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_ShowAllUI'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::ShowAllUI(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:ShowAllUI",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_ShowAllUI'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchNextScorePage(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:FetchNextScorePage");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGLeaderboardWrapper:FetchNextScorePage");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "sdkbox.GPGLeaderboardWrapper:FetchNextScorePage");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchNextScorePage'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::FetchNextScorePage(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:FetchNextScorePage",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchNextScorePage'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_SubmitScore(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        std::string arg1;
        long arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:SubmitScore");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGLeaderboardWrapper:SubmitScore");
        ok &= luaval_to_long(tolua_S, 4, &arg2, "sdkbox.GPGLeaderboardWrapper:SubmitScore");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_SubmitScore'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::SubmitScore(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 4)
    {
        int arg0;
        std::string arg1;
        long arg2;
        std::string arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:SubmitScore");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGLeaderboardWrapper:SubmitScore");
        ok &= luaval_to_long(tolua_S, 4, &arg2, "sdkbox.GPGLeaderboardWrapper:SubmitScore");
        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "sdkbox.GPGLeaderboardWrapper:SubmitScore");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_SubmitScore'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::SubmitScore(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:SubmitScore",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_SubmitScore'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchAllScoreSummaries(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        std::string arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:FetchAllScoreSummaries");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGLeaderboardWrapper:FetchAllScoreSummaries");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "sdkbox.GPGLeaderboardWrapper:FetchAllScoreSummaries");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchAllScoreSummaries'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::FetchAllScoreSummaries(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:FetchAllScoreSummaries",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchAllScoreSummaries'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_ShowUI(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:ShowUI");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGLeaderboardWrapper:ShowUI");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_ShowUI'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::ShowUI(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:ShowUI",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_ShowUI'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_Fetch(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:Fetch");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGLeaderboardWrapper:Fetch");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "sdkbox.GPGLeaderboardWrapper:Fetch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_Fetch'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::Fetch(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:Fetch",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_Fetch'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchScorePage(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLeaderboardWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 7)
    {
        int arg0;
        std::string arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        int arg6;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLeaderboardWrapper:FetchScorePage");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGLeaderboardWrapper:FetchScorePage");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "sdkbox.GPGLeaderboardWrapper:FetchScorePage");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "sdkbox.GPGLeaderboardWrapper:FetchScorePage");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "sdkbox.GPGLeaderboardWrapper:FetchScorePage");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "sdkbox.GPGLeaderboardWrapper:FetchScorePage");
        ok &= luaval_to_int32(tolua_S, 8,(int *)&arg6, "sdkbox.GPGLeaderboardWrapper:FetchScorePage");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchScorePage'", nullptr);
            return 0;
        }
        sdkbox::GPGLeaderboardWrapper::FetchScorePage(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLeaderboardWrapper:FetchScorePage",argc, 7);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchScorePage'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGLeaderboardWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGLeaderboardWrapper");
    tolua_cclass(tolua_S,"GPGLeaderboardWrapper","sdkbox.GPGLeaderboardWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGLeaderboardWrapper");
        tolua_function(tolua_S,"FetchAll", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchAll);
        tolua_function(tolua_S,"FetchScoreSummary", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchScoreSummary);
        tolua_function(tolua_S,"FetchPreviousScorePage", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchPreviousScorePage);
        tolua_function(tolua_S,"ShowAllUI", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_ShowAllUI);
        tolua_function(tolua_S,"FetchNextScorePage", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchNextScorePage);
        tolua_function(tolua_S,"SubmitScore", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_SubmitScore);
        tolua_function(tolua_S,"FetchAllScoreSummaries", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchAllScoreSummaries);
        tolua_function(tolua_S,"ShowUI", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_ShowUI);
        tolua_function(tolua_S,"Fetch", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_Fetch);
        tolua_function(tolua_S,"FetchScorePage", lua_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper_FetchScorePage);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGLeaderboardWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGLeaderboardWrapper";
    g_typeCast["GPGLeaderboardWrapper"] = "sdkbox.GPGLeaderboardWrapper";
    return 1;
}

int lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_FetchAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGAchievementWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGAchievementWrapper:FetchAll");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGAchievementWrapper:FetchAll");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_FetchAll'", nullptr);
            return 0;
        }
        sdkbox::GPGAchievementWrapper::FetchAll(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGAchievementWrapper:FetchAll",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_FetchAll'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Reveal(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGAchievementWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.GPGAchievementWrapper:Reveal");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Reveal'", nullptr);
            return 0;
        }
        sdkbox::GPGAchievementWrapper::Reveal(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGAchievementWrapper:Reveal",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Reveal'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Unlock(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGAchievementWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.GPGAchievementWrapper:Unlock");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Unlock'", nullptr);
            return 0;
        }
        sdkbox::GPGAchievementWrapper::Unlock(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGAchievementWrapper:Unlock",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Unlock'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_ShowAllUI(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGAchievementWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGAchievementWrapper:ShowAllUI");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_ShowAllUI'", nullptr);
            return 0;
        }
        sdkbox::GPGAchievementWrapper::ShowAllUI(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGAchievementWrapper:ShowAllUI",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_ShowAllUI'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_SetStepsAtLeast(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGAchievementWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        unsigned int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.GPGAchievementWrapper:SetStepsAtLeast");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "sdkbox.GPGAchievementWrapper:SetStepsAtLeast");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_SetStepsAtLeast'", nullptr);
            return 0;
        }
        sdkbox::GPGAchievementWrapper::SetStepsAtLeast(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGAchievementWrapper:SetStepsAtLeast",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_SetStepsAtLeast'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Increment(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGAchievementWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        unsigned int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.GPGAchievementWrapper:Increment");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "sdkbox.GPGAchievementWrapper:Increment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Increment'", nullptr);
            return 0;
        }
        sdkbox::GPGAchievementWrapper::Increment(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGAchievementWrapper:Increment",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Increment'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Fetch(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGAchievementWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGAchievementWrapper:Fetch");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGAchievementWrapper:Fetch");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "sdkbox.GPGAchievementWrapper:Fetch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Fetch'", nullptr);
            return 0;
        }
        sdkbox::GPGAchievementWrapper::Fetch(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGAchievementWrapper:Fetch",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Fetch'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGAchievementWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGAchievementWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGAchievementWrapper");
    tolua_cclass(tolua_S,"GPGAchievementWrapper","sdkbox.GPGAchievementWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGAchievementWrapper");
        tolua_function(tolua_S,"FetchAll", lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_FetchAll);
        tolua_function(tolua_S,"Reveal", lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Reveal);
        tolua_function(tolua_S,"Unlock", lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Unlock);
        tolua_function(tolua_S,"ShowAllUI", lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_ShowAllUI);
        tolua_function(tolua_S,"SetStepsAtLeast", lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_SetStepsAtLeast);
        tolua_function(tolua_S,"Increment", lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Increment);
        tolua_function(tolua_S,"Fetch", lua_PluginSdkboxGooglePlayLua_GPGAchievementWrapper_Fetch);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGAchievementWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGAchievementWrapper";
    g_typeCast["GPGAchievementWrapper"] = "sdkbox.GPGAchievementWrapper";
    return 1;
}

int lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_FetchList(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGQuestsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGQuestsWrapper:FetchList");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_FetchList'", nullptr);
            return 0;
        }
        sdkbox::GPGQuestsWrapper::FetchList(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGQuestsWrapper:FetchList");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGQuestsWrapper:FetchList");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_FetchList'", nullptr);
            return 0;
        }
        sdkbox::GPGQuestsWrapper::FetchList(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGQuestsWrapper:FetchList",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_FetchList'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_Accept(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGQuestsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGQuestsWrapper:Accept");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGQuestsWrapper:Accept");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_Accept'", nullptr);
            return 0;
        }
        sdkbox::GPGQuestsWrapper::Accept(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGQuestsWrapper:Accept",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_Accept'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ShowAllUI(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGQuestsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGQuestsWrapper:ShowAllUI");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ShowAllUI'", nullptr);
            return 0;
        }
        sdkbox::GPGQuestsWrapper::ShowAllUI(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGQuestsWrapper:ShowAllUI",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ShowAllUI'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ShowUI(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGQuestsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGQuestsWrapper:ShowUI");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGQuestsWrapper:ShowUI");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ShowUI'", nullptr);
            return 0;
        }
        sdkbox::GPGQuestsWrapper::ShowUI(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGQuestsWrapper:ShowUI",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ShowUI'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ClaimMilestone(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGQuestsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGQuestsWrapper:ClaimMilestone");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGQuestsWrapper:ClaimMilestone");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ClaimMilestone'", nullptr);
            return 0;
        }
        sdkbox::GPGQuestsWrapper::ClaimMilestone(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGQuestsWrapper:ClaimMilestone",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ClaimMilestone'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_Fetch(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGQuestsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGQuestsWrapper:Fetch");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGQuestsWrapper:Fetch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_Fetch'", nullptr);
            return 0;
        }
        sdkbox::GPGQuestsWrapper::Fetch(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3)
    {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGQuestsWrapper:Fetch");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGQuestsWrapper:Fetch");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "sdkbox.GPGQuestsWrapper:Fetch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_Fetch'", nullptr);
            return 0;
        }
        sdkbox::GPGQuestsWrapper::Fetch(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGQuestsWrapper:Fetch",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_Fetch'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGQuestsWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGQuestsWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGQuestsWrapper");
    tolua_cclass(tolua_S,"GPGQuestsWrapper","sdkbox.GPGQuestsWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGQuestsWrapper");
        tolua_function(tolua_S,"FetchList", lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_FetchList);
        tolua_function(tolua_S,"Accept", lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_Accept);
        tolua_function(tolua_S,"ShowAllUI", lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ShowAllUI);
        tolua_function(tolua_S,"ShowUI", lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ShowUI);
        tolua_function(tolua_S,"ClaimMilestone", lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_ClaimMilestone);
        tolua_function(tolua_S,"Fetch", lua_PluginSdkboxGooglePlayLua_GPGQuestsWrapper_Fetch);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGQuestsWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGQuestsWrapper";
    g_typeCast["GPGQuestsWrapper"] = "sdkbox.GPGQuestsWrapper";
    return 1;
}

int lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_FetchAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGEventsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGEventsWrapper:FetchAll");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_FetchAll'", nullptr);
            return 0;
        }
        sdkbox::GPGEventsWrapper::FetchAll(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGEventsWrapper:FetchAll");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGEventsWrapper:FetchAll");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_FetchAll'", nullptr);
            return 0;
        }
        sdkbox::GPGEventsWrapper::FetchAll(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGEventsWrapper:FetchAll",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_FetchAll'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Fetch(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGEventsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGEventsWrapper:Fetch");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGEventsWrapper:Fetch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Fetch'", nullptr);
            return 0;
        }
        sdkbox::GPGEventsWrapper::Fetch(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3)
    {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGEventsWrapper:Fetch");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.GPGEventsWrapper:Fetch");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "sdkbox.GPGEventsWrapper:Fetch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Fetch'", nullptr);
            return 0;
        }
        sdkbox::GPGEventsWrapper::Fetch(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGEventsWrapper:Fetch",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Fetch'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Increment(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGEventsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.GPGEventsWrapper:Increment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Increment'", nullptr);
            return 0;
        }
        sdkbox::GPGEventsWrapper::Increment(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        std::string arg0;
        unsigned int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.GPGEventsWrapper:Increment");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "sdkbox.GPGEventsWrapper:Increment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Increment'", nullptr);
            return 0;
        }
        sdkbox::GPGEventsWrapper::Increment(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGEventsWrapper:Increment",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Increment'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGEventsWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGEventsWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGEventsWrapper");
    tolua_cclass(tolua_S,"GPGEventsWrapper","sdkbox.GPGEventsWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGEventsWrapper");
        tolua_function(tolua_S,"FetchAll", lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_FetchAll);
        tolua_function(tolua_S,"Fetch", lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Fetch);
        tolua_function(tolua_S,"Increment", lua_PluginSdkboxGooglePlayLua_GPGEventsWrapper_Increment);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGEventsWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGEventsWrapper";
    g_typeCast["GPGEventsWrapper"] = "sdkbox.GPGEventsWrapper";
    return 1;
}

int lua_PluginSdkboxGooglePlayLua_GPGStatsWrapper_FetchForPlayer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGStatsWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGStatsWrapper:FetchForPlayer");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.GPGStatsWrapper:FetchForPlayer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGStatsWrapper_FetchForPlayer'", nullptr);
            return 0;
        }
        sdkbox::GPGStatsWrapper::FetchForPlayer(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGStatsWrapper:FetchForPlayer",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGStatsWrapper_FetchForPlayer'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGStatsWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGStatsWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGStatsWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGStatsWrapper");
    tolua_cclass(tolua_S,"GPGStatsWrapper","sdkbox.GPGStatsWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGStatsWrapper");
        tolua_function(tolua_S,"FetchForPlayer", lua_PluginSdkboxGooglePlayLua_GPGStatsWrapper_FetchForPlayer);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGStatsWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGStatsWrapper";
    g_typeCast["GPGStatsWrapper"] = "sdkbox.GPGStatsWrapper";
    return 1;
}
TOLUA_API int register_all_PluginSdkboxGooglePlayLua(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"sdkbox",0);
	tolua_beginmodule(tolua_S,"sdkbox");

	lua_register_PluginSdkboxGooglePlayLua_GPGEventsWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGPlayerWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGQuestsWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGAchievementWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGStatsWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGRealTimeMultiplayerWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGLeaderboardWrapper(tolua_S);

	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}

