
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

    self:setupTestMenu()

end

function TurnBasedMultiplayerScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("Create TB Game Auto"):onClicked(function()
            params = {
                type = "quick_match",
                minimumAutomatchingPlayers = 2,
                maximumAutomatchingPlayers = 2
            }
            gpg.Turnbased:CreateTurnBasedMatch(params, function(o)
                log:d(log:to_str(o))
            end)
        end)
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)
end

function TurnBasedMultiplayerScene:setupGame()
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