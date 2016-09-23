var LayerLeaderboard = cc.Layer.extend({

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
            new cc.MenuItemFont("Show UI [Best gamers]", function() {

                _context.gameServices().Leaderboards.ShowUI("CgkI6KjppNEWEAIQAg");

            }),
            new cc.MenuItemFont("Show All UI", function() {
                _context.gameServices().Leaderboards.ShowAllUI();

            }),
            new cc.MenuItemFont("Submit random score to [Fastest lap]", function() {
                _context.gameServices().Leaderboards.SubmitScore({

                        leaderboard_id: 'CgkI6KjppNEWEAIQAw',

                        // currently there's a bug that won't submit the score if metadata is set.
                        metadata: 'sent from cocos js',

                        // this leaderboard has a max value of 300, and min of 0
                        score: (10 + Math.random() * 290) | 0
                    },
                    function(res) {
                        me._text.setString('result submit score: ' + res.result);
                    });

            }),
            new cc.MenuItemFont("Fetch all score summaries [best gamers]", function() {

                _context.gameServices().Leaderboards.FetchAllScoreSummaries({
                        leaderboard_id: 'CgkI6KjppNEWEAIQAg'
                    },
                    /**
                     * @param result {LeaderboardFetchAllScoreSummariesCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {

                            me._text.setString(
                                result.score_summary_array.reduce(
                                    /**
                                     * @param prev_str {string}
                                     * @param ss {gpg.ScoreSummary}
                                     * @return {string}
                                     */
                                    function(prev_str, ss) {
                                        return prev_str +
                                            ' ts:' + ss.timeSpan +
                                            ' col:' + ss.collection +
                                            ' sc:' + ss.currentPlayerScore.value +
                                            ' @@';
                                    },
                                    '')
                            );

                        } else {
                            me._text.setString("Fetch all score summaries res:" + result.result);
                        }
                    }
                )
            }),
            new cc.MenuItemFont("Fetch all", function() {
                _context.gameServices().Leaderboards.FetchAll(
                    gpg.DataSource.CACHE_OR_NETWORK,
                    /**
                     *
                     * @param result {LeaderboardFetchAllCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {
                            me._text.setString(
                                result.leaderboard_array.reduce(
                                    /**
                                     *
                                     * @param prev_str {string}
                                     * @param ldb {gpg.Leaderboard}
                                     * @returns {string}
                                     */
                                    function(prev_str, ldb) {
                                        return prev_str + 'name: ' + ldb.name + ' ## ';
                                    },
                                    '')
                            );
                        } else {
                            me._text.setString("Fetch all res:" + result.result);
                        }
                    }
                )
            }),
            new cc.MenuItemFont("Fetch score page", function() {

                _context.gameServices().Leaderboards.FetchScorePage({
                        leaderboard_id: 'CgkI6KjppNEWEAIQAg'
                    },
                    /**
                     *
                     * @param result {LeaderboardFetchScorePageCallbackParams}
                     */
                    function(result) {

                        if (gpg.IsSuccess(result.result)) {
                            me._text.setString("Get score page ok.");
                            result.scorePage.entries.forEach(
                                /**
                                 *
                                 * @param entry {gpg.ScorePage.Entry}
                                 */
                                function(entry) {
                                    _context.gameServices().Players.Fetch({
                                            player_id: entry.playerId
                                        },
                                        /**
                                         *
                                         * @param player_info {PlayersFetchCallbackParams}
                                         */
                                        function(player_info) {
                                            __log(player_info.player.name + " pos: " + entry.score.rank + " score: " + entry.score.value);
                                        }
                                    );

                                }
                            )
                        } else {
                            me._text.setString("Get score page error: " + result.result);
                        }
                    }
                );
            }),
            new cc.MenuItemFont("Fetch next score page", function() {

                _context.gameServices().Leaderboards.FetchNextScorePage({},
                    /**
                     *
                     * @param result {LeaderboardFetchScorePageCallbackParams}
                     */
                    function(result) {

                        if (gpg.IsSuccess(result.result)) {
                            me._text.setString("Get next score page ok.");
                            result.scorePage.entries.forEach(
                                /**
                                 *
                                 * @param entry {gpg.ScorePage.Entry}
                                 */
                                function(entry) {
                                    __log(entry.playerId + " pos: " + entry.score.rank + " score: " + entry.score.value);
                                }
                            )
                        } else {
                            me._text.setString("Get score page error: " + result.result);
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

var S_Leaderboard = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerLeaderboard());
    }
});
