local SceneB = class("SceneB", cc.load("mvc").ViewBase)

function SceneB:onCreate()
    self:setupTestMenu()
end

function SceneB:setupTestMenu()
    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("GoToSceneC"):onClicked(function()
            print('GoToSceneC clicked')
            app:enterScene('SceneC')
        end)
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)
end

return SceneB
