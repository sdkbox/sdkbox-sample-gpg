
local log = require "app.views.log"
local gpg = require "app.views.sdkboxgpg"

local QuestScene = class("QuestScene", cc.load("mvc").ViewBase)

function QuestScene:onCreate()

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

function QuestScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    self._show_all_ui_button = cc.MenuItemFont:create("Show All UI"):onClicked(function()
        gpg.Quests:ShowAllUI(function(o)
            log:d(log:to_str(o))
        end)
    end)

    self._fetch_list_button = cc.MenuItemFont:create("Fetch List"):onClicked(function()
        gpg.Quests:FetchList(function(o)
            if o.result == 1 then
                q = o.data[1]
                self._quest_id = q.Id
                print("Setting quest id to " .. q.Id)
                self._milestone_id = q.CurrentMilestone.Id
                log:d("Setting milestone id to " .. self._milestone_id)
            end
            log:d(log:to_str(o))
        end)
    end)

    self._quest_id = nil
    self._fetch_button = cc.MenuItemFont:create("Fetch"):onClicked(function()
        gpg.Quests:Fetch(self._quest_id, function(o)
            log:d(log:to_str(o))
        end)
    end)

    self._increment_button = cc.MenuItemFont:create("Increment"):onClicked(function()
        gpg.Events:Increment("CgkI6KjppNEWEAIQDA")
        log:d("Increment event CgkI6KjppNEWEAIQDA")
    end)

    self._milestone_id = nil
    self._claim_milestone_button = cc.MenuItemFont:create("Claim Milestone"):onClicked(function()
        gpg.Quests:ClaimMilestone(self._milestone_id, function(o)
            log:d(log:to_str(o))
        end)
    end)

    self._fetch_player_stats_button = cc.MenuItemFont:create("Fetch Player Stats"):onClicked(function()
        gpg.Stats:FetchForPlayer(function(o)
            log:d(log:to_str(o))
        end)
    end)

    local menu = cc.Menu:create(
        self._show_all_ui_button,
        self._fetch_list_button,
        self._fetch_button,
        self._increment_button,
        self._claim_milestone_button,
        self._fetch_player_stats_button
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)
end

return QuestScene
