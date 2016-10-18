var LayerTurnBasedMultiplayer = cc.Layer.extend({

    _lbInfo: null,

    ctor: function() {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._lbInfo = new cc.LabelTTF("", "sans", 24);
        this._lbInfo.x = cc.Director.getInstance().getWinSize().width / 2;
        this._lbInfo.y = 120;
        this.addChild(this._lbInfo);
    },

    __createMenu: function() {

        var self = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var menu = new cc.Menu(

            new cc.MenuItemFont("Create TurnBased Match", function() {
                let params = {
                    type: "ui", // "quick_match"
                    minimumAutomatchingPlayers: 1,
                    maximumAutomatchingPlayers: 2
                    // playerIds: 0
                };
                _context.gameServices().TurnBasedMultiplayer.CreateTurnBasedMatch(function(result) {
                    if (gpg.IsSuccess(result.result)) {
                        cc.log('Create TurnBased Match Success');
                        self._match = result.match;
                        self._myId = result.match.pendingParticipant.id;
                        self.handleMatch(self._match);
                    } else {
                        cc.log('Create TurnBased Match Failed:' + result.result);
                    }
                }, params);
            }),
            new cc.MenuItemFont("Show Match Inbox UI", function() {
                _context.gameServices().TurnBasedMultiplayer.ShowMatchInboxUI(function(result) {
                    if (gpg.IsSuccess(result.result)) {
                        cc.log('Show Match Inbox UI Success');
                        self._match = result.match;
                        self.handleMatch(self._match);
                    } else {
                        cc.log('Show Match Inbox UI Failed');
                    }
                });
            }),
            new cc.MenuItemFont('Dismiss Match', function() {
                if (null == self._match) {
                    cc.log('Match is none');
                    return
                }
                _context.gameServices().TurnBasedMultiplayer.DismissMatch(self._match.id);
            }),
            new cc.MenuItemFont('Fetch Match', function() {
                if (null == self._match) {
                    cc.log('Match is none');
                    return
                }
                _context.gameServices().TurnBasedMultiplayer.FetchMatch(function(result) {
                    if (gpg.IsSuccess(result.result)) {
                        cc.log('Fetch Match Success');
                    } else {
                        cc.log('Fetch Match Failed');
                    }
                }, self._match.id);
            }),
            new cc.MenuItemFont('Take My Turn', function() {
                if (null == self._match) {
                    cc.log('Match is none');
                    return
                }
                let participant_results_id = self._match.pendingParticipant.id;
                _context.gameServices().TurnBasedMultiplayer.createParticipantResult(self._myId,
                    participant_results_id,
                    0,
                    gpg.MatchResult.LOSS);
                let next_participant_id = self._match.suggestedNextParticipant.id;
                let data = JSON.stringify({counter: 1});
                _context.gameServices().TurnBasedMultiplayer.TakeMyTurn(function(result) {
                    if (gpg.IsSuccess(result.result)) {
                        cc.log('Take My Turn Success');
                    } else {
                        cc.log('Take My Turn Failed');
                    }
                },
                self._match.id,
                participant_results_id,
                next_participant_id,
                data);
            }),
            new cc.MenuItemFont('Finish Match During MyTurn', function() {
                if (null == self._match) {
                    cc.log('Match is none');
                    return
                }
                let participant_results_id = self._match.pendingParticipant.id;
                let participant_results_id = self._match.pendingParticipant.id;
                _context.gameServices().TurnBasedMultiplayer.createParticipantResult(self._myId,
                    participant_results_id,
                    0,
                    gpg.MatchResult.WIN);
                let data = JSON.stringify({counter: 1})
                _context.gameServices().TurnBasedMultiplayer.FinishMatchDuringMyTurn(function(result) {
                    if (gpg.IsSuccess(result.result)) {
                        cc.log('Finish Match During MyTurn Success');
                    } else {
                        cc.log('Finish Match During MyTurn Failed');
                    }
                },
                self._match.id,
                participant_results_id,
                data);
            }),
            new cc.MenuItemFont('Rematch', function() {
                if (null == self._match) {
                    cc.log('Match is none');
                    return
                }
                _context.gameServices().TurnBasedMultiplayer.Rematch(function(result) {
                    if (gpg.IsSuccess(result.result)) {
                        cc.log('Rematch Success');
                    } else {
                        cc.log('Rematch Failed');
                    }
                },
                self._match.id);
            }),
            new cc.MenuItemFont('Leave Match', function() {
                if (null == self._match) {
                    cc.log('Match is none');
                    return
                }
                if (self._match.matchStatus == gpg.MatchStatus.MY_TURN) {
                    _context.gameServices().TurnBasedMultiplayer.LeaveMatchDuringMyTurn(function(result) {
                        if (gpg.IsSuccess(result.result)) {
                            cc.log('Leave Match Success');
                        } else {
                            cc.log('Leave Match Failed');
                        }
                    },
                    self._match.id,
                    self._match.suggestedNextParticipant.id);
                } else {
                    _context.gameServices().TurnBasedMultiplayer.LeaveMatchDuringTheirTurn(function(result) {
                        if (gpg.IsSuccess(result.result)) {
                            cc.log('Leave Match Success');
                        } else {
                            cc.log('Leave Match Failed');
                        }
                    },
                    self._match.id);
                }
            }),
            new cc.MenuItemFont('Cancel Match', function() {
                if (null == self._match) {
                    cc.log('Match is none');
                    return
                }
                _context.gameServices().TurnBasedMultiplayer.CancelMatch(function(result) {
                    if (gpg.IsSuccess(result.result)) {
                        cc.log('Cancel Match Success');
                    } else {
                        cc.log('Cancel Match Failed');
                    }
                },
                self._match.id);
            }),
            new cc.MenuItemFont('Fetch Matches', function() {
                _context.gameServices().TurnBasedMultiplayer.FetchMatches(function(result) {
                    if (gpg.IsSuccess(result.result)) {
                        cc.log('Fetch Match Success');
                    } else {
                        cc.log('Fetch Match Failed');
                    }
                });
            }),
            new cc.MenuItemFont('Show Player Select UI', function() {
                let min_match_player = 1;
                let max_match_player = 2;
                let allow_automatch = true;
                _context.gameServices().TurnBasedMultiplayer.ShowPlayerSelectUI(function(result) {
                    if (gpg.IsSuccess(result.result)) {
                        cc.log('Show Player Select UI Success');
                    } else {
                        cc.log('Show Player Select UI Failed');
                    }
                },
                min_match_player,
                max_match_player,
                allow_automatch);
            }),

            new cc.MenuItemFont("Main menu", function() {
                cc.director.runScene(new HelloWorldScene());
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    },

    handleMatch: function(match) {
        if (match.matchStatus == gpg.MatchStatus.MY_TURN) {
            this._myId = match.pendingParticipant.id;
        } else if (match.matchStatus == gpg.MatchStatus.THEIR_TURN) {
        } else if (match.matchStatus == gpg.MatchStatus.COMPLETED) {
        } else if (match.matchStatus == gpg.MatchStatus.EXPIRED) {
        } else {
        }
    }

});

var S_TurnBasedMultiplayer = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerTurnBasedMultiplayer());
    }
});
