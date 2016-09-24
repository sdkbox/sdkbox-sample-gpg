
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

    self._listener =
    {
        onRoomStatusChanged = {self, function(room)
            self._text_listener:setString("room status changed. " .. room.status)
        end},

        onConnectedSetChanged = {self, function(room)
            self._text_listener:setString("room connected set changed.")
        end},

        onP2PConnected = {self, function(room, participant)
            self._text_listener:setString("room p2p connected: " .. participant.displayName)
        end},

        onP2PDisconnected = {self, function(room, participant)
            self._text_listener:setString("room p2p disconnected: " .. participant.displayName)
        end},

        onParticipantStatusChanged = {self, function(room, participant)
            self._text_listener:setString("room participant status changed: " .. participant.displayName .. " st:" .. participant.status)
        end},

        onDataReceived = {self, function(room, from_participant, data, is_reliable)
            self._text_listener:setString("data from:" .. from_participant.displayName .. " reliable:" .. is_reliable .. " len:" .. data.length)
            self._text_listener_data:setString("'" .. data .. "'")
        end},
    }

    self:setupTestMenu()

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

    --self._global_label = self._text_listener

    function messageIndex()
        local index = self._message_index
        self._message_index = self._message_index + 1
        return index
    end

    function chooseParticipant()
        for i = 1, #self._room.participants do
            if self._room.participants[i].id ~= self._room.creatingParticipant.id then
                return self._room.participants[i].id
            end
        end
        return nil
    end

    self._mi_message_reliable = cc.MenuItemFont:create("message reliable", function()
        gpg.Realtime.SendReliableMessage(self._room.id, chooseParticipant(), "message " .. messageIndex(), function(result)
            self._text:setString("send reliable message success: " .. result)
        end)
    end)

    self._mi_message_unreliable = cc.MenuItemFont:create("message unreliable", function() {
        gpg.Realtime.SendUnreliableMessage(
            {
                data :              "message " + me._message_index++,
                room_id :           me._room.id,
                participant_ids :   me._room.participants.filter( function( p ) {
                                        return p.id!==me._room.creatingParticipant.id
                                    }).map( function( p ) {
                                        return p.id
                                    })
            }
        )
    })

    self._mi_message_unreliable_to_others = cc.MenuItemFont:create("message unreliable to others", function() {
        gpg.Realtime.SendUnreliableMessageToOthers(
            {
                data :              "message " + me._message_index++,
                room_id :           me._room.id
            }
        )
    })


    self._mi_leaveroom = cc.MenuItemFont:create("Leave room", function() {

        gpg.Realtime.LeaveRoom(
            function (res) {
                if (gpg.IsSuccess(res)) {
                    me._text.setString("Room left.")
                    me._text_listener.setString("")
                    me._room = null
                    me._mi_leaveroom.setVisible(false)
                    me._mi_message_reliable.setVisible(false)
                    me._mi_message_unreliable.setVisible(false)
                    me._mi_message_unreliable_to_others.setVisible(false)
                } else {
                    me._text.setString("Room left error: " + res)
                }
            }
        )
    })

    self._mi_accept_invitation = cc.MenuItemFont:create("Accept invitation", function() {

        if ( me._invitation ) {
            gpg.Realtime.AcceptInvitation(
                {
                    invitation_id :  me._invitation.id,
                    listener : listener
                },
                function (res) {
                    if (gpg.IsSuccess(res.result)) {
                        me._text.setString("accepted invitation. Start game, room: " + res.room.id.substring(0, 10) + "...")
                        me._mi_leaveroom.setVisible(true)
                        me._mi_message_reliable.setVisible(true)
                        me._mi_message_unreliable.setVisible(true)
                        me._mi_message_unreliable_to_others.setVisible(true)


                        me._mi_accept_invitation.setVisible( false )
                        me._mi_dismiss_invitation.setVisible( false )
                        me._mi_decline_invitation.setVisible( false )

                        me._room = res.room
                    } else {
                        me._text.setString("Accept invitation error: " + res.result)
                    }
                }
            )
        } else {
            __log("can't find a local invitation.")
        }
    })

    self._mi_decline_invitation = cc.MenuItemFont:create("Decline invitation", function() {
        gpg.Realtime.DeclineInvitation(me._invitation.id)
    })

    self._mi_dismiss_invitation = cc.MenuItemFont:create("Dismiss invitation", function() {
        gpg.Realtime.DismissInvitation(me._invitation.id)
    })

    self._mi_leaveroom.setVisible( false )
    self._mi_accept_invitation.setVisible( false )
    self._mi_dismiss_invitation.setVisible( false )
    self._mi_decline_invitation.setVisible( false )

    self._mi_message_reliable.setVisible( false )
    self._mi_message_unreliable.setVisible( false )
    self._mi_message_unreliable_to_others.setVisible( false )

    var menu = new cc.Menu(

        cc.MenuItemFont:create("CreateRoom automatch", function() {
            gpg.Realtime.CreateRealTimeRoom(
                {
                    type : "quick_match",
                    quick_match_params : {
                        maximumAutomatchingPlayers : 1,
                        minimumAutomatchingPlayers : 1
                    }
                },
                listener,
                /**
                 *
                 * @param res {RTCreateRoomCallbackParams}
                 */
                function( res ) {

                    if ( gpg.IsSuccess(res.result) ) {
                        me._text.setString("Room created: id="+res.room.id+" participants="+res.room.participants.length)
                        me._room= res.room
                        me._mi_leaveroom.setVisible(true)
                        me._mi_message_reliable.setVisible(true)
                        me._mi_message_unreliable.setVisible(true)
                        me._mi_message_unreliable_to_others.setVisible(true)

                    } else {
                        me._text.setString("RT create room automatch error: "+ res.result)
                    }
                }
            )

        }),

        cc.MenuItemFont:create("CreateRoom select", function() {

            gpg.Realtime.CreateRealTimeRoom(
                {
                    type : "ui",
                    ui_params : {
                        maximumPlayers : 1,
                        minimumPlayers : 1
                    }
                },
                listener,
                /**
                 *
                 * @param res {RTCreateRoomCallbackParams}
                 */
                function( res ) {
                    if ( gpg.IsSuccess(res.result) ) {
                        me._text.setString("Room created: id="+res.room.id.substring(0,10)+"... participants="+res.room.participants.length)
                        me._room= res.room
                        me._mi_leaveroom.setVisible(true)
                        me._mi_message_reliable.setVisible(true)
                        me._mi_message_unreliable.setVisible(true)
                        me._mi_message_unreliable_to_others.setVisible(true)

                    } else {
                        me._text.setString("RT create room ui error: "+ res.result)
                    }

                }
            )

        }),

        cc.MenuItemFont:create("Invitations UI", function() {

            gpg.Realtime.ShowRoomInboxUI(
                /**
                 *
                 * @param res {RTShowRoomInboxUICallbackParams}
                 */
                function( res ) {
                    if ( gpg.IsSuccess(res.result) ) {
                        me._text.setString("got invitation: "+ (res.invitation.id.substr(0,10)) +"..." )
                        me._invitation = res.invitation

                        // normally, you'd accept here the invitation.
                        // we're enabling accept/dismiss/decline ui just for sample purposes.
                        me._mi_accept_invitation.setVisible(true)
                        me._mi_dismiss_invitation.setVisible(true)
                        me._mi_decline_invitation.setVisible(true)
                    } else {
                        me._text.setString("RT invitation ui error: "+ res.result)

                        me._mi_accept_invitation.setVisible(false)
                        me._mi_dismiss_invitation.setVisible(false)
                        me._mi_decline_invitation.setVisible(false)
                    }
                }
            )
        }),

        cc.MenuItemFont:create("Fetch invitations", function() {
            gpg.Realtime.FetchInvitations(
                /**
                 *
                 * @param res {RTFetchInvitationsCallbackParams}
                 */
                function( res ) {
                    if ( gpg.IsSuccess(res.result) ) {
                        me._text.setString("fetched " + res.invitations.length + " invitations.")
                    } else {
                        me._text.setString("fetch invitations error: "+ res.result)
                    }
                }
            )
        }),

        me._mi_leaveroom,

        me._mi_accept_invitation,

        me._mi_dismiss_invitation,

        me._mi_decline_invitation,

        me._mi_message_reliable,

        me._mi_message_unreliable,

        me._mi_message_unreliable_to_others,

        cc.MenuItemFont:create("Main menu", function () {
            cc.director.runScene( new HelloWorldScene() )
        })
    )

    menu.alignItemsVerticallyWithPadding(3)
    menu.x = size.width / 2
    menu.y = size.height / 2 + 40
    self.addChild(menu)



    
end

return RealTimeMultiplayerScene
