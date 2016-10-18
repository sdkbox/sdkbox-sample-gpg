var HelloWorldLayer = cc.Layer.extend({
    sprite: null,
    info: null,
    _text: null,

    _login_menu_item: null,

    _scenes: null,

    createMenu: function() {

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        // create special login menu item
        this._login_menu_item = new cc.MenuItemFont(
            "--",
            function() {
                if (_context.isInitialized()) {
                    if (_context.isSignedIn()) {
                        _context.gameServices().SignOut();
                    } else {
                        _context.gameServices().StartAuthorizationUI();
                    }
                } else {
                    __log('Fatal, no _game_services object present.');
                }
            });

        if (_context && _context.isInitialized()) {
            if (_context.isSignedIn()) {
                this.__disableLoginButton();
            } else {
                this.__enableLoginButton();
            }
        }

        var menu = new cc.Menu(
            this._login_menu_item,
            new cc.MenuItemFont("Snapshots", function() {
                cc.director.runScene(new S_SnapShots());
            }),
            new cc.MenuItemFont("Leaderboards", function() {
                cc.director.runScene(new S_Leaderboard());
            }),
            new cc.MenuItemFont("Achievements", function() {
                cc.director.runScene(new S_Achievement());
            }),
            new cc.MenuItemFont("Quests", function() {
                cc.director.runScene(new S_Quest());
            }),
            new cc.MenuItemFont("Events", function() {
                cc.director.runScene(new S_Events());
            }),
            new cc.MenuItemFont("Player Stats", function() {
                cc.director.runScene(new S_PlayerStats());
            }),
            new cc.MenuItemFont("Realtime Multiplayer", function() {
                cc.director.runScene(new S_RealtimeMultiplayer());
            }),
            new cc.MenuItemFont("TurnBased Multiplayer", function() {
                cc.director.runScene(new S_TurnBasedMultiplayer());
            }),
            new cc.MenuItemFont("Nearby Connection", function() {
                cc.director.runScene(new S_NearbyConnection());
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    },

    ctor: function() {
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
                function(p) {
                    if (p.start === false) { // EndAuthenticationProcess

                        if (p.operation === gpg.AuthOperation.SIGN_IN) { // Sign in ?

                            if (gpg.IsSuccess(p.result)) { // succesful ?

                                me.__disableLoginButton();

                                _context.setLocalPlayer(function(p) { // this is a good spot to get and cache
                                    // local player's info.
                                    if (p) {
                                        // dump to console object contents.
                                        gpg.Player.__Dump(p);
                                        me.info.setString(p.name);
                                    } else {
                                        me.info.setString("can't get my player info.");
                                    }
                                });

                            } else {
                                me.__enableLoginButton(); // no sucessful, set menu item to sign in
                            }
                        } else { // sign out ?
                            me.__enableLoginButton(); // set menu item to sign in.
                        }
                    }
                });
        }

        if (_context === null) {
            _context = new GPGContext({
                /**
                 *
                 * @param _game_services {BuilderCreateCallback}
                 */
                onGameServicesCreated: function(_game_services) {

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
                onMultiplayerInvitation: function(params) {
                    _global_label && _global_label.setString("you received an invitation: " + params.match.id.substring(0, 10) + "...");
                }
            });
        } else {
            me.createMenu();

            if (_context && _context.localPlayer()) {
                me.info.setString(_context.localPlayer().name);
            } else {

                __log("checking for ctx " + (_context !== null));
                __log("checking for ctx.p " + (_context.localPlayer() !== null));
            }

            setContextListeners();
        }

        return true;
    },

    __enableLoginButton: function() {
        this._login_menu_item.setString("Sign in");
        this.info.setString('');
    },

    __disableLoginButton: function() {
        this._login_menu_item.setString("Sign out");
        this.info.setString('');
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter: function() {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});
