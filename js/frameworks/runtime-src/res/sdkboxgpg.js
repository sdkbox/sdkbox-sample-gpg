/**
 * Created by ibon on 10/8/16.
 */


var P_DATA_SOURCE = 'data_source';

var P_SNP_CONFLICT_POLICY = 'conflict_policy';
var P_SNP_TITLE = 'title';
var P_SNP_FILE_NAME = 'filename';
var P_SNP_DESCRIPTION = 'description';
var P_SNP_PAGE_SIZE = 10;

var P_LDB_ORDER= 'order';
var P_LDB_COLLECTION= 'collection';
var P_LDB_START= 'start';
var P_LDB_TIME_SPAN= 'time_span';
var P_LDB_METADATA= 'metadata';
var P_LDB_SCORE_PAGE_SIZE= 'max_items';

/**
 * Default parameter field value.
 * Sets common fields default values if not present on params object.
 * @param params {object}
 * @param fields string[]
 * @private
 */
function __dp( params, fields ) {

    if ( typeof params==='undefined' ) {
        throw new Error('setting def params in undefined object.');
    }

    if ( arguments.length!==2 ) {
        throw new Error('__dp called with '+arguments.length+' params.');
    }

    if ( Object.prototype.toString.call(fields)==='[object Array]') {
        fields.forEach(function (f) {
            __dp1(params, f);
        });
    } else {
        __dp1( params, fields );
    }
}

function __dp1( params, f ) {
    switch (f) {
        case P_DATA_SOURCE:
            if (typeof params[P_DATA_SOURCE] === 'undefined') {
                params[P_DATA_SOURCE] = gpg.DataSource.CACHE_OR_NETWORK;
            }
            break;

        // Snapshot checks
        case P_SNP_CONFLICT_POLICY:
            if ( typeof params[P_SNP_CONFLICT_POLICY]==='undefined' ) {
               params[P_SNP_CONFLICT_POLICY] = gpg.SnapshotConflictPolicy.DefaultConflictPolicy;
            }
            break;
        case P_SNP_TITLE:
            if ( typeof params[P_SNP_TITLE]==='undefined' ) {
               params[P_SNP_TITLE] = 'title';
            }
            break;
        case P_SNP_DESCRIPTION:
            if ( typeof params[P_SNP_DESCRIPTION]==='undefined' ) {
               params[P_SNP_DESCRIPTION] = 'Default game description';
            }
            break;
        case P_SNP_PAGE_SIZE:
            if ( typeof params[P_SNP_PAGE_SIZE]==='undefined' ) {
               params[P_SNP_PAGE_SIZE] = 10;
            }
            break;

        // Leaderboard checks
        case P_LDB_COLLECTION:
            if (typeof params[P_LDB_COLLECTION] === 'undefined') {
                params[P_LDB_COLLECTION] = gpg.LeaderboardCollection.PUBLIC;
            }
            break;
        case P_LDB_ORDER:
            if (typeof params[P_LDB_ORDER] === 'undefined') {
                params[P_LDB_ORDER] = gpg.LeaderboardOrder.LARGER_IS_BETTER;
            }
            break;
        case P_LDB_START:
            if (typeof params[P_LDB_START] === 'undefined') {
                params[P_LDB_START] = gpg.LeaderboardStart.TOP_SCORES;
            }
            break;
        case P_LDB_TIME_SPAN:
            if (typeof params[P_LDB_TIME_SPAN] === 'undefined') {
                params[P_LDB_TIME_SPAN] = gpg.LeaderboardTimeSpan.ALL_TIME;
            }
            break;
        case P_LDB_METADATA:
            if (typeof params[P_LDB_METADATA] === 'undefined') {
                params[P_LDB_METADATA] = '';
            }
            break;
        case P_LDB_SCORE_PAGE_SIZE:
            if (typeof params[P_LDB_SCORE_PAGE_SIZE] === 'undefined') {
                params[P_LDB_SCORE_PAGE_SIZE] = 10;
            }
            break;
    }

}

/**
 * called from native.
 * @param id {number}
 * @param str_json {string}
 */
function __nativeNotify( id, str_json ) {
    __callbackManager.nativeNotify( id, str_json );
}

/**
 * Cocos main namespace.
 * @namespace cc
 */

/**
 * Native wrapped objects namespace
 * @namespace _gpg
 */

/**
 * @namespace GPGWrapper
 * @memberOf _gpg
 */

/**
 * @name CreateGameServices
 * @type function
 * @memberOf _gpg.GPGWrapper
 */

/**
 * @name Fetch
 * @type function
 * @memberOf _gpg.GPGWrapper
 */

////////////// Player Wrapper definitions.

/**
 * @namespace GPGPlayerWrapper
 * @memberOf _gpg
 */

/**
 * @name FetchSelf
 * @type function
 * @memberOf _gpg.GPGPlayerWrapper
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name Fetch
 * @type function
 * @memberOf _gpg.GPGPlayerWrapper
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 * @param player_id {string}
 */

////////////// Snapshot Wrapper definitions.

/**
 * @name GPGSnapshotWrapper
 * @type namespace
 * @memberOf _gpg
 */

/**
 * @name Load
 * @memberOf _gpg.GPGSnapshotWrapper
 * @type function
 * @param index {number}
 * @param filename {string}
 * @param conflict_policy {gpg.SnapshotConflictPolicy}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name Save
 * @memberOf _gpg.GPGSnapshotWrapper
 * @type function
 * @param index {number}
 * @param data {string}
 */

/**
 * @name Delete
 * @memberOf _gpg.GPGSnapshotWrapper
 * @type function
 * @param index {number}
 * @param filename {string}
 */

/**
 * @name ShowSelectUIOperation
 * @memberOf _gpg.GPGSnapshotWrapper
 * @type function
 * @param params {tSnapshotShowSelectionUIOperationParams}
 * @param callback {SnapshotShowSelectUIOperationCallback}
 */

/**
 * @name FetchAll
 * @memberOf _gpg.GPGSnapshotWrapper
 * @type function
 * @param params {tSnapshotFetchAllParams}
 * @param callback {SnapshotFetchAllCallback}
 */

////////////// Leaderboards Wrapper definitions.

/**
 * @name GPGLeaderboardWrapper
 * @type namespace
 * @memberOf _gpg
 */

/**
 * @name Fetch
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 * @param leaderboard_id {string}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name FetchAll
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name FetchScoreSummary
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 * @param leaderboard_id {string}
 * @param time_span {gpg.LeaderboardTimeSpan}
 * @param collection {gpg.LeaderboardCollection}
 */

/**
 * @name FetchAllScoreSummaries
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 * @param leaderboard_id {string}
 */

/**
 * @name SubmitScore
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 * @param leaderboard_id {string}
 * @param score {number}
 * @param metadata? : string
 */

/**
 * @name ShowUI
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 * @param leaderboard_id {string}
 */

/**
 * @name ShowAllUI
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 */

/**
 * @name FetchScorePage
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 * @param leaderboard_id {string}
 * @param data_source {gpg.DataSource}
 * @param start {gpg.LeaderboardStart}
 * @param time_span {gpg.LeaderboardTimeSpan}
 * @param collection {gpg.LeaderboardCollection}
 * @param max_results {number}
 */

/**
 * @name FetchNextScorePage
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 * @param max_results {number}
 */

/**
 * @name FetchPreviousScorePage
 * @memberOf _gpg.GPGLeaderboardWrapper
 * @type function
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 * @param max_results {number}
 */

////////////// Achievement Wrapper definitions.

/**
 * @name GPGAchievementWrapper
 * @type namespace
 * @memberOf _gpg
 */

/**
 * @name Fetch
 * @memberOf _gpg.GPGAchievementWrapper
 * @type function
 * @param callback_id {number}
 * @param achievement_id {string}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name FetchAll
 * @memberOf _gpg.GPGAchievementWrapper
 * @type function
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name ShowAllUI
 * @memberOf _gpg.GPGAchievementWrapper
 * @type function
 * @param callback_id
 */

/**
 * @name Increment
 * @memberOf _gpg.SetStepsAtLeast
 * @type function
 * @param achievement_id {string}
 * @param increment {number}
 */

/**
 * @name SetStepsAtLeast
 * @memberOf _gpg.SetStepsAtLeast
 * @type function
 * @param achievement_id {string}
 * @param increment {number}
 */

/**
 * @name Reveal
 * @memberOf _gpg.SetStepsAtLeast
 * @type function
 * @param achievement_id {string}
 */

/**
 * @name Unlock
 * @memberOf _gpg.SetStepsAtLeast
 * @type function
 * @param achievement_id {string}
 */

////////////// Quests Wrapper definitions.

/**
 * @name GPGQuestsWrapper
 * @namespace
 * @memberOf _gpg
 */

/**
 * @name Fetch
 * @memberOf _gpg.GPGQuestsWrapper
 * @type function
 * @param callback_id {number}
 * @param quest_id {string}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name FetchList
 * @memberOf _gpg.GPGQuestsWrapper
 * @type function
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name ShowUI
 * @memberOf _gpg.GPGQuestsWrapper
 * @type function
 * @param callback_id {number}
 * @param quest_id {string}
 */

/**
 * @name ShowAllUI
 * @memberOf _gpg.GPGQuestsWrapper
 * @type function
 * @param callback_id {number}
 */

/**
 * @name Accept
 * @memberOf _gpg.GPGQuestsWrapper
 * @type function
 * @param callback_id {number}
 * @param quest_id {string}
 */

/**
 * @name ClaimMilestone
 * @memberOf _gpg.GPGQuestsWrapper
 * @type function
 * @param callback_id {number}
 * @param milestone_id {string}
 */

////////////// Events Wrapper definitions.

/**
 * @name GPGEventsWrapper
 * @namespace
 * @memberOf _gpg
 */

/**
 * @name Fetch
 * @memberOf _gpg.GPGEventsWrapper
 * @type function
 * @param callback_id {number}
 * @param event_id {string}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name FetchAll
 * @memberOf _gpg.GPGEventsWrapper
 * @type function
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 */

/**
 * @name Increment
 * @memberOf _gpg.GPGEventsWrapper
 * @type function
 * @param event_id {string}
 * @param increment {number}
 */

////////////// PlayerStats Wrapper definitions.

/**
 * @name GPGStatsWrapper
 * @memberOf _gpg
 * @namespace
 */

/**
 * @name FetchForPlayer
 * @memberOf _gpg.GPGStatsWrapper
 * @type function
 * @param callback_id {number}
 * @param data_source {gpg.DataSource}
 */

////////////// RealTime multiplayer Wrapper definitions.

/**
 * @name GPGRealTimeMultiplayerWrapper
 * @memberOf _gpg
 * @type namespace
 */

/**
 * @name CreateRealTimeRoom
 * @memberOf _gpg.GPGRealTimeMultiplayerWrapper
 * @type function
 * @param callback_id {number}
 * @param params {string}
 */

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Utility method. Should be emptied on production.
 * @param e {object}
 */
function __log( e ) {
    if ( typeof cc!=='undefined' && typeof cc.log!=='undefined' ) {
        cc.log( e );
    } else if ( typeof console!=='undefined' ) {
        console.log(e);
    }
}

__log('Evaluating Sdkbox GPG js layer');

var DefaultCallbacks = {
    DEFAULT_CALLBACKS_BEGIN : 1,
    AUTH_ACTION_STARTED : 1,
    AUTH_ACTION_FINISHED : 2,
    DEFAULT_CALLBACKS_END : 2
};

var BaseStatus = {
    VALID : 1,
    VALID_BUT_STALE : 2,
    VALID_WITH_CONFLICT : 3,
    FLUSHED : 4,
    ERROR_LICENSE_CHECK_FAILED : -1,
    ERROR_INTERNAL : -2,
    ERROR_NOT_AUTHORIZED : -3,
    ERROR_VERSION_UPDATE_REQUIRED : -4,
    ERROR_TIMEOUT : -5,
    ERROR_CANCELED : -6,
    ERROR_MATCH_ALREADY_REMATCHED : -7,
    ERROR_INACTIVE_MATCH : -8,
    ERROR_INVALID_RESULTS : -9,
    ERROR_INVALID_MATCH : -10,
    ERROR_MATCH_OUT_OF_DATE : -11,
    ERROR_UI_BUSY : -12,
    ERROR_QUEST_NO_LONGER_AVAILABLE : -13,
    ERROR_QUEST_NOT_STARTED : -14,
    ERROR_MILESTONE_ALREADY_CLAIMED : -15,
    ERROR_MILESTONE_CLAIM_FAILED : -16,
    ERROR_REAL_TIME_ROOM_NOT_JOINED : -17,
    ERROR_LEFT_ROOM : -18
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////// Authentication callbacks and types

/**
 * @typedef {{AuthOperation:number}}
 */
var tAuthActionStartedCallback;

/**
 * @typedef {{AuthOperation:number, AuthStatus:number}}
 */
var tAuthActionFinishedCallback;

/**
 * @callback AuthActionStartedCallback
 * @param {tAuthActionStartedCallback} result;
 */

/**
 * @callback AuthActionFinishedCallback
 * @param {tAuthActionFinishedCallback} result;
 */

/**
 * @callback LocalPlayerCallback
 * @param {gpg.Player} local_player
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// Players callbacks and types

/**
 * @typedef {{ result : gpg.ResponseStatus, player? : gpg.Player }}
 */
var PlayersFetchSelfCallbackParams;

/**
 * @callback PlayersFetchSelfCallback
 * @param PlayersFetchSelfCallbackParams
 */

/**
 * @typedef {{ data_source? : gpg.DataSource, player_id : string }}
 */
var PlayersFetchParams;

/**
 * @typedef {{ result : gpg.ResponseStatus, player? : gpg.Player }}
 */
var PlayersFetchCallbackParams;

/**
 * @callback PlayerFetchCallback
 * @param PlayerFetchCallbackParams
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// Snapshot callbacks and types

/**
 * Snapshot UI invocation parameters.
 * <code>allow_create</code> and <code>allow_delete</code> default to false.
 * <code>max_snapshots</code> defaults to 10.
 * <code>title</code> defaults to 'title'.
 *
 * @typedef {{ allow_create?:boolean, allow_delete?:boolean, max_snapshots?:number, title:string }}
 */
var tSnapshotShowSelectionUIOperationParams;

/**
 * @typedef {{ result:string, metadata?:gpg.SnapshotMetadata, error_code?:number }}
 */
var tSnapshotShowSelectionUIOperationCallbackResult;

/**
 * @typedef {{ filename:string, conflict_policy?:gpg.SnapshotConflictPolicy, data_source?:gpg.DataSource }}
 */
var tSnapshotLoadParams;

/**
 * @typedef {{ result:gpg.ResponseStatus, metadata:gpg.SnapshotMetadata, data?:string }}
 */
var tSnapshotLoadCallbackResult;

/**
 * @typedef {{ filename : string, conflict_policy? : gpg.SnapshotConflictPolicy, description : string, data : string }}
 */
var tSnapshotSaveParams;

/**
 * @typedef {{ data_source? : gpg.DataSource }}
 */
var tSnapshotFetchAllParams;

/**
 * @callback SnapshotShowSelectUIOperationCallback
 * @param result {tSnapshotShowSelectionUIOperationCallbackResult}
 */

/**
 * @callback SnapshotLoadCallback
 * @param  {tSnapshotLoadCallbackResult}
 */

/**
 * @callback SnapshotSaveCallback
 * @param  {{ result:gpg.ResponseStatus, metadata:gpg.SnapshotMetadata }}
 */

/**
 * @callback SnapshotFetchAllCallback
 * @param  {{ result:gpg.ResponseStatus, metadata_array:gpg.SnapshotMetadata[] }}
 */

/**
 * @callback SnapshotDeleteCallback
 * @param {{ result:'success'|'error', error_code?:number }}
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////// Leaderboard callbacks and types

/**
 * @callback LeaderboardFetchCallback
 * @param {LeaderboardFetchCallbackParams}
 */

/**
 * @typedef {{ result : gpg.ResponseStatus, leaderboard: gpg.Leaderboard }}
 */
var LeaderboardFetchCallbackParams;

/**
 * @callback LeaderboardFetchAllCallback
 * @param {LeaderboardFetchAllCallbackParams}
 */

/**
 * @typedef {{ result : gpg.ResponseStatus, leaderboard_array: gpg.Leaderboard[] }}
 */
var LeaderboardFetchAllCallbackParams;

/**
 * @callback LeaderboardShowUICallback
 * @param {LeaderboardShowUICallbackParams}
 */

/**
 * @typedef {{ result : gpg.UIStatus }}
 */
var LeaderboardShowUICallbackParams;

/**
 * @callback LeaderboardShowAllUICallback
 * @param {LeaderboardShowAllUICallbackParams}
 */

/**
 * @typedef {{ result : gpg.UIStatus }}
 */
var LeaderboardShowAllUICallbackParams;

/**
 * @callback LeaderboardFetchScorePageCallback
 * @param {LeaderboardFetchScorePageCallbackParams}
 */

/**
 * @typedef {{ result : gpg.ResponseStatus, scorePage:gpg.ScorePage }}
 */
var LeaderboardFetchScorePageCallbackParams;

/**
 * @callback LeaderboardSubmitScoreCallback
 * @param {{ result : gpg.ResponseStatus }}
 */

/**
 * @callback LeaderboardFetchScoreSummaryCallback
 * @param {LeaderboardFetchScoreSummaryCallbackParams}
 */

/**
 * @typedef {{ result : gpg.ResponseStatus, score_summary : gpg.ScoreSummary }}
 */
var LeaderboardFetchScoreSummaryCallbackParams;

/**
 * @callback LeaderboardFetchAllScoreSummariesCallback
 * @param {LeaderboardFetchAllScoreSummariesCallbackParams}
 */

/**
 * @typedef {{ data_source? : gpg.DataSource, leaderboard_id : string }}
 */
var LeaderboardFetchParams;

/**
 * @typedef {{ data_source? : gpg.DataSource, timeSpan? : gpg.LeaderboardTimeSpan, collection? : gpg.LeaderboardCollection, leaderboard_id : string }}
 */
var LeaderboardFetchScoreSummaryParams;

/**
 * @typedef {{ data_source? : gpg.DataSource, leaderboard_id : string }}
 */
var LeaderboardFetchAllScoreSummariesParams;

/**
 * @typedef {{ result : gpg.ResponseStatus, score_summary_array : gpg.ScoreSummary[] }}
 */
var LeaderboardFetchAllScoreSummariesCallbackParams;

/**
 * @typedef {{ leaderboard_id : string, score:number, metadata?:string }}
 */
var LeaderboardSubmitScoreParams;

/**
 * @typedef {{ leaderboard_id:string, data_source?:gpg.DataSource, start?:gpg.LeaderboardStart, time_span?:gpg.LeaderboardTimeSpan, collection?:gpg.LeaderboardCollection, max_items?:number }}
 */
var LeaderboardFetchScorePageParams;

/**
 * @typedef {{ data_source?:gpg.DataSource, max_items?:number }}
 */
var LeaderboardFetchOtherScorePageParams;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////// Achievement callbacks and types

/**
 * @callback AchievementFetchAllCallback
 * @param AchievementFetchAllCallbackParams
 */

/**
 * @typedef {{ result : gpg.ResponseStatus, achievement_array: gpg.Achievement[] }}
 */
var AchievementFetchAllCallbackParams;

/**
 * @callback AchievementFetchCallback
 * @param AchievementFetchCallbackParams
 */

/**
 * @typedef {{ result : gpg.ResponseStatus, achievement: gpg.Achievement }}
 */
var AchievementFetchCallbackParams;

/**
 * @typedef {{ achievement_id : string, data_source: gpg.DataSource  }}
 */
var AchievementFetchParams;

/**
 * @callback AchievementShowAllUICallback
 * @param AchievementShowAllUICallbackParams
 */

/**
 * @typedef {{ result : gpg.ResponseStatus }}
 */
var AchievementShowAllUICallbackParams;


/**
 * @typedef {{ achievement_id : string, increment?: number }}
 */
var AchievementIncrementParams;

/**
 * @typedef {{ achievement_id : string, increment?: number }}
 */
var AchievementSetStepsAtLeastParams;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// Quests callbacks and types

/**
 * @typedef {{ quest_id : string, data_source : gpg.DataSource }}
 */
var QuestsFetchParams;

/**
 * @typedef {{ result : gpg.ResponseStatus, quest : gpg.Quest }}
 */
var QuestsFetchCallbackParams;

/**
 * @callback QuestsFetchCallback
 * @param QuestsFetchCallbackParams
 */


/**
 * @typedef {{ result : gpg.ResponseStatus, data : gpg.Quest[] }}
 */
var QuestsFetchListCallbackParams;

/**
 * @callback QuestsFetchListCallback
 * @param QuestsFetchListCallbackParams
 */


/**
 * @typedef {{ result : gpg.ResponseStatus, quest : gpg.Quest }}
 */
var QuestsAcceptCallbackParams;

/**
 * @callback QuestsAcceptCallback
 * @param QuestsAcceptCallbackParams
 */


/**
 * @typedef {{ result : gpg.ResponseStatus, quest : gpg.Quest, milestone : gpg.QuestMilestone }}
 */
var QuestsClaimMilestoneCallbackParams;

/**
 * @callback QuestsClaimMilestoneCallback
 * @param QuestsClaimMilestoneCallbackParams
 */


/**
 * @typedef {{ result : gpg.ResponseStatus, quest? : gpg.Quest }}
 */
var QuestsShowAllUICallbackParams;

/**
 * @callback QuestsShowAllUICallback
 * @param QuestsShowAllUICallbackParams
 */



/**
 * @typedef {{ result : gpg.ResponseStatus, quest? : gpg.Quest }}
 */
var QuestsShowUICallbackParams;

/**
 * @callback QuestsShowUICallback
 * @param QuestsShowUICallbackParams
 */


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// Events callbacks and types

/**
 * @typedef {{ event_id : string, data_source? : gpg.DataSource }}
 */
var EventsFetchParams;

/**
 * @typedef {{ result : gpg.ResponseStatus, event : gpg.Event }}
 */
var EventsFetchCallbackParams;

/**
 * @callback EventsFetchCallback
 * @param EventsFetchCallbackParams
 */


/**
 * @typedef {{ result : gpg.ResponseStatus, data : {event_id : gpg.Event} }}
 */
var EventsFetchAllCallbackParams;

/**
 * @callback EventsFetchAllCallback
 * @param EventsFetchAllCallbackParams
 */

/**
 * @typedef {{ event_id : string, increment? : number }}
 */
var EventsIncrementParams;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// Stats callbacks and types

/**
 * @typedef {{ result : gpg.ResponseStatus, data : gpg.PlayerStats}}
 */
var StatsFetchForPlayerCallbackParams;

/**
 * @callback StatsFetchForPlayerCallback
 * @param StatsFetchForPlayerCallbackParams
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// RealTimeMultiplier callbacks and types

/**
 * @typedef {{  type : 'quick_match' | 'ui'
 *              quick_match_params? : {
 *                  minimumAutomatchingPlayers : number,
 *                  maximumAutomatchingPlayers : number,
 *                  exclusiveBitMask? :          number
 *              },
 *              ui_params? : {
 *                  minimumPlayers : number,
 *                  maximumPlayers : number
 *              }
 * }}
 */
var RTCreateRoomParams;

/**
 * @typedef {{ result : gpg.ResponseStatus, room : gpg.RealTimeRoom }}
 */
var RTCreateRoomCallbackParams;

/**
 * @callback RTCreateRoomCallback
 * @param RTCreateRoomCallbackParams
 */


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Main callback management object.
 * @returns {CallbackManager}
 * @constructor
 */
var CallbackManager = function() {
    this._id_index = 1000;
    this._callbacks = {};

    return this;
};

/**
 * @lends CallbackManager.prototype
 * @type {object}
 */
CallbackManager.prototype = {
    __nextIndex: function () {
        var i = this._id_index;
        this._id_index = this._id_index + 1;
        return i;
    },

    addCallbackById: function (id, callback) {
        if (typeof this._callbacks[id] !== 'undefined') {
            // already a callback for this value ??
            cc.log('addCallbackById is already defined. id=' + id);
        } else {
            this._callbacks[id] = callback;
        }
    },

    addCallback: function (callback) {

        var index;

        if ( typeof callback!=='function' ) {
            __log('addCallback w/o function: ' + JSON.stringify(callback));
            index = -1;
        } else {
            index= this.__nextIndex();
            this.addCallbackById(index, callback);
        }

        return index;
    },

    nativeNotify: function (id, str_json) {
        if ( this._callbacks[id] ) {
            try {
                __log('received id=' + id + ' str=' + str_json);
                this._callbacks[id](JSON.parse(str_json));
            } catch (e) {
                __log('nativeNotify got error ' + e);
            }
        } else {
            __log('No callback for id: '+id);
            __log('   params: '+str_json);
        }

        // callbacks that are temporary one shot calls have to be removed.
        if ( id>=1000 ) {
            this._callbacks[id] = null;
        }
    },

    resetDefaultCallbacks : function() {

        __log('Signed out, clearing default game services callbacks.');

        // clean up previous callbacks
        for (var i = DefaultCallbacks.DEFAULT_CALLBACKS_BEGIN;
             i < DefaultCallbacks.DEFAULT_CALLBACKS_END;
             i += 1) {

            this._callbacks[i] = null;
        }
    }

};


var __callbackManager = new CallbackManager();

/**
 * @namespace
 *
 *
 */
var gpg = {

    /**
     *
     * @param response_status {gpg.ResponseStatus}
     * @returns {boolean}
     */
    IsSuccess : function( response_status ) {
        return response_status === gpg.ResponseStatus.VALID || response_status===gpg.ResponseStatus.VALID_BUT_STALE;
    },

    /**
     * @enum {number}
     */
    AuthOperation : {
        SIGN_IN : 1,
        SIGN_OUT : 2
    },

    /**
     * @enum {number}
     */
    AuthStatus : {
        VALID : BaseStatus.VALID,
        ERROR_INTERNAL : BaseStatus.ERROR_INTERNAL,
        ERROR_NOT_AUTHORIZED : BaseStatus.ERROR_NOT_AUTHORIZED,
        ERROR_VERSION_UPDATE_REQUIRED : BaseStatus.ERROR_VERSION_UPDATE_REQUIRED,
        ERROR_TIMEOUT : BaseStatus.ERROR_TIMEOUT
    },

    /**
     * The set of possible values representing the result of a UI attempt.
     *
     * @enum {number}
     */
    UIStatus : {
        VALID : BaseStatus.VALID,
        ERROR_INTERNAL : BaseStatus.ERROR_INTERNAL,
        ERROR_NOT_AUTHORIZED : BaseStatus.ERROR_NOT_AUTHORIZED,
        ERROR_VERSION_UPDATE_REQUIRED : BaseStatus.ERROR_VERSION_UPDATE_REQUIRED,
        ERROR_TIMEOUT : BaseStatus.ERROR_TIMEOUT,
        ERROR_CANCELED : BaseStatus.ERROR_CANCELED,
        ERROR_UI_BUSY : BaseStatus.ERROR_UI_BUSY,
        ERROR_LEFT_ROOM : BaseStatus.ERROR_LEFT_ROOM
    },

    /**
     * @enum {number}
     */
    LogLevel : {
        VERBOSE : 1,
        INFO : 2,
        WARNING : 3,
        ERROR : 4
    },

    /**
     * @enum {number}
     */
    ImageResolution : {
        ICON: 1,
        HI_RES: 2
    },

    /**
     * @enum {number}
     */
    SnapshotConflictPolicy : {
        MANUAL : 1,
        LONGEST_PLAYTIME : 2,
        LAST_KNOWN_GOOD : 3,
        MOST_RECENTLY_MODIFIED : 4,
        HIGHEST_PROGRESS : 5,
        DefaultConflictPolicy : 4   // MOST_RECENTLY_MODIFIED
    },

    /**
     * @enum {number}
     */
    ResponseStatus : {
        VALID : BaseStatus.VALID,
        VALID_BUT_STALE : BaseStatus.VALID_BUT_STALE,
        ERROR_LICENSE_CHECK_FAILED : BaseStatus.ERROR_LICENSE_CHECK_FAILED,
        ERROR_INTERNAL : BaseStatus.ERROR_INTERNAL,
        ERROR_NOT_AUTHORIZED : BaseStatus.ERROR_NOT_AUTHORIZED,
        ERROR_VERSION_UPDATE_REQUIRED : BaseStatus.ERROR_VERSION_UPDATE_REQUIRED,
        ERROR_TIMEOUT : BaseStatus.ERROR_TIMEOUT
    },

    /**
     * @enum {number}
     */
    DataSource : {
        CACHE_OR_NETWORK: 1,
        NETWORK_ONLY: 2

    },

    /**
     * @enum {number}
     */
    LeaderboardOrder : {
        LARGER_IS_BETTER: 1,
        SMALLER_IS_BETTER: 2,
        INVALID : -1
    },

    /**
     * Values specifying whether rankings are displayed on a leaderboard in order
     * of score or player.
     *
     * @enum {number}
     */
    LeaderboardStart : {
        TOP_SCORES: 1,
        PLAYER_CENTERED: 2,
        INVALID : -1
    },

    /**
     * Values that specify the period of time that a leaderboard covers.
     *
     * @enum {number}
     */
    LeaderboardTimeSpan : {
        DAILY: 1,
        WEEKLY: 2,
        ALL_TIME: 3,
        INVALID : -1
    },

    /**
     * Values that specify whether a leaderboard can be viewed by anyone with a
     * Google+ account (public), or only members of a player's Google+ circles
     * (social).
     *
     * @enum {number}
     *
     */
    LeaderboardCollection : {
        PUBLIC: 1,
        SOCIAL: 2,
        INVALID : -1
    },

    /**
     * Values used to specify achievement type.
     * A player makes gradual progress (steps) toward an incremental achievement.
     * He or she completes a standard achievement in a single step.
     *
     * @enum {number}
     */
    AchievementType : {
        STANDARD : 1,
        INCREMENTAL : 2,
        INVALID : -1
    },

    /**
     * Values used to specify achievement state.
     * A hidden achievement is one whose existence a player has not yet discovered.
     * make him or her aware of it.
     * A revealed achievement is one that the player knows about, but has not yet
     * earned.
     * An unlocked achievement is one that the player has earned.
     *
     * @enum {number}
     */
    AchievementState : {
        HIDDEN : 1,
        REVEALED : 2,
        UNLOCKED : 3,
        INVALID : -1
    },

    /**
     * A struct containing flags which can be provided to
     * QuestManager.FetchList in order to filter the results returned.
     *
     * @enum {number}
     */
    QuestFetchFlags : {
        UPCOMING: 1 << 0,
        OPEN: 1 << 1,
        ACCEPTED: 1 << 2,
        COMPLETED: 1 << 3,
        COMPLETED_NOT_CLAIMED: 1 << 4,
        EXPIRED: 1 << 5,
        ENDING_SOON: 1 << 6,
        FAILED: 1 << 7,
        ALL: -1

    },

    /**
     * Values used to specify the <code>Quest</code> state.
     *
     * @enum {number}
     */
    QuestState : {
        UPCOMING: 1,
        OPEN: 2,
        ACCEPTED: 3,
        COMPLETED: 4,
        EXPIRED: 5,
        FAILED: 6,
        INVALID : -1
    },

    /**
     * Values used to specify the QuestMilestone state.
     *
     * @enum {number}
     */
    QuestMilestoneState : {
        NOT_STARTED: 1,  // Note that this value is new in v1.2.
        NOT_COMPLETED: 2,
        COMPLETED_NOT_CLAIMED: 3,
        CLAIMED: 4,
        INVALID : -1
    },

    /**
     * Values specifying whether an event is hidden to the player,
     * or visible to them.
     *
     * @enum {number}
     */
    EventVisibility : {
        HIDDEN : 1,
        REVEALED : 2
    },

    /**
     * Values which identify the type of a <code>MultiplayerInvitation</code>.
     *
     * @enum {number}
     */
    MultiplayerInvitationType : {
        TURN_BASED : 1,
        REAL_TIME : 2,
        INVALID : -1
    },

    /**
     * Values representing the current status of a RealTimeRoom.
     *
     * @enum {number}
     */
    RealTimeRoomStatus : {
        INVITING : 1,
        CONNECTING : 2,
        AUTO_MATCHING : 3,
        ACTIVE : 4,
        DELETED : 5,
        INVALID : -1
    },

    /**
     * Values used to specify the state of a participant within a
     * <code>TurnBasedMatch</code>.
     *
     * @enum {number}
     */
    ParticipantStatus : {
        INVITED: 1,
        JOINED: 2,
        DECLINED: 3,
        LEFT: 4,
        NOT_INVITED_YET: 5,
        FINISHED: 6,
        UNRESPONSIVE: 7,
        INVALID: -1
    },

    /**
     * Values used to specify the outcome of a <code>TurnBasedMatch</code>
     * for a participant.
     *
     * @enum {number}
     */
    MatchResult : {
        DISAGREED: 1,
        DISCONNECTED: 2,
        LOSS: 3,
        NONE: 4,
        TIE: 5,
        WIN: 6,
        INVALID: -1
    },

    /**
     * Values used to specify the status of a <code>TurnBasedMatch</code> for the
     * local participant.
     *
     * @enum {number}
     */
    MatchStatus : {
       INVITED: 1,
       THEIR_TURN: 2,
       MY_TURN: 3,
       PENDING_COMPLETION: 4,
       COMPLETED: 5,
       CANCELED: 6,
       EXPIRED: 7,
       INVALID: -1
    },

    /**
     * @class PlatformConfiguration
     * @memberOf gpg
     * @returns {gpg.PlatformConfiguration}
     * @constructor
     */
    PlatformConfiguration : function() {

        /**
         * @memberOf PlatformConfiguration
         * @type {string}
         * @private
         */
        this._client_id = '';

        /**
         * The client id defined on the google developer console.
         * @param client_id {string}
         */
        this.SetClientID = function( client_id ) {
            this._client_id = client_id;
        };

        return this;
    },

    /**
     * Leaderboard metadata class
     *
     * @class
     * @constructor
     */
    Leaderboard : {

        /**
         * @type string
         */
        iconURL : '',

        /**
         * @type string
         */
        id      : '',

        /**
         * @type string
         */
        name    : '',

        /**
         * @type number
         */
        order   : 0,

        /**
         * @type boolean
         */
        valid   : false
    },

    /**
     *
     */
    GameServices : {

        IsAuthorized: function () {
            return _gpg.GPGWrapper.IsAuthorized();
        },

        StartAuthorizationUI: function () {
            _gpg.GPGWrapper.StartAuthorizationUI();
        },

        SignOut: function () {
            _gpg.GPGWrapper.SignOut();
        },

        /**
         * @name Builder
         * @memberOf gpg
         * @returns {gpg.Builder}
         */
        Builder: function () {

            this._enable_snapshot = false;
            this._log_level = gpg.LogLevel.VERBOSE;

            /**
             *
             * @param authActionStartedCallback {AuthActionStartedCallback}
             * @returns {gpg.Builder}
             */
            this.SetOnAuthActionStarted = function (authActionStartedCallback) {
                __callbackManager.addCallbackById(DefaultCallbacks.AUTH_ACTION_STARTED, authActionStartedCallback);
                return this;
            };

            /**
             *
             * @param authActionFinishedCallback {AuthActionFinishedCallback}
             * @returns {gpg.Builder}
             */
            this.SetOnAuthActionFinished = function (authActionFinishedCallback) {
                __callbackManager.addCallbackById(
                    DefaultCallbacks.AUTH_ACTION_FINISHED,

                    /**
                     *
                     * @param _authActionFinishedCallback {tAuthActionFinishedCallback}
                     */
                    function (_authActionFinishedCallback) {

                        if (_authActionFinishedCallback.AuthOperation === gpg.AuthOperation.SIGN_OUT &&
                            _authActionFinishedCallback.AuthStatus === gpg.AuthStatus.ERROR_NOT_AUTHORIZED) {
                            // clear default callbacks. A new game_services must be created with a new Builder
                            // so previous callbacks are no longer valid.
                            __callbackManager.resetDefaultCallbacks();
                        }

                        // call user defined auth finished callback.
                        authActionFinishedCallback(_authActionFinishedCallback);
                    });
                return this;
            };

            this.EnableSnapshots = function () {
                this._enable_snapshot = true;
                return this;
            };

            /**
             *
             * @param platform_configuration {gpg.PlatformConfiguration}
             * @returns {gpg.GameServices}
             */
            this.Create = function (platform_configuration) {

                if (platform_configuration._client_id === '') {
                    __log('No client id supplied. will not call.');
                    return null;

                } else {

                    // call native and create the game services instance based on Builder config.
                    _gpg.GPGWrapper.CreateGameServices(JSON.stringify({
                        LogLevel: this._log_level,
                        ClientID: platform_configuration._client_id,
                        EnableSnapshots: this._enable_snapshot
                    }));
                    return gpg.GameServices;
                }
            };

            /**
             * @param level {gpg.LogLevel}
             */
            this.SetLogging = function (level) {
                this._log_level = level;
                return this;
            };

            return this;
        },

        /**
         * @class
         * @memberOf gpg
         * @constructor
         */
        SnapshotMetadata : {

            filename : '',
            coverImageURL: '',
            description: '',
            valid: false,
            lastModifiedTime: 0,
            playedTime:0
        },

        /**
         * Gets and sets various player-related data.
         */
        Players: {

            /**
             *
             * Asynchronously loads all data for all currently signed-in players.
             * Calls the provided FetchSelfCallback on operation completion.
             * Not specifying data_source will default to CACHE_OR_NETWORK.
             *
             * @param data_source {gpg.DataSource}
             * @param callback {PlayersFetchSelfCallback}
             */
            FetchSelf : function( data_source, callback ) {
                _gpg.GPGPlayerWrapper.FetchSelf(
                    __callbackManager.addCallback(callback),
                    data_source
                );
            },

            /**
             * Asynchronously loads all data for a specific player.
             * Calls the provided FetchCallback on operation completion.
             * Not specifying data_source makes it default to CACHE_OR_NETWORK.
             *
             * @param params {PlayersFetchParams}
             * @param callback {PlayerFetchCallback}
             */
            Fetch : function( params, callback ) {

                if ( typeof params.player_id==='undefined' ) {
                    __log("Fetch needs a player id. Won't call.");
                    return;
                }

                __dp( params, P_DATA_SOURCE );

                _gpg.GPGPlayerWrapper.Fetch(
                    __callbackManager.addCallback(callback),
                    params.data_source,
                    params.player_id
                );
            }
        },

        Snapshots: {

            /**
             *
             * @param params {tSnapshotShowSelectionUIOperationParams}
             * @param callback {SnapshotShowSelectUIOperationCallback}
             */
            ShowSelectUIOperation: function (params, callback) {
                if (typeof params.allow_create === 'undefined') {
                    params.allow_create = false;
                }
                if (typeof params.allow_delete === 'undefined') {
                    params.allow_delete = false;
                }

                __dp( params, [P_SNP_TITLE, P_SNP_PAGE_SIZE] );

                var index = __callbackManager.addCallback(callback);
                _gpg.GPGSnapshotWrapper.ShowSelectUIOperation( index, JSON.stringify(params) );
            },

            /**
             * In params object, if conflict_policy is not set, it will default to
             * <code>gpg.SnapshotConflictPolicy.MOST_RECENTLY_MODIFIED</code>.
             * If datasource parameter is not set, it will default to <code>gpg.DataSource.CACHE_OR_NETWORK</code>.
             * @param params {tSnapshotLoadParams}
             * @param callback {SnapshotLoadCallback}
             */
            Load : function( params, callback ) {

                if ( typeof params[P_SNP_FILE_NAME]==='undefined' || !params[P_SNP_FILE_NAME] ) {
                    __log('Snapshot load has no filename. Will not call');
                    return;
                }

                __dp( params, [P_SNP_CONFLICT_POLICY, P_DATA_SOURCE]);

                var index = __callbackManager.addCallback(callback);
                _gpg.GPGSnapshotWrapper.Load( index, params[P_SNP_FILE_NAME], params[P_SNP_CONFLICT_POLICY], params[P_DATA_SOURCE] );
            },

            /**
             *
             * @param params {tSnapshotSaveParams}
             * @param callback {SnapshotSaveCallback}
             */
            Save : function( params, callback ) {

                if ( typeof params[P_SNP_FILE_NAME]==='undefined' || typeof params.data==='undefined' ) {
                    __log('Snapshot save has no filename or no contents to save. Will not call.');
                    return;
                }

                __dp( params, [P_SNP_CONFLICT_POLICY, P_SNP_DESCRIPTION] );

                var index = __callbackManager.addCallback(callback);
                _gpg.GPGSnapshotWrapper.Save( index, JSON.stringify(params) );
            },

            /**
             *
             * @param params {tSnapshotFetchAllParams}
             * @param callback {SnapshotFetchAllCallback}
             * @constructor
             */
            FetchAll : function( params, callback ) {
                __dp( params, P_DATA_SOURCE );

                var index = __callbackManager.addCallback(callback);
                _gpg.GPGSnapshotWrapper.FetchAll( index, JSON.stringify(params) );
            },

            /**
             *
             * @param filename {string} A SnapshotMetadata valid filename.
             * @param callback {SnapshotDeleteCallback}
             */
            Delete : function( filename, callback ) {
                if ( !filename ) {
                    __log('Snapshot delete needs a filename. Will not call.');
                    return;
                }

                var index = __callbackManager.addCallback(callback);
                _gpg.GPGSnapshotWrapper.Delete( index, filename );
            }
        },

        Leaderboards : {
            /**
             * Asynchronously loads leaderboard data for the currently signed-in player.
             * @param params {LeaderboardFetchParams}
             * @param callback? {LeaderboardFetchCallback}
             */
            Fetch : function( params, callback ) {

                if ( typeof params.leaderboard_id==='undefined' ) {
                    __log('Leaderboards Fetch needs a leaderboard id. Will not call.');
                    __log('received params: '+JSON.stringify(params));
                    return;
                }

                __dp( params, [P_DATA_SOURCE] );

                _gpg.GPGLeaderboardWrapper.Fetch(
                    __callbackManager.addCallback(callback),
                    params.leaderboard_id,
                    params.data_source );
            },

            /**
             * Asynchronously loads data for all leaderboards for the currently
             * signed-in player.
             * @param datasource {gpg.DataSource}
             * @param callback? {LeaderboardFetchAllCallback}
             */
            FetchAll : function( datasource, callback ) {
                _gpg.GPGLeaderboardWrapper.FetchAll(
                    __callbackManager.addCallback(callback),
                    datasource );
            },

            /**
             * Asynchronously fetches all data for a specific leaderboard score summary,
             * which comprises a given leaderboard's collection and time span.
             * Specify gpg.LeaderboardTimeSpan.DAILY, gpg.LeaderboardTimeSpan.WEEKLY, or
             * gpg.LeaderboardTimeSpan.ALL_TIME for time span.
             * Specify gpg.LeaderboardCollection.PUBLIC or gpg.LeaderboardCollection.SOCIAL
             * for collection.
             * Not specifying data_source makes this function call to use gpg.DataSource.CACHE_OR_NETWORK.
             * Not specifying time_span, makes this function call to use gpg.LeaderboardTimeSpan.ALL_TIME.
             * Not specifying collection makes this function call to use gpg.LeaderboardCollection.PUBLIC.
             *
             * @param params {LeaderboardFetchScoreSummaryParams}
             * @param callback?  {LeaderboardFetchScoreSummaryCallback}
             */
            FetchScoreSummary : function( params, callback ) {

                if ( typeof params.leaderboard_id ==='undefined' ) {
                    __log('Leaderboards Fetch score summary needs a leaderboard id. Will not call.');
                    __log('received params: '+JSON.stringify(params));
                    return;
                }

                __dp( params, [P_DATA_SOURCE, P_LDB_COLLECTION, P_LDB_TIME_SPAN]);

                _gpg.GPGLeaderboardWrapper.FetchScoreSummary(
                    __callbackManager.addCallback(callback),
                    params.data_source,
                    params.leaderboard_id,
                    params.timeSpan,
                    params.collection
                );
            },

            /**
             * Asynchronously fetches all score summaries for a specific leaderboard.
             * Not specifying data_source makes this function call to use gpg.DataSource.CACHE_OR_NETWORK.
             *
             * @param params {LeaderboardFetchAllScoreSummariesParams}
             * @param callback? {LeaderboardFetchAllScoreSummariesCallback}
             */
            FetchAllScoreSummaries : function( params, callback ) {
                if ( typeof params.leaderboard_id ==='undefined' ) {
                    __log('Leaderboards Fetch all score summaries needs a leaderboard id. Will not call.');
                    __log('received params: '+JSON.stringify(params));
                    return;
                }

                __dp( params, P_DATA_SOURCE );

                _gpg.GPGLeaderboardWrapper.FetchAllScoreSummaries(
                    __callbackManager.addCallback(callback),
                    params.data_source,
                    params.leaderboard_id
                );
            },

            /**
             * Submit, for the currently signed-in player, a score to the leaderboard
             * optionally associated with a specific id and metadata (such as something the player
             * did to earn the score). The score is ignored if it is worse (as defined in
             * the leaderboard configuration) than a previously submitted score for the
             * same player.
             *
             * @param params {LeaderboardSubmitScoreParams}
             * @param callback? {LeaderboardSubmitScoreCallback}
             */
            SubmitScore : function( params, callback ) {

                if ( typeof params.leaderboard_id ==='undefined' || typeof params.score==='undefined' ) {
                    __log('Leaderboards submit score needs a leaderboard id and a score. Will not call.');
                    __log('received params: '+JSON.stringify(params));
                    return;
                }

                __dp( params, P_LDB_METADATA );

                _gpg.GPGLeaderboardWrapper.SubmitScore(
                    __callbackManager.addCallback(callback),
                    params.leaderboard_id,
                    params.score,
                    params.metadata
                );
            },

            /**
             * Presents to the user a UI that displays information about a specific
             * leaderboard.  It asynchronously calls <code>callback</code>.
             *
             * @param leaderboard_id {string}
             * @param callback? {LeaderboardShowUICallback}
             */
            ShowUI : function( leaderboard_id, callback ) {
                _gpg.GPGLeaderboardWrapper.ShowUI(
                    __callbackManager.addCallback(callback),
                    leaderboard_id
                );
            },

            /**
             * Presents to the user a UI that displays information about all leaderboards.
             * It asynchronously calls <code>callback</code>.
             *
             * @param callback? {LeaderboardShowAllUICallback}
             */
            ShowAllUI : function( callback ) {
                _gpg.GPGLeaderboardWrapper.ShowAllUI( __callbackManager.addCallback(callback) );
            },

            /**
             * Asynchronously returns data for a score page identified by score-page
             * token. max_results specifies the maximum number of scores to include
             * on the resulting score page, which may be no larger than 25.
             *
             * if no collection is set, it will default to gpg.LeaderboardCollection.PUBLIC.
             * if no data source is set, it will default to gpg.DataSource.CACHE_OR_NETWORK.
             * if no max items is set, it will default to 10.
             * if no start is defined, it will default to gpg.LeaderboardStart.PLAYER_CENTERED.
             * if no time span is set, it will default to gpg.LeaderboardTimeSpan.ALL_TIME.
             *
             * @param params {LeaderboardFetchScorePageParams}
             * @param callback? {LeaderboardFetchScorePageCallback}
             * @constructor
             */
            FetchScorePage : function( params, callback ) {
                if ( typeof params.leaderboard_id==='undefined' ) {
                    __log('Leaderboards Fetch Score page needs a leaderboard id and a score. Will not call.');
                    __log('received params: '+JSON.stringify(params));
                    return;
                }

                __dp(
                    params,
                    [
                        P_DATA_SOURCE,
                        P_LDB_START,
                        P_LDB_TIME_SPAN,
                        P_LDB_COLLECTION,
                        P_LDB_SCORE_PAGE_SIZE
                    ] );

                _gpg.GPGLeaderboardWrapper.FetchScorePage(
                    __callbackManager.addCallback(callback),
                    params.leaderboard_id,
                    params.data_source,
                    params.start,
                    params.time_span,
                    params.collection,
                    params.max_items
                );
            },

            /**
             *
             * @param params {LeaderboardFetchOtherScorePageParams}
             * @param callback? {LeaderboardFetchScorePageCallback}
             * @constructor
             */
            FetchNextScorePage : function( params, callback ) {

                __dp( params, [ P_DATA_SOURCE, P_LDB_SCORE_PAGE_SIZE ]);

                _gpg.GPGLeaderboardWrapper.FetchNextScorePage(
                    __callbackManager.addCallback(callback),
                    params.data_source,
                    params.max_items
                );
            },

            /**
             *
             * @param params {LeaderboardFetchOtherScorePageParams}
             * @param callback? {LeaderboardFetchScorePageCallback}
             * @constructor
             */
            FetchPreviousScorePage : function( params, callback ) {

                __dp( params, [ P_DATA_SOURCE, P_LDB_SCORE_PAGE_SIZE ]);

                _gpg.GPGLeaderboardWrapper.FetchPreviousScorePage(
                    __callbackManager.addCallback(callback),
                    params.data_source,
                    params.max_items
                );
            }
        },

        /**
         *
         */
        Achievements : {
            /**
             * Asynchronously loads data for all leaderboards for the currently
             * signed-in player.
             * @param datasource {gpg.DataSource}
             * @param callback? {AchievementFetchAllCallback}
             */
            FetchAll : function( datasource, callback ) {
                _gpg.GPGAchievementWrapper.FetchAll(
                    __callbackManager.addCallback(callback),
                    datasource);
            },

            /**
             * Asynchronously loads data for a specific achievement for the currently
             * signed-in player. Calls the provided <code>FetchCallback</code> on
             * operation completion.
             *
             * if params.data_source is not set, it will default to <code>CACHE_OR_NETWORK</code>.
             *
             * @param params {AchievementFetchParams}
             * @param callback {AchievementFetchCallback}
             */
            Fetch : function( params, callback ) {

                __dp( params, P_DATA_SOURCE );

                _gpg.GPGAchievementWrapper.Fetch(
                    __callbackManager.addCallback(callback),
                    params.achievement_id,
                    params.data_source);
            },

            /**
             * Presents to the user a UI that displays information about all achievements.
             * It asynchronously calls <code>ShowAllUICallback</code>.
             * @param callback {AchievementShowAllUICallback}
             * @constructor
             */
            ShowAllUI : function( callback ) {
                _gpg.GPGAchievementWrapper.ShowAllUI(__callbackManager.addCallback(callback));
            },

            /**
             * Increments an achievement by the given number of steps. Leaving the
             * increment undefined causes its value to default to 1. The achievement
             * must be an incremental achievement. Once an achievement reaches the
             * maximum number of steps, it is unlocked automatically. Any further
             * increments are ignored.
             *
             * This method has no callback.
             *
             * @param params {AchievementIncrementParams}
             * @constructor
             */
            Increment : function( params ) {
                if ( typeof params.increment==='undefined' ) {
                    params.increment = 1;
                }

                _gpg.GPGAchievementWrapper.Increment(
                    params.achievement_id,
                    params.increment );
            },

            /**
             * Set an achievement to have at least the given number of steps completed.
             * Calling this method while the achievement already has more steps than the
             * provided value is a no-op. Once the achievement reaches the maximum number
             * of steps, the achievement is automatically unlocked, and any further
             * mutation operations are ignored.
             *
             * @param params {AchievementSetStepsAtLeastParams}
             */
            SetStepsAtLeast : function( params ) {
                if ( typeof params.increment==='undefined' ) {
                    params.increment = 1;
                }

                _gpg.GPGAchievementWrapper.SetStepsAtLeast(
                    params.achievement_id,
                    params.increment
                );
            },

            /**
             * Reveal a hidden achievement to the currently signed-in player. If the
             * achievement has already been unlocked, this will have no effect.
             *
             * @param achievement_id {string}
             */
            Reveal : function( achievement_id ) {
                _gpg.GPGAchievementWrapper.Reveal( achievement_id );
            },

            /**
             * Unlocks an achievement for the currently signed in player. If the
             * achievement is hidden, the SDK reveals it, as well.
             *
             * @param achievement_id {string}
             */
            Unlock : function( achievement_id ) {
                _gpg.GPGAchievementWrapper.Unlock( achievement_id );
            }
        },

        RealTimeMultiplayer : {

            /**
             * Asynchronously creates a <code>RealTimeRoom</code> object using the
             * provided
             * <code>RealTimeRoomConfig</code> class. If creation is successful, this
             * function returns the <code>RealTimeRoom</code> object via the provided
             * <code>RealTimeRoomCallback</code>.
             *
             * @param params {RTCreateRoomParams}
             * @param callback {RTCreateRoomCallback}
             */
            CreateRealTimeRoom : function( params, callback ) {
                _gpg.GPGRealTimeMultiplayerWrapper.CreateRealTimeRoom(
                    __callbackManager.addCallback(callback),
                    JSON.stringify(params)
                );
            }

        },

        Quests : {
            /**
             * Asynchronously loads quest data for the currently signed-in player.
             * Calls the provided <code>FetchCallback</code> upon operation completion.
             * Specify <code>data_source</code> as <code>CACHE_OR_NETWORK</code> or
             * <code>NETWORK_ONLY</code>.
             * @param params {QuestsFetchParams}
             * @param callback? {QuestsFetchCallback}
             */
            Fetch : function(params, callback) {

                if ( typeof params.quest_id==='undefined' ) {
                    __log("Quest fetch needs quest id. Won't call.");
                    return;
                }

                __dp( params, P_DATA_SOURCE );

                _gpg.GPGQuestsWrapper.Fetch(
                    __callbackManager.addCallback(callback),
                    params.quest_id,
                    params.data_source
                );
            },

            /**
             * Asynchronously loads data for all quests, regardless of state, for the
             * currently signed-in player.
             * Specify <code>data_source</code> as <code>CACHE_OR_NETWORK</code>
             * or <code>NETWORK_ONLY</code>.
             *
             * @param data_source? {gpg.DataSource}
             * @param callback? {QuestsFetchListCallback}
             */
            FetchList : function(data_source, callback) {

                if ( arguments.length===1 ) {
                    callback = data_source;
                    data_source = undefined;
                }

                if ( typeof data_source==='undefined' ) {
                    data_source = gpg.DataSource.CACHE_OR_NETWORK;
                }

                _gpg.GPGQuestsWrapper.FetchList(
                    __callbackManager.addCallback(callback),
                    data_source
                );
            },

            /**
             * Presents to the user a UI that displays information about all quests.
             * It asynchronously calls <code>callback</code>.
             *
             * @param callback? {QuestsShowAllUICallback}
             */
            ShowAllUI : function(callback) {

                _gpg.GPGQuestsWrapper.ShowAllUI(
                    __callbackManager.addCallback(callback)
                );
            },

            ShowUI : function(quest_id, callback) {

                _gpg.GPGQuestsWrapper.ShowUI(
                    __callbackManager.addCallback(callback),
                    quest_id
                );

            },

            /**
             * Asynchronously accept a quest. The quest must have a state
             * <code>QuestState.OPEN</code>. Incrementing the associated events will
             * start tracking progress toward the milestone goal.
             *
             * @param quest_id {string}
             * @param callback? {QuestsAcceptCallbackParams}
             */
            Accept : function( quest_id, callback ) {
                if ( typeof quest_id==='undefined' ) {
                    __log("Quest accept needs quest id. Won't call.");
                    return;
                }

                _gpg.GPGQuestsWrapper.Accept(
                    __callbackManager.addCallback(callback),
                    quest_id
                );
            },

            /**
             * Asynchronously claims the milestone. Doing so calls the server, marking
             * the milestone as completed. If the milestone is currently unclaimable, or
             * if it has been claimed already on this or another device, you will get an
             * error. If this call returns <code>QuestClaimMilestoneStatus.VALID</code>,
             * you (as a developer) must still reward the player. Use the milestone
             * <code>CompletionRewardData</code> to do so.
             *
             * @param milestone_id {string}
             * @param callback? {QuestsClaimMilestoneCallback}
             */
            ClaimMilestone : function(milestone_id, callback) {
                if ( typeof milestone_id==='undefined' ) {
                    __log("Quest claim milestone needs milestone id. Won't call.");
                    return;
                }

                _gpg.GPGQuestsWrapper.ClaimMilestone(
                    __callbackManager.addCallback(callback),
                    milestone_id
                );
            }
        },

        Events : {
            /**
             * Asynchronously loads data for a specific event for the currently
             * signed-in player Calls the provided <code>callback</code> on operation
             * completion. Specify <code>data_source</code> as
             * <code>CACHE_OR_NETWORK</code> or <code>NETWORK_ONLY</code>.
             *
             * @param params {EventsFetchParams}
             * @param callback? {EventsFetchCallback}
             */
            Fetch : function(params, callback) {

                if ( typeof params.event_id==='undefined' ) {
                    __log("Events Fetch needs event id. Won't call.");
                    return;
                }

                __dp( params, P_DATA_SOURCE );

                _gpg.GPGEventsWrapper.Fetch(
                    __callbackManager.addCallback(callback),
                    params.event_id,
                    params.data_source
                );
            },

            /**
             * Asynchronously loads all event data for the currently signed-in
             * player. Calls the provided <code>callback</code> on operation
             * completion. Specify data_source as <code>CACHE_OR_NETWORK</code> or
             * <code>NETWORK_ONLY</code>.
             *
             * @param data_source? {gpg.DataSource}
             * @param callback {EventsFetchAllCallback}
             */
            FetchAll : function( data_source, callback) {

                if ( arguments.length===1 ) {
                    callback = data_source;
                    data_source = undefined;
                }

                if ( typeof data_source === 'undefined' ) {
                    data_source = gpg.DataSource.CACHE_OR_NETWORK;
                }

                _gpg.GPGEventsWrapper.FetchAll(
                    __callbackManager.addCallback(callback),
                    data_source
                );
            },

            /**
             * Increments an event by the given number of steps.
             *
             * @param params {EventsIncrementParams}
             */
            Increment : function( params ) {

                if ( typeof params.event_id === 'undefined' ) {
                    __log("Events increment needs event id. Won't call.");
                    return;
                }

                if ( typeof params.increment==='undefined' ) {
                    params.increment = 1;
                }

                _gpg.GPGEventsWrapper.Increment(
                    params.event_id,
                    params.increment
                );
            }
        },

        Stats : {

            /**
             * Asynchronously loads all stats data for the currently signed-in player.
             * Calls the provided FetchForPlayerCallback on operation completion.
             * Specify data_source as CACHE_OR_NETWORK or NETWORK_ONLY.
             *
             * @param data_source? {gpg.DataSource}
             * @param callback {StatsFetchForPlayerCallback}
             */
            FetchForPlayer : function(data_source, callback) {

                if (arguments.length === 1) {
                    callback = data_source;
                    data_source = undefined;
                }

                if (typeof data_source === 'undefined') {
                    data_source = gpg.DataSource.CACHE_OR_NETWORK;
                }

                _gpg.GPGStatsWrapper.FetchForPlayer(
                    __callbackManager.addCallback(callback),
                    data_source
                );
            }
        }
    }
};

/**
 * @typedef {{ valid:boolean, levelNumber:number, minimumXP:number, maximumXP:number }}
 */
gpg.PlayerLevel;


/**
 * A local player wrapper object.
 * This object can be safely cached for information requests on the current logged-in player.
 *
 * @class Player
 * @memberOf gpg
 * @constructor
 */
gpg.Player= function( ) {
    return this;
};

/**
 * @lends gpg.Player.prototype
 * @type {object}
 */
gpg.Player.prototype = {

    /**
     * Get local player display name.
     */
    name: '',

    id: '',

    avatarUrlIconRes: '',

    avatarUrlHiRes: '',

    /**
     *
     * @returns {boolean}
     */
    hasLevelInfo: false,

    /**
     *
     * @type number
     */
    currentXP: -1,

    /**
     *
     * @type number
     */
    lastLevelUpTime: -1,

    /**
     *
     * @returns {string}
     */
    title: '',

    /**
     *
     * @type gpg.PlayerLevel|null
     */
    currentLevel: null,

    /**
     *
     * @type {gpg.PlayerLevel|null}
     */
    nextLevel: null
};

gpg.Player.__Dump = function( p ) {
    __log('Id=' + p.id);
    __log('Name=' + p.name);
    __log('Title=' + p.title);
    __log('AvatarURL icon=' + p.avatarUrlIconRes);
    __log('AvatarURL hires=' + p.avatarUrlHiRes);
    __log('CurrentXP=' + p.currentXP);
    __log('LastLevelUpTime=' + p.lastLevelUpTime);
    __log('HasLevelInfo=' + p.hasLevelInfo);
    __log('CurrentLevel=' + p.currentLevel.levelNumber);
    __log('NextLevel=' + p.nextLevel.levelNumber);
};

/**
 * A data structure that allows you to access data about a specific player.
 *
 * @class
 * @memberOf gpg
 * @constructor
 */
gpg.PlayerStats = function() {
    return this;
};

/**
 * @lends gpg.PlayerStats.prototype
 */
gpg.PlayerStats.prototype = {

    /**
     * Returns true when the returned PlayerStats object is populated with data
     * and is accompanied by a successful response status; false for an
     * unpopulated user-created PlayerStats or for a populated one accompanied by
     * an unsuccessful response status.
     * It must be true for the getter functions on this object to be usable.
     */
    valid : false,

    /**
     * Returns whether or not this PlayerStats object has average session length
     * available. It must be true for <code>averageSessionLength</code>
     * to be usable.
     */
    hasAverageSessionLength : false,

    /**
     * Retrieves the average session length for this player, if known.
     * <code>hasAverageSessionLength</code> must be true for this function
     * to be usable.
     *
     * @type number
     */
    averageSessionLength : -1,

    /**
     * Whether or not this PlayerStats object has churn probability
     * available. It must be true for <code>churnProbability</code> to be
     * usable.
     */
    hasChurnProbability : false,

    /**
     * Retrieves the churn probability for this player, if known.
     * <code>hasChurnProbability</code> must be true for this function
     * to be usable.
     *
     * @type number
     */
    churnProbability : -1,

    /**
     * Whether or not this PlayerStats object has days since last played
     * available. It must be true for <code>daysSinceLastPlayed</code> to be
     * usable.
     */
    hasDaysSinceLastPlayed : false,

    /**
     * Days since last played for this player, if known.
     * <code>hasDaysSinceLastPlayed</code> must be true for this function to
     * be usable.
     *
     * @type number
     */
    daysSinceLastPlayed : -1,

    /**
     * Whether or not this PlayerStats object has number of purchases
     * available. It must be true for <code>numberOfPurchases</code> to be
     * usable.
     */
    hasNumberOfPurchases : false,

    /**
     * Number of purchases for this player, if known.
     * <code>hasNumberOfPurchases</code> must be true for this function to
     * be usable.
     *
     * @type number
     */
    numberOfPurchases : -1,

    /**
     * Whether or not this PlayerStats object has number of sessions
     * available. It must return true for <code>numberOfSessions</code> to be
     * usable.
     */
    hasNumberOfSessions : false,

    /**
     * Number of sessions for this player, if known.
     * <code>hasNumberOfSessions</code> must be true for this function to
     * be usable.
     *
     * @type number
     */
    numberOfSessions : -1,

    /**
     * Whether or not this PlayerStats object has session percentile
     * available. It must return true for <code>sessionPercentile</code> to be
     * usable.
     */
    hasSessionPercentile : false,

    /**
     * Retrieves the session percentile information for this player, if known.
     * <code>hasSessionPercentile</code> must be true for this function
     * to be usable.
     *
     * @type number
     */
    sessionPercentile : -1,

    /**
     * Whether or not this PlayerStats object has spend percentile
     * available. It must be true for <code>spendPercentile()</code> to be
     * usable.
     */
    hasSpendPercentile : false,

    /**
     * Spend percentile information for this player, if known.
     * <code>hasSpendPercentile</code> must return true for this function
     * to be usable.
     *
     * @type number
     */
    spendPercentile : -1
};

/**
 * @class RealTimeRoot
 * @memberOf gpg
 * @constructor
 */
gpg.RealTimeRoom = function() {
    return this;
};

/**
 * @lends gpg.RealTimeRoom.prototype
 */
gpg.RealTimeRoom.prototype = {

    /**
     * true if this <code>RealTimeRoom</code> object is populated with
     * data.
     */
    valid : false,

    /**
     * Returns an ID that uniquely identifies this <code>RealTimeRoom</code>
     * object.
     * To retrieve this room at a later point, use this ID with
     * <code>RealTimeRoom.FetchRoom</code>.
     */
    id : '',

    /**
     * Time at which this <code>RealTimeRoom</code> object was created
     * (expressed as milliseconds since the Unix epoch).
     *
     * @type number
     */
    creationTime : -1,

    /**
     * Returns the participant who created this room.
     *
     * @type gpg.MultiplayerParticipant
     */
    creatingParticipant : null,

    /**
     * Returns the status of the room. The status determines what actions can be
     * taken on a room.
     *
     * @type gpg.RealTimeRoomStatus
     */
    status : gpg.RealTimeRoomStatus.INVALID,

    /**
     * A game-specific variant identifier that can be used by a game to
     * identify different game modes.
     *
     * @type number
     */
    variant : -1,

    /**
     * A server-generated summary of the state of the room.
     */
    description : '',

    /**
     * A vector of all participants in this room.
     *
     * @type gpg.MultiplayerParticipant[]
     */
    participants : null,

    /**
     * A server-generated estimate of the amount of time it will take to fill this
     * room's auto-matching slots.
     *
     * @type number
     */
    automatchWaitEstimate : -1,

    /**
     * Returns the number of available auto-matching slots for the room. This
     * number is equal to the number of auto-matching slots with which the room
     * was created, minus the number of participants who have already been added
     * via auto-matching.
     *
     * @type number
     */
    remainingAutomatchingSlots : -1

};

/**
 * A data structure containing data about a participant in a multiplayer match.
 * @class MultiplayerParticipant
 * @memberOf gpg
 * @constructor
 */
gpg.MultiplayerParticipant = function() {
    return this;
};

/**
 * @lends gpg.MultiplayerParticipant.prototype
 */
gpg.MultiplayerParticipant.prototype = {

    /**
     * true if this <code>MultiplayerParticipant</code> is populated
     * with data. Must be true in order for the getter functions
     * (<code>DisplayName</code>, <code>AvatarUrl</code>, <code>Id</code>, etc.)
     * on this <code>MultiplayerParticipant</code> to be usable.
     */
    valid: false,

    /**
     * The display name for this <code>MultiplayerParticipant</code>
     */
    displayName: '',

    /**
     * URL where the image of this
     * <code>MultiplayerParticipant</code>'s avatar resides.
     */
    avatarUrlHiRes: '',

    /**
     * URL where the image of this
     * <code>MultiplayerParticipant</code>'s avatar resides.
     */
    avatarUrlIconRes: '',

    /**
     * The <code>Id</code> of this <code>MultiplayerParticipant</code>.
     * <code>Id</code>'s are only valid in the scope of a single match, and are
     * different from <code>Player.id</code>'s.
     */
    id: '',

    /**
     * Whether a Player is associated with this
     * <code>MultiplayerParticipant</code>.
     */
    hasPlayer: false,

    /**
     * The Player associated with this
     * <code>MultiplayerParticipant</code>.
     *
     * @type gpg.Player|null
     */
    player: null,

    /**
     * The status of this <code>MultiplayerParticipant</code> with respect to the
     * match.
     */
    status: gpg.ParticipantStatus.INVALID,

    /**
     * Whether this participant has a result for this match. If false,
     * {@link matchResult} and {@link matchRank} do not return valid data.
     *
     */
    hasMatchResult: false,

    /**
     * The result of the match for this <code>gpg.MultiplayerParticipant</code>.
     * {@link valid} must return true for this function to be usable. If
     * <code>hasMatchResult</code> does not return true, this function returns
     * <code>gpg.MatchResult.None</code>.
     *
     * @type gpg.MatchResult
     */
    matchResult: gpg.MatchResult.INVALID,

    /**
     * The rank for this <code>MultiplayerParticipant</code> within its match.
     * {@link valid} must return true for this function to be usable. If
     * <code>hasMatchResult</code> does not return true, this function returns
     * 0.
     *
     * @type number
     */
    matchRank: -1,

    /**
     * Whether this participant is connected to a <code>RealTimeRoom</code>.
     * Always false if this is a participant from a <code>TurnBasedMatch</code>.
     */
    isConnectedToRoom: false
};

/**
 * Quest metadata object.
 * @class
 * @memberOf gpg
 * @constructor
 */
gpg.QuestMilestone = function() {
    return this;
};

/**
 * @lends gpg.QuestMilestone.prototype
 */
gpg.QuestMilestone.prototype= {

    valid : false,

    id : '',

    questId : '',

    eventId : '',

    /**
     * @type gpg.QuestMilestoneState
     */
    state : gpg.QuestMilestoneState.INVALID,

    /**
     * @type number
     */
    currentCount : -1,

    /**
     * @type number
     */
    targetCount : -1,

    completionRewardData : ''
};

/**
 * A single data structure allowing you to access data about the status of a
 * specific quest.
 *
 * @class
 * @memberOf gpg
 * @constructor
 */
gpg.Quest = function() {
    return this;
};

/**
 * @lends gpg.Quest.prototype
 */
gpg.Quest.prototype = {
    valid : false,

    id : '',

    name : '',

    description : '',

    iconUrl : '',

    bannerUrl : '',

    /**
     * @type gpg.QuestMilestone
     */
    currentMilestone : null,

    /**
     * @type gpg.QuestState
     */
    questState : gpg.QuestState.INVALID,

    /**
     * @type number
     */
    startTime : -1,

    /**
     * @type number
     */
    expirationTime : -1,

    /**
     * @type number
     */
    acceptedTime : -1
};

/**
 * A single data structure containing data about the status of
 * a specific event. Data comprise two types: user-specific (e.g.,
 * whether the user has unlocked the event), and global (e.g., event name).
 *
 * @class
 * @memberOf gpg
 * @constructor
 */
gpg.Event = function() {
    return this;
};

/**
 * @lends gpg.Event.prototype
 */
gpg.Event.prototype = {

    valid : false,

    id : '',

    name : '',

    description : '',

    /**
     * @type gpg.EventVisibility
     */
    visibility : gpg.EventVisibility.INVALID,

    /**
     * @type number
     */
    count : -1
};


/**
 * Achievement metadata class
 *
 * @class
 * @memberOf gpg
 * @constructor
 */
gpg.Achievement = function() {
    return this;
};

/**
 *
 * @lends gpg.Achievement.prototype
 */
gpg.Achievement.prototype = {

    /**
     * @type number
     */
    currentSteps : -1,

    /**
     * @type string
     */
    description : '',

    /**
     * @type string
     */
    id : '',

    /**
     * millis.
     * @type number
     */
    lastModifiedTime : -1,

    /**
     * @type string
     */
    name : '',

    /**
     * @type string
     */
    revealedIconUrl : '',

    /**
     * @type gpg.AchievementState
     */
    state : gpg.AchievementState.INVALID,

    /**
     * @type number
     */
    totalSteps : -1,

    /**
     * @type gpg.AchievementType
     */
    type : gpg.AchievementType.INVALID,

    /**
     * @type string
     */
    unlockedIconUrl : '',

    /**
     * @type boolean
     */
    valid : false,

    /**
     * @type number
     */
    xp : -1
};


/**
 * Single data structure which allows you to access data about a player's
 * score.
 *
 * @class
 * @memberOf gpg;
 * @constructor
 */
gpg.Score = function() {
    return this;
};

/**
 * @lends gpg.Score.prototype
 */
gpg.Score.prototype = {
    /**
     * @type boolean
     */
    valid : false,

    /**
     * @type number
     */
    rank : 0,

    /**
     * @type number
     */
    value : 0,

    /**
     * @type string
     */
    metadata : ''
};

/**
 * A single data structure which allows you to access a summary of score
 * information.
 *
 * @class
 * @memberOf gpg
 * @constructor
 */
gpg.ScoreSummary= function() {
    return this;
};

/**
 * @lends gpg.ScoreSummary.prototype
 */
gpg.ScoreSummary.prototype = {

    /**
     * @type boolean
     */
    valid : false,

    /**
     * @type string
     */
    leaderboardId : '',

    /**
     * @type gpg.LeaderboardTimeSpan
     */
    timeSpan : gpg.LeaderboardTimeSpan.INVALID,

    /**
     * @type gpg.LeaderboardCollection
     */
    collection : gpg.LeaderboardCollection.INVALID,

    /**
     * @type number
     */
    approximateNumberOfScores : 0,

    /**
     * @type gpg.Score
     */
    currentPlayerScore : null
};

/**
 * A single data structure which allows you to access score data.
 * Data include Leaderboard id, start, timespan, collection, previous
 * score-page token, next score-page token, and the vector of all
 * score entries.
 *
 * @class
 * @memberOf gpg
 * @constructor
 */
gpg.ScorePage = function() {
    return this;
};

/**
 * A class that creates an entry on a score page.
 *
 * @name Entry
 * @memberOf gpg.ScorePage
 * @constructor
 */
gpg.ScorePage.Entry = function() {
    return this;
};

/**
 * @lends gpg.ScorePage.Entry.prototype
 */
gpg.ScorePage.Entry.prototype = {

    /**
     * @type string
     */
    playerId : '',

    /**
     * time in millis
     * @type number
     */
    lastModifiedTime : 0,

    /**
     * @type boolean
     */
    valid : false,

    /**
     * @type gpg.Score
     */
    score : null
};

/**
 * @lends gpg.ScorePage.prototype
 */
gpg.ScorePage.prototype = {

    /**
     * @type string
     */
    leaderboardId : '',

    /**
     * @type gpg.LeaderboardStart
     */
    start : gpg.LeaderboardStart.INVALID,

    /**
     * @type gpg.LeaderboardTimeSpan
     */
    timeSpan : gpg.LeaderboardTimeSpan.INVALID,

    /**
     * @type boolean
     */
    valid : false,

    /**
     * @type gpg.LeaderboardCollection
     */
    collection : gpg.LeaderboardCollection.INVALID,

    /**
     * @type gpg.ScorePage.Entry[]
     */
    entries : null,

    /**
     * @type boolean
     */
    hasNextScorePage : false,

    /**
     * @type boolean
     */
    hasPreviousScorePage : false
};
