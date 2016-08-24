#ifndef __PluginSdkboxGooglePlayJS_h__
#define __PluginSdkboxGooglePlayJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_sdkbox_GPGWrapper_class;
extern JSObject *jsb_sdkbox_GPGWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginSdkboxGooglePlayJS_GPGWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginSdkboxGooglePlayJS_GPGWrapper(JSContext *cx, JSObject* global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginSdkboxGooglePlayJS_GPGWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginSdkboxGooglePlayJS_GPGWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_NotifyToScripting(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_NotifyToScripting(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_IsAuthorized(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_IsAuthorized(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_CreateGameServices(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_CreateGameServices(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_StartAuthorizationUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_StartAuthorizationUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGWrapper_SignOut(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGWrapper_SignOut(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGLocalPlayerWrapper_class;
extern JSObject *jsb_sdkbox_GPGLocalPlayerWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper(JSContext *cx, JSObject* global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentLevel(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentLevel(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Name(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Name(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_AvatarUrl(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_AvatarUrl(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_LastLevelUpTime(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_LastLevelUpTime(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Title(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Title(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentXP(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_CurrentXP(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_HasLevelInfo(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_HasLevelInfo(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_NextLevel(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_NextLevel(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Id(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLocalPlayerWrapper_Id(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGSnapshotWrapper_class;
extern JSObject *jsb_sdkbox_GPGSnapshotWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper(JSContext *cx, JSObject* global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Load(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Load(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_ShowSelectUIOperation(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_ShowSelectUIOperation(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Save(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Save(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Delete(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_Delete(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGSnapshotWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGLeaderboardWrapper_class;
extern JSObject *jsb_sdkbox_GPGLeaderboardWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper(JSContext *cx, JSObject* global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchScoreSummary(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchScoreSummary(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchPreviousScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchPreviousScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchNextScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchNextScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_SubmitScore(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_SubmitScore(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchAllScoreSummaries(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchAllScoreSummaries(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_ShowUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_ShowUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGLeaderboardWrapper_FetchScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGAchievementWrapper_class;
extern JSObject *jsb_sdkbox_GPGAchievementWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginSdkboxGooglePlayJS_GPGAchievementWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginSdkboxGooglePlayJS_GPGAchievementWrapper(JSContext *cx, JSObject* global);
void register_all_PluginSdkboxGooglePlayJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_Reveal(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_Reveal(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_Unlock(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_Unlock(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_SetStepsAtLeast(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_SetStepsAtLeast(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_Increment(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_Increment(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginSdkboxGooglePlayJS_GPGAchievementWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#endif

