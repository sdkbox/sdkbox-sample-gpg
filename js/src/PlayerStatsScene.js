var LayerPlayerStats = cc.Layer.extend({

    _text: null,

    ctor: function() {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);
    },

    __createMenu: function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var menu = new cc.Menu(

            new cc.MenuItemFont("FetchForPlayer", function() {

                // there's no callback for this method.
                _context.gameServices().Stats.FetchForPlayer(
                    /**
                     *
                     * @param result {StatsFetchForPlayerCallbackParams}
                     */
                    function(result) {
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

            new cc.MenuItemFont("Main menu", function() {
                cc.director.runScene(new HelloWorldScene());
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_PlayerStats = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerPlayerStats());
    }
});
