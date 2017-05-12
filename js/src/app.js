"use strict";

/**
 * @namespace
 * @name cc
 */

/**
 * @name MenuItemFont
 * @constructor
 * @memberOf cc
 */

/**
 * @name setString
 * @type function
 * @param string
 * @memberOf MenuItemFont
 */

/**
 * @name Menu
 * @constructor
 * @memberOf cc
 */

/**
 * @name Layer
 * @constructor
 * @memberOf cc
 */

/**
 * @name Scene
 * @constructor
 * @memberOf cc
 */

/**
 * @name director
 * @namespace
 * @memberOf cc
 */

/**
 * @name Director
 * @namespace
 * @memberOf cc
 */

/**
 * @typedef {{ start : boolean, operation:gpg.AuthOperation, status?:gpg.AuthStatus }}
 */
var GPGContextAuthenticationListenerParam;

/**
 * @callback GPGContextAuthenticationListener
 * @param GPGContextAuthenticationListenerParam
 */

/**
 * @typedef {{ onGameServicesCreated? : BuilderCreateCallback, onMultiplayerInvitation? : MultiplayerInvitationCallback }}
 */
var GPGContextInitializationCallbacks;

/**
 * @class
 * @name GPGContext
 * @constructor
 *
 * @param gpgcallbacks {GPGContextInitializationCallbacks}
 */
function GPGContext(gpgcallbacks) {

    /**
     * @name _game_services
     * @memberOf GPGContext
     * @type {gpg.GameServices}
     */
    this._game_services = null;

    this._signed_in = false;
    this._initialized = false;

    /**
     *
     * @type {gpg.Player}
     */
    this._localPlayer = null;

    /**
     * @name _listeners
     * @memberOf GPGContext
     * @type {GPGContextAuthenticationListener[]}
     */
    this._listeners = [];

    this.__initGPG(gpgcallbacks);

    return this;
}

GPGContext.prototype = {

    gameServices: function() {
        return this._game_services;
    },

    /**
     * @param params {GPGContextInitializationCallbacks}
     * @private
     */
    __initGPG: function(params) {

        var me = this;

        me._initialized = true;

        var config = new gpg.PlatformConfiguration();
        config.SetClientID('777734739048-cdkbeieil19d6pfkavddrri5o19gk4ni.apps.googleusercontent.com');

        new gpg.GameServices.Builder()
            .SetOnAuthActionStarted(
                /**
                 *
                 * @param result {AuthActionStartedCallbackParams}
                 */
                function(result) {
                    __log('on auth action started: ' + result.AuthOperation);
                    me.__notifyListeners({
                        start: true,
                        operation: result.AuthOperation,
                        result: gpg.AuthStatus.VALID
                    });
                })
            .SetOnAuthActionFinished(
                /**
                 *
                 * @param result {AuthActionFinishedCallbackParams}
                 */
                function(result) {
                    __log('on auth action finished: ' + result.AuthOperation + ' ' + result.AuthStatus);

                    me._signed_in = gpg.IsSuccess(result.AuthStatus);

                    me.__notifyListeners({
                        start: false,
                        operation: result.AuthOperation,
                        result: result.AuthStatus
                    });
                })
            .SetOnMultiplayerInvitationEvent(
                /**
                 *
                 * @param result {MultiplayerInvitationCallback}
                 */
                function(result) {
                    params.onMultiplayerInvitation && params.onMultiplayerInvitation(result);
                })
            .SetLogging(gpg.LogLevel.INFO)
            .EnableSnapshots()
            .Create(
                /**
                 *
                 * @param gs {gpg.GameServices}
                 */
                function(gs) {

                    __log('on auth created');

                    me._game_services = gs;
                    if (null === gs) {
                        __log("No GameServices object created. Internal library error.");
                    }

                    params.onGameServicesCreated && params.onGameServicesCreated(gs);
                }, config);
    },

    isSignedIn: function() {
        return this._signed_in;
    },

    isInitialized: function() {
        return this._game_services !== null;
    },

    /**
     *
     * @returns {gpg.Player}
     */
    localPlayer: function() {
        return this._localPlayer;
    },

    /**
     * @param l {GPGContextAuthenticationListener}
     */
    removeListener: function(l) {
        var pos = this._listeners.indexOf(l);
        if (pos !== -1) {
            this._listeners.splice(pos, 1);
        }
    },

    /**
     * @param l {GPGContextAuthenticationListener}
     */
    addListener: function(l) {
        this._listeners.push(l);
    },

    removeAllListeners: function() {
        this._listeners = [];
    },

    /**
     *
     * @param p {GPGContextAuthenticationListenerParam}
     */
    __notifyListeners: function(p) {
        this._listeners.forEach(function(l) {
            l(p)
        });
    },

    /**
     *
     * @param callback {function( p : gpg.Player )}
     */
    setLocalPlayer: function(callback) {

        var me = this;

        this.gameServices().Players.FetchSelf(
            gpg.DataSource.CACHE_OR_NETWORK,
            /**
             *
             * @param res {PlayersFetchSelfCallbackParams}
             */
            function(res) {

                if (gpg.IsSuccess(res.result)) {
                    me._localPlayer = res.player;
                } else {
                    me._localPlayer = null;
                }

                callback(me._localPlayer);
            });
    }
};

/**
 * @type GPGContext|null
 */
var _context = null;

/**
 * bug bug. need a global label to notify on multiplayer or main scene.
 */
var _global_label = null;
