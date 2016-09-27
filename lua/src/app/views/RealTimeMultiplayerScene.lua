local log = require "app.views.log"
if not json then
    require "cocos.cocos2d.json"
end

local RealTimeMultiplayerScene = class("RealTimeMultiplayerScene", cc.load("mvc").ViewBase)

function RealTimeMultiplayerScene:onCreate()

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

    self._text = nil
    self._text_listener = nil
    self._text_listener_data = nil

    self._room = nil

    self._invitation = nil

    self._mi_accept_invitation = nil
    self._mi_dismiss_invitation = nil
    self._mi_decline_invitation = nil

    self._mi_message_reliable = nil
    self._mi_message_unreliable = nil
    self._mi_message_unreliable_to_others = nil

    self._mi_leaveroom = nil

    self._message_index = 0

    self._listener = {
        onRoomStatusChanged        = {self, RealTimeMultiplayerScene.onRoomStatusChanged},
        onConnectedSetChanged      = {self, RealTimeMultiplayerScene.onConnectedSetChanged},
        onP2PConnected             = {self, RealTimeMultiplayerScene.onP2PConnected},
        onP2PDisconnected          = {self, RealTimeMultiplayerScene.onP2PDisconnected},
        onParticipantStatusChanged = {self, RealTimeMultiplayerScene.onParticipantStatusChanged},
        onDataReceived             = {self, RealTimeMultiplayerScene.onDataReceived}
    }

    self:setupTestMenu()

end

function RealTimeMultiplayerScene:onRoomStatusChanged(room)
    self._text_listener:setString("room status changed. " .. room.status)
end

function RealTimeMultiplayerScene:onConnectedSetChanged(room)
    self._text_listener:setString("room connected set changed.")
end

function RealTimeMultiplayerScene:onP2PConnected(room, participant)
    self._text_listener:setString("room p2p connected: " .. participant.displayName)
end

function RealTimeMultiplayerScene:onP2PDisconnected(room, participant)
    self._text_listener:setString("room p2p disconnected: " .. participant.displayName)
end

function RealTimeMultiplayerScene:onParticipantStatusChanged(room, participant)
    self._text_listener:setString("room participant status changed: " .. participant.displayName .. " st:" .. participant.status)
end

function RealTimeMultiplayerScene:onDataReceived(room, from_participant, data, is_reliable)
    self._text_listener:setString("data from:" .. from_participant.displayName .. " reliable:" .. is_reliable .. " len:" .. data.length)
    self._text_listener_data:setString("'" .. data .. "'")
end

function RealTimeMultiplayerScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")

    local size = cc.Director:getInstance():getWinSize()
    local halfwidth = cc.Director:getInstance():getWinSize().width / 2

    self._text = cc.LabelTTF:create("", "sans", 24)
    self._text.x = halfwidth
    self._text.y = 120
    self:addChild(self._text)

    self._text_listener = cc.LabelTTF:create("", "sans", 24)
    self._text_listener.x = halfwidth
    self._text_listener.y = 95
    self:addChild(self._text_listener)

    self._text_listener_data = cc.LabelTTF:create("", "sans", 18)
    self._text_listener_data.x = halfwidth
    self._text_listener_data.y = 75
    self:addChild(self._text_listener_data)

    local function messageIndex()
        local index = self._message_index
        self._message_index = self._message_index + 1
        return index
    end

    local function chooseParticipant()
        for i = 1, #self._room.participants do
            if self._room.participants[i].id ~= self._room.creatingParticipant.id then
                return self._room.participants[i].id
            end
        end
        return nil
    end

    self._mi_message_reliable = cc.MenuItemFont:create("message reliable"):onClicked(function()
        gpg.Realtime:SendReliableMessage(self._room.id, chooseParticipant(), "message " .. messageIndex(), function(result)
            log:d(log:to_str(result))
        end)
    end)

    self._mi_message_unreliable = cc.MenuItemFont:create("message unreliable"):onClicked(function()
        msg = "message " .. messageIndex()
        print("MESSAGE "..msg)
        gpg.Realtime:SendUnreliableMessage({
            data = msg,
            room_id = self._room.id,
            participant_ids = chooseParticipant()
        })
    end)

    self._mi_message_unreliable_to_others = cc.MenuItemFont:create("message unreliable to others"):onClicked(function()
        msg = "message " .. messageIndex()
        print("MESSAGE "..msg)
        gpg.Realtime:SendUnreliableMessageToOthers(self._room.id, {
            data = msg,
            room_id = self._room.id
        })
    end)

    self._mi_leaveroom = cc.MenuItemFont:create("Leave room"):onClicked(function()
        gpg.Realtime:LeaveRoom(self._room.id, {self, RealTimeMultiplayerScene.handleLeaveRoom})
    end)

    self._mi_accept_invitation = cc.MenuItemFont:create("Accept invitation"):onClicked(function()

        if (self._invitation) then
            gpg.Realtime:AcceptInvitation(invitation_id, self._listener, {self, RealTimeMultiplayerScene.handleAcceptInvitation})
        else
            log:d("can't find a local invitation.")
        end
    end)

    self._mi_decline_invitation = cc.MenuItemFont:create("Decline invitation"):onClicked(function()
        gpg.Realtime:DeclineInvitation(self._invitation.id)
    end)

    self._mi_dismiss_invitation = cc.MenuItemFont:create("Dismiss invitation"):onClicked(function()
        gpg.Realtime:DismissInvitation(self._invitation.id)
    end)

    self._mi_leaveroom:setVisible(false)
    self._mi_accept_invitation:setVisible(false)
    self._mi_dismiss_invitation:setVisible(false)
    self._mi_decline_invitation:setVisible(false)
    self._mi_message_reliable:setVisible(false)
    self._mi_message_unreliable:setVisible(false)
    self._mi_message_unreliable_to_others:setVisible(false)
    
    local menu = cc.Menu:create(cc.MenuItemFont:create("CreateRoom automatch"):onClicked(function()
        gpg.Realtime:CreateRealTimeRoom({
            type = "quick_match",
            quick_match_params = {
                maximumAutomatchingPlayers = 1,
                minimumAutomatchingPlayers = 1
            }
        },
        self._listener, {self, RealTimeMultiplayerScene.handleCreateRoom})
    end),

    cc.MenuItemFont:create("CreateRoom select"):onClicked(function()

        gpg.Realtime:CreateRealTimeRoom({
            type = "ui",
            ui_params = {
                maximumPlayers = 1,
                minimumPlayers = 1
            }
        },
        self.listener, {self, RealTimeMultiplayerScene.handleCreateRoomSelect})
    end),

    cc.MenuItemFont:create("Invitations UI"):onClicked(function()
        gpg.Realtime:ShowRoomInboxUI({self, RealTimeMultiplayerScene.handleInvitationsUI})
    end),

    cc.MenuItemFont:create("Fetch invitations"):onClicked(function()
        gpg.Realtime:FetchInvitations({self, RealTimeMultiplayerScene.handleFetchInvitations})
    end),

    self._mi_leaveroom,
    self._mi_accept_invitation,
    self._mi_dismiss_invitation,
    self._mi_decline_invitation,
    self._mi_message_reliable,
    self._mi_message_unreliable,
    self._mi_message_unreliable_to_others)

    menu:alignItemsVerticallyWithPadding(3)
    menu.x = size.width / 2
    menu.y = size.height / 2 + 40
    self:addChild(menu)
end

function RealTimeMultiplayerScene:handleCreateRoom(res)
    if (gpg:IsSuccess(res.result)) then
        --self._text:setString("Room created: id=" .. res.room.id .. " participants=" .. res.room.participants.length)
        self._room = res.room
        self._mi_leaveroom:setVisible(true)
        self._mi_message_reliable:setVisible(true)
        self._mi_message_unreliable:setVisible(true)
        self._mi_message_unreliable_to_others:setVisible(true)
    else
        self._text:setString("RT create room automatch error: " .. res.result)
    end
end

function RealTimeMultiplayerScene:handleCreateRoomSelect(res)
    if (gpg:IsSuccess(res.result)) then
        --self._text:setString("Room created: id=" .. res.room.id.substring(0, 10) .. "... participants=" .. res.room.participants.length)
        self._room = res.room
        self._mi_leaveroom:setVisible(true)
        self._mi_message_reliable:setVisible(true)
        self._mi_message_unreliable:setVisible(true)
        self._mi_message_unreliable_to_others:setVisible(true)
    else
        self._text:setString("RT create room ui error: " .. res.result)
    end
end

function RealTimeMultiplayerScene:handleFetchInvitations(res)
    if (gpg:IsSuccess(res.result)) then
        self._text:setString("fetched " .. res.invitations.length .. " invitations.")
    else
        self._text:setString("fetch invitations error: " .. res.result)
    end
end

function RealTimeMultiplayerScene:handleInvitationsUI(res)
    if (gpg:IsSuccess(res.result)) then
        self._text:setString("got invitation: " .. (res.invitation.id.substr(0, 10)) .. "...")
        self._invitation = res.invitation
        self._mi_accept_invitation:setVisible(true)
        self._mi_dismiss_invitation:setVisible(true)
        self._mi_decline_invitation:setVisible(true)
    else
        self._text:setString("RT invitation ui error: " .. res.result)
        self._mi_accept_invitation:setVisible(false)
        self._mi_dismiss_invitation:setVisible(false)
        self._mi_decline_invitation:setVisible(false)
    end
end

function RealTimeMultiplayerScene:handleLeaveRoom(res)
    if (gpg:IsSuccess(res)) then
        self._text:setString("Room left.")
        self._text_listener:setString("")
        self._room = null
        self._mi_leaveroom:setVisible(false)
        self._mi_message_reliable:setVisible(false)
        self._mi_message_unreliable:setVisible(false)
        self._mi_message_unreliable_to_others:setVisible(false)
    else
        self._text:setString("Room left error: " .. res)
    end
end

function RealTimeMultiplayerScene:handleAcceptInvitation(res)
    if (gpg:IsSuccess(res.result)) then
        self._text:setString("accepted invitation. Start game, room: " .. res.room.id)
        self._mi_leaveroom:setVisible(true)
        self._mi_message_reliable:setVisible(true)
        self._mi_message_unreliable:setVisible(true)
        self._mi_message_unreliable_to_others:setVisible(true)
        self._mi_accept_invitation:setVisible(false)
        self._mi_dismiss_invitation:setVisible(false)
        self._mi_decline_invitation:setVisible(false)
        self._room = res.room
    else
        self._text:setString("Accept invitation error: " .. res.result)
    end
end

return RealTimeMultiplayerScene
