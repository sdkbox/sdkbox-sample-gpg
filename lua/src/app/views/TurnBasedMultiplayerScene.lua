
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

    self._create_menu = cc.Menu:create(
        cc.MenuItemFont:create("Show Match Inbox UI"):onClicked(function()
            gpg.Turnbased:ShowMatchInboxUI(function(o)
                log:d(log:to_str(o))
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

    self._match_menu = cc.Menu:create(
        cc.MenuItemFont:create("Win"):onClicked(function()
            gpg.Turnbased:ShowMatchInboxUI(function(o)
                log:d(log:to_str(o))
            end)
        end),
        cc.MenuItemFont:create("Lose"):onClicked(function()
            gpg.Turnbased:ShowMatchInboxUI(function(o)
                log:d(log:to_str(o))
            end)
        end),
        cc.MenuItemFont:create("Leave"):onClicked(function()
            self:leaveMatch(self._match)
        end)
    )

    self:addMenu(self._create_menu, true)
    self:addMenu(self._match_menu, false)

    self:setupGame()
end

function TurnBasedMultiplayerScene:addMenu(menu, visible)
    local size = cc.Director:getInstance():getWinSize()
    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)
    menu:setVisible(visible)
end

function TurnBasedMultiplayerScene:setupGame()
    self._match = nil
    self._create_menu:setVisible(true)
    self._match_menu:setVisible(false)

end

function TurnBasedMultiplayerScene:handleMatchEvent(o)
    log:d("TurnBasedMultiplayerScene:handleMatchEvent")
    log:d(log:to_str(o))
end

function TurnBasedMultiplayerScene:playMatch(match)
    self._match = match
    self._create_menu:setVisible(false)
    self._match_menu:setVisible(true)
    log:d(log:to_str(match))
end

function TurnBasedMultiplayerScene:leaveMatch(match)
    if match.status == gpg.MatchStatus.MY_TURN then
        gpg.Turnbased:LeaveMatchDuringMyTurn(match.id, match.suggestedNextParticipant.id, function(o)
            log:d(log:to_str(o))
            self:setupGame()
        end)
    else
        gpg.Turnbased:LeaveMatchDuringTheirTurn(match.id, function(o)
            log:d(log:to_str(o))
            self:setupGame()
        end)
    end
end

return TurnBasedMultiplayerScene


--[[

 flow for sample

 setup
 choose players -> create game
 2 accept invitation

 1 take turn
 2 take turn -> finish game -> setup

 ]]
