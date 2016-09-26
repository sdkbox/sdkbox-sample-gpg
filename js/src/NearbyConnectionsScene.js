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
            _context.gameServices().NearbyConnections.StartAdvertising(
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
                    _context.gameServices().NearbyConnections.AcceptConnectionRequest(
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
                    _context.gameServices().NearbyConnections.SendUnreliableMessage(
                        remote_endpoint_id, payload);
                    //reject connection
                    // _context.gameServices().NearbyConnections.RejectConnectionRequest(remote_endpoint_id);
                    self._text.setString('receive connect request');
                });
        });
        this._mi_stop_advertising = new cc.MenuItemFont("StopAdvertising", function() {
            self._mi_start_advertising.setVisible(true);
            self._mi_stop_advertising.setVisible(false);
            self._mi_start_discovery.setVisible(true);
            _context.gameServices().NearbyConnections.StopAdvertising();
        });
        this._mi_start_discovery = new cc.MenuItemFont("StartDiscovery", function() {
            const server_id = 'com.sdkbox.hugo.test.gpg.nearby';
            self._mi_start_advertising.setVisible(false);
            self._mi_start_discovery.setVisible(false);
            self._mi_stop_discovery.setVisible(true);
            _context.gameServices().NearbyConnections.StartDiscovery(server_id, 0,
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
                        _context.gameServices().NearbyConnections.SendConnectionRequest(
                            name, remote_endpoint_id, payload,
                            function(result) {
                                //connect_response_callback
                                if (1 == result.response.status) {
                                    __log('Connect advertising success');
                                    const remote_endpoint_id = result.response.remote_endpoint_id;
                                    const payload = self._msg_discovery;
                                    _context.gameServices().NearbyConnections.SendUnreliableMessage(
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
            _context.gameServices().NearbyConnections.StopDiscovery(server_id);
        });
        this._mi_send_reliable_message = new cc.MenuItemFont("SendReliableMessage", function() {
            const remote_endpoint_id = '';
            const payload = 'this message';
            _context.gameServices().NearbyConnections.SendReliableMessage(
                remote_endpoint_id, payload);
        });
        this._mi_send_unreliable_message = new cc.MenuItemFont("SendUnreliableMessage", function() {
            const remote_endpoint_id = '';
            const payload = 'this is unreliable message';
            _context.gameServices().NearbyConnections.SendUnreliableMessage(
                remote_endpoint_id, payload);
        });
        this._mi_disconnect = new cc.MenuItemFont("Disconnect", function() {
            const remote_endpoint_id = '';
            _context.gameServices().NearbyConnections.Disconnect(remote_endpoint_id);
        });
        this._mi_stop = new cc.MenuItemFont("Stop", function() {
            _context.gameServices().NearbyConnections.Stop();
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
        if (!_context.gameServices().NearbyConnections.Init("{\"LogLevel\":1}", function(result) {
                __log("GPG InitializationStatus:" + result.InitializationStatus);
                if (result.InitializationStatus) {
                    self._mi_start_advertising.setVisible(true);
                    self._mi_start_discovery.setVisible(true);
                    const deviceId = _context.gameServices().NearbyConnections.GetLocalDeviceId();
                    const endpointId = _context.gameServices().NearbyConnections.GetLocalEndpointId();
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
    }
});

var S_NearbyConnection = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerNearbyConnection());

    }
});
