#include "PluginGPGJS.hpp"
#include "PluginGPG/SdkboxGooglePlayWrappedObjects.h"
#include "SDKBoxJSHelper.h"
#include "sdkbox/Sdkbox.h"


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 52
#elif MOZJS_MAJOR_VERSION >= 33
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS_ReportErrorUTF8(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp) {
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
JSClass  *jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGRealTimeMultiplayerWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::CreateRealTimeRoom(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::CreateRealTimeRoom(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_LeaveRoom(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_LeaveRoom : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::LeaveRoom(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_LeaveRoom : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_LeaveRoom(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::LeaveRoom(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessage(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessage : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::SendUnreliableMessage(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessage : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessage(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::SendUnreliableMessage(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DismissInvitation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DismissInvitation : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::DismissInvitation(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DismissInvitation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DismissInvitation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::DismissInvitation(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DeclineInvitation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DeclineInvitation : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::DeclineInvitation(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DeclineInvitation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DeclineInvitation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::DeclineInvitation(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendReliableMessage(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        int arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendReliableMessage : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::SendReliableMessage(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendReliableMessage : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendReliableMessage(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 4) {
        int arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        ok &= jsval_to_std_string(cx, argv[3], &arg3);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::SendReliableMessage(arg0, arg1, arg2, arg3);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_AcceptInvitation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_AcceptInvitation : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::AcceptInvitation(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_AcceptInvitation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_AcceptInvitation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::AcceptInvitation(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_FetchInvitations(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_FetchInvitations : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::FetchInvitations(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_FetchInvitations : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_FetchInvitations(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::FetchInvitations(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessageToOthers(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessageToOthers : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::SendUnreliableMessageToOthers(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessageToOthers : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessageToOthers(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::SendUnreliableMessageToOthers(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_ShowRoomInboxUI(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_ShowRoomInboxUI : Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::ShowRoomInboxUI(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_ShowRoomInboxUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_ShowRoomInboxUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGRealTimeMultiplayerWrapper::ShowRoomInboxUI(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGRealTimeMultiplayerWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGRealTimeMultiplayerWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->finalize = js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_finalize;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("CreateRealTimeRoom", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LeaveRoom", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_LeaveRoom, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendUnreliableMessage", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DismissInvitation", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DismissInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DeclineInvitation", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DeclineInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendReliableMessage", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendReliableMessage, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AcceptInvitation", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_AcceptInvitation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchInvitations", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_FetchInvitations, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendUnreliableMessageToOthers", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessageToOthers, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowRoomInboxUI", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_ShowRoomInboxUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class,
        dummy_constructor<sdkbox::GPGRealTimeMultiplayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGRealTimeMultiplayerWrapper>(cx, jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGRealTimeMultiplayerWrapper>(cx, jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGRealTimeMultiplayerWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGRealTimeMultiplayerWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->name = "GPGRealTimeMultiplayerWrapper";
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->finalize = js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_finalize;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("CreateRealTimeRoom", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LeaveRoom", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_LeaveRoom, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendUnreliableMessage", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DismissInvitation", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DismissInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DeclineInvitation", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DeclineInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendReliableMessage", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendReliableMessage, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AcceptInvitation", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_AcceptInvitation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchInvitations", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_FetchInvitations, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendUnreliableMessageToOthers", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessageToOthers, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowRoomInboxUI", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_ShowRoomInboxUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class,
        dummy_constructor<sdkbox::GPGRealTimeMultiplayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGRealTimeMultiplayerWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGRealTimeMultiplayerWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class;
        p->proto = jsb_sdkbox_GPGRealTimeMultiplayerWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->name = "GPGRealTimeMultiplayerWrapper";
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->finalize = js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_finalize;
    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("CreateRealTimeRoom", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LeaveRoom", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_LeaveRoom, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendUnreliableMessage", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DismissInvitation", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DismissInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DeclineInvitation", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DeclineInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendReliableMessage", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendReliableMessage, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AcceptInvitation", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_AcceptInvitation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchInvitations", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_FetchInvitations, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendUnreliableMessageToOthers", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessageToOthers, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowRoomInboxUI", js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_ShowRoomInboxUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGRealTimeMultiplayerWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class,
        dummy_constructor<sdkbox::GPGRealTimeMultiplayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGRealTimeMultiplayerWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGRealTimeMultiplayerWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class;
        p->proto = jsb_sdkbox_GPGRealTimeMultiplayerWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowPlayerSelectUI(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        int arg0;
        int arg1;
        int arg2;
        bool arg3;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        ok &= sdkbox::js_to_bool(cx, args.get(3), (bool *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowPlayerSelectUI : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::ShowPlayerSelectUI(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowPlayerSelectUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowPlayerSelectUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 4) {
        int arg0;
        int arg1;
        int arg2;
        bool arg3;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        ok &= sdkbox::js_to_bool(cx, argv[3], (bool *)&arg3);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::ShowPlayerSelectUI(arg0, arg1, arg2, arg3);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CancelMatch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CancelMatch : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::CancelMatch(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CancelMatch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CancelMatch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::CancelMatch(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissMatch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissMatch : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::DismissMatch(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissMatch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissMatch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::DismissMatch(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowMatchInboxUI(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowMatchInboxUI : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::ShowMatchInboxUI(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowMatchInboxUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowMatchInboxUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::ShowMatchInboxUI(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_SynchronizeData(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::GPGTurnBasedMultiplayerWrapper::SynchronizeData();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_SynchronizeData : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_SynchronizeData(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::GPGTurnBasedMultiplayerWrapper::SynchronizeData();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateTurnBasedMatch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateTurnBasedMatch : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::CreateTurnBasedMatch(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateTurnBasedMatch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateTurnBasedMatch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::CreateTurnBasedMatch(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissInvitation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissInvitation : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::DismissInvitation(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissInvitation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissInvitation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::DismissInvitation(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatch : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::FetchMatch(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::FetchMatch(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DeclineInvitation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DeclineInvitation : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::DeclineInvitation(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DeclineInvitation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DeclineInvitation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::DeclineInvitation(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ConfirmPendingCompletion(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ConfirmPendingCompletion : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::ConfirmPendingCompletion(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ConfirmPendingCompletion : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ConfirmPendingCompletion(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::ConfirmPendingCompletion(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FinishMatchDuringMyTurn(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        int arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FinishMatchDuringMyTurn : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::FinishMatchDuringMyTurn(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FinishMatchDuringMyTurn : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FinishMatchDuringMyTurn(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 4) {
        int arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        ok &= jsval_to_std_string(cx, argv[3], &arg3);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::FinishMatchDuringMyTurn(arg0, arg1, arg2, arg3);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_Rematch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_Rematch : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::Rematch(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_Rematch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_Rematch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::Rematch(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringTheirTurn(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringTheirTurn : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::LeaveMatchDuringTheirTurn(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringTheirTurn : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringTheirTurn(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::LeaveMatchDuringTheirTurn(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateParticipantResult(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        int arg2;
        int arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateParticipantResult : Error processing arguments");
        std::string ret = sdkbox::GPGTurnBasedMultiplayerWrapper::CreateParticipantResult(arg0, arg1, arg2, arg3);
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateParticipantResult : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateParticipantResult(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        int arg2;
        int arg3;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        std::string ret = sdkbox::GPGTurnBasedMultiplayerWrapper::CreateParticipantResult(arg0, arg1, arg2, arg3);
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_TakeMyTurn(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 5) {
        int arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        std::string arg4;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_TakeMyTurn : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::TakeMyTurn(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_TakeMyTurn : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_TakeMyTurn(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 5) {
        int arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        std::string arg4;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        ok &= jsval_to_std_string(cx, argv[3], &arg3);
        ok &= jsval_to_std_string(cx, argv[4], &arg4);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::TakeMyTurn(arg0, arg1, arg2, arg3, arg4);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatches(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatches : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::FetchMatches(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatches : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatches(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::FetchMatches(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringMyTurn(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        int arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringMyTurn : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::LeaveMatchDuringMyTurn(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringMyTurn : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringMyTurn(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        int arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::LeaveMatchDuringMyTurn(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_AcceptInvitation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_AcceptInvitation : Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::AcceptInvitation(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_AcceptInvitation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_AcceptInvitation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGTurnBasedMultiplayerWrapper::AcceptInvitation(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGTurnBasedMultiplayerWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGTurnBasedMultiplayerWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->finalize = js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_finalize;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("ShowPlayerSelectUI", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowPlayerSelectUI, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CancelMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CancelMatch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DismissMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissMatch, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowMatchInboxUI", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowMatchInboxUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SynchronizeData", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_SynchronizeData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateTurnBasedMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateTurnBasedMatch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DismissInvitation", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DeclineInvitation", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DeclineInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ConfirmPendingCompletion", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ConfirmPendingCompletion, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FinishMatchDuringMyTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FinishMatchDuringMyTurn, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Rematch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_Rematch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LeaveMatchDuringTheirTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringTheirTurn, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateParticipantResult", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateParticipantResult, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("TakeMyTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_TakeMyTurn, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchMatches", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatches, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LeaveMatchDuringMyTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringMyTurn, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AcceptInvitation", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_AcceptInvitation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class,
        dummy_constructor<sdkbox::GPGTurnBasedMultiplayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGTurnBasedMultiplayerWrapper>(cx, jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGTurnBasedMultiplayerWrapper>(cx, jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGTurnBasedMultiplayerWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGTurnBasedMultiplayerWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->name = "GPGTurnBasedMultiplayerWrapper";
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->finalize = js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_finalize;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("ShowPlayerSelectUI", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowPlayerSelectUI, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CancelMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CancelMatch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DismissMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissMatch, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowMatchInboxUI", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowMatchInboxUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SynchronizeData", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_SynchronizeData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateTurnBasedMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateTurnBasedMatch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DismissInvitation", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DeclineInvitation", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DeclineInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ConfirmPendingCompletion", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ConfirmPendingCompletion, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FinishMatchDuringMyTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FinishMatchDuringMyTurn, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Rematch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_Rematch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LeaveMatchDuringTheirTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringTheirTurn, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateParticipantResult", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateParticipantResult, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("TakeMyTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_TakeMyTurn, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchMatches", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatches, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LeaveMatchDuringMyTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringMyTurn, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AcceptInvitation", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_AcceptInvitation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class,
        dummy_constructor<sdkbox::GPGTurnBasedMultiplayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGTurnBasedMultiplayerWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGTurnBasedMultiplayerWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class;
        p->proto = jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->name = "GPGTurnBasedMultiplayerWrapper";
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->finalize = js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_finalize;
    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("ShowPlayerSelectUI", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowPlayerSelectUI, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CancelMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CancelMatch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DismissMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissMatch, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowMatchInboxUI", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowMatchInboxUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SynchronizeData", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_SynchronizeData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateTurnBasedMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateTurnBasedMatch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DismissInvitation", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchMatch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DeclineInvitation", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DeclineInvitation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ConfirmPendingCompletion", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ConfirmPendingCompletion, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FinishMatchDuringMyTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FinishMatchDuringMyTurn, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Rematch", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_Rematch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LeaveMatchDuringTheirTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringTheirTurn, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateParticipantResult", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateParticipantResult, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("TakeMyTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_TakeMyTurn, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchMatches", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatches, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LeaveMatchDuringMyTurn", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringMyTurn, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AcceptInvitation", js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_AcceptInvitation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class,
        dummy_constructor<sdkbox::GPGTurnBasedMultiplayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGTurnBasedMultiplayerWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGTurnBasedMultiplayerWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class;
        p->proto = jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGWrapper_StartAuthorizationUI(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::GPGWrapper::StartAuthorizationUI();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGWrapper_StartAuthorizationUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_StartAuthorizationUI(JSContext *cx, uint32_t argc, jsval *vp)
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
bool js_PluginGPGJS_GPGWrapper_getAuthCode(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::GPGWrapper::getAuthCode();
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGWrapper_getAuthCode : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_getAuthCode(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::GPGWrapper::getAuthCode();
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGWrapper_IsAuthorized(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        bool ret = sdkbox::GPGWrapper::IsAuthorized();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGWrapper_IsAuthorized : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_IsAuthorized(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        bool ret = sdkbox::GPGWrapper::IsAuthorized();
        jsval jsret;
        jsret = JS::BooleanValue(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGWrapper_NotifyToScripting(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGWrapper_NotifyToScripting : Error processing arguments");
        sdkbox::GPGWrapper::NotifyToScripting(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGWrapper_NotifyToScripting : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_NotifyToScripting(JSContext *cx, uint32_t argc, jsval *vp)
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
bool js_PluginGPGJS_GPGWrapper_CreateGameServices(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGWrapper_CreateGameServices : Error processing arguments");
        sdkbox::GPGWrapper::CreateGameServices(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGWrapper_CreateGameServices : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_CreateGameServices(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGWrapper::CreateGameServices(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGWrapper_SignOut(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::GPGWrapper::SignOut();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGWrapper_SignOut : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_SignOut(JSContext *cx, uint32_t argc, jsval *vp)
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


void js_PluginGPGJS_GPGWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGWrapper_class->finalize = js_PluginGPGJS_GPGWrapper_finalize;
    jsb_sdkbox_GPGWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("StartAuthorizationUI", js_PluginGPGJS_GPGWrapper_StartAuthorizationUI, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAuthCode", js_PluginGPGJS_GPGWrapper_getAuthCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("IsAuthorized", js_PluginGPGJS_GPGWrapper_IsAuthorized, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("NotifyToScripting", js_PluginGPGJS_GPGWrapper_NotifyToScripting, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateGameServices", js_PluginGPGJS_GPGWrapper_CreateGameServices, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SignOut", js_PluginGPGJS_GPGWrapper_SignOut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGWrapper_class,
        dummy_constructor<sdkbox::GPGWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGWrapper>(cx, jsb_sdkbox_GPGWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGWrapper>(cx, jsb_sdkbox_GPGWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGWrapper_class->name = "GPGWrapper";
    jsb_sdkbox_GPGWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGWrapper_class->finalize = js_PluginGPGJS_GPGWrapper_finalize;
    jsb_sdkbox_GPGWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("StartAuthorizationUI", js_PluginGPGJS_GPGWrapper_StartAuthorizationUI, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAuthCode", js_PluginGPGJS_GPGWrapper_getAuthCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("IsAuthorized", js_PluginGPGJS_GPGWrapper_IsAuthorized, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("NotifyToScripting", js_PluginGPGJS_GPGWrapper_NotifyToScripting, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateGameServices", js_PluginGPGJS_GPGWrapper_CreateGameServices, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SignOut", js_PluginGPGJS_GPGWrapper_SignOut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
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
void js_register_PluginGPGJS_GPGWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGWrapper_class->name = "GPGWrapper";
    jsb_sdkbox_GPGWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGWrapper_class->finalize = js_PluginGPGJS_GPGWrapper_finalize;
    jsb_sdkbox_GPGWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("StartAuthorizationUI", js_PluginGPGJS_GPGWrapper_StartAuthorizationUI, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAuthCode", js_PluginGPGJS_GPGWrapper_getAuthCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("IsAuthorized", js_PluginGPGJS_GPGWrapper_IsAuthorized, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("NotifyToScripting", js_PluginGPGJS_GPGWrapper_NotifyToScripting, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CreateGameServices", js_PluginGPGJS_GPGWrapper_CreateGameServices, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SignOut", js_PluginGPGJS_GPGWrapper_SignOut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
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
JSClass  *jsb_sdkbox_GPGPlayerWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGPlayerWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyConnected(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyConnected : Error processing arguments");
        sdkbox::GPGPlayerWrapper::FetchRecentlyConnected(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyConnected : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyConnected(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGPlayerWrapper::FetchRecentlyConnected(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyInvitable(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyInvitable : Error processing arguments");
        sdkbox::GPGPlayerWrapper::FetchRecentlyInvitable(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyInvitable : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyInvitable(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGPlayerWrapper::FetchRecentlyInvitable(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_Fetch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        int arg0;
        int arg1;
        std::string arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGPlayerWrapper_Fetch : Error processing arguments");
        sdkbox::GPGPlayerWrapper::Fetch(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGPlayerWrapper_Fetch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        int arg0;
        int arg1;
        std::string arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGPlayerWrapper::Fetch(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyPlayed(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyPlayed : Error processing arguments");
        sdkbox::GPGPlayerWrapper::FetchRecentlyPlayed(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyPlayed : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyPlayed(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGPlayerWrapper::FetchRecentlyPlayed(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_FetchSelf(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGPlayerWrapper_FetchSelf : Error processing arguments");
        sdkbox::GPGPlayerWrapper::FetchSelf(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGPlayerWrapper_FetchSelf : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_FetchSelf(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGPlayerWrapper::FetchSelf(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGPGJS_GPGPlayerWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGPlayerWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGPlayerWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGPlayerWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGPlayerWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGPlayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGPlayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGPlayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGPlayerWrapper_class->finalize = js_PluginGPGJS_GPGPlayerWrapper_finalize;
    jsb_sdkbox_GPGPlayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchRecentlyConnected", js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyConnected, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchRecentlyInvitable", js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyInvitable, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGPlayerWrapper_Fetch, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchRecentlyPlayed", js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyPlayed, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchSelf", js_PluginGPGJS_GPGPlayerWrapper_FetchSelf, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGPlayerWrapper_class,
        dummy_constructor<sdkbox::GPGPlayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGPlayerWrapper>(cx, jsb_sdkbox_GPGPlayerWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGPlayerWrapper>(cx, jsb_sdkbox_GPGPlayerWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGPlayerWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGPlayerWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGPlayerWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGPlayerWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGPlayerWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGPlayerWrapper_class->name = "GPGPlayerWrapper";
    jsb_sdkbox_GPGPlayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGPlayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGPlayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGPlayerWrapper_class->finalize = js_PluginGPGJS_GPGPlayerWrapper_finalize;
    jsb_sdkbox_GPGPlayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchRecentlyConnected", js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyConnected, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchRecentlyInvitable", js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyInvitable, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGPlayerWrapper_Fetch, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchRecentlyPlayed", js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyPlayed, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchSelf", js_PluginGPGJS_GPGPlayerWrapper_FetchSelf, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGPlayerWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGPlayerWrapper_class,
        dummy_constructor<sdkbox::GPGPlayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGPlayerWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGPlayerWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGPlayerWrapper_class;
        p->proto = jsb_sdkbox_GPGPlayerWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGPGJS_GPGPlayerWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGPlayerWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGPlayerWrapper_class->name = "GPGPlayerWrapper";
    jsb_sdkbox_GPGPlayerWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGPlayerWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGPlayerWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGPlayerWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGPlayerWrapper_class->finalize = js_PluginGPGJS_GPGPlayerWrapper_finalize;
    jsb_sdkbox_GPGPlayerWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchRecentlyConnected", js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyConnected, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchRecentlyInvitable", js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyInvitable, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGPlayerWrapper_Fetch, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchRecentlyPlayed", js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyPlayed, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchSelf", js_PluginGPGJS_GPGPlayerWrapper_FetchSelf, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGPlayerWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGPlayerWrapper_class,
        dummy_constructor<sdkbox::GPGPlayerWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGPlayerWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGPlayerWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGPlayerWrapper_class;
        p->proto = jsb_sdkbox_GPGPlayerWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGSnapshotWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGSnapshotWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGSnapshotWrapper_Load(JSContext *cx, uint32_t argc, JS::Value *vp)
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
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGSnapshotWrapper_Load : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::Load(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGSnapshotWrapper_Load : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_Load(JSContext *cx, uint32_t argc, jsval *vp)
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
bool js_PluginGPGJS_GPGSnapshotWrapper_ShowSelectUIOperation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGSnapshotWrapper_ShowSelectUIOperation : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::ShowSelectUIOperation(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGSnapshotWrapper_ShowSelectUIOperation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_ShowSelectUIOperation(JSContext *cx, uint32_t argc, jsval *vp)
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
bool js_PluginGPGJS_GPGSnapshotWrapper_Save(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGSnapshotWrapper_Save : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::Save(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGSnapshotWrapper_Save : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_Save(JSContext *cx, uint32_t argc, jsval *vp)
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
bool js_PluginGPGJS_GPGSnapshotWrapper_Delete(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGSnapshotWrapper_Delete : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::Delete(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGSnapshotWrapper_Delete : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_Delete(JSContext *cx, uint32_t argc, jsval *vp)
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
bool js_PluginGPGJS_GPGSnapshotWrapper_FetchAll(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGSnapshotWrapper_FetchAll : Error processing arguments");
        sdkbox::GPGSnapshotWrapper::FetchAll(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGSnapshotWrapper_FetchAll : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp)
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


void js_PluginGPGJS_GPGSnapshotWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGSnapshotWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGSnapshotWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGSnapshotWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGSnapshotWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGSnapshotWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->finalize = js_PluginGPGJS_GPGSnapshotWrapper_finalize;
    jsb_sdkbox_GPGSnapshotWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Load", js_PluginGPGJS_GPGSnapshotWrapper_Load, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowSelectUIOperation", js_PluginGPGJS_GPGSnapshotWrapper_ShowSelectUIOperation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Save", js_PluginGPGJS_GPGSnapshotWrapper_Save, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Delete", js_PluginGPGJS_GPGSnapshotWrapper_Delete, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchAll", js_PluginGPGJS_GPGSnapshotWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGSnapshotWrapper_class,
        dummy_constructor<sdkbox::GPGSnapshotWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGSnapshotWrapper>(cx, jsb_sdkbox_GPGSnapshotWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGSnapshotWrapper>(cx, jsb_sdkbox_GPGSnapshotWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGSnapshotWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGSnapshotWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGSnapshotWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGSnapshotWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGSnapshotWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGSnapshotWrapper_class->name = "GPGSnapshotWrapper";
    jsb_sdkbox_GPGSnapshotWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->finalize = js_PluginGPGJS_GPGSnapshotWrapper_finalize;
    jsb_sdkbox_GPGSnapshotWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Load", js_PluginGPGJS_GPGSnapshotWrapper_Load, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowSelectUIOperation", js_PluginGPGJS_GPGSnapshotWrapper_ShowSelectUIOperation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Save", js_PluginGPGJS_GPGSnapshotWrapper_Save, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Delete", js_PluginGPGJS_GPGSnapshotWrapper_Delete, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchAll", js_PluginGPGJS_GPGSnapshotWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
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
void js_register_PluginGPGJS_GPGSnapshotWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGSnapshotWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGSnapshotWrapper_class->name = "GPGSnapshotWrapper";
    jsb_sdkbox_GPGSnapshotWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGSnapshotWrapper_class->finalize = js_PluginGPGJS_GPGSnapshotWrapper_finalize;
    jsb_sdkbox_GPGSnapshotWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Load", js_PluginGPGJS_GPGSnapshotWrapper_Load, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowSelectUIOperation", js_PluginGPGJS_GPGSnapshotWrapper_ShowSelectUIOperation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Save", js_PluginGPGJS_GPGSnapshotWrapper_Save, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Delete", js_PluginGPGJS_GPGSnapshotWrapper_Delete, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchAll", js_PluginGPGJS_GPGSnapshotWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
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
JSClass  *jsb_sdkbox_GPGLeaderboardWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGLeaderboardWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchAll(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchAll : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchAll(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchAll : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchAll(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchScoreSummary(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 5) {
        int arg0;
        int arg1;
        std::string arg2;
        int arg3;
        int arg4;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchScoreSummary : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchScoreSummary(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchScoreSummary : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchScoreSummary(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 5) {
        int arg0;
        int arg1;
        std::string arg2;
        int arg3;
        int arg4;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, argv[4], (int32_t *)&arg4);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchScoreSummary(arg0, arg1, arg2, arg3, arg4);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchPreviousScorePage(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        int arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchPreviousScorePage : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchPreviousScorePage(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchPreviousScorePage : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchPreviousScorePage(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        int arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchPreviousScorePage(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_ShowAllUI(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_ShowAllUI : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::ShowAllUI(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_ShowAllUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::ShowAllUI(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchNextScorePage(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        int arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchNextScorePage : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchNextScorePage(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchNextScorePage : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchNextScorePage(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        int arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchNextScorePage(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        int arg0;
        std::string arg1;
        long arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_long(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::SubmitScore(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 4) {
        int arg0;
        std::string arg1;
        long arg2;
        std::string arg3;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_long(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::SubmitScore(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        int arg0;
        std::string arg1;
        long arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_long(cx, argv[2], &arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::SubmitScore(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 4) {
        int arg0;
        std::string arg1;
        long arg2;
        std::string arg3;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_long(cx, argv[2], &arg2);
        ok &= jsval_to_std_string(cx, argv[3], &arg3);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::SubmitScore(arg0, arg1, arg2, arg3);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchAllScoreSummaries(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        int arg0;
        int arg1;
        std::string arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchAllScoreSummaries : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchAllScoreSummaries(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchAllScoreSummaries : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchAllScoreSummaries(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        int arg0;
        int arg1;
        std::string arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchAllScoreSummaries(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_ShowUI(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_ShowUI : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::ShowUI(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_ShowUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_ShowUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::ShowUI(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_Fetch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_Fetch : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::Fetch(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_Fetch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::Fetch(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchScorePage(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 7) {
        int arg0;
        std::string arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        int arg6;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
        ok &= jsval_to_int32(cx, args.get(5), (int32_t *)&arg5);
        ok &= jsval_to_int32(cx, args.get(6), (int32_t *)&arg6);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchScorePage : Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchScorePage(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGLeaderboardWrapper_FetchScorePage : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchScorePage(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 7) {
        int arg0;
        std::string arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        int arg6;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, argv[4], (int32_t *)&arg4);
        ok &= jsval_to_int32(cx, argv[5], (int32_t *)&arg5);
        ok &= jsval_to_int32(cx, argv[6], (int32_t *)&arg6);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGLeaderboardWrapper::FetchScorePage(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGPGJS_GPGLeaderboardWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGLeaderboardWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGLeaderboardWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGLeaderboardWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGLeaderboardWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGLeaderboardWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->finalize = js_PluginGPGJS_GPGLeaderboardWrapper_finalize;
    jsb_sdkbox_GPGLeaderboardWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchAll", js_PluginGPGJS_GPGLeaderboardWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchScoreSummary", js_PluginGPGJS_GPGLeaderboardWrapper_FetchScoreSummary, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchPreviousScorePage", js_PluginGPGJS_GPGLeaderboardWrapper_FetchPreviousScorePage, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowAllUI", js_PluginGPGJS_GPGLeaderboardWrapper_ShowAllUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchNextScorePage", js_PluginGPGJS_GPGLeaderboardWrapper_FetchNextScorePage, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SubmitScore", js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchAllScoreSummaries", js_PluginGPGJS_GPGLeaderboardWrapper_FetchAllScoreSummaries, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowUI", js_PluginGPGJS_GPGLeaderboardWrapper_ShowUI, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGLeaderboardWrapper_Fetch, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchScorePage", js_PluginGPGJS_GPGLeaderboardWrapper_FetchScorePage, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGLeaderboardWrapper_class,
        dummy_constructor<sdkbox::GPGLeaderboardWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGLeaderboardWrapper>(cx, jsb_sdkbox_GPGLeaderboardWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGLeaderboardWrapper>(cx, jsb_sdkbox_GPGLeaderboardWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGLeaderboardWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGLeaderboardWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGLeaderboardWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGLeaderboardWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGLeaderboardWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGLeaderboardWrapper_class->name = "GPGLeaderboardWrapper";
    jsb_sdkbox_GPGLeaderboardWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->finalize = js_PluginGPGJS_GPGLeaderboardWrapper_finalize;
    jsb_sdkbox_GPGLeaderboardWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchAll", js_PluginGPGJS_GPGLeaderboardWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchScoreSummary", js_PluginGPGJS_GPGLeaderboardWrapper_FetchScoreSummary, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchPreviousScorePage", js_PluginGPGJS_GPGLeaderboardWrapper_FetchPreviousScorePage, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowAllUI", js_PluginGPGJS_GPGLeaderboardWrapper_ShowAllUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchNextScorePage", js_PluginGPGJS_GPGLeaderboardWrapper_FetchNextScorePage, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SubmitScore", js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchAllScoreSummaries", js_PluginGPGJS_GPGLeaderboardWrapper_FetchAllScoreSummaries, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowUI", js_PluginGPGJS_GPGLeaderboardWrapper_ShowUI, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGLeaderboardWrapper_Fetch, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchScorePage", js_PluginGPGJS_GPGLeaderboardWrapper_FetchScorePage, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGLeaderboardWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGLeaderboardWrapper_class,
        dummy_constructor<sdkbox::GPGLeaderboardWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGLeaderboardWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGLeaderboardWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGLeaderboardWrapper_class;
        p->proto = jsb_sdkbox_GPGLeaderboardWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGPGJS_GPGLeaderboardWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGLeaderboardWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGLeaderboardWrapper_class->name = "GPGLeaderboardWrapper";
    jsb_sdkbox_GPGLeaderboardWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGLeaderboardWrapper_class->finalize = js_PluginGPGJS_GPGLeaderboardWrapper_finalize;
    jsb_sdkbox_GPGLeaderboardWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchAll", js_PluginGPGJS_GPGLeaderboardWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchScoreSummary", js_PluginGPGJS_GPGLeaderboardWrapper_FetchScoreSummary, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchPreviousScorePage", js_PluginGPGJS_GPGLeaderboardWrapper_FetchPreviousScorePage, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowAllUI", js_PluginGPGJS_GPGLeaderboardWrapper_ShowAllUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchNextScorePage", js_PluginGPGJS_GPGLeaderboardWrapper_FetchNextScorePage, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SubmitScore", js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchAllScoreSummaries", js_PluginGPGJS_GPGLeaderboardWrapper_FetchAllScoreSummaries, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowUI", js_PluginGPGJS_GPGLeaderboardWrapper_ShowUI, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGLeaderboardWrapper_Fetch, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("FetchScorePage", js_PluginGPGJS_GPGLeaderboardWrapper_FetchScorePage, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGLeaderboardWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGLeaderboardWrapper_class,
        dummy_constructor<sdkbox::GPGLeaderboardWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGLeaderboardWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGLeaderboardWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGLeaderboardWrapper_class;
        p->proto = jsb_sdkbox_GPGLeaderboardWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGAchievementWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGAchievementWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_FetchAll(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGAchievementWrapper_FetchAll : Error processing arguments");
        sdkbox::GPGAchievementWrapper::FetchAll(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGAchievementWrapper_FetchAll : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGAchievementWrapper::FetchAll(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_Reveal(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGAchievementWrapper_Reveal : Error processing arguments");
        sdkbox::GPGAchievementWrapper::Reveal(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGAchievementWrapper_Reveal : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_Reveal(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGAchievementWrapper::Reveal(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_Unlock(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGAchievementWrapper_Unlock : Error processing arguments");
        sdkbox::GPGAchievementWrapper::Unlock(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGAchievementWrapper_Unlock : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_Unlock(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGAchievementWrapper::Unlock(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_ShowAllUI(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGAchievementWrapper_ShowAllUI : Error processing arguments");
        sdkbox::GPGAchievementWrapper::ShowAllUI(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGAchievementWrapper_ShowAllUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGAchievementWrapper::ShowAllUI(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_SetStepsAtLeast(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        unsigned int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGAchievementWrapper_SetStepsAtLeast : Error processing arguments");
        sdkbox::GPGAchievementWrapper::SetStepsAtLeast(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGAchievementWrapper_SetStepsAtLeast : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_SetStepsAtLeast(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        std::string arg0;
        unsigned int arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_uint32(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGAchievementWrapper::SetStepsAtLeast(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_Increment(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        unsigned int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGAchievementWrapper_Increment : Error processing arguments");
        sdkbox::GPGAchievementWrapper::Increment(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGAchievementWrapper_Increment : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_Increment(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        std::string arg0;
        unsigned int arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_uint32(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGAchievementWrapper::Increment(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_Fetch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGAchievementWrapper_Fetch : Error processing arguments");
        sdkbox::GPGAchievementWrapper::Fetch(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGAchievementWrapper_Fetch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGAchievementWrapper::Fetch(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGPGJS_GPGAchievementWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGAchievementWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGAchievementWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGAchievementWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGAchievementWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGAchievementWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGAchievementWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGAchievementWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGAchievementWrapper_class->finalize = js_PluginGPGJS_GPGAchievementWrapper_finalize;
    jsb_sdkbox_GPGAchievementWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchAll", js_PluginGPGJS_GPGAchievementWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Reveal", js_PluginGPGJS_GPGAchievementWrapper_Reveal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Unlock", js_PluginGPGJS_GPGAchievementWrapper_Unlock, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowAllUI", js_PluginGPGJS_GPGAchievementWrapper_ShowAllUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SetStepsAtLeast", js_PluginGPGJS_GPGAchievementWrapper_SetStepsAtLeast, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Increment", js_PluginGPGJS_GPGAchievementWrapper_Increment, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGAchievementWrapper_Fetch, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGAchievementWrapper_class,
        dummy_constructor<sdkbox::GPGAchievementWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGAchievementWrapper>(cx, jsb_sdkbox_GPGAchievementWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGAchievementWrapper>(cx, jsb_sdkbox_GPGAchievementWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGAchievementWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGAchievementWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGAchievementWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGAchievementWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGAchievementWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGAchievementWrapper_class->name = "GPGAchievementWrapper";
    jsb_sdkbox_GPGAchievementWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGAchievementWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGAchievementWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGAchievementWrapper_class->finalize = js_PluginGPGJS_GPGAchievementWrapper_finalize;
    jsb_sdkbox_GPGAchievementWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchAll", js_PluginGPGJS_GPGAchievementWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Reveal", js_PluginGPGJS_GPGAchievementWrapper_Reveal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Unlock", js_PluginGPGJS_GPGAchievementWrapper_Unlock, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowAllUI", js_PluginGPGJS_GPGAchievementWrapper_ShowAllUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SetStepsAtLeast", js_PluginGPGJS_GPGAchievementWrapper_SetStepsAtLeast, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Increment", js_PluginGPGJS_GPGAchievementWrapper_Increment, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGAchievementWrapper_Fetch, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGAchievementWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGAchievementWrapper_class,
        dummy_constructor<sdkbox::GPGAchievementWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGAchievementWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGAchievementWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGAchievementWrapper_class;
        p->proto = jsb_sdkbox_GPGAchievementWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGPGJS_GPGAchievementWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGAchievementWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGAchievementWrapper_class->name = "GPGAchievementWrapper";
    jsb_sdkbox_GPGAchievementWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGAchievementWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGAchievementWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGAchievementWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGAchievementWrapper_class->finalize = js_PluginGPGJS_GPGAchievementWrapper_finalize;
    jsb_sdkbox_GPGAchievementWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchAll", js_PluginGPGJS_GPGAchievementWrapper_FetchAll, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Reveal", js_PluginGPGJS_GPGAchievementWrapper_Reveal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Unlock", js_PluginGPGJS_GPGAchievementWrapper_Unlock, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowAllUI", js_PluginGPGJS_GPGAchievementWrapper_ShowAllUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SetStepsAtLeast", js_PluginGPGJS_GPGAchievementWrapper_SetStepsAtLeast, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Increment", js_PluginGPGJS_GPGAchievementWrapper_Increment, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGAchievementWrapper_Fetch, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGAchievementWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGAchievementWrapper_class,
        dummy_constructor<sdkbox::GPGAchievementWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGAchievementWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGAchievementWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGAchievementWrapper_class;
        p->proto = jsb_sdkbox_GPGAchievementWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGQuestsWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGQuestsWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_FetchList(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGQuestsWrapper_FetchList : Error processing arguments");
        sdkbox::GPGQuestsWrapper::FetchList(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGQuestsWrapper_FetchList : Error processing arguments");
        sdkbox::GPGQuestsWrapper::FetchList(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGQuestsWrapper_FetchList : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_FetchList(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGQuestsWrapper::FetchList(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGQuestsWrapper::FetchList(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_Accept(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGQuestsWrapper_Accept : Error processing arguments");
        sdkbox::GPGQuestsWrapper::Accept(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGQuestsWrapper_Accept : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_Accept(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGQuestsWrapper::Accept(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_ShowAllUI(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGQuestsWrapper_ShowAllUI : Error processing arguments");
        sdkbox::GPGQuestsWrapper::ShowAllUI(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGQuestsWrapper_ShowAllUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGQuestsWrapper::ShowAllUI(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_ShowUI(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGQuestsWrapper_ShowUI : Error processing arguments");
        sdkbox::GPGQuestsWrapper::ShowUI(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGQuestsWrapper_ShowUI : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_ShowUI(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGQuestsWrapper::ShowUI(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_ClaimMilestone(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGQuestsWrapper_ClaimMilestone : Error processing arguments");
        sdkbox::GPGQuestsWrapper::ClaimMilestone(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGQuestsWrapper_ClaimMilestone : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_ClaimMilestone(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGQuestsWrapper::ClaimMilestone(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_Fetch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGQuestsWrapper_Fetch : Error processing arguments");
        sdkbox::GPGQuestsWrapper::Fetch(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGQuestsWrapper_Fetch : Error processing arguments");
        sdkbox::GPGQuestsWrapper::Fetch(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGQuestsWrapper_Fetch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGQuestsWrapper::Fetch(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 3) {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGQuestsWrapper::Fetch(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGPGJS_GPGQuestsWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGQuestsWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGQuestsWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGQuestsWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGQuestsWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGQuestsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGQuestsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGQuestsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGQuestsWrapper_class->finalize = js_PluginGPGJS_GPGQuestsWrapper_finalize;
    jsb_sdkbox_GPGQuestsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchList", js_PluginGPGJS_GPGQuestsWrapper_FetchList, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Accept", js_PluginGPGJS_GPGQuestsWrapper_Accept, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowAllUI", js_PluginGPGJS_GPGQuestsWrapper_ShowAllUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowUI", js_PluginGPGJS_GPGQuestsWrapper_ShowUI, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ClaimMilestone", js_PluginGPGJS_GPGQuestsWrapper_ClaimMilestone, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGQuestsWrapper_Fetch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGQuestsWrapper_class,
        dummy_constructor<sdkbox::GPGQuestsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGQuestsWrapper>(cx, jsb_sdkbox_GPGQuestsWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGQuestsWrapper>(cx, jsb_sdkbox_GPGQuestsWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGQuestsWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGQuestsWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGQuestsWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGQuestsWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGQuestsWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGQuestsWrapper_class->name = "GPGQuestsWrapper";
    jsb_sdkbox_GPGQuestsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGQuestsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGQuestsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGQuestsWrapper_class->finalize = js_PluginGPGJS_GPGQuestsWrapper_finalize;
    jsb_sdkbox_GPGQuestsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchList", js_PluginGPGJS_GPGQuestsWrapper_FetchList, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Accept", js_PluginGPGJS_GPGQuestsWrapper_Accept, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowAllUI", js_PluginGPGJS_GPGQuestsWrapper_ShowAllUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowUI", js_PluginGPGJS_GPGQuestsWrapper_ShowUI, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ClaimMilestone", js_PluginGPGJS_GPGQuestsWrapper_ClaimMilestone, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGQuestsWrapper_Fetch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGQuestsWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGQuestsWrapper_class,
        dummy_constructor<sdkbox::GPGQuestsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGQuestsWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGQuestsWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGQuestsWrapper_class;
        p->proto = jsb_sdkbox_GPGQuestsWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGPGJS_GPGQuestsWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGQuestsWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGQuestsWrapper_class->name = "GPGQuestsWrapper";
    jsb_sdkbox_GPGQuestsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGQuestsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGQuestsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGQuestsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGQuestsWrapper_class->finalize = js_PluginGPGJS_GPGQuestsWrapper_finalize;
    jsb_sdkbox_GPGQuestsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchList", js_PluginGPGJS_GPGQuestsWrapper_FetchList, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Accept", js_PluginGPGJS_GPGQuestsWrapper_Accept, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowAllUI", js_PluginGPGJS_GPGQuestsWrapper_ShowAllUI, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ShowUI", js_PluginGPGJS_GPGQuestsWrapper_ShowUI, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ClaimMilestone", js_PluginGPGJS_GPGQuestsWrapper_ClaimMilestone, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGQuestsWrapper_Fetch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGQuestsWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGQuestsWrapper_class,
        dummy_constructor<sdkbox::GPGQuestsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGQuestsWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGQuestsWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGQuestsWrapper_class;
        p->proto = jsb_sdkbox_GPGQuestsWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGEventsWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGEventsWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGEventsWrapper_FetchAll(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGEventsWrapper_FetchAll : Error processing arguments");
        sdkbox::GPGEventsWrapper::FetchAll(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGEventsWrapper_FetchAll : Error processing arguments");
        sdkbox::GPGEventsWrapper::FetchAll(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGEventsWrapper_FetchAll : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGEventsWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGEventsWrapper::FetchAll(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGEventsWrapper::FetchAll(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGEventsWrapper_Fetch(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGEventsWrapper_Fetch : Error processing arguments");
        sdkbox::GPGEventsWrapper::Fetch(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGEventsWrapper_Fetch : Error processing arguments");
        sdkbox::GPGEventsWrapper::Fetch(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGEventsWrapper_Fetch : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGEventsWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGEventsWrapper::Fetch(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 3) {
        int arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGEventsWrapper::Fetch(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGEventsWrapper_Increment(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGEventsWrapper_Increment : Error processing arguments");
        sdkbox::GPGEventsWrapper::Increment(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        unsigned int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGEventsWrapper_Increment : Error processing arguments");
        sdkbox::GPGEventsWrapper::Increment(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGEventsWrapper_Increment : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGEventsWrapper_Increment(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGEventsWrapper::Increment(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 2) {
        std::string arg0;
        unsigned int arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_uint32(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGEventsWrapper::Increment(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGPGJS_GPGEventsWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGEventsWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGEventsWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGEventsWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGEventsWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGEventsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGEventsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGEventsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGEventsWrapper_class->finalize = js_PluginGPGJS_GPGEventsWrapper_finalize;
    jsb_sdkbox_GPGEventsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchAll", js_PluginGPGJS_GPGEventsWrapper_FetchAll, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGEventsWrapper_Fetch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Increment", js_PluginGPGJS_GPGEventsWrapper_Increment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGEventsWrapper_class,
        dummy_constructor<sdkbox::GPGEventsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGEventsWrapper>(cx, jsb_sdkbox_GPGEventsWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGEventsWrapper>(cx, jsb_sdkbox_GPGEventsWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGEventsWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGEventsWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGEventsWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGEventsWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGEventsWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGEventsWrapper_class->name = "GPGEventsWrapper";
    jsb_sdkbox_GPGEventsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGEventsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGEventsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGEventsWrapper_class->finalize = js_PluginGPGJS_GPGEventsWrapper_finalize;
    jsb_sdkbox_GPGEventsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchAll", js_PluginGPGJS_GPGEventsWrapper_FetchAll, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGEventsWrapper_Fetch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Increment", js_PluginGPGJS_GPGEventsWrapper_Increment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGEventsWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGEventsWrapper_class,
        dummy_constructor<sdkbox::GPGEventsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGEventsWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGEventsWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGEventsWrapper_class;
        p->proto = jsb_sdkbox_GPGEventsWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGPGJS_GPGEventsWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGEventsWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGEventsWrapper_class->name = "GPGEventsWrapper";
    jsb_sdkbox_GPGEventsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGEventsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGEventsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGEventsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGEventsWrapper_class->finalize = js_PluginGPGJS_GPGEventsWrapper_finalize;
    jsb_sdkbox_GPGEventsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchAll", js_PluginGPGJS_GPGEventsWrapper_FetchAll, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Fetch", js_PluginGPGJS_GPGEventsWrapper_Fetch, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Increment", js_PluginGPGJS_GPGEventsWrapper_Increment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGEventsWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGEventsWrapper_class,
        dummy_constructor<sdkbox::GPGEventsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGEventsWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGEventsWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGEventsWrapper_class;
        p->proto = jsb_sdkbox_GPGEventsWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGStatsWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGStatsWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGStatsWrapper_FetchForPlayer(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGStatsWrapper_FetchForPlayer : Error processing arguments");
        sdkbox::GPGStatsWrapper::FetchForPlayer(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGStatsWrapper_FetchForPlayer : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGStatsWrapper_FetchForPlayer(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGStatsWrapper::FetchForPlayer(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGPGJS_GPGStatsWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGStatsWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGStatsWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGStatsWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGStatsWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGStatsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGStatsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGStatsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGStatsWrapper_class->finalize = js_PluginGPGJS_GPGStatsWrapper_finalize;
    jsb_sdkbox_GPGStatsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchForPlayer", js_PluginGPGJS_GPGStatsWrapper_FetchForPlayer, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGStatsWrapper_class,
        dummy_constructor<sdkbox::GPGStatsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGStatsWrapper>(cx, jsb_sdkbox_GPGStatsWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGStatsWrapper>(cx, jsb_sdkbox_GPGStatsWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGStatsWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGStatsWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGStatsWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGStatsWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGStatsWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGStatsWrapper_class->name = "GPGStatsWrapper";
    jsb_sdkbox_GPGStatsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGStatsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGStatsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGStatsWrapper_class->finalize = js_PluginGPGJS_GPGStatsWrapper_finalize;
    jsb_sdkbox_GPGStatsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchForPlayer", js_PluginGPGJS_GPGStatsWrapper_FetchForPlayer, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGStatsWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGStatsWrapper_class,
        dummy_constructor<sdkbox::GPGStatsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGStatsWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGStatsWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGStatsWrapper_class;
        p->proto = jsb_sdkbox_GPGStatsWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGPGJS_GPGStatsWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGStatsWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGStatsWrapper_class->name = "GPGStatsWrapper";
    jsb_sdkbox_GPGStatsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGStatsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGStatsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGStatsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGStatsWrapper_class->finalize = js_PluginGPGJS_GPGStatsWrapper_finalize;
    jsb_sdkbox_GPGStatsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("FetchForPlayer", js_PluginGPGJS_GPGStatsWrapper_FetchForPlayer, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGStatsWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGStatsWrapper_class,
        dummy_constructor<sdkbox::GPGStatsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGStatsWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGStatsWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGStatsWrapper_class;
        p->proto = jsb_sdkbox_GPGStatsWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
JSClass  *jsb_sdkbox_GPGNearbyConnectionsWrapper_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_GPGNearbyConnectionsWrapper_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartDiscovery(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartDiscovery : Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::StartDiscovery(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartDiscovery : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartDiscovery(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        std::string arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::StartDiscovery(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_RejectConnectionRequest(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_RejectConnectionRequest : Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::RejectConnectionRequest(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_RejectConnectionRequest : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_RejectConnectionRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::RejectConnectionRequest(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Disconnect(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_Disconnect : Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::Disconnect(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_Disconnect : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Disconnect(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::Disconnect(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendUnreliableMessage(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    do {
        if (argc == 2) {
            std::vector<std::string> arg0;
            ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            sdkbox::GPGNearbyConnectionsWrapper::SendUnreliableMessage(arg0, arg1);
            return true;
        }
    } while (0);

    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            sdkbox::GPGNearbyConnectionsWrapper::SendUnreliableMessage(arg0, arg1);
            return true;
        }
    } while (0);
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendUnreliableMessage : wrong number of arguments");
    return false;
}
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalDeviceId(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::GPGNearbyConnectionsWrapper::GetLocalDeviceId();
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalDeviceId : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalDeviceId(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::GPGNearbyConnectionsWrapper::GetLocalDeviceId();
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopAdvertising(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::GPGNearbyConnectionsWrapper::StopAdvertising();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopAdvertising : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopAdvertising(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::GPGNearbyConnectionsWrapper::StopAdvertising();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Stop(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::GPGNearbyConnectionsWrapper::Stop();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_Stop : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::GPGNearbyConnectionsWrapper::Stop();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendReliableMessage(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    do {
        if (argc == 2) {
            std::vector<std::string> arg0;
            ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            sdkbox::GPGNearbyConnectionsWrapper::SendReliableMessage(arg0, arg1);
            return true;
        }
    } while (0);

    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            sdkbox::GPGNearbyConnectionsWrapper::SendReliableMessage(arg0, arg1);
            return true;
        }
    } while (0);
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendReliableMessage : wrong number of arguments");
    return false;
}
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalEndpointId(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::GPGNearbyConnectionsWrapper::GetLocalEndpointId();
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalEndpointId : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalEndpointId(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::GPGNearbyConnectionsWrapper::GetLocalEndpointId();
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Init(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_Init : Error processing arguments");
        bool ret = sdkbox::GPGNearbyConnectionsWrapper::Init(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_Init : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Init(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        std::string arg0;
        int arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        bool ret = sdkbox::GPGNearbyConnectionsWrapper::Init(arg0, arg1);
        jsval jsret;
        jsret = JS::BooleanValue(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopDiscovery(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopDiscovery : Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::StopDiscovery(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopDiscovery : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopDiscovery(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::StopDiscovery(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendConnectionRequest(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 5) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        int arg3;
        int arg4;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendConnectionRequest : Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::SendConnectionRequest(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendConnectionRequest : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendConnectionRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 5) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        int arg3;
        int arg4;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, argv[4], (int32_t *)&arg4);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::SendConnectionRequest(arg0, arg1, arg2, arg3, arg4);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartAdvertising(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartAdvertising : Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::StartAdvertising(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartAdvertising : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartAdvertising(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        std::string arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::StartAdvertising(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_AcceptConnectionRequest(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_AcceptConnectionRequest : Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::AcceptConnectionRequest(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGPGJS_GPGNearbyConnectionsWrapper_AcceptConnectionRequest : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_AcceptConnectionRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::GPGNearbyConnectionsWrapper::AcceptConnectionRequest(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGPGJS_GPGNearbyConnectionsWrapper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GPGNearbyConnectionsWrapper)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "GPGNearbyConnectionsWrapper",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->finalize = js_PluginGPGJS_GPGNearbyConnectionsWrapper_finalize;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("StartDiscovery", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartDiscovery, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("RejectConnectionRequest", js_PluginGPGJS_GPGNearbyConnectionsWrapper_RejectConnectionRequest, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Disconnect", js_PluginGPGJS_GPGNearbyConnectionsWrapper_Disconnect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendUnreliableMessage", js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendUnreliableMessage, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("GetLocalDeviceId", js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalDeviceId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StopAdvertising", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopAdvertising, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Stop", js_PluginGPGJS_GPGNearbyConnectionsWrapper_Stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendReliableMessage", js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendReliableMessage, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("GetLocalEndpointId", js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalEndpointId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Init", js_PluginGPGJS_GPGNearbyConnectionsWrapper_Init, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StopDiscovery", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopDiscovery, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendConnectionRequest", js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendConnectionRequest, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StartAdvertising", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartAdvertising, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AcceptConnectionRequest", js_PluginGPGJS_GPGNearbyConnectionsWrapper_AcceptConnectionRequest, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_GPGNearbyConnectionsWrapper_class,
        dummy_constructor<sdkbox::GPGNearbyConnectionsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::GPGNearbyConnectionsWrapper>(cx, jsb_sdkbox_GPGNearbyConnectionsWrapper_class, proto);
#else
    jsb_register_class<sdkbox::GPGNearbyConnectionsWrapper>(cx, jsb_sdkbox_GPGNearbyConnectionsWrapper_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::GPGNearbyConnectionsWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGNearbyConnectionsWrapper_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "GPGNearbyConnectionsWrapper");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->name = "GPGNearbyConnectionsWrapper";
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->finalize = js_PluginGPGJS_GPGNearbyConnectionsWrapper_finalize;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("StartDiscovery", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartDiscovery, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("RejectConnectionRequest", js_PluginGPGJS_GPGNearbyConnectionsWrapper_RejectConnectionRequest, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Disconnect", js_PluginGPGJS_GPGNearbyConnectionsWrapper_Disconnect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendUnreliableMessage", js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendUnreliableMessage, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("GetLocalDeviceId", js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalDeviceId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StopAdvertising", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopAdvertising, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Stop", js_PluginGPGJS_GPGNearbyConnectionsWrapper_Stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendReliableMessage", js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendReliableMessage, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("GetLocalEndpointId", js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalEndpointId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Init", js_PluginGPGJS_GPGNearbyConnectionsWrapper_Init, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StopDiscovery", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopDiscovery, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendConnectionRequest", js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendConnectionRequest, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StartAdvertising", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartAdvertising, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AcceptConnectionRequest", js_PluginGPGJS_GPGNearbyConnectionsWrapper_AcceptConnectionRequest, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGNearbyConnectionsWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGNearbyConnectionsWrapper_class,
        dummy_constructor<sdkbox::GPGNearbyConnectionsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "GPGNearbyConnectionsWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGNearbyConnectionsWrapper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_GPGNearbyConnectionsWrapper_class;
        p->proto = jsb_sdkbox_GPGNearbyConnectionsWrapper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(JSContext *cx, JSObject *global) {
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->name = "GPGNearbyConnectionsWrapper";
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->resolve = JS_ResolveStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->convert = JS_ConvertStub;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->finalize = js_PluginGPGJS_GPGNearbyConnectionsWrapper_finalize;
    jsb_sdkbox_GPGNearbyConnectionsWrapper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("StartDiscovery", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartDiscovery, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("RejectConnectionRequest", js_PluginGPGJS_GPGNearbyConnectionsWrapper_RejectConnectionRequest, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Disconnect", js_PluginGPGJS_GPGNearbyConnectionsWrapper_Disconnect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendUnreliableMessage", js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendUnreliableMessage, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("GetLocalDeviceId", js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalDeviceId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StopAdvertising", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopAdvertising, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Stop", js_PluginGPGJS_GPGNearbyConnectionsWrapper_Stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendReliableMessage", js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendReliableMessage, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("GetLocalEndpointId", js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalEndpointId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Init", js_PluginGPGJS_GPGNearbyConnectionsWrapper_Init, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StopDiscovery", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopDiscovery, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendConnectionRequest", js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendConnectionRequest, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StartAdvertising", js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartAdvertising, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AcceptConnectionRequest", js_PluginGPGJS_GPGNearbyConnectionsWrapper_AcceptConnectionRequest, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_GPGNearbyConnectionsWrapper_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_GPGNearbyConnectionsWrapper_class,
        dummy_constructor<sdkbox::GPGNearbyConnectionsWrapper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "GPGNearbyConnectionsWrapper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::GPGNearbyConnectionsWrapper> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_GPGNearbyConnectionsWrapper_class;
        p->proto = jsb_sdkbox_GPGNearbyConnectionsWrapper_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "_gpg", &ns);

    js_register_PluginGPGJS_GPGEventsWrapper(cx, ns);
    js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(cx, ns);
    js_register_PluginGPGJS_GPGPlayerWrapper(cx, ns);
    js_register_PluginGPGJS_GPGSnapshotWrapper(cx, ns);
    js_register_PluginGPGJS_GPGWrapper(cx, ns);
    js_register_PluginGPGJS_GPGQuestsWrapper(cx, ns);
    js_register_PluginGPGJS_GPGLeaderboardWrapper(cx, ns);
    js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(cx, ns);
    js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(cx, ns);
    js_register_PluginGPGJS_GPGAchievementWrapper(cx, ns);
    js_register_PluginGPGJS_GPGStatsWrapper(cx, ns);

    sdkbox::setProjectType("js");
}
#else
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj) {
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

    js_register_PluginGPGJS_GPGEventsWrapper(cx, obj);
    js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(cx, obj);
    js_register_PluginGPGJS_GPGPlayerWrapper(cx, obj);
    js_register_PluginGPGJS_GPGSnapshotWrapper(cx, obj);
    js_register_PluginGPGJS_GPGWrapper(cx, obj);
    js_register_PluginGPGJS_GPGQuestsWrapper(cx, obj);
    js_register_PluginGPGJS_GPGLeaderboardWrapper(cx, obj);
    js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(cx, obj);
    js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(cx, obj);
    js_register_PluginGPGJS_GPGAchievementWrapper(cx, obj);
    js_register_PluginGPGJS_GPGStatsWrapper(cx, obj);

    sdkbox::setProjectType("js");
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj) {
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

    js_register_PluginGPGJS_GPGEventsWrapper(cx, obj);
    js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(cx, obj);
    js_register_PluginGPGJS_GPGPlayerWrapper(cx, obj);
    js_register_PluginGPGJS_GPGSnapshotWrapper(cx, obj);
    js_register_PluginGPGJS_GPGWrapper(cx, obj);
    js_register_PluginGPGJS_GPGQuestsWrapper(cx, obj);
    js_register_PluginGPGJS_GPGLeaderboardWrapper(cx, obj);
    js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(cx, obj);
    js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(cx, obj);
    js_register_PluginGPGJS_GPGAchievementWrapper(cx, obj);
    js_register_PluginGPGJS_GPGStatsWrapper(cx, obj);

    sdkbox::setProjectType("js");
}
#endif