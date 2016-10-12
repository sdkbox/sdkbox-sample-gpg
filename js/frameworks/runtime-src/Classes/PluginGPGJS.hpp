#ifndef __PluginGPGJS_h__
#define __PluginGPGJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_sdkbox_GPGRealTimeMultiplayerWrapper_class;
extern JSObject *jsb_sdkbox_GPGRealTimeMultiplayerWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGRealTimeMultiplayerWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_CreateRealTimeRoom(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_LeaveRoom(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_LeaveRoom(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessage(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DismissInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DismissInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DeclineInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_DeclineInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendReliableMessage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendReliableMessage(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_AcceptInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_AcceptInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_FetchInvitations(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_FetchInvitations(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessageToOthers(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_SendUnreliableMessageToOthers(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_ShowRoomInboxUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGRealTimeMultiplayerWrapper_ShowRoomInboxUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_class;
extern JSObject *jsb_sdkbox_GPGTurnBasedMultiplayerWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGTurnBasedMultiplayerWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowPlayerSelectUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowPlayerSelectUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CancelMatch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CancelMatch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissMatch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissMatch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowMatchInboxUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ShowMatchInboxUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_SynchronizeData(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_SynchronizeData(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateTurnBasedMatch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateTurnBasedMatch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DismissInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DeclineInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_DeclineInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ConfirmPendingCompletion(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_ConfirmPendingCompletion(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FinishMatchDuringMyTurn(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FinishMatchDuringMyTurn(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_Rematch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_Rematch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringTheirTurn(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringTheirTurn(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateParticipantResult(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_CreateParticipantResult(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_TakeMyTurn(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_TakeMyTurn(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatches(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_FetchMatches(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringMyTurn(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_LeaveMatchDuringMyTurn(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_AcceptInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGTurnBasedMultiplayerWrapper_AcceptInvitation(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGWrapper_class;
extern JSObject *jsb_sdkbox_GPGWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGWrapper_NotifyToScripting(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_NotifyToScripting(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGWrapper_IsAuthorized(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_IsAuthorized(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGWrapper_CreateGameServices(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_CreateGameServices(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGWrapper_StartAuthorizationUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_StartAuthorizationUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGWrapper_SignOut(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGWrapper_SignOut(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGPlayerWrapper_class;
extern JSObject *jsb_sdkbox_GPGPlayerWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGPlayerWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGPlayerWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGPlayerWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGPlayerWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyConnected(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyConnected(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyInvitable(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyInvitable(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyPlayed(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_FetchRecentlyPlayed(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGPlayerWrapper_FetchSelf(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGPlayerWrapper_FetchSelf(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGSnapshotWrapper_class;
extern JSObject *jsb_sdkbox_GPGSnapshotWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGSnapshotWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGSnapshotWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGSnapshotWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGSnapshotWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGSnapshotWrapper_Load(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_Load(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGSnapshotWrapper_ShowSelectUIOperation(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_ShowSelectUIOperation(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGSnapshotWrapper_Save(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_Save(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGSnapshotWrapper_Delete(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_Delete(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGSnapshotWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGSnapshotWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGLeaderboardWrapper_class;
extern JSObject *jsb_sdkbox_GPGLeaderboardWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGLeaderboardWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGLeaderboardWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGLeaderboardWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGLeaderboardWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchScoreSummary(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchScoreSummary(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchPreviousScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchPreviousScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchNextScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchNextScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_SubmitScore(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchAllScoreSummaries(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchAllScoreSummaries(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_ShowUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_ShowUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGLeaderboardWrapper_FetchScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGLeaderboardWrapper_FetchScorePage(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGAchievementWrapper_class;
extern JSObject *jsb_sdkbox_GPGAchievementWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGAchievementWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGAchievementWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGAchievementWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGAchievementWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_Reveal(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_Reveal(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_Unlock(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_Unlock(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_SetStepsAtLeast(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_SetStepsAtLeast(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_Increment(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_Increment(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGAchievementWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGAchievementWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGQuestsWrapper_class;
extern JSObject *jsb_sdkbox_GPGQuestsWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGQuestsWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGQuestsWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGQuestsWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGQuestsWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_FetchList(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_FetchList(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_Accept(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_Accept(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_ShowAllUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_ShowUI(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_ShowUI(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_ClaimMilestone(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_ClaimMilestone(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGQuestsWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGQuestsWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGEventsWrapper_class;
extern JSObject *jsb_sdkbox_GPGEventsWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGEventsWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGEventsWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGEventsWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGEventsWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGEventsWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGEventsWrapper_FetchAll(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGEventsWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGEventsWrapper_Fetch(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGEventsWrapper_Increment(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGEventsWrapper_Increment(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGStatsWrapper_class;
extern JSObject *jsb_sdkbox_GPGStatsWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGStatsWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGStatsWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGStatsWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGStatsWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGStatsWrapper_FetchForPlayer(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGStatsWrapper_FetchForPlayer(JSContext *cx, uint32_t argc, jsval *vp);
#endif

extern JSClass  *jsb_sdkbox_GPGNearbyConnectionsWrapper_class;
extern JSObject *jsb_sdkbox_GPGNearbyConnectionsWrapper_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(JSContext *cx, JS::HandleObject global);
void register_all_PluginGPGJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGPGJS_GPGNearbyConnectionsWrapper(JSContext *cx, JSObject* global);
void register_all_PluginGPGJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginGPGJS_GPGNearbyConnectionsWrapper_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartDiscovery(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartDiscovery(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_RejectConnectionRequest(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_RejectConnectionRequest(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Disconnect(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Disconnect(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendUnreliableMessage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendUnreliableMessage(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalDeviceId(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalDeviceId(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopAdvertising(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopAdvertising(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Stop(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Stop(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendReliableMessage(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendReliableMessage(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalEndpointId(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_GetLocalEndpointId(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Init(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_Init(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopDiscovery(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StopDiscovery(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendConnectionRequest(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_SendConnectionRequest(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartAdvertising(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_StartAdvertising(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGPGJS_GPGNearbyConnectionsWrapper_AcceptConnectionRequest(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginGPGJS_GPGNearbyConnectionsWrapper_AcceptConnectionRequest(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#endif

