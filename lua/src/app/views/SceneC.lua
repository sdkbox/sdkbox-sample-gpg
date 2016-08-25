local SceneC = class("SceneC", cc.load("mvc").ViewBase)

function SceneC:onCreate()
    self:setupTestMenu()
end

function SceneC:setupTestMenu()
    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("GoToSceneA"):onClicked(function()
            print('GoToSceneA clicked')
            app:enterScene('MainScene')
        end)
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)
end

return SceneC
