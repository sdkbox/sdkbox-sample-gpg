#include "SnapshotMetadataLuaHelper.h"
#include "PluginSdkboxGooglePlay/PluginSdkboxGooglePlay.h"
#include "PluginSdkboxGooglePlay/SnapshotManager.h"
#include "SDKBoxLuaHelper.h"

//int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_operator=(lua_State* tolua_S)
//{
//    int argc = 0;
//    gpg::SnapshotMetadata* cobj = nullptr;
//    bool ok  = true;
//
//#if COCOS2D_DEBUG >= 1
//    tolua_Error tolua_err;
//#endif
//
//
//#if COCOS2D_DEBUG >= 1
//    if (!tolua_isusertype(tolua_S,1,"gpg.SnapshotMetadata",0,&tolua_err)) goto tolua_lerror;
//#endif
//
//    cobj = (gpg::SnapshotMetadata*)tolua_tousertype(tolua_S,1,0);
//
//#if COCOS2D_DEBUG >= 1
//    if (!cobj)
//    {
//        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_operator='", nullptr);
//        return 0;
//    }
//#endif
//
//    argc = lua_gettop(tolua_S)-1;
//    if (argc == 1)
//    {
//        gpg::SnapshotMetadata arg0;
//
//        ok &= luaval_to_object<gpg::SnapshotMetadata>(tolua_S, 2, "gpg.SnapshotMetadata",&arg0);
//        if(!ok)
//        {
//            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_operator='", nullptr);
//            return 0;
//        }
//        gpg::SnapshotMetadata& ret = cobj->operator=(arg0);
//        object_to_luaval<gpg::SnapshotMetadata&>(tolua_S, "gpg.SnapshotMetadata",(gpg::SnapshotMetadata&)ret);
//        return 1;
//    }
//    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "gpg.SnapshotMetadata:operator=",argc, 1);
//    return 0;
//
//#if COCOS2D_DEBUG >= 1
//    tolua_lerror:
//    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_operator='.",&tolua_err);
//#endif
//
//    return 0;
//}

#if 0
int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Description(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotMetadata* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gpg.SnapshotMetadata",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gpg::SnapshotMetadata*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Description'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Description'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->Description();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "gpg.SnapshotMetadata:Description",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Description'.",&tolua_err);
#endif

    return 0;
}

int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_IsOpen(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotMetadata* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gpg.SnapshotMetadata",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gpg::SnapshotMetadata*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_IsOpen'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_IsOpen'", nullptr);
            return 0;
        }
        bool ret = cobj->IsOpen();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "gpg.SnapshotMetadata:IsOpen",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_IsOpen'.",&tolua_err);
#endif

    return 0;
}

int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_CoverImageURL(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotMetadata* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gpg.SnapshotMetadata",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gpg::SnapshotMetadata*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_CoverImageURL'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_CoverImageURL'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->CoverImageURL();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "gpg.SnapshotMetadata:CoverImageURL",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_CoverImageURL'.",&tolua_err);
#endif

    return 0;
}

int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_FileName(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotMetadata* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gpg.SnapshotMetadata",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gpg::SnapshotMetadata*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_FileName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_FileName'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->FileName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "gpg.SnapshotMetadata:FileName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_FileName'.",&tolua_err);
#endif

    return 0;
}

int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Valid(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotMetadata* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gpg.SnapshotMetadata",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gpg::SnapshotMetadata*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Valid'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Valid'", nullptr);
            return 0;
        }
        bool ret = cobj->Valid();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "gpg.SnapshotMetadata:Valid",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Valid'.",&tolua_err);
#endif

    return 0;
}

int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_PlayedTime(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotMetadata* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gpg.SnapshotMetadata",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gpg::SnapshotMetadata*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_PlayedTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_PlayedTime'", nullptr);
            return 0;
        }
        std::chrono::duration<long long, std::ratio<1, 1000> > ret = cobj->PlayedTime();
        #pragma warning NO CONVERSION FROM NATIVE FOR duration<long long, std::ratio<1, 1000> >;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "gpg.SnapshotMetadata:PlayedTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_PlayedTime'.",&tolua_err);
#endif

    return 0;
}

int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_LastModifiedTime(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotMetadata* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gpg.SnapshotMetadata",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gpg::SnapshotMetadata*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_LastModifiedTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_LastModifiedTime'", nullptr);
            return 0;
        }
        std::chrono::duration<long long, std::ratio<1, 1000> > ret = cobj->LastModifiedTime();
        #pragma warning NO CONVERSION FROM NATIVE FOR duration<long long, std::ratio<1, 1000> >;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "gpg.SnapshotMetadata:LastModifiedTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_LastModifiedTime'.",&tolua_err);
#endif

    return 0;
}

int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_ProgressValue(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotMetadata* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gpg.SnapshotMetadata",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gpg::SnapshotMetadata*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_ProgressValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_ProgressValue'", nullptr);
            return 0;
        }
        long long ret = cobj->ProgressValue();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "gpg.SnapshotMetadata:ProgressValue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_ProgressValue'.",&tolua_err);
#endif

    return 0;
}

int lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_constructor(lua_State* tolua_S)
{
    int argc = 0;
    gpg::SnapshotMetadata* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::shared_ptr<gpg::SnapshotMetadataImpl> arg0;
            ok &= luaval_to_object<std::shared_ptr<gpg::SnapshotMetadataImpl>>(tolua_S, 2, "std::shared_ptr<gpg::SnapshotMetadataImpl>",&arg0);

            if (!ok) { break; }
            cobj = new gpg::SnapshotMetadata(arg0);
            tolua_pushusertype(tolua_S,(void*)cobj,"gpg.SnapshotMetadata");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj = new gpg::SnapshotMetadata();
            tolua_pushusertype(tolua_S,(void*)cobj,"gpg.SnapshotMetadata");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            ?? arg0;
            #pragma warning NO CONVERSION TO NATIVE FOR ??
		ok = false;

            if (!ok) { break; }
            cobj = new gpg::SnapshotMetadata(arg0);
            tolua_pushusertype(tolua_S,(void*)cobj,"gpg.SnapshotMetadata");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "gpg.SnapshotMetadata:SnapshotMetadata",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_constructor'.",&tolua_err);
#endif

    return 0;
}
#endif // 0

int lua_register_PluginSdkboxGooglePlayLua_SnapshotMetadata(lua_State* tolua_S)
{
//    tolua_usertype(tolua_S,"gpg.SnapshotMetadata");
//    tolua_cclass(tolua_S,"SnapshotMetadata","gpg.SnapshotMetadata","",nullptr);
//
//    tolua_beginmodule(tolua_S,"SnapshotMetadata");
////        tolua_function(tolua_S,"new",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_constructor);
////        tolua_function(tolua_S,"operator=",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_operator=);
//        tolua_function(tolua_S,"Description",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Description);
//        tolua_function(tolua_S,"IsOpen",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_IsOpen);
//        tolua_function(tolua_S,"CoverImageURL",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_CoverImageURL);
//        tolua_function(tolua_S,"FileName",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_FileName);
//        tolua_function(tolua_S,"Valid",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_Valid);
//        tolua_function(tolua_S,"PlayedTime",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_PlayedTime);
//        tolua_function(tolua_S,"LastModifiedTime",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_LastModifiedTime);
//        tolua_function(tolua_S,"ProgressValue",lua_PluginSdkboxGooglePlayLua_SnapshotMetadata_ProgressValue);
//    tolua_endmodule(tolua_S);
//    std::string typeName = typeid(gpg::SnapshotMetadata).name();
//    g_luaType[typeName] = "gpg.SnapshotMetadata";
//    g_typeCast["SnapshotMetadata"] = "gpg.SnapshotMetadata";
    return 1;
}
