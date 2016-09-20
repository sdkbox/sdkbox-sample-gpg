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
function GPGContext( gpgcallbacks ) {

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

    this.__initGPG( gpgcallbacks );

    return this;
}

GPGContext.prototype = {

    gameServices : function() {
        return this._game_services;
    },

    /**
     * @param params {GPGContextInitializationCallbacks}
     * @private
     */
    __initGPG : function( params ) {

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
                function( result ) {
                    __log('on auth action started: ' + result.AuthOperation);
                    me.__notifyListeners({
                        start : true,
                        operation : result.AuthOperation,
                        result : gpg.AuthStatus.VALID
                    });
                })
            .SetOnAuthActionFinished(
                /**
                 *
                 * @param result {AuthActionFinishedCallbackParams}
                 */
                function( result ) {
                    __log('on auth action finished: ' + result.AuthOperation + ' ' + result.AuthStatus);

                    me._signed_in = gpg.IsSuccess(result.AuthStatus);

                    me.__notifyListeners({
                        start : false,
                        operation : result.AuthOperation,
                        result : result.AuthStatus
                    });
                })
            .SetOnMultiplayerInvitationEvent(
                /**
                 *
                 * @param result {MultiplayerInvitationCallback}
                 */
                function( result ) {
                    params.onMultiplayerInvitation && params.onMultiplayerInvitation( result );
                })
            .SetLogging( gpg.LogLevel.INFO )
            .EnableSnapshots()
            .Create(
                config,

                /**
                 *
                 * @param gs {gpg.GameServices}
                 */
                function( gs ) {

                    __log('on auth created');

                    me._game_services = gs;
                    if (null === gs) {
                        __log("No GameServices object created. Internal library error.");
                    }

                    params.onGameServicesCreated && params.onGameServicesCreated(gs);
                });
    },

    isSignedIn : function() {
        return this._signed_in;
    },

    isInitialized : function() {
        return this._game_services!==null;
    },

    /**
     *
     * @returns {gpg.Player}
     */
    localPlayer : function( ) {
        return this._localPlayer;
    },

    /**
     * @param l {GPGContextAuthenticationListener}
     */
    removeListener: function (l) {
        var pos = this._listeners.indexOf( l );
        if ( pos!==-1 ) {
            this._listeners.splice( pos, 1 );
        }
    },

    /**
     * @param l {GPGContextAuthenticationListener}
     */
    addListener: function (l) {
        this._listeners.push(l);
    },

    removeAllListeners : function() {
        this._listeners = [];
    },

    /**
     *
     * @param p {GPGContextAuthenticationListenerParam}
     */
    __notifyListeners : function( p ) {
        this._listeners.forEach( function(l) {
            l(p)
        });
    },

    /**
     *
     * @param callback {function( p : gpg.Player )}
     */
    setLocalPlayer : function( callback ) {

        var me = this;

        this.gameServices().Players.FetchSelf(
            gpg.DataSource.CACHE_OR_NETWORK,
            /**
             *
             * @param res {PlayersFetchSelfCallbackParams}
             */
            function (res) {

                if (gpg.IsSuccess(res.result)) {
                    me._localPlayer= res.player;
                } else {
                    me._localPlayer= null;
                }

                callback( me._localPlayer );
            });
    }
};

/**
 * @type GPGContext|null
 */
var _context= null;

/**
 * bug bug. need a global label to notify on multiplayer or main scene.
 */
var _global_label= null;

var HelloWorldLayer = cc.Layer.extend({
    sprite          : null,
    info            : null,
    _text           : null,

    _login_menu_item: null,

    _scenes         : null,

    createMenu : function() {

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        // create special login menu item
        this._login_menu_item = new cc.MenuItemFont(
            "--",
            function () {
                if ( _context.isInitialized() ) {
                    if (_context.isSignedIn()) {
                        _context.gameServices().SignOut();
                    } else {
                        _context.gameServices().StartAuthorizationUI();
                    }
                } else {
                    __log('Fatal, no _game_services object present.');
                }
            });

        if ( _context && _context.isInitialized() ) {
            if ( _context.isSignedIn() ) {
                this.__disableLoginButton();
            } else {
                this.__enableLoginButton();
            }
        }

        var menu = new cc.Menu(
            this._login_menu_item,
            new cc.MenuItemFont("Snapshots", function () {
                cc.director.runScene(new S_SnapShots());
            }),
            new cc.MenuItemFont("Leaderboards", function () {
                cc.director.runScene(new S_Leaderboard());
            }),
            new cc.MenuItemFont("Achievements", function () {
                cc.director.runScene(new S_Achievement());
            }),
            new cc.MenuItemFont("Quests", function () {
                cc.director.runScene(new S_Quest());
            }),
            new cc.MenuItemFont("Events", function () {
                cc.director.runScene(new S_Events());
            }),
            new cc.MenuItemFont("Player Stats", function () {
                cc.director.runScene(new S_PlayerStats());
            }),
            new cc.MenuItemFont("Realtime Multiplayer", function () {
                cc.director.runScene(new S_RealtimeMultiplayer());
            }),
            new cc.MenuItemFont("Nearby Connection", function () {
                cc.director.runScene(new S_NearbyConnection());
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    },

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        var winsize = cc.winSize;
        var me = this;

        var logo = new cc.Sprite("res/Logo.png");
        var logoSize = logo.getContentSize();
        logo.x = logoSize.width / 2;
        logo.y = winsize.height - logoSize.height / 2;
        this.addChild(logo);

        this.info = new cc.LabelTTF("", "sans", 24);
        this.info.x = cc.Director.getInstance().getWinSize().width / 2;
        this.info.y = 90;
        this.addChild(this.info);

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);

        _global_label = this._text;

        function setContextListeners() {
            _context.removeAllListeners();
            _context.addListener(
                /**
                 *
                 * @param p {GPGContextAuthenticationListenerParam}
                 */
                function (p) {
                    if (p.start === false) {                            // EndAuthenticationProcess

                        if (p.operation === gpg.AuthOperation.SIGN_IN) {    // Sign in ?

                            if (gpg.IsSuccess(p.result)) {                      // succesful ?

                                me.__disableLoginButton();

                                _context.setLocalPlayer( function(p) {          // this is a good spot to get and cache
                                                                                // local player's info.
                                    if ( p ) {
                                        // dump to console object contents.
                                        gpg.Player.__Dump(p);
                                        me.info.setString(p.name);
                                    } else {
                                        me.info.setString("can't get my player info.");
                                    }
                                });

                            } else {
                                me.__enableLoginButton();                       // no sucessful, set menu item to sign in
                            }
                        } else {                                            // sign out ?
                            me.__enableLoginButton();                           // set menu item to sign in.
                        }
                    }
                });
        }

        if ( _context===null ) {
            _context = new GPGContext(
                {
                    /**
                     *
                     * @param _game_services {BuilderCreateCallback}
                     */
                    onGameServicesCreated: function (_game_services) {

                        if (_game_services) {
                            me.createMenu();
                        } else {
                            me.info.setString("Could not create game services native object.");
                        }

                        setContextListeners();


                    },

                    /**
                     *
                     * @param params {MultiplayerInvitationCallbackParams}
                     */
                    onMultiplayerInvitation: function ( params ) {
                        _global_label && _global_label.setString("you received an invitation: "+params.match.id.substring(0,10) + "...");
                    }
                });
        } else {
            me.createMenu();

            if ( _context && _context.localPlayer() ) {
                me.info.setString( _context.localPlayer().name );
            } else {

__log("checking for ctx " + (_context!==null));
__log("checking for ctx.p " + (_context.localPlayer()!==null));
            }

            setContextListeners();
        }

        return true;
    },

    __enableLoginButton : function() {
        this._login_menu_item.setString("Sign in");
        this.info.setString('');
    },

    __disableLoginButton : function() {
        this._login_menu_item.setString("Sign out");
        this.info.setString('');
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter: function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

var LayerSnapShot = cc.Layer.extend({

    _text : null,

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);
    },

    __createMenu : function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var menu = new cc.Menu(
            new cc.MenuItemFont("Show SnapshotUI", function () {
                if ( _context.isSignedIn() ) {
                    _context.gameServices().Snapshots.ShowSelectUIOperation(
                        {
                            allow_create : true,
                            allow_delete : true,
                            max_snapshots : 8,
                            title : 'a title for snapshoting'
                        },
                        /**
                         *
                         * @param result {tSnapshotShowSelectionUIOperationCallbackResult}
                         */
                        function( result ) {
                            if ( result.result==='load' ) {

                                __log('snapshot load game');
                                var metadata = result.metadata;

                                _context.gameServices().Snapshots.Load(
                                    {
                                        conflict_policy : gpg.SnapshotConflictPolicy.DefaultConflictPolicy,
                                        filename :        metadata.filename
                                    },
                                    /**
                                     *
                                     * @param result {tSnapshotLoadCallbackResult}
                                     */
                                    function( result ) {
                                        var metadata = JSON.stringify(result.metadata);
                                        __log(' load game. metadata: ' + metadata);
                                        if ( gpg.IsSuccess( result.result ) ) {
                                            me._text.setString( 'load game metadata ok: '+metadata );
                                        } else {
                                            me._text.setString(' result not valid, so no contents.');
                                        }
                                    }
                                );

                            } else if ( result.result==='create' ) {

                                __log('snapshot create game');

                                _context.gameServices().Snapshots.Save(
                                    {
                                        filename : 'gpg_testing',
                                        description : 'a valued saved game',
                                        data : JSON.stringify({ a:7 , b:'abcd', c: { d:false, e:[1,2,3], f : Math.random()}})
                                    },
                                    function( result ) {
                                        __log(' saved game. metadata: ' + JSON.stringify(result.metadata));
                                        if ( gpg.IsSuccess( result.result ) ) {
                                            me._text.setString( 'saved ok' );
                                        } else {
                                            me._text.setString('  saved with error. code: ' + result.result);
                                        }
                                    }
                                );

                            } else if ( result.result==='error' ) {
                                me._text.setString('snapshot ui error: '+result.error_code);
                            } else {
                                me._text.setString('snapshot ui error, unknown result ');
                            }
                        }
                    );
                }
            }),
            new cc.MenuItemFont("Fetch all games", function () {

                _context.gameServices().Snapshots.FetchAll(
                    {
                        data_source : gpg.DataSource.CACHE_OR_NETWORK
                    },
                    function( result ) {
                        if ( gpg.IsSuccess(result.result) ) {
                            me._text.setString('Fetch all games success. Snapshots loaded: '+result.metadata_array.length);

                            result.metadata_array.forEach(
                                /**
                                 *
                                 * @param metadata {gpg.SnapshotMetadata}
                                 */
                                function(metadata) {
                                    __log( '       '+metadata.filename );
                                });

                        } else {
                            me._text.setString('Fetch all games error. Code: '+result.result);
                        }
                    }
                )
            }),
            new cc.MenuItemFont("Delete gpg_testing game", function () {

                var filename = 'gpg_testing';

                _context.gameServices().Snapshots.Delete(filename, function(result) {
                    if ( result.result==='success' ) {
                        me._text.setString('game '+filename+' deleted.');
                    } else {
                        me._text.setString('game '+filename+' did not delete. Reason:' + result.error_code + '.' );
                    }
                });
            }),

            new cc.MenuItemFont("Main menu", function () {
                cc.director.runScene( new HelloWorldScene() );
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_SnapShots = cc.Scene.extend({
    onEnter : function() {
        this._super();
        var l = new LayerSnapShot();
        this.addChild( l );
    }
});

var LayerLeaderboard = cc.Layer.extend({

    _text : null,

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);
    },

    __createMenu : function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var menu = new cc.Menu(
            new cc.MenuItemFont("Show UI [Best gamers]", function () {

                _context.gameServices().Leaderboards.ShowUI("CgkI6KjppNEWEAIQAg");

            }),
            new cc.MenuItemFont("Show All UI", function () {
                _context.gameServices().Leaderboards.ShowAllUI( );

            }),
            new cc.MenuItemFont("Submit random score to [Fastest lap]", function () {
                _context.gameServices().Leaderboards.SubmitScore(
                    {

                        leaderboard_id : 'CgkI6KjppNEWEAIQAw',

                        // currently there's a bug that won't submit the score if metadata is set.
                        metadata : 'sent from cocos js',

                        // this leaderboard has a max value of 300, and min of 0
                        score : (10 + Math.random()*290)|0
                    },
                    function( res ) {
                        me._text.setString('result submit score: '+res.result);
                    });

            }),
            new cc.MenuItemFont("Fetch all score summaries [best gamers]", function () {

                _context.gameServices().Leaderboards.FetchAllScoreSummaries(
                    {
                        leaderboard_id : 'CgkI6KjppNEWEAIQAg'
                    },
                    /**
                     * @param result {LeaderboardFetchAllScoreSummariesCallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess( result.result ) ) {

                            me._text.setString(
                                result.score_summary_array.reduce(
                                    /**
                                     * @param prev_str {string}
                                     * @param ss {gpg.ScoreSummary}
                                     * @return {string}
                                     */
                                    function( prev_str, ss ) {
                                        return prev_str +
                                            ' ts:' + ss.timeSpan +
                                            ' col:' + ss.collection +
                                            ' sc:' + ss.currentPlayerScore.value +
                                            ' @@';
                                    },
                                    '')
                            );

                        } else {
                            me._text.setString("Fetch all score summaries res:"+result.result);
                        }
                    }
                )
            }),
            new cc.MenuItemFont("Fetch all", function () {
                _context.gameServices().Leaderboards.FetchAll(
                    gpg.DataSource.CACHE_OR_NETWORK,
                    /**
                     *
                     * @param result {LeaderboardFetchAllCallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess(result.result ) ) {
                            me._text.setString(
                                result.leaderboard_array.reduce(
                                    /**
                                     *
                                     * @param prev_str {string}
                                     * @param ldb {gpg.Leaderboard}
                                     * @returns {string}
                                     */
                                    function( prev_str, ldb ) {
                                        return prev_str + 'name: ' + ldb.name + ' ## ';
                                    },
                                    '')
                            );
                        } else {
                            me._text.setString("Fetch all res:"+result.result);
                        }
                    }
                )
            }),
            new cc.MenuItemFont("Fetch score page", function () {

                _context.gameServices().Leaderboards.FetchScorePage(
                    {
                        leaderboard_id : 'CgkI6KjppNEWEAIQAg'
                    },
                    /**
                     *
                     * @param result {LeaderboardFetchScorePageCallbackParams}
                     */
                    function( result ) {

                        if ( gpg.IsSuccess(result.result ) ) {
                            me._text.setString("Get score page ok.");
                            result.scorePage.entries.forEach(
                                /**
                                 *
                                 * @param entry {gpg.ScorePage.Entry}
                                 */
                                function( entry ) {
                                    _context.gameServices().Players.Fetch(
                                        {
                                            player_id : entry.playerId
                                        },
                                        /**
                                         *
                                         * @param player_info {PlayersFetchCallbackParams}
                                         */
                                        function( player_info ) {
                                            __log( player_info.player.name + " pos: " + entry.score.rank + " score: " + entry.score.value );
                                        }
                                    );

                                }
                            )
                        } else {
                            me._text.setString("Get score page error: "+ result.result);
                        }
                    }
                );
            }),
            new cc.MenuItemFont("Fetch next score page", function () {

                _context.gameServices().Leaderboards.FetchNextScorePage(
                    {},
                    /**
                     *
                     * @param result {LeaderboardFetchScorePageCallbackParams}
                     */
                    function( result ) {

                        if ( gpg.IsSuccess(result.result ) ) {
                            me._text.setString("Get next score page ok.");
                            result.scorePage.entries.forEach(
                                /**
                                 *
                                 * @param entry {gpg.ScorePage.Entry}
                                 */
                                function( entry ) {
                                    __log( entry.playerId + " pos: " + entry.score.rank + " score: " + entry.score.value );
                                }
                            )
                        } else{
                            me._text.setString("Get score page error: "+ result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Main menu", function () {
                cc.director.runScene( new HelloWorldScene() );
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_Leaderboard = cc.Scene.extend({
    onEnter : function() {
        this._super();
        this.addChild( new LayerLeaderboard() );
    }
});

var LayerAchievement = cc.Layer.extend({

    _text : null,

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);
    },

    __createMenu : function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var menu = new cc.Menu(
            new cc.MenuItemFont("Show UI", function() {
                // this method has no callback.
                _context.gameServices().Achievements.ShowAllUI(
                    /**
                     *
                     * @param result {AchievementShowAllUICallbackParams}
                     */
                    function( result ) {

                    });
            }),
            new cc.MenuItemFont("Fetch all achievements", function () {
                _context.gameServices().Achievements.FetchAll(
                    gpg.DataSource.CACHE_OR_NETWORK,
                    /**
                     *
                     * @param result {AchievementFetchAllCallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess( result.result ) ) {

                            me._text.setString("Achievements fetch all got "+result.achievement_array.length+" achievements.");
                            result.achievement_array.forEach(
                                /**
                                 *
                                 * @param a {gpg.Achievement}
                                 */
                                function( a ) {
                                    __log(
                                        a.name +
                                        ' type:' + (a.type===gpg.AchievementType.INCREMENTAL ? 'incremental' : 'standard') +
                                        ' state:' + a.state);
                                });

                        } else {
                            me._text.setString("Achievements fetch all error: "+ result.result);
                        }
                    }
                );
            }),
            new cc.MenuItemFont("Fetch achievement 'Incremental'", function() {
                _context.gameServices().Achievements.Fetch(
                    {
                        achievement_id : 'CgkI6KjppNEWEAIQBQ',
                        data_source : gpg.DataSource.CACHE_OR_NETWORK
                    },
                    /**
                     *
                     * @param result {AchievementFetchCallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess( result.result ) ) {
                            var a = result.achievement;
                            me._text.setString(
                                a.name +
                                ' type:' + (a.type===gpg.AchievementType.INCREMENTAL ? 'incremental' : 'standard') +
                                ' state:' + a.state);

                        } else {
                            me._text.setString("Achievements fetch error: "+ result.result);
                        }
                    }
                );
            }),
            new cc.MenuItemFont("Increment achievement", function() {
                // this method has no callback.
                _context.gameServices().Achievements.Increment(
                    {
                        achievement_id: 'CgkI6KjppNEWEAIQDg',
                        increment : 1
                    });

                me._text.setString("Method w/o callback. Check by fetching or UI.");
            }),
            new cc.MenuItemFont("Set Steps at least achievement", function() {
                // this method has no callback.
                _context.gameServices().Achievements.SetStepsAtLeast(
                    {
                        achievement_id: 'CgkI6KjppNEWEAIQDg',
                        increment : 20
                    });

                me._text.setString("Method w/o callback. Check by fetching or UI.");
            }),
            new cc.MenuItemFont("Unlock achievement", function() {
                // this method has no callback.
                _context.gameServices().Achievements.Unlock('CgkI6KjppNEWEAIQDg');
                me._text.setString("Method w/o callback. Check by fetching or UI.");
            }),
            new cc.MenuItemFont("Reveal achievement", function() {
                // this method has no callback.
                _context.gameServices().Achievements.Reveal('CgkI6KjppNEWEAIQDg');
                me._text.setString("Method w/o callback. Check by fetching or UI.");
            }),

            new cc.MenuItemFont("Main menu", function () {
                cc.director.runScene( new HelloWorldScene() );
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_Achievement = cc.Scene.extend({
    onEnter : function() {
        this._super();
        this.addChild( new LayerAchievement() );
    }
});

var LayerQuest = cc.Layer.extend({

    _text : null,

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);
    },

    __createMenu : function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var menu = new cc.Menu(
            new cc.MenuItemFont("Fetch quest list", function () {
                _context.gameServices().Quests.FetchList(
                    gpg.DataSource.CACHE_OR_NETWORK,
                    /**
                     *
                     * @param result {QuestsFetchListCallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess( result.result ) ) {

                            me._text.setString("Quests fetch list, got "+result.data.length+" quests.");
                            result.data.forEach(
                                /**
                                 *
                                 * @param a {gpg.Quest}
                                 */
                                function( a ) {
                                    __log(
                                        a.name +
                                        ' state:' + a.questState +
                                        ' id:' + a.id +
                                        ' valid: ' + a.valid );
                                });

                        } else {
                            me._text.setString("Quests fetch list error: "+ result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Fetch quest", function () {
                _context.gameServices().Quests.Fetch(
                    {

                        data_source : gpg.DataSource.CACHE_OR_NETWORK,
                        quest_id : '<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ'
                    },
                    /**
                     *
                     * @param result {QuestsFetchCallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess( result.result ) ) {

                            var a = result.quest;

                            me._text.setString("Quests fetch " +
                                        a.name +
                                        ' state:' + a.questState +
                                        ' id:' + a.id +
                                        ' valid: ' + a.valid );

                        } else {
                            me._text.setString("Quests fetch error: "+ result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Show All UI", function () {
                _context.gameServices().Quests.ShowAllUI(
                    /**
                     *
                     * @param result {QuestsShowAllUICallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess( result.result ) ) {
                            me._text.setString("Quests show all ok. Quest:"+result.quest.name );

                        } else {
                            me._text.setString("Quests show all ui error: "+ result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Show UI quest", function () {
                _context.gameServices().Quests.ShowUI(
                    '<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ',
                    /**
                     *
                     * @param result {QuestsShowUICallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess( result.result ) ) {
                            me._text.setString("Quests show all ok. Quest:"+result.quest.name );

                        } else {
                            me._text.setString("Quests show all ui error: "+ result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Accept quest", function () {
                _context.gameServices().Quests.Accept(
                    '<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ',
                    /**
                     *
                     * @param result {QuestsAcceptCallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess( result.result ) ) {
                            me._text.setString("Quests accept ok. Quest:"+result.quest.name );

                        } else {
                            me._text.setString("Quests accept error: "+ result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Claim milestone", function () {
                _context.gameServices().Quests.ClaimMilestone(
                    '<ChwKCQjg9PmjmwMQARINCgkI6KjppNEWEAIQDRgBEgIIAQ',
                    /**
                     *
                     * @param result {QuestsClaimMilestoneCallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess( result.result ) ) {
                            me._text.setString(
                                "Quests claim milestone." +
                                " Quest:"+result.quest.name+
                                " Mlstone st:"+result.milestone.state +
                                " count"+result.milestone.currentCount+"/"+result.milestone.currentCount );

                        } else {
                            me._text.setString("Quests claim milestone error: "+ result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Main menu", function () {
                cc.director.runScene( new HelloWorldScene() );
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_Quest = cc.Scene.extend({
    onEnter : function() {
        this._super();
        this.addChild( new LayerQuest() );
    }
});

var LayerEvents = cc.Layer.extend({

    _text : null,

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);
    },

    __createMenu : function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var menu = new cc.Menu(

            new cc.MenuItemFont("FetchAll", function () {

                _context.gameServices().Events.FetchAll(
                    /**
                     *
                     * @param result {EventsFetchAllCallbackParams}
                     */
                    function(result) {
                        if ( gpg.IsSuccess(result.result) ) {

                            Object.keys(result.data).forEach(
                                function( key ) {
                                    /**
                                     *
                                     * @param e {gpg.Event}
                                     */
                                    var e = result.data[key];
                                    __log(
                                        "Event: '" + e.name + "'" +
                                        " count:" + e.count +
                                        " visibility: " + e.visibility);
                                }
                            );
                            me._text.setString("Events fetch all got: "+ Object.keys(result.data).length + "elements.");
                        } else {
                            me._text.setString("Events fetch all error: "+ result.result);
                        }
                    });
            }),

            new cc.MenuItemFont("Fetch", function () {

                _context.gameServices().Events.Fetch(
                    {
                        event_id : 'CgkI6KjppNEWEAIQDA'
                    },
                    /**
                     *
                     * @param result {EventsFetchCallbackParams}
                     */
                    function(result) {
                        if ( gpg.IsSuccess(result.result) ) {

                            var e = result.event;
                            me._text.setString("Event: " + e.name +
                                                " count:" + e.count +
                                                " visibility: " + e.visibility);
                        } else {
                            me._text.setString("Events fetch error: "+ result.result);
                        }
                    });
            }),

            new cc.MenuItemFont("Increment", function () {

                // there's no callback for this method.
                _context.gameServices().Events.Increment(
                    {
                        event_id : 'CgkI6KjppNEWEAIQDA',
                        increment : 2
                    });
            }),

            new cc.MenuItemFont("Main menu", function () {
                cc.director.runScene( new HelloWorldScene() );
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_Events = cc.Scene.extend({
    onEnter : function() {
        this._super();
        this.addChild( new LayerEvents() );
    }
});

var LayerPlayerStats = cc.Layer.extend({

    _text : null,

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);
    },

    __createMenu : function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var menu = new cc.Menu(

            new cc.MenuItemFont("FetchForPlayer", function () {

                // there's no callback for this method.
                _context.gameServices().Stats.FetchForPlayer(
                    /**
                     *
                     * @param result {StatsFetchForPlayerCallbackParams}
                     */
                    function (result) {
                        if (gpg.IsSuccess(result.result)) {

                            var e = result.data;
                            me._text.setString(
                                "Player stats fetch for player ok. eg. daysSinceLastPlayed:" +
                                e.daysSinceLastPlayed
                            );
                        } else {
                            me._text.setString("Player stats fetch for player error: " + result.result);
                        }
                    }
                )
            }),

            new cc.MenuItemFont("Main menu", function () {
                cc.director.runScene( new HelloWorldScene() );
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_PlayerStats = cc.Scene.extend({
    onEnter : function() {
        this._super();
        this.addChild( new LayerPlayerStats() );
    }
});


var LayerRealtimeMultiplayer = cc.Layer.extend({

    _text : null,
    _text_listener : null,
    _text_listener_data : null,

    /**
     * @type  {gpg.RealTimeRoom}
     */
    _room : null,

    /**
     * @type {gpg.MultiplayerInvitation}
     */
    _invitation : null,

    _mi_accept_invitation : null,
    _mi_dismiss_invitation : null,
    _mi_decline_invitation : null,

    _mi_message_reliable : null,
    _mi_message_unreliable : null,
    _mi_message_unreliable_to_others : null,

    _mi_leaveroom : null,

    _message_index : 0,

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);

        this._text_listener = new cc.LabelTTF("", "sans", 24);
        this._text_listener.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text_listener.y = 95;
        this.addChild(this._text_listener);

        this._text_listener_data = new cc.LabelTTF("", "sans", 18);
        this._text_listener_data.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text_listener_data.y = 75;
        this.addChild(this._text_listener_data);

        _global_label = this._text_listener;
    },

    __createMenu : function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        /**
         *
         * @type {gpg.RealTimeEventListener}
         */
        var listener = {

            onRoomStatusChanged: function (room) {
                me._text_listener.setString("room status changed. "+room.status);
            },

            onConnectedSetChanged: function (room) {
                me._text_listener.setString("room connected set changed.");
            },

            onP2PConnected: function (room, participant) {
                me._text_listener.setString("room p2p connected: " + participant.displayName);
            },

            onP2PDisconnected: function (room, participant) {
                me._text_listener.setString("room p2p disconnected: " + participant.displayName);
            },

            onParticipantStatusChanged: function (room, participant) {
                me._text_listener.setString("room participant status changed: "+ participant.displayName + " st:" + participant.status);
            },

            onDataReceived: function (room, from_participant, data, is_reliable) {
                me._text_listener.setString("data from:" + from_participant.displayName + " reliable:" + is_reliable + " len:"+data.length);
                me._text_listener_data.setString("'" + data + "'");
            }

        };

        this._mi_message_reliable = new cc.MenuItemFont("message reliable", function() {
            _context.gameServices().RealTimeMultiplayer.SendReliableMessage(
                {
                    data : "message " + me._message_index++,
                    room_id : me._room.id,
                    to_participant_id : me._room.participants.filter( function( p ) {
                        return p.id!==me._room.creatingParticipant.id;
                    })[0].id
                },
                /**
                 *
                 * @param result {gpg.MultiplayerStatus}
                 */
                function( result ) {
                    me._text.setString("send reliable message success: " + gpg.IsSuccess(result) ? "true" : "no. code:"+result);
                }
            );
        });

        this._mi_message_unreliable = new cc.MenuItemFont("message unreliable", function() {
            _context.gameServices().RealTimeMultiplayer.SendUnreliableMessage(
                {
                    data :              "message " + me._message_index++,
                    room_id :           me._room.id,
                    participant_ids :   me._room.participants.filter( function( p ) {
                                            return p.id!==me._room.creatingParticipant.id;
                                        }).map( function( p ) {
                                            return p.id;
                                        })
                }
            );
        });

        this._mi_message_unreliable_to_others = new cc.MenuItemFont("message unreliable to others", function() {
            _context.gameServices().RealTimeMultiplayer.SendUnreliableMessageToOthers(
                {
                    data :              "message " + me._message_index++,
                    room_id :           me._room.id
                }
            );
        });


        this._mi_leaveroom = new cc.MenuItemFont("Leave room", function() {

            _context.gameServices().RealTimeMultiplayer.LeaveRoom(
                /**
                 *
                 * @param res {gpg.ResponseStatus}
                 */
                function (res) {
                    if (gpg.IsSuccess(res)) {
                        me._text.setString("Room left.");
                        me._text_listener.setString("");
                        me._room = null;
                        me._mi_leaveroom.setVisible(false);
                        me._mi_message_reliable.setVisible(false);
                        me._mi_message_unreliable.setVisible(false);
                        me._mi_message_unreliable_to_others.setVisible(false);
                    } else {
                        me._text.setString("Room left error: " + res);
                    }
                }
            );
        });

        this._mi_accept_invitation = new cc.MenuItemFont("Accept invitation", function() {

            if ( me._invitation ) {
                _context.gameServices().RealTimeMultiplayer.AcceptInvitation(
                    {
                        invitation_id :  me._invitation.id,
                        listener : listener
                    },
                    /**
                     *
                     * @param res {RTAcceptInvitationCallbackParams}
                     */
                    function (res) {
                        if (gpg.IsSuccess(res.result)) {
                            me._text.setString("accepted invitation. Start game, room: " + res.room.id.substring(0, 10) + "...");
                            me._mi_leaveroom.setVisible(true);
                            me._mi_message_reliable.setVisible(true);
                            me._mi_message_unreliable.setVisible(true);
                            me._mi_message_unreliable_to_others.setVisible(true);


                            me._mi_accept_invitation.setVisible( false );
                            me._mi_dismiss_invitation.setVisible( false );
                            me._mi_decline_invitation.setVisible( false );

                            me._room = res.room;
                        } else {
                            me._text.setString("Accept invitation error: " + res.result);
                        }
                    }
                );
            } else {
                __log("can't find a local invitation.");
            }
        });

        this._mi_decline_invitation = new cc.MenuItemFont("Decline invitation", function() {
            _context.gameServices().RealTimeMultiplayer.DeclineInvitation(me._invitation.id);
        });

        this._mi_dismiss_invitation = new cc.MenuItemFont("Dismiss invitation", function() {
            _context.gameServices().RealTimeMultiplayer.DismissInvitation(me._invitation.id);
        });

        this._mi_leaveroom.setVisible( false );
        this._mi_accept_invitation.setVisible( false );
        this._mi_dismiss_invitation.setVisible( false );
        this._mi_decline_invitation.setVisible( false );

        this._mi_message_reliable.setVisible( false );
        this._mi_message_unreliable.setVisible( false );
        this._mi_message_unreliable_to_others.setVisible( false );

        var menu = new cc.Menu(

            new cc.MenuItemFont("CreateRoom automatch", function() {
                _context.gameServices().RealTimeMultiplayer.CreateRealTimeRoom(
                    {
                        type : "quick_match",
                        quick_match_params : {
                            maximumAutomatchingPlayers : 1,
                            minimumAutomatchingPlayers : 1
                        }
                    },
                    listener,
                    /**
                     *
                     * @param res {RTCreateRoomCallbackParams}
                     */
                    function( res ) {

                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("Room created: id="+res.room.id+" participants="+res.room.participants.length);
                            me._room= res.room;
                            me._mi_leaveroom.setVisible(true);
                            me._mi_message_reliable.setVisible(true);
                            me._mi_message_unreliable.setVisible(true);
                            me._mi_message_unreliable_to_others.setVisible(true);

                        } else {
                            me._text.setString("RT create room automatch error: "+ res.result);
                        }
                    }
                );

            }),

            new cc.MenuItemFont("CreateRoom select", function() {

                _context.gameServices().RealTimeMultiplayer.CreateRealTimeRoom(
                    {
                        type : "ui",
                        ui_params : {
                            maximumPlayers : 1,
                            minimumPlayers : 1
                        }
                    },
                    listener,
                    /**
                     *
                     * @param res {RTCreateRoomCallbackParams}
                     */
                    function( res ) {
                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("Room created: id="+res.room.id.substring(0,10)+"... participants="+res.room.participants.length);
                            me._room= res.room;
                            me._mi_leaveroom.setVisible(true);
                            me._mi_message_reliable.setVisible(true);
                            me._mi_message_unreliable.setVisible(true);
                            me._mi_message_unreliable_to_others.setVisible(true);

                        } else {
                            me._text.setString("RT create room ui error: "+ res.result);
                        }

                    }
                );

            }),

            new cc.MenuItemFont("Invitations UI", function() {

                _context.gameServices().RealTimeMultiplayer.ShowRoomInboxUI(
                    /**
                     *
                     * @param res {RTShowRoomInboxUICallbackParams}
                     */
                    function( res ) {
                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("got invitation: "+ (res.invitation.id.substr(0,10)) +"..." );
                            me._invitation = res.invitation;

                            // normally, you'd accept here the invitation.
                            // we're enabling accept/dismiss/decline ui just for sample purposes.
                            me._mi_accept_invitation.setVisible(true);
                            me._mi_dismiss_invitation.setVisible(true);
                            me._mi_decline_invitation.setVisible(true);
                        } else {
                            me._text.setString("RT invitation ui error: "+ res.result);

                            me._mi_accept_invitation.setVisible(false);
                            me._mi_dismiss_invitation.setVisible(false);
                            me._mi_decline_invitation.setVisible(false);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Fetch invitations", function() {
                _context.gameServices().RealTimeMultiplayer.FetchInvitations(
                    /**
                     *
                     * @param res {RTFetchInvitationsCallbackParams}
                     */
                    function( res ) {
                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("fetched " + res.invitations.length + " invitations.");
                        } else {
                            me._text.setString("fetch invitations error: "+ res.result);
                        }
                    }
                );
            }),

            me._mi_leaveroom,

            me._mi_accept_invitation,

            me._mi_dismiss_invitation,

            me._mi_decline_invitation,

            me._mi_message_reliable,

            me._mi_message_unreliable,

            me._mi_message_unreliable_to_others,

            new cc.MenuItemFont("Main menu", function () {
                cc.director.runScene( new HelloWorldScene() );
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_RealtimeMultiplayer = cc.Scene.extend({
    onEnter : function() {
        this._super();
        this.addChild( new LayerRealtimeMultiplayer() );
    }
});

var LayerNearbyConnection = cc.Layer.extend({

    _text : null,
    _text_listener : null,
    _text_listener_data : null,

    /**
     * @type  {gpg.RealTimeRoom}
     */
    _room : null,

    /**
     * @type {gpg.MultiplayerInvitation}
     */
    _invitation : null,

    _mi_accept_invitation : null,
    _mi_dismiss_invitation : null,
    _mi_decline_invitation : null,

    _mi_message_reliable : null,
    _mi_message_unreliable : null,
    _mi_message_unreliable_to_others : null,

    _mi_leaveroom : null,

    _message_index : 0,

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        this._endpoints = new Array();
        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);

        this._text_listener = new cc.LabelTTF("", "sans", 24);
        this._text_listener.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text_listener.y = 95;
        this.addChild(this._text_listener);

        this._text_listener_data = new cc.LabelTTF("", "sans", 18);
        this._text_listener_data.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text_listener_data.y = 75;
        this.addChild(this._text_listener_data);

        _global_label = this._text_listener;

        this._msg_advertising = 'this is a reliable from advertising';
        this._msg_discovery = 'this is a reliable msg from discovery'
    },

    __createMenu : function() {
        const self = this;
        cc.MenuItemFont.setFontName("sans");
        const winSize = cc.Director.getInstance().getWinSize();

        this._mi_start_advertising = new cc.MenuItemFont("StartAdvertising", function() {
            _context.gameServices().NearbyConnection.StartAdvertising(
                "\"name\":\"\",\"duration\":0,\"app_identifiers\":{\"identifier\":\"com.sdkbox.gpg\"},",
                function(result) {
                    //start_advertising_callback
                    if (1 == result.start_advertising_result.status) {
                        self._mi_start_advertising.setVisible(false);
                        self._mi_stop_advertising.setVisible(true);
                        self._mi_start_discovery.setVisible(false);
                        __log("GPG start advertising result:" + result.client_id
                            + " status:" + result.start_advertising_result.status
                            + " local_endpoint_name:" + result.start_advertising_result.local_endpoint_name);
                        self._text.setString('start advertising success');
                    } else {
                        __log("GPG advertising start failed");
                        self._text.setString('start advertising failed');
                    }
                },
                function(result) {
                    //request_callback

                    const remote_endpoint_id = result.request.remote_endpoint_id;
                    let payload = result.request.payload;

                    //accept connection
                    _context.gameServices().NearbyConnection.AcceptConnectionRequest(
                        remote_endpoint_id,
                        payload,
                        function (result) {
                            __log('advertising connect listener')
                            self._text.setString('receive event:' + result.event);
                            if ('OnMessageReceived' == result.event) {
                                __log('OnMessageReceived client_id:' + result.client_id
                                    + ' remote_endpoint_id:' + result.remote_endpoint_id
                                    + ' payload:' + result.payload
                                    + ' is_reliable:' + result.is_reliable)
                                self._text_listener_data.setString(result.payload);
                            } else if ('OnDisconnected' == result.event) {
                                __log('OnDisconnected client_id:' + result.client_id
                                    + ' remote_endpoint_id:' + result.remote_endpoint_id)
                            } else {
                                __log('Unknown event:' + result.event);
                            }
                        });
                    //send message to connector
                    payload = self._msg_advertising;
                    _context.gameServices().NearbyConnection.SendUnreliableMessage(
                        remote_endpoint_id, payload);
                    //reject connection
                    // _context.gameServices().NearbyConnection.RejectConnectionRequest(remote_endpoint_id);
                    self._text.setString('receive connect request');
                });
        });
        this._mi_stop_advertising = new cc.MenuItemFont("StopAdvertising", function() {
            self._mi_start_advertising.setVisible(true);
            self._mi_stop_advertising.setVisible(false);
            self._mi_start_discovery.setVisible(true);
            _context.gameServices().NearbyConnection.StopAdvertising();
        });
        this._mi_start_discovery = new cc.MenuItemFont("StartDiscovery", function() {
            const server_id = 'com.sdkbox.hugo.test.gpg.nearby';
            self._mi_start_advertising.setVisible(false);
            self._mi_start_discovery.setVisible(false);
            self._mi_stop_discovery.setVisible(true);
            _context.gameServices().NearbyConnection.StartDiscovery(server_id, 0,
                function(result) {
                    self._text.setString('discovery event:' + result.event);
                    if ('OnEndpointFound' == result.event) {
                        __log('found client_id:' + result.client_id
                            + 'endpoint detail endpoint_id:' + result.endpoint_details.endpoint_id
                            + 'device_id:' + result.endpoint_details.device_id
                            + 'name:' + result.endpoint_details.name
                            + 'service_id:' + result.endpoint_details.server_id);
                        self.__addEndpoint(result.client_id,
                            result.endpoint_details.endpoint_id,
                            result.endpoint_details.device_id,
                            result.endpoint_details.name,
                            result.endpoint_details.server_id);
                        const name = '';
                        const remote_endpoint_id = result.endpoint_details.endpoint_id;
                        const payload = '';
                        _context.gameServices().NearbyConnection.SendConnectionRequest(
                            name, remote_endpoint_id, payload,
                            function(result) {
                                //connect_response_callback
                                if (1 == result.response.status) {
                                    __log('Connect advertising success');
                                    const remote_endpoint_id = result.response.remote_endpoint_id;
                                    const payload = self._msg_discovery;
                                    _context.gameServices().NearbyConnection.SendUnreliableMessage(
                                        remote_endpoint_id, payload);
                                    self._text.setString('connect advertising success');
                                } else {
                                    __log('Connect advertising failed');
                                    self._text.setString('connect advertising failed');
                                }
                                // __log('GPG connect client_id:' + result.client_id
                                //     + ' REI:' + result.response.remote_endpoint_id
                                //     + ' Status:' + result.response.status
                                //     + ' Payload: ' + result.response.payload);
                            },
                            function(result) {
                                //message callback
                                self._text.setString('discovery receive:' + result.event);
                                if ('OnMessageReceived' == result.event) {
                                    __log('OnMessageReceived client_id:' + result.client_id
                                        + ' remote_endpoint_id:' + result.remote_endpoint_id
                                        + ' payload:' + result.payload
                                        + ' is_reliable:' + result.is_reliable)
                                    self._text_listener_data.setString(result.payload);
                                } else if ('OnDisconnected' == result.event) {
                                    __log('OnDisconnected client_id:' + result.client_id
                                        + ' remote_endpoint_id:' + result.remote_endpoint_id)
                                } else {
                                    __log('Unknown event:' + result.event);
                                }
                            });
                    } else if ('OnEndpointLost' == result.event) {
                        __log('lost client_id:' + result.client_id
                            + ' remote_endpoint_id:' + result.remote_endpoint_id);
                        self.__removeEndpoint(result.client_id, result.remote_endpoint_id);
                    } else {
                        __log('GPG discovery unknown event:' + result.event);
                    }
                });
        });
        this._mi_stop_discovery = new cc.MenuItemFont("StopDiscovery", function() {
            const server_id = 'com.sdkbox.hugo.test.gpg.nearby';
            self._mi_start_advertising.setVisible(true);
            self._mi_start_discovery.setVisible(true);
            self._mi_stop_discovery.setVisible(false);
            _context.gameServices().NearbyConnection.StopDiscovery(server_id);
        });
        this._mi_send_reliable_message = new cc.MenuItemFont("SendReliableMessage", function() {
            const remote_endpoint_id = '';
            const payload = 'this message';
            _context.gameServices().NearbyConnection.SendReliableMessage(
                remote_endpoint_id, payload);
        });
        this._mi_send_unreliable_message = new cc.MenuItemFont("SendUnreliableMessage", function() {
            const remote_endpoint_id = '';
            const payload = 'this is unreliable message';
            _context.gameServices().NearbyConnection.SendUnreliableMessage(
                remote_endpoint_id, payload);
        });
        this._mi_disconnect = new cc.MenuItemFont("Disconnect", function() {
            const remote_endpoint_id = '';
            _context.gameServices().NearbyConnection.Disconnect(remote_endpoint_id);
        });
        this._mi_stop = new cc.MenuItemFont("Stop", function() {
            _context.gameServices().NearbyConnection.Stop();
        });

        const menu = new cc.Menu(
            this._mi_start_advertising,
            this._mi_stop_advertising,
            this._mi_start_discovery,
            this._mi_stop_discovery,
            this._mi_send_reliable_message,
            this._mi_send_unreliable_message,
            this._mi_disconnect,
            this._mi_stop,
            new cc.MenuItemFont("Main menu", function () {
                cc.director.runScene( new HelloWorldScene() );
            })
            );
        menu.alignItemsVerticallyWithPadding(3);
        menu.x = winSize.width / 2;
        menu.y = winSize.height / 2 + 40;
        this.addChild(menu);

        this._mi_start_advertising.setVisible(false);
        this._mi_start_discovery.setVisible(false);
        this._mi_stop_advertising.setVisible(false);
        this._mi_stop_discovery.setVisible(false);
        this._mi_send_reliable_message.setVisible(false);
        this._mi_send_unreliable_message.setVisible(false);
        this._mi_disconnect.setVisible(false);
        this._mi_stop.setVisible(false);

        // let gs = _context.gameServices().RealTimeMultiplayer;
        // console.log(gs);
        if (!_context.gameServices().NearbyConnection.Init("{\"LogLevel\":1,\"ClientID\":234,\"ServiceID\":\"com.sdkbox.hugo.test.gpg.nearby\"}", function(result) {
            __log("GPG InitializationStatus:" + result.InitializationStatus);
            if (result.InitializationStatus) {
                self._mi_start_advertising.setVisible(true);
                self._mi_start_discovery.setVisible(true);
                const deviceId = _context.gameServices().NearbyConnection.GetLocalDeviceId();
                const endpointId = _context.gameServices().NearbyConnection.GetLocalEndpointId();
                __log('GPG NearbyConnection deviceId:' + deviceId + ' endpointId:' + endpointId);
                self._text.setString('NearbyConnection init success');
            } else {
                __log('GPG init failed');
                self._text.setString('NearbyConnection init failed');
            }
        })) {
            __log("GPG NearbyConnection init failed");
        }

        this._Menu = menu;
    },

    __addEndpoint : function(client_id, endpoint_id, device_id, name, server_id ) {
        const detail = {
            client_id: client_id,
            endpoint_id: endpoint_id,
            device_id: device_id,
            name: name,
            server_id: server_id
        }
        this._endpoints.push(detail);
        // detail._menu_item = new cc.MenuItemFont('Advertor: ' + name, function () {
        //     __log('Click on endpoint item');
        // })
        // this._Menu.addChild(detail._menu_item);
    },

    __removeEndpoint : function (client_id, endpoint_id) {
        let i = 0;
        for (i = this._endpoints.length - 1; i >= 0; i--) {
            const detail = this._endpoints[i];
            if (detail.endpoint_id == endpoint_id) {
                break;
            }
        }
        // this._Menu.removeChild(this._endpoints[i]._menu_item);
        this._endpoints.splice(i, 1);
    },

    __createMenu1 : function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        /**
         *
         * @type {gpg.RealTimeEventListener}
         */
        var listener = {

            onRoomStatusChanged: function (room) {
                me._text_listener.setString("room status changed. "+room.status);
            },

            onConnectedSetChanged: function (room) {
                me._text_listener.setString("room connected set changed.");
            },

            onP2PConnected: function (room, participant) {
                me._text_listener.setString("room p2p connected: " + participant.displayName);
            },

            onP2PDisconnected: function (room, participant) {
                me._text_listener.setString("room p2p disconnected: " + participant.displayName);
            },

            onParticipantStatusChanged: function (room, participant) {
                me._text_listener.setString("room participant status changed: "+ participant.displayName + " st:" + participant.status);
            },

            onDataReceived: function (room, from_participant, data, is_reliable) {
                me._text_listener.setString("data from:" + from_participant.displayName + " reliable:" + is_reliable + " len:"+data.length);
                me._text_listener_data.setString("'" + data + "'");
            }

        };

        this._mi_message_reliable = new cc.MenuItemFont("message reliable", function() {
            _context.gameServices().RealTimeMultiplayer.SendReliableMessage(
                {
                    data : "message " + me._message_index++,
                    room_id : me._room.id,
                    to_participant_id : me._room.participants.filter( function( p ) {
                        return p.id!==me._room.creatingParticipant.id;
                    })[0].id
                },
                /**
                 *
                 * @param result {gpg.MultiplayerStatus}
                 */
                function( result ) {
                    me._text.setString("send reliable message success: " + gpg.IsSuccess(result) ? "true" : "no. code:"+result);
                }
            );
        });

        this._mi_message_unreliable = new cc.MenuItemFont("message unreliable", function() {
            _context.gameServices().RealTimeMultiplayer.SendUnreliableMessage(
                {
                    data :              "message " + me._message_index++,
                    room_id :           me._room.id,
                    participant_ids :   me._room.participants.filter( function( p ) {
                                            return p.id!==me._room.creatingParticipant.id;
                                        }).map( function( p ) {
                                            return p.id;
                                        })
                }
            );
        });

        this._mi_message_unreliable_to_others = new cc.MenuItemFont("message unreliable to others", function() {
            _context.gameServices().RealTimeMultiplayer.SendUnreliableMessageToOthers(
                {
                    data :              "message " + me._message_index++,
                    room_id :           me._room.id
                }
            );
        });


        this._mi_leaveroom = new cc.MenuItemFont("Leave room", function() {

            _context.gameServices().RealTimeMultiplayer.LeaveRoom(
                /**
                 *
                 * @param res {gpg.ResponseStatus}
                 */
                function (res) {
                    if (gpg.IsSuccess(res)) {
                        me._text.setString("Room left.");
                        me._text_listener.setString("");
                        me._room = null;
                        me._mi_leaveroom.setVisible(false);
                        me._mi_message_reliable.setVisible(false);
                        me._mi_message_unreliable.setVisible(false);
                        me._mi_message_unreliable_to_others.setVisible(false);
                    } else {
                        me._text.setString("Room left error: " + res);
                    }
                }
            );
        });

        this._mi_accept_invitation = new cc.MenuItemFont("Accept invitation", function() {

            if ( me._invitation ) {
                _context.gameServices().RealTimeMultiplayer.AcceptInvitation(
                    {
                        invitation_id :  me._invitation.id,
                        listener : listener
                    },
                    /**
                     *
                     * @param res {RTAcceptInvitationCallbackParams}
                     */
                    function (res) {
                        if (gpg.IsSuccess(res.result)) {
                            me._text.setString("accepted invitation. Start game, room: " + res.room.id.substring(0, 10) + "...");
                            me._mi_leaveroom.setVisible(true);
                            me._mi_message_reliable.setVisible(true);
                            me._mi_message_unreliable.setVisible(true);
                            me._mi_message_unreliable_to_others.setVisible(true);


                            me._mi_accept_invitation.setVisible( false );
                            me._mi_dismiss_invitation.setVisible( false );
                            me._mi_decline_invitation.setVisible( false );

                            me._room = res.room;
                        } else {
                            me._text.setString("Accept invitation error: " + res.result);
                        }
                    }
                );
            } else {
                __log("can't find a local invitation.");
            }
        });

        this._mi_decline_invitation = new cc.MenuItemFont("Decline invitation", function() {
            _context.gameServices().RealTimeMultiplayer.DeclineInvitation(me._invitation.id);
        });

        this._mi_dismiss_invitation = new cc.MenuItemFont("Dismiss invitation", function() {
            _context.gameServices().RealTimeMultiplayer.DismissInvitation(me._invitation.id);
        });

        this._mi_leaveroom.setVisible( false );
        this._mi_accept_invitation.setVisible( false );
        this._mi_dismiss_invitation.setVisible( false );
        this._mi_decline_invitation.setVisible( false );

        this._mi_message_reliable.setVisible( false );
        this._mi_message_unreliable.setVisible( false );
        this._mi_message_unreliable_to_others.setVisible( false );

        var menu = new cc.Menu(

            new cc.MenuItemFont("CreateRoom automatch", function() {
                _context.gameServices().RealTimeMultiplayer.CreateRealTimeRoom(
                    {
                        type : "quick_match",
                        quick_match_params : {
                            maximumAutomatchingPlayers : 1,
                            minimumAutomatchingPlayers : 1
                        }
                    },
                    listener,
                    /**
                     *
                     * @param res {RTCreateRoomCallbackParams}
                     */
                    function( res ) {

                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("Room created: id="+res.room.id+" participants="+res.room.participants.length);
                            me._room= res.room;
                            me._mi_leaveroom.setVisible(true);
                            me._mi_message_reliable.setVisible(true);
                            me._mi_message_unreliable.setVisible(true);
                            me._mi_message_unreliable_to_others.setVisible(true);

                        } else {
                            me._text.setString("RT create room automatch error: "+ res.result);
                        }
                    }
                );

            }),

            new cc.MenuItemFont("CreateRoom select", function() {

                _context.gameServices().RealTimeMultiplayer.CreateRealTimeRoom(
                    {
                        type : "ui",
                        ui_params : {
                            maximumPlayers : 1,
                            minimumPlayers : 1
                        }
                    },
                    listener,
                    /**
                     *
                     * @param res {RTCreateRoomCallbackParams}
                     */
                    function( res ) {
                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("Room created: id="+res.room.id.substring(0,10)+"... participants="+res.room.participants.length);
                            me._room= res.room;
                            me._mi_leaveroom.setVisible(true);
                            me._mi_message_reliable.setVisible(true);
                            me._mi_message_unreliable.setVisible(true);
                            me._mi_message_unreliable_to_others.setVisible(true);

                        } else {
                            me._text.setString("RT create room ui error: "+ res.result);
                        }

                    }
                );

            }),

            new cc.MenuItemFont("Invitations UI", function() {

                _context.gameServices().RealTimeMultiplayer.ShowRoomInboxUI(
                    /**
                     *
                     * @param res {RTShowRoomInboxUICallbackParams}
                     */
                    function( res ) {
                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("got invitation: "+ (res.invitation.id.substr(0,10)) +"..." );
                            me._invitation = res.invitation;

                            // normally, you'd accept here the invitation.
                            // we're enabling accept/dismiss/decline ui just for sample purposes.
                            me._mi_accept_invitation.setVisible(true);
                            me._mi_dismiss_invitation.setVisible(true);
                            me._mi_decline_invitation.setVisible(true);
                        } else {
                            me._text.setString("RT invitation ui error: "+ res.result);

                            me._mi_accept_invitation.setVisible(false);
                            me._mi_dismiss_invitation.setVisible(false);
                            me._mi_decline_invitation.setVisible(false);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Fetch invitations", function() {
                _context.gameServices().RealTimeMultiplayer.FetchInvitations(
                    /**
                     *
                     * @param res {RTFetchInvitationsCallbackParams}
                     */
                    function( res ) {
                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("fetched " + res.invitations.length + " invitations.");
                        } else {
                            me._text.setString("fetch invitations error: "+ res.result);
                        }
                    }
                );
            }),

            me._mi_leaveroom,

            me._mi_accept_invitation,

            me._mi_dismiss_invitation,

            me._mi_decline_invitation,

            me._mi_message_reliable,

            me._mi_message_unreliable,

            me._mi_message_unreliable_to_others,

            new cc.MenuItemFont("Main menu", function () {
                cc.director.runScene( new HelloWorldScene() );
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_NearbyConnection = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerNearbyConnection());

    }
});
