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
 *
 * @type {gpg.GameServices}
 * @name _game_services
 */
var _game_services = null;



var HelloWorldLayer = cc.Layer.extend({
    sprite          : null,
    info            : null,
    _text           : null,

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

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);

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

                    _game_services.Players.FetchSelf(
                        gpg.DataSource.CACHE_OR_NETWORK,
                        /**
                         *
                         * @param res {PlayersFetchSelfCallbackParams}
                         */
                        function( res ) {

                            if (gpg.IsSuccess(res.result) ) {
                                // dump to console object contents.
                                gpg.Player.__Dump( res.player );
                                me.info.setString(res.player.name);
                            } else {
                                me.info.setString("can't get my player info.");
                            }
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
            //
            // new cc.MenuItemFont("Snp: Show SnapshotUI", function () {
            //     if ( me._signed_in ) {
            //         _game_services.Snapshots.ShowSelectUIOperation(
            //             {
            //                 allow_create : true,
            //                 allow_delete : true,
            //                 max_snapshots : 8,
            //                 title : 'a title for snapshoting'
            //             },
            //             /**
            //              *
            //              * @param result {tSnapshotShowSelectionUIOperationCallbackResult}
            //              */
            //             function( result ) {
            //                 if ( result.result==='load' ) {
            //                     __log('snapshot load game');
            //                     var metadata = result.metadata;
            //
            //                     _game_services.Snapshots.Load(
            //                         {
            //                             conflict_policy : gpg.SnapshotConflictPolicy.DefaultConflictPolicy,
            //                             filename :        metadata.filename
            //                         },
            //                         /**
            //                          *
            //                          * @param result {tSnapshotLoadCallbackResult}
            //                          */
            //                         function( result ) {
            //                             __log(' load game. metadata: ' + JSON.stringify(result.metadata));
            //                             if ( result.result===gpg.ResponseStatus.VALID || result.result===gpg.ResponseStatus.VALID_BUT_STALE) {
            //                                 __log( 'result: '+result.data );
            //                             } else {
            //                                 __log(' result not valid, so no contents.');
            //                             }
            //                         }
            //                     );
            //
            //                 } else if ( result.result==='create' ) {
            //
            //                     __log('snapshot create game');
            //
            //                     _game_services.Snapshots.Save(
            //                         {
            //                             filename : 'ibon_testing',
            //                             description : 'a valued saved game',
            //                             data : JSON.stringify({ a:7 , b:'abcd', c: { d:false, e:[1,2,3], f : Math.random()}})
            //                         },
            //                         function( result ) {
            //                             __log(' saved game. metadata: ' + JSON.stringify(result.metadata));
            //                             if ( result.result===gpg.ResponseStatus.VALID || result.result===gpg.ResponseStatus.VALID_BUT_STALE) {
            //                                 __log( 'saved ok' );
            //                             } else {
            //                                 __log('  saved with error. code: ' + result.result);
            //                             }
            //                         }
            //                     );
            //
            //                 } else if ( result.result==='error' ) {
            //                     __log('snapshot ui error: '+result.error_code);
            //                 } else {
            //                     __log('snapshot ui error, unknown result ');
            //                 }
            //             }
            //         );
            //     }
            // }),
            // new cc.MenuItemFont("Snp: Fetch all games", function () {
            //     _game_services.Snapshots.FetchAll(
            //         {
            //             data_source : gpg.DataSource.CACHE_OR_NETWORK
            //         },
            //         function( result ) {
            //             if ( gpg.IsSuccess(result.result) ) {
            //                 __log('Fetch all games success.');
            //                 __log('  Snapshots loaded: '+result.metadata_array.length);
            //
            //                 result.metadata_array.forEach(
            //                     /**
            //                      *
            //                      * @param metadata {gpg.SnapshotMetadata}
            //                      */
            //                     function(metadata) {
            //                         __log( '       '+metadata.filename );
            //                     });
            //
            //             } else {
            //                 __log('Fetch all games error. Code: '+result.result);
            //             }
            //         }
            //     )
            // }),
            // new cc.MenuItemFont("Snp: Delete ibon_testing game", function () {
            //
            //     var filename = 'ibon_testing';
            //
            //     _game_services.Snapshots.Delete(filename, function(result) {
            //         if ( result.result==='success' ) {
            //             __log('game '+filename+' deleted.');
            //         } else {
            //             __log('game '+filename+' did not delete. Reason:' + result.error_code + '.' );
            //         }
            //     });
            // }),
            // new cc.MenuItemFont("Ldb: Show UI [Best gamers]", function () {
            //
            //     _game_services.Leaderboards.ShowUI("CgkI6KjppNEWEAIQAg");
            //
            // }),
            // new cc.MenuItemFont("Ldb: Show All UI", function () {
            //     _game_services.Leaderboards.ShowAllUI( );
            //
            // }),
            // new cc.MenuItemFont("Ldb: Submit random score to [Fastest lap]", function () {
            //     _game_services.Leaderboards.SubmitScore(
            //         {
            //
            //             leaderboard_id : 'CgkI6KjppNEWEAIQAw',
            //
            //             // currently there's a bug that won't submit the score if metadata is set.
            //             metadata : 'sent from cocos js',
            //
            //             // this leaderboard has a max value of 300, and min of 0
            //             score : (10 + Math.random()*290)|0
            //         },
            //         function( res ) {
            //             __log('result submit score: '+res.result);
            //         });
            //
            // }),
            // new cc.MenuItemFont("Ldb: fetch all score summaries [best gamers]", function () {
            //
            //     _game_services.Leaderboards.FetchAllScoreSummaries(
            //         {
            //             leaderboard_id : 'CgkI6KjppNEWEAIQAg'
            //         },
            //         /**
            //          * @param result {LeaderboardFetchAllScoreSummariesCallbackParams}
            //          */
            //         function( result ) {
            //             if ( gpg.IsSuccess( result.result ) ) {
            //
            //                 me._text.setString(
            //                     result.score_summary_array.reduce(
            //                         /**
            //                          * @param prev_str {string}
            //                          * @param ss {gpg.ScoreSummary}
            //                          * @return {string}
            //                          */
            //                         function( prev_str, ss ) {
            //                             return prev_str +
            //                                 ' ts:' + ss.timeSpan +
            //                                 ' col:' + ss.collection +
            //                                 ' sc:' + ss.currentPlayerScore.value +
            //                                 ' @@';
            //                         },
            //                         '')
            //                 );
            //
            //             } else {
            //                 me._text.setString("Fetch all score summaries res:"+result.result);
            //             }
            //         }
            //     )
            // }),
            // new cc.MenuItemFont("Ldb: fetch all", function () {
            //     _game_services.Leaderboards.FetchAll(
            //         gpg.DataSource.CACHE_OR_NETWORK,
            //         /**
            //          *
            //          * @param result {LeaderboardFetchAllCallbackParams}
            //          */
            //         function( result ) {
            //             if ( gpg.IsSuccess(result.result ) ) {
            //                 me._text.setString(
            //                     result.leaderboard_array.reduce(
            //                         /**
            //                          *
            //                          * @param prev_str {string}
            //                          * @param ldb {gpg.Leaderboard}
            //                          * @returns {string}
            //                          */
            //                         function( prev_str, ldb ) {
            //                             return prev_str + 'name: ' + ldb.name + ' ## ';
            //                         },
            //                         '')
            //                 );
            //             } else {
            //                 me._text.setString("Fetch all res:"+result.result);
            //             }
            //         }
            //     )
            // }),
            // new cc.MenuItemFont("Ldb: Fetch score page", function () {
            //
            //     _game_services.Leaderboards.FetchScorePage(
            //         {
            //             leaderboard_id : 'CgkI6KjppNEWEAIQAg'
            //         },
            //         /**
            //          *
            //          * @param result {LeaderboardFetchScorePageCallbackParams}
            //          */
            //         function( result ) {
            //
            //             if ( gpg.IsSuccess(result.result ) ) {
            //                 me._text.setString("Get score page ok.");
            //                 result.scorePage.entries.forEach(
            //                     /**
            //                      *
            //                      * @param entry {gpg.ScorePage.Entry}
            //                      */
            //                     function( entry ) {
            //                         _game_services.Players.Fetch(
            //                             {
            //                                 player_id : entry.playerId
            //                             },
            //                             /**
            //                              *
            //                              * @param player_info {PlayersFetchCallbackParams}
            //                              */
            //                             function( player_info ) {
            //                                 __log( player_info.player.name + " pos: " + entry.score.rank + " score: " + entry.score.value );
            //                             }
            //                         );
            //
            //                     }
            //                 )
            //             } else {
            //                 me._text.setString("Get score page error: "+ result.result);
            //             }
            //         }
            //     );
            // }),
            // new cc.MenuItemFont("Ldb: Fetch next score page", function () {
            //
            //     _game_services.Leaderboards.FetchNextScorePage(
            //         {},
            //         /**
            //          *
            //          * @param result {LeaderboardFetchScorePageCallbackParams}
            //          */
            //         function( result ) {
            //
            //             if ( gpg.IsSuccess(result.result ) ) {
            //                 me._text.setString("Get next score page ok.");
            //                 result.scorePage.entries.forEach(
            //                     /**
            //                      *
            //                      * @param entry {gpg.ScorePage.Entry}
            //                      */
            //                     function( entry ) {
            //                         __log( entry.playerId + " pos: " + entry.score.rank + " score: " + entry.score.value );
            //                     }
            //                 )
            //             } else{
            //                 me._text.setString("Get score page error: "+ result.result);
            //             }
            //         }
            //     );
            // }),
            // new cc.MenuItemFont("Ach: Show UI", function() {
            //     // this method has no callback.
            //     _game_services.Achievements.ShowAllUI(
            //         /**
            //          *
            //          * @param result {AchievementShowAllUICallbackParams}
            //          */
            //         function( result ) {
            //
            //         });
            // }),
            // new cc.MenuItemFont("Ach: Fetch all achievements", function () {
            //     _game_services.Achievements.FetchAll(
            //         gpg.DataSource.CACHE_OR_NETWORK,
            //         /**
            //          *
            //          * @param result {AchievementFetchAllCallbackParams}
            //          */
            //         function( result ) {
            //             if ( gpg.IsSuccess( result.result ) ) {
            //                 result.achievement_array.forEach(
            //                     /**
            //                      *
            //                      * @param a {gpg.Achievement}
            //                      */
            //                     function( a ) {
            //                         __log(
            //                             a.name +
            //                             ' type:' + (a.type===gpg.AchievementType.INCREMENTAL ? 'incremental' : 'standard') +
            //                             ' state:' + a.state);
            //                     });
            //
            //             } else {
            //                 me._text.setString("Achievements fetch all error: "+ result.result);
            //             }
            //         }
            //     );
            // }),
            // new cc.MenuItemFont("Ach: Fetch achievement 'Incremental'", function() {
            //     _game_services.Achievements.Fetch(
            //         {
            //             achievement_id : 'CgkI6KjppNEWEAIQBQ',
            //             data_source : gpg.DataSource.CACHE_OR_NETWORK
            //         },
            //         /**
            //          *
            //          * @param result {AchievementFetchCallbackParams}
            //          */
            //         function( result ) {
            //             if ( gpg.IsSuccess( result.result ) ) {
            //                 var a = result.achievement;
            //                 me._text.setString(
            //                     a.name +
            //                     ' type:' + (a.type===gpg.AchievementType.INCREMENTAL ? 'incremental' : 'standard') +
            //                     ' state:' + a.state);
            //
            //             } else {
            //                 me._text.setString("Achievements fetch error: "+ result.result);
            //             }
            //         }
            //     );
            // }),
            // new cc.MenuItemFont("Ach: Increment achievement", function() {
            //     // this method has no callback.
            //     _game_services.Achievements.Increment(
            //         {
            //             achievement_id: 'CgkI6KjppNEWEAIQDg',
            //             increment : 1
            //         });
            // }),
            // new cc.MenuItemFont("Ach: Set Steps at least achievement", function() {
            //     // this method has no callback.
            //     _game_services.Achievements.SetStepsAtLeast(
            //         {
            //             achievement_id: 'CgkI6KjppNEWEAIQDg',
            //             increment : 20
            //         });
            // }),
            // new cc.MenuItemFont("Ach: Unlock achievement", function() {
            //     // this method has no callback.
            //     _game_services.Achievements.Unlock('CgkI6KjppNEWEAIQDg');
            // }),
            // new cc.MenuItemFont("Ach: Reveal achievement", function() {
            //     // this method has no callback.
            //     _game_services.Achievements.Reveal('CgkI6KjppNEWEAIQDg');
            // }),

            new cc.MenuItemFont("Qst: Fetch quest list", function () {
                _game_services.Quests.FetchList(
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

            new cc.MenuItemFont("Qst: Fetch quest", function () {
                _game_services.Quests.Fetch(
                    {

                        data_source : gpg.DataSource.CACHE_OR_NETWORK,
                        quest_id : '<CgkIyv_j68cCEAESDQoJCOio6aTRFhACEA0YAQ'
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

            new cc.MenuItemFont("Qst: Show All UI", function () {
                _game_services.Quests.ShowAllUI(
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

            new cc.MenuItemFont("Qst: Show UI quest", function () {
                _game_services.Quests.ShowUI(
                    '<CgkIyv_j68cCEAESDQoJCOio6aTRFhACEA0YAQ',
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

            new cc.MenuItemFont("Qst: Accept quest", function () {
                _game_services.Quests.Accept(
                    '<CgkIyv_j68cCEAESDQoJCOio6aTRFhACEA0YAQ',
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

            new cc.MenuItemFont("Qst: Claim milestone", function () {
                _game_services.Quests.ClaimMilestone(
                    '<ChwKCQjK_-PrxwIQARINCgkI6KjppNEWEAIQDRgBEgIIAQ',
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

            new cc.MenuItemFont("Evt: FetchAll", function () {

                _game_services.Events.FetchAll(
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
                            me._text.setString("Events fetch all got: "+ result.data.length + "elements.");
                        } else {
                            me._text.setString("Events fetch all error: "+ result.result);
                        }
                    });
            }),

            new cc.MenuItemFont("Evt: Fetch", function () {

                _game_services.Events.Fetch(
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

            new cc.MenuItemFont("Evt: Increment", function () {

                // there's no callback for this method.
                _game_services.Events.Increment(
                    {
                        event_id : 'CgkI6KjppNEWEAIQDA',
                        increment : 2
                    });
            }),

            new cc.MenuItemFont("PlStats: FetchForPlayer", function () {

                // there's no callback for this method.
                _game_services.Stats.FetchForPlayer(
                    /**
                     *
                     * @param result {StatsFetchForPlayerCallbackParams}
                     */
                    function( result ) {
                        if ( gpg.IsSuccess(result.result) ) {

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



            new cc.MenuItemFont("RT: CreateRoom automatch", function() {
                _game_services.RealTimeMultiplayer.CreateRealTimeRoom(
                    {
                        type : "quick_match",
                        quick_match_params : {
                            maximumAutomatchingPlayers : 1,
                            minimumAutomatchingPlayers : 1
                        }
                    },
                    /**
                     *
                     * @param res {RTCreateRoomCallbackParams}
                     */
                    function( res ) {

                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("Room created: id="+res.room.id+" participants="+res.room.participants.length);
                        } else {
                            me._text.setString("RT create room automatch error: "+ res.result);
                        }
                    }
                );

            }),

            new cc.MenuItemFont("RT: CreateRoom select", function() {

                _game_services.RealTimeMultiplayer.CreateRealTimeRoom(
                    {
                        type : "ui",
                        ui_params : {
                            maximumPlayers : 1,
                            minimumPlayers : 1
                        }
                    },
                    /**
                     *
                     * @param res {RTCreateRoomCallbackParams}
                     */
                    function( res ) {
                        if ( gpg.IsSuccess(res.result) ) {
                            me._text.setString("Room created: id="+res.room.id+" participants="+res.room.participants.length);
                        } else {
                            me._text.setString("RT create room ui error: "+ res.result);
                        }

                    }
                );

            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
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

