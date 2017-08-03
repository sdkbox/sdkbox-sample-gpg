#ifndef __PluginGPGJS_h__
#define __PluginGPGJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGPlayerWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGPlayerWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGSnapshotWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGSnapshotWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGLeaderboardWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGLeaderboardWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGAchievementWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGAchievementWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGQuestsWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGQuestsWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGEventsWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGEventsWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGStatsWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGStatsWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif
#endif

