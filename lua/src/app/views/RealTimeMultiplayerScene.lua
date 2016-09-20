
local log = require "app.views.log"
if not json then
    require "cocos.cocos2d.json"
end

local RealTimeMultiplayerScene = class("RealTimeMultiplayerScene", cc.load("mvc").ViewBase)

function RealTimeMultiplayerScene:onCreate()

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

    --self:setupTestMenu()

end

return RealTimeMultiplayerScene
