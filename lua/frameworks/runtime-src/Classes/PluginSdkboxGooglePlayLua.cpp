#include "PluginSdkboxGooglePlayLua.hpp"
#include "PluginSdkboxGooglePlay/SdkboxGooglePlayWrappedObjects.h"
#include "SDKBoxLuaHelper.h"
#include "sdkbox/Sdkbox.h"



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

int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_CurrentLevel(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_CurrentLevel'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::GPGLocalPlayerWrapper::CurrentLevel();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:CurrentLevel",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_CurrentLevel'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Name(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Name'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::GPGLocalPlayerWrapper::Name();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:Name",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Name'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_AvatarUrl(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLocalPlayerWrapper:AvatarUrl");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_AvatarUrl'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::GPGLocalPlayerWrapper::AvatarUrl(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:AvatarUrl",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_AvatarUrl'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_LastLevelUpTime(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_LastLevelUpTime'", nullptr);
            return 0;
        }
        long long ret = sdkbox::GPGLocalPlayerWrapper::LastLevelUpTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:LastLevelUpTime",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_LastLevelUpTime'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Title(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Title'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::GPGLocalPlayerWrapper::Title();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:Title",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Title'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_CurrentXP(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_CurrentXP'", nullptr);
            return 0;
        }
        long long ret = sdkbox::GPGLocalPlayerWrapper::CurrentXP();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:CurrentXP",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_CurrentXP'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Fetch(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.GPGLocalPlayerWrapper:Fetch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Fetch'", nullptr);
            return 0;
        }
        sdkbox::GPGLocalPlayerWrapper::Fetch(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:Fetch",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Fetch'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_HasLevelInfo(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_HasLevelInfo'", nullptr);
            return 0;
        }
        bool ret = sdkbox::GPGLocalPlayerWrapper::HasLevelInfo();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:HasLevelInfo",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_HasLevelInfo'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_NextLevel(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_NextLevel'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::GPGLocalPlayerWrapper::NextLevel();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:NextLevel",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_NextLevel'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Id(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.GPGLocalPlayerWrapper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Id'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::GPGLocalPlayerWrapper::Id();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.GPGLocalPlayerWrapper:Id",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Id'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GPGLocalPlayerWrapper)");
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.GPGLocalPlayerWrapper");
    tolua_cclass(tolua_S,"GPGLocalPlayerWrapper","sdkbox.GPGLocalPlayerWrapper","",nullptr);

    tolua_beginmodule(tolua_S,"GPGLocalPlayerWrapper");
        tolua_function(tolua_S,"CurrentLevel", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_CurrentLevel);
        tolua_function(tolua_S,"Name", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Name);
        tolua_function(tolua_S,"AvatarUrl", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_AvatarUrl);
        tolua_function(tolua_S,"LastLevelUpTime", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_LastLevelUpTime);
        tolua_function(tolua_S,"Title", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Title);
        tolua_function(tolua_S,"CurrentXP", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_CurrentXP);
        tolua_function(tolua_S,"Fetch", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Fetch);
        tolua_function(tolua_S,"HasLevelInfo", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_HasLevelInfo);
        tolua_function(tolua_S,"NextLevel", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_NextLevel);
        tolua_function(tolua_S,"Id", lua_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper_Id);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::GPGLocalPlayerWrapper).name();
    g_luaType[typeName] = "sdkbox.GPGLocalPlayerWrapper";
    g_typeCast["GPGLocalPlayerWrapper"] = "sdkbox.GPGLocalPlayerWrapper";
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
TOLUA_API int register_all_PluginSdkboxGooglePlayLua(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"sdkbox",0);
	tolua_beginmodule(tolua_S,"sdkbox");

	lua_register_PluginSdkboxGooglePlayLua_GPGLocalPlayerWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGQuestsWrapper(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_GPGSnapshotWrapper(tolua_S);

	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}

