var LayerNearbyConnection = cc.Layer.extend({

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

    __createMenu: function() {
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
                        __log("GPG start advertising result:" + result.client_id + " status:" + result.start_advertising_result.status + " local_endpoint_name:" + result.start_advertising_result.local_endpoint_name);
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
                        function(result) {
                            __log('advertising connect listener')
                            self._text.setString('receive event:' + result.event);
                            if ('OnMessageReceived' == result.event) {
                                __log('OnMessageReceived client_id:' + result.client_id + ' remote_endpoint_id:' + result.remote_endpoint_id + ' payload:' + result.payload + ' is_reliable:' + result.is_reliable)
                                self._text_listener_data.setString(result.payload);
                            } else if ('OnDisconnected' == result.event) {
                                __log('OnDisconnected client_id:' + result.client_id + ' remote_endpoint_id:' + result.remote_endpoint_id)
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
                        __log('found client_id:' + result.client_id + 'endpoint detail endpoint_id:' + result.endpoint_details.endpoint_id + 'device_id:' + result.endpoint_details.device_id + 'name:' + result.endpoint_details.name + 'service_id:' + result.endpoint_details.server_id);
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
                                    __log('OnMessageReceived client_id:' + result.client_id + ' remote_endpoint_id:' + result.remote_endpoint_id + ' payload:' + result.payload + ' is_reliable:' + result.is_reliable)
                                    self._text_listener_data.setString(result.payload);
                                } else if ('OnDisconnected' == result.event) {
                                    __log('OnDisconnected client_id:' + result.client_id + ' remote_endpoint_id:' + result.remote_endpoint_id)
                                } else {
                                    __log('Unknown event:' + result.event);
                                }
                            });
                    } else if ('OnEndpointLost' == result.event) {
                        __log('lost client_id:' + result.client_id + ' remote_endpoint_id:' + result.remote_endpoint_id);
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
            new cc.MenuItemFont("Main menu", function() {
                cc.director.runScene(new HelloWorldScene());
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

    __addEndpoint: function(client_id, endpoint_id, device_id, name, server_id) {
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

    __removeEndpoint: function(client_id, endpoint_id) {
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

    __createMenu1: function() {

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

var S_NearbyConnection = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerNearbyConnection());

    }
});
