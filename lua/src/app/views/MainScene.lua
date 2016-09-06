
if not json then
    require "cocos.cocos2d.json"
end
local log = require "app.views.log"
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()

    local label = cc.Label:createWithSystemFont("QUIT", "sans", 32)
    local quit = cc.MenuItemLabel:create(label)
    quit:onClicked(function()
        os.exit(0)
    end)

    local size = label:getContentSize()
    local menu = cc.Menu:create(quit)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    self:setupTestMenu()

    log:setup(self, 300, 18)
    
end

function MainScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    self._snapshots = cc.MenuItemFont:create("Snapshots"):onClicked(function()
            app:enterScene('SnapshotScene')
        end)

    self._quests = cc.MenuItemFont:create("Quests"):onClicked(function()
            app:enterScene('QuestScene')
        end)

    self._achievements = cc.MenuItemFont:create("Achievements"):onClicked(function()
            app:enterScene('AchievementsScene')
        end)

    self._leaderboards = cc.MenuItemFont:create("Leaderboards"):onClicked(function()
            app:enterScene('LeaderboardScene')
        end)

    self._playerstats = cc.MenuItemFont:create("Player Stats"):onClicked(function()
            app:enterScene('PlayerStatsScene')
        end)

    local menu = cc.Menu:create(
        self._snapshots,
        self._quests,
        self._achievements,
        self._leaderboards,
        self._playerstats
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)

end

return MainScene
