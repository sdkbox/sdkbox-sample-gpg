var LayerAchievement = cc.Layer.extend({

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
            new cc.MenuItemFont("Show UI", function() {
                // this method has no callback.
                _context.gameServices().Achievements.ShowAllUI(
                    /**
                     *
                     * @param result {AchievementShowAllUICallbackParams}
                     */
                    function(result) {

                    });
            }),
            new cc.MenuItemFont("Fetch all achievements", function() {
                _context.gameServices().Achievements.FetchAll(
                    gpg.DataSource.CACHE_OR_NETWORK,
                    /**
                     *
                     * @param result {AchievementFetchAllCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {

                            me._text.setString("Achievements fetch all got " + result.achievement_array.length + " achievements.");
                            result.achievement_array.forEach(
                                /**
                                 *
                                 * @param a {gpg.Achievement}
                                 */
                                function(a) {
                                    __log(
                                        a.name +
                                        ' type:' + (a.type === gpg.AchievementType.INCREMENTAL ? 'incremental' : 'standard') +
                                        ' state:' + a.state);
                                });

                        } else {
                            me._text.setString("Achievements fetch all error: " + result.result);
                        }
                    }
                );
            }),
            new cc.MenuItemFont("Fetch achievement 'Incremental'", function() {
                _context.gameServices().Achievements.Fetch({
                        achievement_id: 'CgkI6KjppNEWEAIQBQ',
                        data_source: gpg.DataSource.CACHE_OR_NETWORK
                    },
                    /**
                     *
                     * @param result {AchievementFetchCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {
                            var a = result.achievement;
                            me._text.setString(
                                a.name +
                                ' type:' + (a.type === gpg.AchievementType.INCREMENTAL ? 'incremental' : 'standard') +
                                ' state:' + a.state);

                        } else {
                            me._text.setString("Achievements fetch error: " + result.result);
                        }
                    }
                );
            }),
            new cc.MenuItemFont("Increment achievement", function() {
                // this method has no callback.
                _context.gameServices().Achievements.Increment({
                    achievement_id: 'CgkI6KjppNEWEAIQDg',
                    increment: 1
                });

                me._text.setString("Method w/o callback. Check by fetching or UI.");
            }),
            new cc.MenuItemFont("Set Steps at least achievement", function() {
                // this method has no callback.
                _context.gameServices().Achievements.SetStepsAtLeast({
                    achievement_id: 'CgkI6KjppNEWEAIQDg',
                    increment: 20
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

var S_Achievement = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerAchievement());
    }
});
