

#ifndef __js__PluginSdkboxGPGJSHelper_H_
#define __js__PluginSdkboxGPGJSHelper_H_

#include "jsapi.h"
#include "jsfriendapi.h"

#include "SDKBoxJSHelper.h"

#if MOZJS_MAJOR_VERSION >= 31
 void register_all_PluginGPGJS_helper(JSContext* cx, JS::HandleObject global);
#else
 void register_all_PluginGPGJS_helper(JSContext* cx, JSObject* global);
#endif


class NativeJSNotifier {
public:
    NativeJSNotifier(JSContext*);
    ~NativeJSNotifier();
    void __notifyImpl( int id, const std::string& json );
private:
    JSContext* s_cx;
};

class NativeJSNotifierScheduler : public cocos2d::Ref {
public:
    
    NativeJSNotifierScheduler(int id, const std::string& json);
    void schedule();
    void notityJs(float dt);
    
protected:
    int _id;
    std::string _json;
};

#endif 
