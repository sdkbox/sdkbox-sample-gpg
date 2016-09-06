
local log = require "app.views.log"
if not json then
    require "cocos.cocos2d.json"
end

local PlayerStatsScene = class("PlayerStatsScene", cc.load("mvc").ViewBase)

function PlayerStatsScene:onCreate()

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

function PlayerStatsScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()
    
    local menu = cc.Menu:create(

        cc.MenuItemFont:create("Fetch For Player"):onClicked(function()
            log:d("Fetching player stats")
            gpg.Stats:FetchForPlayer(function(o)
                d = o.data

                if d.hasAverageSessionLength then
                    log:d("averageSessionLength " .. d.averageSessionLength)
                end

                if d.hasChurnProbability then
                    log:d("churnProbability " .. d.churnProbability)
                end

                if d.hasDaysSinceLastPlayed then
                    log:d("daysSinceLastPlayed " .. d.daysSinceLastPlayed)
                end

                if d.hasNumberOfPurchases then
                    log:d("numberOfPurchases " .. d.numberOfPurchases)
                end

                if d.hasNumberOfSessions then
                    log:d("numberOfSessions " .. d.numberOfSessions)
                end

                if d.hasSessionPercentile then
                    log:d("sessionPercentile " .. d.sessionPercentile)
                end

                if d.hasSpendPercentile then
                    log:d("spendPercentile " .. d.spendPercentile)
                end

            end)
        end)

    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)

end

return PlayerStatsScene
