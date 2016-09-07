
local log = require "app.views.log"

local LeaderboardScene = class("LeaderboardScene", cc.load("mvc").ViewBase)

function LeaderboardScene:onCreate()

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

function LeaderboardScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()
    
    local menu = cc.Menu:create(

        cc.MenuItemFont:create("Show UI [Best gamers]"):onClicked(function()
            gpg.Leaderboards:ShowUI("CgkI6KjppNEWEAIQAg")
        end),

        cc.MenuItemFont:create("Show All UI"):onClicked(function()
            gpg.Leaderboards:ShowAllUI()
        end),

        cc.MenuItemFont:create("Submit random score to [Fastest lap]"):onClicked(function()
            local score = 10 + math.random() * 290
            gpg.Leaderboards:SubmitScore('CgkI6KjppNEWEAIQAw', score, 'sent from cocos Lua', function(result)
                log:d(log:to_str(result))
            end)
        end),

        cc.MenuItemFont:create("Fetch all score summaries [best gamers]"):onClicked(function()
            gpg.Leaderboards:FetchAllScoreSummaries('CgkI6KjppNEWEAIQAg', nil, function(result)
                log:d(log:to_str(result))
            end)
        end),

        cc.MenuItemFont:create("Fetch All"):onClicked(function()
            gpg.Leaderboards:FetchAll(gpg.DataSource.CACHE_OR_NETWORK, nil, function(result)
                log:d(log:to_str(result))
            end)
        end),

        cc.MenuItemFont:create("Fetch Score Page"):onClicked(function()
            gpg.Leaderboards:FetchScorePage('CgkI6KjppNEWEAIQAg', nil, nil, nil, nil, nil, function(result)
                log:d(log:to_str(result))
            end)
        end),

        cc.MenuItemFont:create("Fetch Next Score Page"):onClicked(function()
            gpg.Leaderboards:FetchNextScorePage(gpg.DataSource.CACHE_OR_NETWORK, 100, function(result)
                log:d(log:to_str(result))
            end)
        end)
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)

end

return LeaderboardScene
