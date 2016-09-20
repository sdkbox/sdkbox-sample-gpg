
local log = require "app.views.log"
if not json then
    require "cocos.cocos2d.json"
end

local TurnBasedMultiplayerScene = class("TurnBasedMultiplayerScene", cc.load("mvc").ViewBase)

function TurnBasedMultiplayerScene:onCreate()

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

    gpg.Turnbased:addMatchEventCallback(gpg.DefaultCallbacks.TURN_BASED_MATCH_EVENT, {self, handleMatchEvent})
    self:setupTestMenu()

end

function TurnBasedMultiplayerScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")

    self._match = nil
    self._menus = {}

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("Show Match Inbox UI"):onClicked(function()
            gpg.Turnbased:ShowMatchInboxUI(function(o)
                if gpg:IsSuccess(o.result) then
                    self:handleShowMatchInbox(o.match)
                end
            end)
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
    log:d(log:to_str(o))
end

function TurnBasedMultiplayerScene:handleShowMatchInbox(match)
    log:d("TurnBasedMultiplayerScene:handleShowMatchInbox")
    log:d(log:to_str(match))
    if match.matchStatus == gpg.MatchStatus.MY_TURN then
        self:playMatch(match)
    elseif match.matchStatus == gpg.MatchStatus.THEIR_TURN then
        self:manageMatch(match, true, true, false)
    elseif match.matchStatus == gpg.MatchStatus.COMPLETED then
        self:manageMatch(match, false, false, true)
    elseif match.matchStatus == gpg.MatchStatus.EXPIRED then
        self:manageMatch(match, false, false, false)
    else
        log:d("Unhandled status "..match.matchStatus)
    end
end

function TurnBasedMultiplayerScene:playMatch(match)
    log:d("TurnBasedMultiplayerScene:playMatch")
    self._match = match
    log:d(log:to_str(match))

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("Win"):onClicked(function()
            self:popMenu()
        end),
        cc.MenuItemFont:create("Lose"):onClicked(function()
            self:popMenu()
        end),
        cc.MenuItemFont:create("Leave"):onClicked(function()
            self:leaveMatch()
            self:popMenu()
        end)
    )

    self:pushMenu(menu)
end

function TurnBasedMultiplayerScene:manageMatch(match, leave, cancel, rematch)
    log:d("TurnBasedMultiplayerScene:manageMatch")
    self._match = match
    log:d(log:to_str(match))

    if not (leave and cancel and rematch) then
        log:d("Nothing to manage")
        return
    end

    local menu = cc.Menu:create()

    if (leave) then
        menu:addChild(cc.MenuItemFont:create("Leave"):onClicked(function()
            self:leaveMatch()
            self:popMenu()
        end))
    end

    if (cancel) then
        menu:addChild(cc.MenuItemFont:create("Cancel"):onClicked(function()
            self:cancelMatch()
            self:popMenu()
        end))
    end

    if (rematch) then
        menu:addChild(cc.MenuItemFont:create("Rematch"):onClicked(function()
            self:rematch()
            self:popMenu()
        end))
    end

    self:pushMenu(menu)
end

function TurnBasedMultiplayerScene:leaveMatch()
    match = self._match
    if match.matchStatus == gpg.MatchStatus.MY_TURN then
        gpg.Turnbased:LeaveMatchDuringMyTurn(match.id, match.suggestedNextParticipant.id, function(o)
            log:d(log:to_str(o))
        end)
    else
        gpg.Turnbased:LeaveMatchDuringTheirTurn(match.id, function(o)
            log:d(log:to_str(o))
        end)
    end
end

function TurnBasedMultiplayerScene:cancelMatch()
    gpg.Turnbased:CancelMatch(self._match, function(o)
        log:d(log:to_str(o))
    end)
end

function TurnBasedMultiplayerScene:rematch()
    gpg.Turnbased:Rematch(self._match, function(o)
        if gpg:IsSuccess(o.result) then
            self:playMatch(o.match)
        end
    end)
end

return TurnBasedMultiplayerScene


