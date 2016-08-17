
#include "PluginSdkboxGooglePlayLuaHelper.h"
#include "PluginSdkboxGooglePlay/PluginSdkboxGooglePlay.h"
#include "PluginSdkboxGooglePlay/SnapshotManager.h"
#include "PluginSdkboxGooglePlay/SdkboxGooglePlayWrappedObjects.h"
#include "SnapshotMetadataLuaHelper.h"
#include "SDKBoxLuaHelper.h"

//bool luaval_to_json(lua_State* L, int lo, sdkbox::json* ret, const char* funcName)
//{
//	using namespace sdkbox;
//
//    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
//        return false;
//
//    tolua_Error tolua_err;
//    bool ok = true;
//    if (!tolua_istable(L, lo, 0, &tolua_err))
//    {
//#if COCOS2D_DEBUG >=1
//        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
//#endif
//        ok = false;
//    }
//
//    if (!ok)
//        return ok;
//
//    lua_pushnil(L);
//    std::string key;
//    while (lua_next(L, lo) != 0)
//    {
//        if (lua_isstring(L, -2))
//        {
//            json value;
//
//            if (lua_isstring(L, -1))
//            {
//                std::string v;
//                luaval_to_std_string(L, -1, &v)
//				value = json(v);
//            }
//            else if (lua_isboolean(L, -1))
//            {
//                bool b;
//                luaval_to_boolean(L, -1, &b);
//                value = json(b);
//            }
//            else if (lua_isnumber(L, -1))
//            {
//                double n;
//                luaval_to_number(L, -1, &n);
//                value = json(n);
//            }
//
//            if (luaval_to_std_string(L, -2, &key))
//            {
//                (*ret)[key] = value;
//            }
//        }
//        else
//        {
//            CCASSERT(false, "string key is needed");
//        }
//
//        lua_pop(L, 1);
//    }
//
//    return ok;
//}

int lua_PluginSdkboxGooglePlayLua_GPGWrapper_IsAuthorized(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginSdkboxGooglePlay",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginSdkboxGooglePlay:IsAuthorized",argc, 0);
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
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginSdkboxGooglePlay",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2, &arg0, "sdkbox.PluginSdkboxGooglePlay:CreateGameServices");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_CreateGameServices'", nullptr);
            return 0;
        }
        sdkbox::GPGWrapper::CreateGameServices(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginSdkboxGooglePlay:CreateGameServices",argc, 1);
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
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginSdkboxGooglePlay",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginSdkboxGooglePlay:StartAuthorizationUI",argc, 0);
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
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginSdkboxGooglePlay",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginSdkboxGooglePlay:SignOut",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_GPGWrapper_SignOut'.",&tolua_err);
#endif
    return 0;
}

int lua_PluginSdkboxGooglePlayLua_SnapshotManager_ShowSelectUIOperation(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sdkbox.SnapshotManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gpg::SnapshotManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotManager_ShowSelectUIOperation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5)
    {
        bool arg0;
        bool arg1;
        unsigned int arg2;
        std::string arg3;
        std::function<void (const gpg::SnapshotManager::SnapshotSelectUIResponse &)> arg4;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "sdkbox.SnapshotManager:ShowSelectUIOperation");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "sdkbox.SnapshotManager:ShowSelectUIOperation");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "sdkbox.SnapshotManager:ShowSelectUIOperation");

        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "sdkbox.SnapshotManager:ShowSelectUIOperation");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotManager_ShowSelectUIOperation'", nullptr);
            return 0;
        }
        cobj->ShowSelectUIOperation(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "sdkbox.SnapshotManager:ShowSelectUIOperation",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotManager_ShowSelectUIOperation'.",&tolua_err);
#endif

    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_SnapshotManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.SnapshotManager");
    tolua_cclass(tolua_S,"SnapshotManager","sdkbox.SnapshotManager","",nullptr);

    tolua_beginmodule(tolua_S,"SnapshotManager");
//        tolua_function(tolua_S,"FetchAll",lua_PluginSdkboxGooglePlayLua_SnapshotManager_FetchAll);
        tolua_function(tolua_S,"ShowSelectUIOperation",lua_PluginSdkboxGooglePlayLua_SnapshotManager_ShowSelectUIOperation);
//        tolua_function(tolua_S,"Read",lua_PluginSdkboxGooglePlayLua_SnapshotManager_Read);
//        tolua_function(tolua_S,"Open",lua_PluginSdkboxGooglePlayLua_SnapshotManager_Open);
//        tolua_function(tolua_S,"FetchAllBlocking",lua_PluginSdkboxGooglePlayLua_SnapshotManager_FetchAllBlocking);
//        tolua_function(tolua_S,"ReadBlocking",lua_PluginSdkboxGooglePlayLua_SnapshotManager_ReadBlocking);
//        tolua_function(tolua_S,"ResolveConflictBlocking",lua_PluginSdkboxGooglePlayLua_SnapshotManager_ResolveConflictBlocking);
//        tolua_function(tolua_S,"OpenBlocking",lua_PluginSdkboxGooglePlayLua_SnapshotManager_OpenBlocking);
//        tolua_function(tolua_S,"ShowSelectUIOperationBlocking",lua_PluginSdkboxGooglePlayLua_SnapshotManager_ShowSelectUIOperationBlocking);
//        tolua_function(tolua_S,"Commit",lua_PluginSdkboxGooglePlayLua_SnapshotManager_Commit);
//        tolua_function(tolua_S,"CommitBlocking",lua_PluginSdkboxGooglePlayLua_SnapshotManager_CommitBlocking);
//        tolua_function(tolua_S,"ResolveConflict",lua_PluginSdkboxGooglePlayLua_SnapshotManager_ResolveConflict);
//        tolua_function(tolua_S,"Delete",lua_PluginSdkboxGooglePlayLua_SnapshotManager_Delete);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(gpg::SnapshotManager).name();
    g_luaType[typeName] = "sdkbox.SnapshotManager";
    g_typeCast["SnapshotManager"] = "sdkbox.SnapshotManager";
    return 1;
}

int lua_PluginSdkboxGooglePlayLua_PluginSdkboxGooglePlay_snapshotManager(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginSdkboxGooglePlay",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_PluginSdkboxGooglePlay_snapshotManager'", nullptr);
            return 0;
        }
        sdkbox::SnapshotManager* ret = sdkbox::PluginSdkboxGooglePlay::snapshotManager();
        object_to_luaval<sdkbox::SnapshotManager>(tolua_S, "sdkbox.SnapshotManager",(sdkbox::SnapshotManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginSdkboxGooglePlay:snapshotManager",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_PluginSdkboxGooglePlay_snapshotManager'.",&tolua_err);
#endif
    return 0;
}

int lua_register_PluginSdkboxGooglePlayLua_PluginSdkboxGooglePlay(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.PluginSdkboxGooglePlay");
    tolua_cclass(tolua_S,"PluginSdkboxGooglePlay","sdkbox.PluginSdkboxGooglePlay","",nullptr);

    tolua_beginmodule(tolua_S,"PluginSdkboxGooglePlay");
        tolua_function(tolua_S,"IsAuthorized", lua_PluginSdkboxGooglePlayLua_GPGWrapper_IsAuthorized);
        tolua_function(tolua_S,"CreateGameServices", lua_PluginSdkboxGooglePlayLua_GPGWrapper_CreateGameServices);
        tolua_function(tolua_S,"StartAuthorizationUI", lua_PluginSdkboxGooglePlayLua_GPGWrapper_StartAuthorizationUI);
        tolua_function(tolua_S,"SignOut", lua_PluginSdkboxGooglePlayLua_GPGWrapper_SignOut);
        tolua_function(tolua_S,"snapshotManager", lua_PluginSdkboxGooglePlayLua_PluginSdkboxGooglePlay_snapshotManager);
    tolua_endmodule(tolua_S);

    std::string typeName = typeid(sdkbox::PluginSdkboxGooglePlay).name();
    g_luaType[typeName] = "sdkbox.PluginSdkboxGooglePlay";
    g_typeCast["PluginSdkboxGooglePlay"] = "sdkbox.PluginSdkboxGooglePlay";
    return 1;
}

TOLUA_API int register_all_PluginSdkboxGooglePlayLua_helper(lua_State* tolua_S)
{
	tolua_module(tolua_S,"sdkbox",0);
	tolua_beginmodule(tolua_S,"sdkbox");

	lua_register_PluginSdkboxGooglePlayLua_PluginSdkboxGooglePlay(tolua_S);
	lua_register_PluginSdkboxGooglePlayLua_SnapshotManager(tolua_S);

	tolua_endmodule(tolua_S);

	lua_register_PluginSdkboxGooglePlayLua_SnapshotMetadata(tolua_S);

	return 1;
}

NativeLuaNotifierScheduler::NativeLuaNotifierScheduler(int id, const std::string& json)
	: _id(id)
	, _json(json)
{
}

void NativeLuaNotifierScheduler::schedule()
{
    retain();
    cocos2d::Director::getInstance()->getScheduler()->schedule(schedule_selector(NativeLuaNotifierScheduler::notity), this, 0, false);
    autorelease();
}

void NativeLuaNotifierScheduler::notity(float dt)
{
    lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    lua_getglobal(L, "__nativeNotify");
    lua_pushinteger(L, _id);
    lua_pushstring(L, _json.c_str());
    auto ret = lua_pcall(L, 2, 0, 0);
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    release();
}

void sdkbox::GPGWrapper::NotifyToScripting(int id, const std::string& str_json)
{
    NativeLuaNotifierScheduler* ns = new NativeLuaNotifierScheduler(id, str_json);
    ns->schedule();
}

