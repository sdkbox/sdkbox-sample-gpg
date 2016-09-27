
local log = require "app.views.log"

local NearbyConnectionsScene = class("NearbyConnectionsScene", cc.load("mvc").ViewBase)

function NearbyConnectionsScene:onCreate()

    self.server_id = 'com.sdkbox.hugo.test.gpg.nearby'
    self._msg_advertising = 'this is a msg from advertising'
    self._msg_discovery = 'this is a msg from discovery'

    local label = cc.Label:createWithSystemFont("Back", "sans", 32)
    local back = cc.MenuItemLabel:create(label)
    back:onClicked(function()
        app:enterScene('MainScene')
    end)

    local size = label:getContentSize()
    local menu = cc.Menu:create(back)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    log:setup(self, 300, 20)

    self:setupTestMenu()

end

function NearbyConnectionsScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    self._mi_start_advertising = cc.MenuItemFont:create("StartAdvertising"):onClicked(function()
        self._mi_start_advertising:setVisible(false)
        self._mi_stop_advertising:setVisible(true)
        self._mi_start_discovery:setVisible(false)
        gpg.NearbyConnections:StartAdvertising(
            "\"name\":\"\",\"duration\":0,\"app_identifiers\":{\"identifier\":\"com.sdkbox.gpg\"},",
            function(result)
                if (1 == result.start_advertising_result.status) then
                    log:d("GPG start advertising result:" .. result.client_id
                        .. " status:" .. result.start_advertising_result.status
                        .. " local_endpoint_name:" .. result.start_advertising_result.local_endpoint_name)
                else
                    log:d('start advertising failed:' .. result.start_advertising_result.status)
                    self._mi_start_advertising:setVisible(true)
                    self._mi_start_discovery:setVisible(true)
                end
            end,
            function(result)
                --request_callback

                local remote_endpoint_id = result.request.remote_endpoint_id
                local payload = result.request.payload

                log:d('GPG receive connect request:' .. remote_endpoint_id)

                --accept connection
                gpg.NearbyConnections:AcceptConnectionRequest(
                    remote_endpoint_id,
                    payload,
                    function (result)
                        log:d('advertising event:' .. result.event)
                        if 'OnMessageReceived' == result.event then
                            log:d('OnMessageReceived client_id:' .. (result.client_id or '')
                                .. ' remote_endpoint_id:' .. (result.remote_endpoint_id or '')
                                .. ' payload:' .. (result.payload or '')
                                .. ' is_reliable:' .. tostring(result.is_reliable))
                        elseif 'OnDisconnected' == result.event then
                            log:d('OnDisconnected client_id:' .. (result.client_id or '')
                                .. ' remote_endpoint_id:' .. (result.remote_endpoint_id or ''))
                        else
                            log:d('Unknown event:' .. result.event);
                        end
                    end)
                --send message to connector
                payload = self._msg_advertising;
                log:d('Send to:' .. (remote_endpoint_id or '')
                    .. ' msg:' .. (payload or ''))
                gpg.NearbyConnections:SendUnreliableMessage(remote_endpoint_id, payload);
                -- reject connection
                -- gpg.NearbyConnections:RejectConnectionRequest(remote_endpoint_id);
            end)
    end)
    self._mi_stop_advertising = cc.MenuItemFont:create("StopAdvertising"):onClicked(function()
        self._mi_start_advertising:setVisible(true)
        self._mi_stop_advertising:setVisible(false)
        self._mi_start_discovery:setVisible(true)
        gpg.NearbyConnections:StopAdvertising();
    end)
    self._mi_start_discovery = cc.MenuItemFont:create("StartDiscovery"):onClicked(function()
        self._mi_start_advertising:setVisible(false)
        self._mi_start_discovery:setVisible(false)
        self._mi_stop_discovery:setVisible(true)
        gpg.NearbyConnections:StartDiscovery(self.server_id, 0,
            function (result)
                if 'OnEndpointFound' == result.event then
                    log:d('found client_id:' .. (result.client_id or '')
                        .. ' endpoint_id:' .. (result.endpoint_details.endpoint_id or '')
                        .. ' device_id:' .. (result.endpoint_details.device_id or '')
                        .. ' name:' .. (result.endpoint_details.name or '')
                        .. ' service_id:' .. (result.endpoint_details.server_id or '') )
                    local name = ''
                    local remote_endpoint_id = result.endpoint_details.endpoint_id
                    local payload = ''
                    gpg.NearbyConnections:SendConnectionRequest(
                        name, remote_endpoint_id, payload,
                        function(result)
                            -- connect_response_callback
                            if (1 == result.response.status) then
                                log:d('Connect advertising success');
                                local remote_endpoint_id = result.response.remote_endpoint_id;
                                local payload = self._msg_discovery;
                                log:d('Send to:' .. (remote_endpoint_id or '')
                                    .. ' msg:' .. (payload or ''))
                                gpg.NearbyConnections:SendUnreliableMessage(
                                    remote_endpoint_id, payload);
                            else
                                log:d('Connect advertising failed');
                            end
                        end,
                        function(result)
                            if 'OnMessageReceived' == result.event then
                                log:d('OnMessageReceived client_id:' .. (result.client_id or '')
                                    .. ' remote_endpoint_id:' .. (result.remote_endpoint_id or '')
                                    .. ' payload:' .. (result.payload or '')
                                    .. ' is_reliable:' .. tostring(result.is_reliable))
                            elseif 'OnDisconnected' == result.event then
                                log:d('OnDisconnected client_id:' .. (result.client_id or '')
                                    .. ' remote_endpoint_id:' .. (result.remote_endpoint_id or ''))
                            else
                                log:d('Unknown event:' .. result.event);
                            end
                        end)
                elseif 'OnEndpointLost' == result.event then
                    log:d('endpoint lost')
                else
                    log:d('unknown event')
                end
            end)
    end)
    self._mi_stop_discovery = cc.MenuItemFont:create("StopDiscovery"):onClicked(function()
        self._mi_start_advertising:setVisible(true)
        self._mi_start_discovery:setVisible(true)
        self._mi_stop_discovery:setVisible(false)
        gpg.NearbyConnections:StopDiscovery(self.server_id);
    end)
    self._mi_disconnect = cc.MenuItemFont:create("Disconnect"):onClicked(function()
        self._mi_disconnect:setVisible(false)
        local remote_endpoint_id = '' -- TODO need use actual remote endpoint id
        gpg.NearbyConnections:Disconnect(remote_endpoint_id);
    end)
    self._mi_stop = cc.MenuItemFont:create("Stop"):onClicked(function()
        self._mi_stop:setVisible(false)
        gpg.NearbyConnections:Stop();
    end)

    -- init gpg nearby connections
    local support = gpg.NearbyConnections:Init("{\"LogLevel\":1,\"ClientID\":234,\"ServiceID\":\"com.sdkbox.hugo.test.gpg.nearby\"}",
        function(result)
            if (result.InitializationStatus) then
                log:d('GPG Nearby init success')
                self._mi_stop:setVisible(true)
            else
                log:d('GPG Nearby init failed')
                self._mi_stop:setVisible(false)
            end
        end)
    if not support then
        log:d('GPG Nearby is not support ios')
    end

    local menu = cc.Menu:create(
        self._mi_start_advertising,
        self._mi_stop_advertising,
        self._mi_start_discovery,
        self._mi_stop_discovery,
        self._mi_disconnect,
        self._mi_stop
    )

    self._mi_start_advertising:setVisible(true)
    self._mi_stop_advertising:setVisible(false)
    self._mi_start_discovery:setVisible(true)
    self._mi_stop_discovery:setVisible(false)
    self._mi_disconnect:setVisible(false)
    self._mi_stop:setVisible(false)

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)

end

return NearbyConnectionsScene

