#include "PluginSdkboxGooglePlayJS.hpp"
#include "PluginSdkboxGooglePlay/SdkboxGooglePlayWrappedObjects.h"
#include "SDKBoxJSHelper.h"
#include "sdkbox/Sdkbox.h"

#if defined(SDKBOX_COCOS_CREATOR)
    #define SDKBOX_COCOS_JSB_VERSION 2
#elif COCOS2D_VERSION >= 0x00031000
    #define SDKBOX_COCOS_JSB_VERSION 2
#else
    #define SDKBOX_COCOS_JSB_VERSION 1
#endif

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

#if (SDKBOX_COCOS_JSB_VERSION >= 2)
        JS::RootedObject proto(cx, typeClass->proto.ref());
        JS::RootedObject parent(cx, typeClass->parentProto.ref());
#else
        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
#endif
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));

        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        AddObjectRoot(cx, &pp->obj);
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
#else
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        JS_AddObjectRoot(cx, &pp->obj);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    vp.set(BOOLEAN_TO_JSVAL(true));
    return true;
}
#endif
#elif defined(JS_VERSION)
template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    TypeTest<T> t;
    T* cobj = new T();
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    assert(p);
    JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
    js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

    return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return JS_FALSE;
}
#endif
JSClass  *jsb_sdkbox_GPGWrapper_class;
JSObject *jsb_sdkbox_GPGWrapper_prototype;

#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_NotifyToScripting(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginSdkboxGooglePlayJS_GPGWrapper_NotifyToScripting : Error processing arguments");
        sdkbox::GPGWrapper::NotifyToScripting(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGWrapper_NotifyToScripting : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_NotifyToScripting(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGWrapper::NotifyToScripting(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_IsAuthorized(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        bool ret = sdkbox::GPGWrapper::IsAuthorized();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGWrapper_IsAuthorized : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_IsAuthorized(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        bool ret = sdkbox::GPGWrapper::IsAuthorized();
        jsval jsret;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_CreateGameServices(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginSdkboxGooglePlayJS_GPGWrapper_CreateGameServices : Error processing arguments");
        sdkbox::GPGWrapper::CreateGameServices(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGWrapper_CreateGameServices : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_CreateGameServices(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGWrapper::CreateGameServices(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_StartAuthorizationUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::GPGWrapper::StartAuthorizationUI();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGWrapper_StartAuthorizationUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_StartAuthorizationUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::GPGWrapper::StartAuthorizationUI();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_SignOut(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::GPGWrapper::SignOut();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGWrapper_SignOut : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_SignOut(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::GPGWrapper::SignOut();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginSdkboxGooglePlayJS_GPGWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGWrapper)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;

#if (SDKBOX_COCOS_JSB_VERSION >= 2)
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
#else
    jsproxy = jsb_get_js_proxy(obj);
#endif

    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        sdkbox::GPGWrapper *nobj = static_cast<sdkbox::GPGWrapper *>(nproxy->ptr);
        if (nobj)
            delete nobj;

        jsb_remove_proxy(nproxy, jsproxy);
    }
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginSdkboxGooglePlayJS_GPGWrapper(JSContext *cx, JS::HandleObject global) {
    jsb_sdkbox_GPGWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGWrapper_class->name = "GPGWrapper";
    jsb_sdkbox_GPGWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGWrapper_class->finalize = js_PluginSdkboxGooglePlayJS_GPGWrapper_finalize;
    jsb_sdkbox_GPGWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("NotifyToScripting", js_PluginSdkboxGooglePlayJS_GPGWrapper_NotifyToScripting, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("IsAuthorized", js_PluginSdkboxGooglePlayJS_GPGWrapper_IsAuthorized, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateGameServices", js_PluginSdkboxGooglePlayJS_GPGWrapper_CreateGameServices, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StartAuthorizationUI", js_PluginSdkboxGooglePlayJS_GPGWrapper_StartAuthorizationUI, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SignOut", js_PluginSdkboxGooglePlayJS_GPGWrapper_SignOut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGWrapper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_sdkbox_GPGWrapper_class,
        dummy_constructor<sdkbox::GPGWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
    JS::RootedObject proto(cx, jsb_sdkbox_GPGWrapper_prototype);
    jsb_register_class<sdkbox::GPGWrapper>(cx, jsb_sdkbox_GPGWrapper_class, proto, JS::NullPtr());
#else
    TypeTest<sdkbox::GPGWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGWrapper_class;
        p->proto = jsb_sdkbox_GPGWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif
}
#else
void js_register_PluginSdkboxGooglePlayJS_GPGWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGWrapper_class->name = "GPGWrapper";
    jsb_sdkbox_GPGWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGWrapper_class->finalize = js_PluginSdkboxGooglePlayJS_GPGWrapper_finalize;
    jsb_sdkbox_GPGWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("NotifyToScripting", js_PluginSdkboxGooglePlayJS_GPGWrapper_NotifyToScripting, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("IsAuthorized", js_PluginSdkboxGooglePlayJS_GPGWrapper_IsAuthorized, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateGameServices", js_PluginSdkboxGooglePlayJS_GPGWrapper_CreateGameServices, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StartAuthorizationUI", js_PluginSdkboxGooglePlayJS_GPGWrapper_StartAuthorizationUI, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SignOut", js_PluginSdkboxGooglePlayJS_GPGWrapper_SignOut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGWrapper_class,
        dummy_constructor<sdkbox::GPGWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGWrapper_class;
        p->proto = jsb_sdkbox_GPGWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginSdkboxGooglePlayJS_GPGWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGWrapper_class->name = "GPGWrapper";
    jsb_sdkbox_GPGWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGWrapper_class->finalize = js_PluginSdkboxGooglePlayJS_GPGWrapper_finalize;
    jsb_sdkbox_GPGWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("NotifyToScripting", js_PluginSdkboxGooglePlayJS_GPGWrapper_NotifyToScripting, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("IsAuthorized", js_PluginSdkboxGooglePlayJS_GPGWrapper_IsAuthorized, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateGameServices", js_PluginSdkboxGooglePlayJS_GPGWrapper_CreateGameServices, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StartAuthorizationUI", js_PluginSdkboxGooglePlayJS_GPGWrapper_StartAuthorizationUI, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SignOut", js_PluginSdkboxGooglePlayJS_GPGWrapper_SignOut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGWrapper_class,
        dummy_constructor<sdkbox::GPGWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGWrapper_class;
        p->proto = jsb_sdkbox_GPGWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGLocalPlayerWrapper_class;
JSObject *jsb_sdkbox_GPGLocalPlayerWrapper_prototype;

#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentLevel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::CurrentLevel();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentLevel : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentLevel(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::CurrentLevel();
        jsval jsret;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Name(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::Name();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Name : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Name(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::Name();
        jsval jsret;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_AvatarUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_AvatarUrl : Error processing arguments");
        std::string ret = sdkbox::GPGLocalPlayerWrapper::AvatarUrl(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_AvatarUrl : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_AvatarUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        std::string ret = sdkbox::GPGLocalPlayerWrapper::AvatarUrl(arg0);
        jsval jsret;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_LastLevelUpTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        long long ret = sdkbox::GPGLocalPlayerWrapper::LastLevelUpTime();
        jsval jsret = JSVAL_NULL;
        jsret = long_long_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_LastLevelUpTime : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_LastLevelUpTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        long long ret = sdkbox::GPGLocalPlayerWrapper::LastLevelUpTime();
        jsval jsret;
        jsret = long_long_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Title(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::Title();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Title : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Title(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::Title();
        jsval jsret;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentXP(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        long long ret = sdkbox::GPGLocalPlayerWrapper::CurrentXP();
        jsval jsret = JSVAL_NULL;
        jsret = long_long_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentXP : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentXP(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        long long ret = sdkbox::GPGLocalPlayerWrapper::CurrentXP();
        jsval jsret;
        jsret = long_long_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Fetch : Error processing arguments");
        sdkbox::GPGLocalPlayerWrapper::Fetch(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Fetch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLocalPlayerWrapper::Fetch(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_HasLevelInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        bool ret = sdkbox::GPGLocalPlayerWrapper::HasLevelInfo();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_HasLevelInfo : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_HasLevelInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        bool ret = sdkbox::GPGLocalPlayerWrapper::HasLevelInfo();
        jsval jsret;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_NextLevel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::NextLevel();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_NextLevel : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_NextLevel(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::NextLevel();
        jsval jsret;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Id(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::Id();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Id : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Id(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::GPGLocalPlayerWrapper::Id();
        jsval jsret;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGLocalPlayerWrapper)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;

#if (SDKBOX_COCOS_JSB_VERSION >= 2)
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
#else
    jsproxy = jsb_get_js_proxy(obj);
#endif

    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        sdkbox::GPGLocalPlayerWrapper *nobj = static_cast<sdkbox::GPGLocalPlayerWrapper *>(nproxy->ptr);
        if (nobj)
            delete nobj;

        jsb_remove_proxy(nproxy, jsproxy);
    }
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper(JSContext *cx, JS::HandleObject global) {
    jsb_sdkbox_GPGLocalPlayerWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGLocalPlayerWrapper_class->name = "GPGLocalPlayerWrapper";
    jsb_sdkbox_GPGLocalPlayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->finalize = js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_finalize;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("CurrentLevel", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentLevel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Name", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Name, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AvatarUrl", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_AvatarUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LastLevelUpTime", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_LastLevelUpTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Title", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Title, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CurrentXP", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentXP, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Fetch, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("HasLevelInfo", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_HasLevelInfo, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("NextLevel", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_NextLevel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Id", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Id, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGLocalPlayerWrapper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_sdkbox_GPGLocalPlayerWrapper_class,
        dummy_constructor<sdkbox::GPGLocalPlayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGLocalPlayerWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
    JS::RootedObject proto(cx, jsb_sdkbox_GPGLocalPlayerWrapper_prototype);
    jsb_register_class<sdkbox::GPGLocalPlayerWrapper>(cx, jsb_sdkbox_GPGLocalPlayerWrapper_class, proto, JS::NullPtr());
#else
    TypeTest<sdkbox::GPGLocalPlayerWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGLocalPlayerWrapper_class;
        p->proto = jsb_sdkbox_GPGLocalPlayerWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif
}
#else
void js_register_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGLocalPlayerWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGLocalPlayerWrapper_class->name = "GPGLocalPlayerWrapper";
    jsb_sdkbox_GPGLocalPlayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->finalize = js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_finalize;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("CurrentLevel", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentLevel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Name", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Name, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AvatarUrl", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_AvatarUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LastLevelUpTime", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_LastLevelUpTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Title", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Title, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CurrentXP", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentXP, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Fetch, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("HasLevelInfo", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_HasLevelInfo, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("NextLevel", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_NextLevel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Id", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Id, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGLocalPlayerWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGLocalPlayerWrapper_class,
        dummy_constructor<sdkbox::GPGLocalPlayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGLocalPlayerWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGLocalPlayerWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGLocalPlayerWrapper_class;
        p->proto = jsb_sdkbox_GPGLocalPlayerWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGLocalPlayerWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGLocalPlayerWrapper_class->name = "GPGLocalPlayerWrapper";
    jsb_sdkbox_GPGLocalPlayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->finalize = js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_finalize;
    jsb_sdkbox_GPGLocalPlayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("CurrentLevel", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentLevel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Name", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Name, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AvatarUrl", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_AvatarUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LastLevelUpTime", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_LastLevelUpTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Title", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Title, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CurrentXP", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentXP, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Fetch, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("HasLevelInfo", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_HasLevelInfo, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("NextLevel", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_NextLevel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Id", js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Id, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGLocalPlayerWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGLocalPlayerWrapper_class,
        dummy_constructor<sdkbox::GPGLocalPlayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGLocalPlayerWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGLocalPlayerWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGLocalPlayerWrapper_class;
        p->proto = jsb_sdkbox_GPGLocalPlayerWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGSnapshotWrapper_class;
JSObject *jsb_sdkbox_GPGSnapshotWrapper_prototype;

#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Load(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        int arg0;
        std::string arg1;
        int arg2;
        int arg3;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Load : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::Load(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Load : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Load(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 4) {
        int arg0;
        std::string arg1;
        int arg2;
        int arg3;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGSnapshotWrapper::Load(arg0, arg1, arg2, arg3);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_ShowSelectUIOperation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_ShowSelectUIOperation : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::ShowSelectUIOperation(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_ShowSelectUIOperation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_ShowSelectUIOperation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGSnapshotWrapper::ShowSelectUIOperation(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Save(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Save : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::Save(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Save : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Save(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGSnapshotWrapper::Save(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Delete(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Delete : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::Delete(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Delete : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Delete(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGSnapshotWrapper::Delete(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_FetchAll : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::FetchAll(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_FetchAll : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGSnapshotWrapper::FetchAll(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGSnapshotWrapper)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;

#if (SDKBOX_COCOS_JSB_VERSION >= 2)
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
#else
    jsproxy = jsb_get_js_proxy(obj);
#endif

    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        sdkbox::GPGSnapshotWrapper *nobj = static_cast<sdkbox::GPGSnapshotWrapper *>(nproxy->ptr);
        if (nobj)
            delete nobj;

        jsb_remove_proxy(nproxy, jsproxy);
    }
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper(JSContext *cx, JS::HandleObject global) {
    jsb_sdkbox_GPGSnapshotWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGSnapshotWrapper_class->name = "GPGSnapshotWrapper";
    jsb_sdkbox_GPGSnapshotWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->finalize = js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_finalize;
    jsb_sdkbox_GPGSnapshotWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Load", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Load, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowSelectUIOperation", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_ShowSelectUIOperation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Save", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Save, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Delete", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Delete, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchAll", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGSnapshotWrapper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_sdkbox_GPGSnapshotWrapper_class,
        dummy_constructor<sdkbox::GPGSnapshotWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGSnapshotWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
    JS::RootedObject proto(cx, jsb_sdkbox_GPGSnapshotWrapper_prototype);
    jsb_register_class<sdkbox::GPGSnapshotWrapper>(cx, jsb_sdkbox_GPGSnapshotWrapper_class, proto, JS::NullPtr());
#else
    TypeTest<sdkbox::GPGSnapshotWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGSnapshotWrapper_class;
        p->proto = jsb_sdkbox_GPGSnapshotWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif
}
#else
void js_register_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGSnapshotWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGSnapshotWrapper_class->name = "GPGSnapshotWrapper";
    jsb_sdkbox_GPGSnapshotWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->finalize = js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_finalize;
    jsb_sdkbox_GPGSnapshotWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Load", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Load, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowSelectUIOperation", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_ShowSelectUIOperation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Save", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Save, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Delete", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Delete, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchAll", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGSnapshotWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGSnapshotWrapper_class,
        dummy_constructor<sdkbox::GPGSnapshotWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGSnapshotWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGSnapshotWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGSnapshotWrapper_class;
        p->proto = jsb_sdkbox_GPGSnapshotWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGSnapshotWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGSnapshotWrapper_class->name = "GPGSnapshotWrapper";
    jsb_sdkbox_GPGSnapshotWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->finalize = js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_finalize;
    jsb_sdkbox_GPGSnapshotWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Load", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Load, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowSelectUIOperation", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_ShowSelectUIOperation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Save", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Save, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Delete", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Delete, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchAll", js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGSnapshotWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGSnapshotWrapper_class,
        dummy_constructor<sdkbox::GPGSnapshotWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGSnapshotWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGSnapshotWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGSnapshotWrapper_class;
        p->proto = jsb_sdkbox_GPGSnapshotWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "_gpg", &ns);

    js_register_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper(cx, ns);
    js_register_PluginSdkboxGooglePlayJS_GPGWrapper(cx, ns);
    js_register_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper(cx, ns);

    sdkbox::setProjectType("js");
}
#else
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "_gpg", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "_gpg", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper(cx, obj);
    js_register_PluginSdkboxGooglePlayJS_GPGWrapper(cx, obj);
    js_register_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper(cx, obj);

    sdkbox::setProjectType("js");
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    jsval nsval;
    JSObject *ns;
    JS_GetProperty(cx, obj, "_gpg", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "_gpg", &nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper(cx, obj);
    js_register_PluginSdkboxGooglePlayJS_GPGWrapper(cx, obj);
    js_register_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper(cx, obj);

    sdkbox::setProjectType("js");
}
#endif