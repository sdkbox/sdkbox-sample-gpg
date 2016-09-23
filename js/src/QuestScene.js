var LayerQuest = cc.Layer.extend({

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
            new cc.MenuItemFont("Fetch quest list", function() {
                _context.gameServices().Quests.FetchList(
                    gpg.DataSource.CACHE_OR_NETWORK,
                    /**
                     *
                     * @param result {QuestsFetchListCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {

                            me._text.setString("Quests fetch list, got " + result.data.length + " quests.");
                            result.data.forEach(
                                /**
                                 *
                                 * @param a {gpg.Quest}
                                 */
                                function(a) {
                                    __log(
                                        a.name +
                                        ' state:' + a.questState +
                                        ' id:' + a.id +
                                        ' valid: ' + a.valid);
                                });

                        } else {
                            me._text.setString("Quests fetch list error: " + result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Fetch quest", function() {
                _context.gameServices().Quests.Fetch({

                        data_source: gpg.DataSource.CACHE_OR_NETWORK,
                        quest_id: '<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ'
                    },
                    /**
                     *
                     * @param result {QuestsFetchCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {

                            var a = result.quest;

                            me._text.setString("Quests fetch " +
                                a.name +
                                ' state:' + a.questState +
                                ' id:' + a.id +
                                ' valid: ' + a.valid);

                        } else {
                            me._text.setString("Quests fetch error: " + result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Show All UI", function() {
                _context.gameServices().Quests.ShowAllUI(
                    /**
                     *
                     * @param result {QuestsShowAllUICallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {
                            me._text.setString("Quests show all ok. Quest:" + result.quest.name);

                        } else {
                            me._text.setString("Quests show all ui error: " + result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Show UI quest", function() {
                _context.gameServices().Quests.ShowUI(
                    '<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ',
                    /**
                     *
                     * @param result {QuestsShowUICallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {
                            me._text.setString("Quests show all ok. Quest:" + result.quest.name);

                        } else {
                            me._text.setString("Quests show all ui error: " + result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Accept quest", function() {
                _context.gameServices().Quests.Accept(
                    '<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ',
                    /**
                     *
                     * @param result {QuestsAcceptCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {
                            me._text.setString("Quests accept ok. Quest:" + result.quest.name);

                        } else {
                            me._text.setString("Quests accept error: " + result.result);
                        }
                    }
                );
            }),

            new cc.MenuItemFont("Claim milestone", function() {
                _context.gameServices().Quests.ClaimMilestone(
                    '<ChwKCQjg9PmjmwMQARINCgkI6KjppNEWEAIQDRgBEgIIAQ',
                    /**
                     *
                     * @param result {QuestsClaimMilestoneCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {
                            me._text.setString(
                                "Quests claim milestone." +
                                " Quest:" + result.quest.name +
                                " Mlstone st:" + result.milestone.state +
                                " count" + result.milestone.currentCount + "/" + result.milestone.currentCount);

                        } else {
                            me._text.setString("Quests claim milestone error: " + result.result);
                        }
                    }
                );
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

var S_Quest = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerQuest());
    }
});
