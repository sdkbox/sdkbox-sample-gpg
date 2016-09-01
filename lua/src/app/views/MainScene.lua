
if not json then
    require "cocos.cocos2d.json"
end

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

end

function MainScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    self._snapshots = cc.MenuItemFont:create("Snapshots"):onClicked(function()
        end)
    self._quests = cc.MenuItemFont:create("Quests"):onClicked(function()
            app:enterScene('QuestScene')
        end)

    local menu = cc.Menu:create(
        self._snapshots,
        self._quests
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)

end

return MainScene
