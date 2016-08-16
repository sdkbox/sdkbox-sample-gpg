
#include "PluginSdkboxGooglePlayJSHelper.h"
#include "PluginSdkboxGooglePlay/PluginSdkboxGooglePlay.h"

#if (COCOS2D_VERSION < 0x00030000)
#define Ref CCObject
#define Director CCDirector
#define getInstance sharedDirector
#define schedule scheduleSelector
#endif


std::unique_ptr<NativeJSNotifier> _njsn = nullptr;

void register_all_PluginSdkboxGooglePlayJS_helper(JSContext* cx, JS::HandleObject global) {
    _njsn = std::unique_ptr<NativeJSNotifier>(new NativeJSNotifier(cx));
    
    // load and inject gpg js layer.
    ScriptingCore::getInstance()->runScript("res/sdkboxgpg.js");
}

NativeJSNotifier::NativeJSNotifier( JSContext* cx ) : s_cx(cx) {
}

NativeJSNotifier::~NativeJSNotifier() {
}

void NativeJSNotifier::__notifyImpl(int id, const std::string &json) {
    if (!s_cx) {
        return;
    }
    JSContext* cx = s_cx;
    const char* func_name = "__nativeNotify";
    
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
    bool hasAction;
    JS::RootedValue retval(cx);
    JS::RootedValue func_handle(cx);
#else
    bool hasAction;
    jsval retval;
    JS::RootedValue func_handle(cx);
#endif
#elif defined(JS_VERSION)
    JSBool hasAction;
    jsval retval;
    jsval func_handle;
#endif
    
    
    JS::RootedObject obj (cx,ScriptingCore::getInstance()->getGlobalObject());
    JSAutoCompartment ac(cx, obj);
    
    if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {

        jsval pvals[2];
        pvals[0]= INT_TO_JSVAL(id);
        pvals[1]= std_string_to_jsval(cx, json);
    
        #if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(2, pvals ), &retval);
        #else
            JS_CallFunctionName(cx, obj, func_name, 1, pvals, &retval);
        #endif
    } else {
        CCLOGINFO("no function %s found.", func_name);
    }
    
}

NativeJSNotifierScheduler::NativeJSNotifierScheduler( int id, const std::string& json ): _id(id), _json(json) {
}

void NativeJSNotifierScheduler::schedule() {
    retain();
    cocos2d::Director::getInstance()->getScheduler()->schedule(schedule_selector(NativeJSNotifierScheduler::notityJs), this, 0, false);
    autorelease();
}

void NativeJSNotifierScheduler::notityJs(float dt) {
    _njsn->__notifyImpl( _id, _json );
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    release();
}


void sdkbox::GPGWrapper::NotifyToScripting( int id, const std::string& str_json ) {
    NativeJSNotifierScheduler* ns = new NativeJSNotifierScheduler(id, str_json);
    ns->schedule();
}

