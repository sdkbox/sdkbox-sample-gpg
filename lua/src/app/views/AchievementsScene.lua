
local log = require "app.views.log"

local AchievementsScene = class("AchievementsScene", cc.load("mvc").ViewBase)

function AchievementsScene:onCreate()

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

function AchievementsScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()
    
    local menu = cc.Menu:create(

        cc.MenuItemFont:create("Show all UI"):onClicked(function()
            gpg.Achievements:ShowAllUI(function(result)
                log:d(log:to_str(result))
            end)
        end),

        cc.MenuItemFont:create("Fetch all achievements"):onClicked(function()
            gpg.Achievements:FetchAll(nil, function(result)
                log:d(log:to_str(result))
            end)
        end),

        cc.MenuItemFont:create("Fetch achievement Incremental"):onClicked(function()
            gpg.Achievements:Fetch('CgkI6KjppNEWEAIQBQ', nil, function(result)
                log:d(log:to_str(result))
            end)
        end),

        cc.MenuItemFont:create("Increment achievement"):onClicked(function()
            gpg.Achievements:Increment('CgkI6KjppNEWEAIQBQ')
        end),

        cc.MenuItemFont:create("Unlock achievement"):onClicked(function()
            gpg.Achievements:Unlock('CgkI6KjppNEWEAIQBQ')
        end),

        cc.MenuItemFont:create("Reveal achievement"):onClicked(function()
            gpg.Achievements:Reveal('CgkI6KjppNEWEAIQBQ')
        end)
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)

end

return AchievementsScene
