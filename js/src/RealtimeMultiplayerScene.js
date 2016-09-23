var LayerRealtimeMultiplayer = cc.Layer.extend({

    _text: null,
    _text_listener: null,
    _text_listener_data: null,

    /**
     * @type  {gpg.RealTimeRoom}
     */
    _room: null,

    /**
     * @type {gpg.MultiplayerInvitation}
     */
    _invitation: null,

    _mi_accept_invitation: null,
    _mi_dismiss_invitation: null,
    _mi_decline_invitation: null,

    _mi_message_reliable: null,
    _mi_message_unreliable: null,
    _mi_message_unreliable_to_others: null,

    _mi_leaveroom: null,

    _message_index: 0,

    ctor: function() {
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

    __createMenu: function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        /**
         *
         * @type {gpg.RealTimeEventListener}
         */
        var listener = {

            onRoomStatusChanged: function(room) {
                me._text_listener.setString("room status changed. " + room.status);
            },

            onConnectedSetChanged: function(room) {
                me._text_listener.setString("room connected set changed.");
            },

            onP2PConnected: function(room, participant) {
                me._text_listener.setString("room p2p connected: " + participant.displayName);
            },

            onP2PDisconnected: function(room, participant) {
                me._text_listener.setString("room p2p disconnected: " + participant.displayName);
            },

            onParticipantStatusChanged: function(room, participant) {
                me._text_listener.setString("room participant status changed: " + participant.displayName + " st:" + participant.status);
            },

            onDataReceived: function(room, from_participant, data, is_reliable) {
                me._text_listener.setString("data from:" + from_participant.displayName + " reliable:" + is_reliable + " len:" + data.length);
                me._text_listener_data.setString("'" + data + "'");
            }

        };

        this._mi_message_reliable = new cc.MenuItemFont("message reliable", function() {
            _context.gameServices().RealTimeMultiplayer.SendReliableMessage({
                    data: "message " + me._message_index++,
                    room_id: me._room.id,
                    to_participant_id: me._room.participants.filter(function(p) {
                        return p.id !== me._room.creatingParticipant.id;
                    })[0].id
                },
                /**
                 *
                 * @param result {gpg.MultiplayerStatus}
                 */
                function(result) {
                    me._text.setString("send reliable message success: " + gpg.IsSuccess(result) ? "true" : "no. code:" + result);
                }
            );
        });

        this._mi_message_unreliable = new cc.MenuItemFont("message unreliable", function() {
            _context.gameServices().RealTimeMultiplayer.SendUnreliableMessage({
                data: "message " + me._message_index++,
                room_id: me._room.id,
                participant_ids: me._room.participants.filter(function(p) {
                    return p.id !== me._room.creatingParticipant.id;
                }).map(function(p) {
                    return p.id;
                })
            });
        });

        this._mi_message_unreliable_to_others = new cc.MenuItemFont("message unreliable to others", function() {
            _context.gameServices().RealTimeMultiplayer.SendUnreliableMessageToOthers({
                data: "message " + me._message_index++,
                room_id: me._room.id
            });
        });


        this._mi_leaveroom = new cc.MenuItemFont("Leave room", function() {

            _context.gameServices().RealTimeMultiplayer.LeaveRoom(
                /**
                 *
                 * @param res {gpg.ResponseStatus}
                 */
                function(res) {
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

            if (me._invitation) {
                _context.gameServices().RealTimeMultiplayer.AcceptInvitation({
                        invitation_id: me._invitation.id,
                        listener: listener
                    },
                    /**
                     *
                     * @param res {RTAcceptInvitationCallbackParams}
                     */
                    function(res) {
                        if (gpg.IsSuccess(res.result)) {
                            me._text.setString("accepted invitation. Start game, room: " + res.room.id.substring(0, 10) + "...");
                            me._mi_leaveroom.setVisible(true);
                            me._mi_message_reliable.setVisible(true);
                            me._mi_message_unreliable.setVisible(true);
                            me._mi_message_unreliable_to_others.setVisible(true);


                            me._mi_accept_invitation.setVisible(false);
                            me._mi_dismiss_invitation.setVisible(false);
                            me._mi_decline_invitation.setVisible(false);

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

        this._mi_leaveroom.setVisible(false);
        this._mi_accept_invitation.setVisible(false);
        this._mi_dismiss_invitation.setVisible(false);
        this._mi_decline_invitation.setVisible(false);

        this._mi_message_reliable.setVisible(false);
        this._mi_message_unreliable.setVisible(false);
        this._mi_message_unreliable_to_others.setVisible(false);

        var menu = new cc.Menu(

            new cc.MenuItemFont("CreateRoom automatch", function() {
                _context.gameServices().RealTimeMultiplayer.CreateRealTimeRoom({
                        type: "quick_match",
                        quick_match_params: {
                            maximumAutomatchingPlayers: 1,
                            minimumAutomatchingPlayers: 1
                        }
                    },
                    listener,
                    /**
                     *
                     * @param res {RTCreateRoomCallbackParams}
                     */
                    function(res) {

                        if (gpg.IsSuccess(res.result)) {
                            me._text.setString("Room created: id=" + res.room.id + " participants=" + res.room.participants.length);
                            me._room = res.room;
                            me._mi_leaveroom.setVisible(true);
                            me._mi_message_reliable.setVisible(true);
                            me._mi_message_unreliable.setVisible(true);
                            me._mi_message_unreliable_to_others.setVisible(true);

                        } else {
                            me._text.setString("RT create room automatch error: " + res.result);
                        }
                    }
                );

            }),

            new cc.MenuItemFont("CreateRoom select", function() {

                _context.gameServices().RealTimeMultiplayer.CreateRealTimeRoom({
                        type: "ui",
                        ui_params: {
                            maximumPlayers: 1,
                            minimumPlayers: 1
                        }
                    },
                    listener,
                    /**
                     *
                     * @param res {RTCreateRoomCallbackParams}
                     */
                    function(res) {
                        if (gpg.IsSuccess(res.result)) {
                            me._text.setString("Room created: id=" + res.room.id.substring(0, 10) + "... participants=" + res.room.participants.length);
                            me._room = res.room;
                            me._mi_leaveroom.setVisible(true);
                            me._mi_message_reliable.setVisible(true);
                            me._mi_message_unreliable.setVisible(true);
                            me._mi_message_unreliable_to_others.setVisible(true);

                        } else {
                            me._text.setString("RT create room ui error: " + res.result);
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
                    function(res) {
                        if (gpg.IsSuccess(res.result)) {
                            me._text.setString("got invitation: " + (res.invitation.id.substr(0, 10)) + "...");
                            me._invitation = res.invitation;

                            // normally, you'd accept here the invitation.
                            // we're enabling accept/dismiss/decline ui just for sample purposes.
                            me._mi_accept_invitation.setVisible(true);
                            me._mi_dismiss_invitation.setVisible(true);
                            me._mi_decline_invitation.setVisible(true);
                        } else {
                            me._text.setString("RT invitation ui error: " + res.result);

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
                    function(res) {
                        if (gpg.IsSuccess(res.result)) {
                            me._text.setString("fetched " + res.invitations.length + " invitations.");
                        } else {
                            me._text.setString("fetch invitations error: " + res.result);
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

var S_RealtimeMultiplayer = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerRealtimeMultiplayer());
    }
});
