/**
 * Created by ibon on 10/8/16.
 */


/**
 * called from native.
 * @param id {number}
 * @param str_json {string}
 * @private
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

/**
 * @namespace GPGLocalPlayerWrapper
 * @memberOf _gpg
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
 * @param datasource {gpg.DataSource}
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
 * Utility method. Should be emptied on production.
 * @param e {object}
 * @private
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

/**
 * @typedef {{success:boolean}}
 */
var tGenericResultValue;

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
 * @typedef {{ allow_create:boolean, allow_delete:boolean, max_snapshots:number, title:string }}
 */
var tSnapshotShowSelectionUIOperationParams;

/**
 * @typedef {{ filename:string, conflict_policy?:gpg.SnapshotConflictPolicy, datasource?:gpg.DataSource }}
 */
var tSnapshotLoadParams;

/**
 * @typedef {{ filename : string, conflict_policy : gpg.SnapshotConflictPolicy, description : string, data : string }}
 */
var tSnapshotSaveParams;

/**
 * @typedef {{ datasource : gpg.DataSource }}
 */
var tSnapshotFetchAllParams;

/**
 * @callback LocalPlayerCallback
 * @param {gpg.Player} local_player
 */

/**
 * @memberOf gpg
 * {{ CoverImageURL:string, Description:string, Filename:string, Valid:boolean, LastModifiedTime:number, PlayedTime:number  }}
 */
var SnapshotMetadata;

/**
 * @callback SnapshotShowSelectUIOperationCallback
 * @param  {{ result:string, metadata?:SnapshotMetadata, error_code?:number }}
 */

/**
 * @callback SnapshotLoadCallback
 * @param  {{ result:gpg.ResponseStatus, metadata:SnapshotMetadata, data?:string }}
 */

/**
 * @callback SnapshotSaveCallback
 * @param  {{ result:gpg.ResponseStatus, metadata:SnapshotMetadata }}
 */

/**
 * @callback SnapshotFetchAllCallback
 * @param  {{ result:gpg.ResponseStatus, metadata_array:SnapshotMetadata[] }}
 */

/**
 * @callback SnapshotDeleteCallback
 * @param {{ result:'success'|'error', error_code?:number }}
 */

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

        var index = this.__nextIndex();

        if ( typeof callback!=='function' ) {
            __log('addCallback w/o function: ' + JSON.stringify(callback));
        } else {
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

    GameServices : {

        /**
         *
         * @param player_callback {LocalPlayerCallback}
         */
        LocalPlayer: function (player_callback) {
            var index = __callbackManager.addCallback(
                /**
                 *
                 * @param result {tGenericResultValue}
                 */
                function getLocalPlayerCallback(result) {
                    player_callback(new gpg.Player(result.success));
                });

            _gpg.GPGLocalPlayerWrapper.Fetch(index);
        },

        /**
         * Multiplayer games player descriptor.
         * @returns {gpg.Players}
         * @constructor
         */
        Players: function () {
            return gpg.Players;
        },

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
                if (typeof params.max_snapshots === 'undefined') {
                    params.max_snapshots = 10;
                }
                if (typeof params.title === 'undefined') {
                    params.title = 'title';
                }

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

                if ( typeof params.filename==='undefined' || !params.filename ) {
                    __log('Snapshot load has no filename. Will not call');
                    return;
                }
                if ( typeof params.conflict_policy==='undefined' ) {
                    params.conflict_policy = gpg.SnapshotConflictPolicy.DefaultConflictPolicy;
                }
                if ( typeof params.datasource==='undefined' ) {
                    params.datasource = gpg.DataSource.CACHE_OR_NETWORK;
                }

                var index = __callbackManager.addCallback(callback);
                _gpg.GPGSnapshotWrapper.Load( index, params.filename, params.conflict_policy, params.datasource );
            },

            /**
             *
             * @param params {tSnapshotSaveParams}
             * @param callback {SnapshotSaveCallback}
             */
            Save : function( params, callback ) {

                if ( typeof params.filename==='undefined' || typeof params.data==='undefined' ) {
                    __log('Snapshot save has no filename or no contents to save. Will not call.');
                    return;
                }
                if ( typeof params.conflict_policy==='undefined' ) {
                    params.conflict_policy = gpg.SnapshotConflictPolicy.DefaultConflictPolicy;
                }
                if ( typeof params.description==='undefined' ) {
                    params.description = 'Default game description.';
                }

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
                if ( typeof params.datasource==='undefined' ) {
                    params.datasource = gpg.DataSource.CACHE_OR_NETWORK;
                }

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
        }
    }
};

/**
 * @typedef {{ Valid:boolean, LevelNumber:number, MinimumXP:number, MaximumXP:number }}
 */
gpg.PlayerLevel;


/**
 * A local player wrapper object.
 * This object can be safely cached for information requests on the current logged-in player.
 *
 * @class Player
 * @memberOf gpg
 * @param valid {boolean}
 * @constructor
 */
gpg.Player= function( valid ) {
    this._valid = valid;
    return this;
};

/**
 * @lends gpg.Player.prototype
 * @type {object}
 */
gpg.Player.prototype = {

    /**
     * @type boolean
     */
    _valid : false,

    /**
     * Get local player display name.
     * @returns {string}
     */
    Name : function() {
        return this._valid ?
            _gpg.GPGLocalPlayerWrapper.Name() :
            '';
    },

    /**
     *
     * @returns {string}
     */
    Id : function() {
        return this._valid ?
            _gpg.GPGLocalPlayerWrapper.Id() :
            '';
    },

    /**
     *
     * @param image_resolution {gpg.ImageResolution}
     * @returns {string}
     */
    AvatarUrl : function( image_resolution) {
        return this._valid ?
            _gpg.GPGLocalPlayerWrapper.AvatarUrl( image_resolution||gpg.ImageResolution.ICON ) :
            '';
    },

    /**
     *
     * @returns {boolean}
     */
    HasLevelInfo : function( ) {
        return this._valid ?
            _gpg.GPGLocalPlayerWrapper.HasLevelInfo( ) :
            false;
    },

    /**
     *
     * @returns {number}
     */
    CurrentXP : function( ) {
        return this._valid ?
            _gpg.GPGLocalPlayerWrapper.CurrentXP( ) :
            0;
    },

    /**
     *
     * @returns {number}
     */
    LastLevelUpTime : function( ) {
        return this._valid ?
            _gpg.GPGLocalPlayerWrapper.LastLevelUpTime( ) :
            0;
    },

    /**
     *
     * @returns {string}
     */
    Title : function( ) {
        return this._valid ?
            _gpg.GPGLocalPlayerWrapper.Title( ) :
            '';
    },

    __levelImpl : function(str) {
        if ( str!=='' ) {
            try {
                return JSON.parse(str);
            } catch (e) {
            }
        }

        return null;
    },

    /**
     *
     * @returns {gpg.PlayerLevel|null}
     */
    CurrentLevel : function() {
        if ( this._valid ) {
            return this.__levelImpl(_gpg.GPGLocalPlayerWrapper.CurrentLevel());
        }
        return null;
    },

    /**
     *
     * @returns {gpg.PlayerLevel|null}
     */
    NextLevel : function() {
        if ( this._valid ) {
            return this.__levelImpl(_gpg.GPGLocalPlayerWrapper.NextLevel());
        }
        return null;
    },

    __dump : function() {
        __log( 'Id='+this.Id() );
        __log( 'Name='+this.Name() );
        __log( 'Title='+this.Title() );
        __log( 'AvatarURL icon='+this.AvatarUrl( gpg.ImageResolution.ICON ) );
        __log( 'AvatarURL hires='+this.AvatarUrl( gpg.ImageResolution.HI_RES ) );
        __log( 'CurrentXP='+this.CurrentXP() );
        __log( 'LastLevelUpTime='+this.LastLevelUpTime() );
        __log( 'HasLevelInfo='+this.HasLevelInfo() );
        __log( 'CurrentLevel='+ this.CurrentLevel().LevelNumber );
        __log( 'NextLevel='+ this.NextLevel().LevelNumber );
    }
};

var _game_services = null;