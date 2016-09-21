
local log = require "app.views.log"
if not json then
    require "cocos.cocos2d.json"
end

local TurnBasedMultiplayerScene = class("TurnBasedMultiplayerScene", cc.load("mvc").ViewBase)

TurnBasedMultiplayerScene.TurnResult = {
    TAKE_TURN = 0,
    WIN = 1,
    LOSE = 2
}

TurnBasedMultiplayerScene.AUTOMATCHING_PARTICIPANT = "AUTOMATCHING_PARTICIPANT"

function TurnBasedMultiplayerScene:onCreate()

    local label = cc.Label:createWithSystemFont("Back", "sans", 32)
    local back = cc.MenuItemLabel:create(label)
    back:onClicked(function()
        if #self._menus > 1 then
            self:popMenu()
        else
            app:enterScene('MainScene')
        end
    end)

    local size = label:getContentSize()
    local menu = cc.Menu:create(back)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    log:setup(self, 300, 20)

    gpg.Turnbased:addMatchEventCallback(gpg.DefaultCallbacks.TURN_BASED_MATCH_EVENT, {self, handleMatchEvent})
    gpg.Turnbased:addMatchEventCallback(gpg.DefaultCallbacks.MULTIPLAYER_INVITATION_EVENT, {self, handleInvitationEvent})

    self:setupTestMenu()

end

function TurnBasedMultiplayerScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")

    self._match = nil
    self._menus = {}

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("Show Match Inbox UI"):onClicked(function()
            self:showMatchInbox()
        end),
        cc.MenuItemFont:create("Quick Match"):onClicked(function()
            params = {
                type = "quick_match",
                minimumAutomatchingPlayers = 1,
                maximumAutomatchingPlayers = 2
            }
            gpg.Turnbased:CreateTurnBasedMatch(params, function(o)
                if gpg:IsSuccess(o.result) then
                    self:playMatch(o.match)
                end
            end)
        end),
        cc.MenuItemFont:create("Choose Players"):onClicked(function()
            gpg.Turnbased:ShowPlayerSelectUI(1, 2, false, function(o)
                log:d(log:to_str(o))
                params = {
                    type = "quick_match",
                    minimumAutomatchingPlayers = o.minimumAutomatchingPlayers,
                    maximumAutomatchingPlayers = o.maximumAutomatchingPlayers,
                    playerIds = o.playerIds
                }
                gpg.Turnbased:CreateTurnBasedMatch(params, function(o)
                    log:d(log:to_str(o))
                    if gpg:IsSuccess(o.result) then
                        self:playMatch(o.match)
                    end
                end)
            end)
        end),
        cc.MenuItemFont:create("Create Match"):onClicked(function()
            params = {
                type = "ui",
                minimumAutomatchingPlayers = 1,
                maximumAutomatchingPlayers = 2
            }
            gpg.Turnbased:CreateTurnBasedMatch(params, function(o)
                log:d(log:to_str(o))
            end)
        end)
    )

    self:pushMenu(menu)
end

function TurnBasedMultiplayerScene:pushMenu(menu)
    local size = cc.Director:getInstance():getWinSize()
    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)

    local count = #self._menus
    if count > 0 then
        local last = self._menus[1]
        self:removeChild(last)
    end

    table.insert(self._menus, 1, menu)
    menu:retain()
    self:addChild(menu)
end

function TurnBasedMultiplayerScene:popMenu()
    local count = #self._menus
    if count > 1 then
        local last = self._menus[1]
        self:removeChild(last)
        table.remove(self._menus, 1)
        last:release()
        last = self._menus[1]
        self:addChild(last)
    end
end

function TurnBasedMultiplayerScene:handleMatchEvent(o)
    log:d("TurnBasedMultiplayerScene:handleMatchEvent")
    self:showMatchInbox(o)
end

function TurnBasedMultiplayerScene:handleInvitationEvent(o)
    log:d("TurnBasedMultiplayerScene:handleInvitationEvent")
    self:showMatchInbox(o)
end

function TurnBasedMultiplayerScene:handleShowMatchInbox(match)
    log:d("TurnBasedMultiplayerScene:handleShowMatchInbox")
    if match.matchStatus == gpg.MatchStatus.MY_TURN then
        self:playMatch(match)
    elseif match.matchStatus == gpg.MatchStatus.THEIR_TURN then
        self:manageMatch(match, true, true, false)
    elseif match.matchStatus == gpg.MatchStatus.COMPLETED then
        self:manageMatch(match, false, false, true)
    elseif match.matchStatus == gpg.MatchStatus.EXPIRED then
        self:manageMatch(match, false, false, false)
    else
        log:d("Unhandled status")
    end
end

function TurnBasedMultiplayerScene:showMatchInbox()
    gpg.Turnbased:ShowMatchInboxUI(function(o)
        if gpg:IsSuccess(o.result) then
            self:handleShowMatchInbox(o.match)
        end
    end)
end

function TurnBasedMultiplayerScene:playMatch(match)
    log:d("TurnBasedMultiplayerScene:playMatch")
    self._match = match
    local menu = nil

    --log:d(log:to_str(match))

    local myId = match.pendingParticipant.id
    local myResults = match.participantResults[myId]
    log:d("myId "..myId)
    log:d(log:to_str(myResults))

    if myResults.hasResultsForParticipant == true and myResults.matchResultForParticipant ~= gpg.MatchResult.NONE then
        local results = {
            [3] = "You Lose",
            [6] = "You Win"
        }
        local result_str = results[myResults.matchResultForParticipant]
        menu = cc.Menu:create(
            cc.MenuItemFont:create(result_str):onClicked(function()
                self:dismissMatch()
                self:popMenu()
            end)
        )
    else
        menu = cc.Menu:create(
            cc.MenuItemFont:create("Win"):onClicked(function()
                self:takeTurn(self.TurnResult.WIN)
                self:popMenu()
            end),
            cc.MenuItemFont:create("Lose"):onClicked(function()
                self:takeTurn(self.TurnResult.LOSE)
                self:popMenu()
            end),
            cc.MenuItemFont:create("Leave"):onClicked(function()
                self:leaveMatch()
                self:popMenu()
            end),
            cc.MenuItemFont:create("Take Turn!"):onClicked(function()
                self:takeTurn(self.TurnResult.TAKE_TURN)
            end)
        )
    end

    self:pushMenu(menu)
end

function TurnBasedMultiplayerScene:takeTurn(result)
    local results = self._match.participantResults
    if result == self.TurnResult.WIN then
        results = gpg.Turnbased:createParticipantResult(self._match.id, self._match.pendingParticipant.id, 0, gpg.MatchResult.WIN)
    elseif result == self.TurnResult.LOSE then
        results = gpg.Turnbased:createParticipantResult(self._match.id, self._match.pendingParticipant.id, 0, gpg.MatchResult.LOSS)
    end
    log:d(log:to_str(results))
    data = json.encode({
        counter = 1
    })
    local nextParticipant = "AUTOMATCHING_PARTICIPANT"
    if self._match.suggestedNextParticipant.valid and self._match.suggestedNextParticipant.id ~= "" then
        nextParticipant = self._match.suggestedNextParticipant.id
    end
    gpg.Turnbased:TakeMyTurn(self._match.id, self._match.pendingParticipant.id, nextParticipant, data, function(o)
        log:d("TakeMyTurn "..log:to_str(o))
    end)
end

function TurnBasedMultiplayerScene:manageMatch(match, leave, cancel, rematch)
    log:d("TurnBasedMultiplayerScene:manageMatch")

    self._match = match

    local menu = cc.Menu:create()

    if leave then
        menu:addChild(cc.MenuItemFont:create("Leave"):onClicked(function()
            self:leaveMatch()
            self:popMenu()
        end))
    end

    if cancel then
        menu:addChild(cc.MenuItemFont:create("Cancel"):onClicked(function()
            self:cancelMatch()
            self:popMenu()
        end))
    end

    if rematch then
        menu:addChild(cc.MenuItemFont:create("Rematch"):onClicked(function()
            self:rematch()
            self:popMenu()
        end))
    end
    
    self:pushMenu(menu)
end

function TurnBasedMultiplayerScene:dismissMatch()
    gpg.Turnbased:DismissMatch(self._match.id)
    self._match = nil
end

function TurnBasedMultiplayerScene:leaveMatch()
    local match = self._match
    if match.matchStatus == gpg.MatchStatus.MY_TURN then
        gpg.Turnbased:LeaveMatchDuringMyTurn(match.id, match.suggestedNextParticipant.id, function(o)
            log:d(log:to_str(o))
        end)
    else
        gpg.Turnbased:LeaveMatchDuringTheirTurn(match.id, function(o)
            log:d(log:to_str(o))
        end)
    end
    self._match = nil
end

function TurnBasedMultiplayerScene:cancelMatch()
    gpg.Turnbased:CancelMatch(self._match.id, function(o)
        log:d(log:to_str(o))
    end)
    self._match = nil
end

function TurnBasedMultiplayerScene:rematch()
    gpg.Turnbased:Rematch(self._match.id, function(o)
        if gpg:IsSuccess(o.result) then
            self:playMatch(o.match)
        end
    end)
end

return TurnBasedMultiplayerScene


