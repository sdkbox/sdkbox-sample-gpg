

var HelloWorldLayer = cc.Layer.extend({
    sprite          : null,
    info            : null,

    _signed_in      : false,
    _login_menu_item: null,

    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        cc.log("Sample Startup")

        this.createTestMenu();

        var winsize = cc.winSize;

        var logo = new cc.Sprite("res/Logo.png");
        var logoSize = logo.getContentSize();
        logo.x = logoSize.width / 2;
        logo.y = winsize.height - logoSize.height / 2;
        this.addChild(logo);

        var quit = new cc.MenuItemLabel(new cc.LabelTTF("QUIT", "sans", 32), function () {
            cc.log("QUIT");
        });
        var menu = new cc.Menu(quit);
        var size = quit.getContentSize();
        menu.x = winsize.width - size.width / 2 - 16;
        menu.y = size.height / 2 + 16;
        this.addChild(menu);

        this.info = new cc.LabelTTF("unknown status", "sans", 24);
        this.info.x = cc.Director.getInstance().getWinSize().width / 2;
        this.info.y = 90;
        this.addChild(this.info);

        this.__initGPG();

        return true;
    },

    __initGPG : function() {
        var me = this;

        var config = new gpg.PlatformConfiguration();
        config.SetClientID('777734739048-cdkbeieil19d6pfkavddrri5o19gk4ni.apps.googleusercontent.com');

        _game_services = new gpg.GameServices.Builder()
            .SetOnAuthActionStarted( function( result ) {
                __log('on auth action started: '+result.AuthOperation);
            })
            .SetOnAuthActionFinished( function( result ) {
                __log('on auth action finished: '+result.AuthOperation+' '+result.AuthStatus);

                if( result.AuthStatus === gpg.AuthStatus.VALID ) {
                    me._signed_in = true;
                    me.__disableLoginButton();

                    _game_services.LocalPlayer( function(local_player) {

                        // dump to console object contents.
                        local_player.__dump();
                        me.info.setString( local_player.Name() );
                    } );

                }
                else {
                    me._signed_in = false;
                    me.__enableLoginButton();
                }

            })
            .SetLogging( gpg.LogLevel.VERBOSE )
            .EnableSnapshots()
            .Create( config );
    },

    __enableLoginButton : function() {
        this._login_menu_item.setString("Sign in");
    },

    __disableLoginButton : function() {
        this._login_menu_item.setString("Sign out");
        this.info.setString('');
    },

    createTestMenu: function () {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        this._login_menu_item = new cc.MenuItemFont(
            "--",
            function () {
                if ( me._signed_in ) {
                    _game_services.SignOut();
                } else {
                    _gpg.GPGWrapper.StartAuthorizationUI();
                }
            });

        var menu = new cc.Menu(

            this._login_menu_item,

            new cc.MenuItemFont("Show SnapshotUI", function () {
                if ( me._signed_in ) {
                    _game_services.Snapshots.ShowSelectUIOperation(
                        {
                            allow_create : true,
                            allow_delete : true,
                            max_snapshots : 8,
                            title : 'a title for snapshoting'
                        },
                        /**
                         *
                         * @param result {tShowSelectionUIOperationParams}
                         */
                        function( result ) {
                            if ( result.result==='load' ) {
                                __log('snapshot load game');
                                var metadata = result.metadata;

                                _game_services.Snapshots.Load(
                                    {
                                        conflict_policy : gpg.SnapshotDefaultConflictPolicy,
                                        filename :        metadata.Filename
                                    },
                                    function( result ) {
                                        __log(' load game. metadata: ' + JSON.stringify(result.metadata));
                                        if ( result.result===gpg.ResponseStatus.VALID || result.result===gpg.ResponseStatus.VALID_BUT_STALE) {
                                            __log( 'result: '+result.data );
                                        } else {
                                            _log(' result not valid, so no contents.');
                                        }
                                    }
                                );

                            } else if ( result.result==='create' ) {

                                __log('snapshot create game');

                                _game_services.Snapshots.Save(
                                    {
                                        filename : 'ibon_testing',
                                        description : 'a valued saved game',
                                        data : JSON.stringify({ a:7 , b:'abcd', c: { d:false, e:[1,2,3], f : Math.random()}})
                                    },
                                    function( result ) {
                                        __log(' saved game. metadata: ' + JSON.stringify(result.metadata));
                                        if ( result.result===gpg.ResponseStatus.VALID || result.result===gpg.ResponseStatus.VALID_BUT_STALE) {
                                            __log( 'saved ok' );
                                        } else {
                                            _log('  saved with error. code: ' + result.result);
                                        }
                                    }
                                );

                            } else if ( result.result==='error' ) {
                                __log('snapshot ui error: '+result.error_code);
                            } else {
                                __log('snapshot ui error, unknown result ');
                            }
                        }
                    );
                }
            }),
            new cc.MenuItemFont("Fetch all games", function () {
                _game_services.Snapshots.FetchAll(
                    {
                        datasource : gpg.SnapshotConflictPolicy.DefaultConflictPolicy
                    },
                    function( result ) {
                        if ( gpg.IsSuccess(result.result) ) {
                            __log('Fetch all games success.');
                            __log('  Snapshots loaded: '+result.metadata_array.length);

                            result.metadata_array.forEach(
                                /**
                                 *
                                 * @param metadata {gpg.SnapshotMetadata}
                                 */
                                function(metadata) {
                                    __log( '       '+metadata.Filename );
                                });

                        } else {
                            __log('Fetch all games error. Code: '+result.result);
                        }
                    }
                )
            }),
            
            new cc.MenuItemFont("Delete ibon_testing game", function () {

                var filename = 'ibon_testing'

                _game_services.Snapshots.Delete(filename, function(result) {
                    if ( result.result==='success' ) {
                        __log('game '+filename+' deleted.');
                    } else {
                        __log('game '+filename+' did not delete. Reason:' + result.error_code + '.' );
                    }
                });
            })
            /*,
            new cc.MenuItemFont("Unlock Hunter", function () {

            }),
            new cc.MenuItemFont("Unlock Ten Games", function () {

            }),
            new cc.MenuItemFont("Unlock incremental", function () {

            }),
            new cc.MenuItemFont("Submit Score 1000", function () {

            })
            */
        );

        menu.alignItemsVerticallyWithPadding(5);
        menu.x = size.width / 2;
        menu.y = size.height / 2;
        this.addChild(menu);

    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter: function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

