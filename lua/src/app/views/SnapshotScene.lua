
local log = require "app.views.log"
if not json then
    require "cocos.cocos2d.json"
end

local SnapshotScene = class("SnapshotScene", cc.load("mvc").ViewBase)

function SnapshotScene:onCreate()

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

function SnapshotScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()
    
    local menu = cc.Menu:create(

        cc.MenuItemFont:create("Show Snapshot UI"):onClicked(function()
            gpg.Snapshots:ShowSelectUIOperation(true, true, 8, 'Title for snapshot', function(o)
                log:d(log:to_str(o))

                if o.result == 'load' then
                    gpg.Snapshots:Load(gpg.SnapshotConflictPolicy.DefaultConflictPolicy, result.metadata.filename,
                        function(result)
                            log:d(log:to_str(result))
                        end)

                elseif o.result == 'create' then
                    data = json.encode({
                        a = 7,
                        b = 'abcd',
                        c = {
                            d = '123'
                        }
                    })
                    log:d("saving "..data)
                    gpg.Snapshots:Save('testing', 'a more valued saved game', gpg.SnapshotConflictPolicy.DefaultConflictPolicy, data)
                end

            end)
        end),

        cc.MenuItemFont:create("Fetch All Games"):onClicked(function()
            gpg.Snapshots:FetchAll(gpg.DataSource.CACHE_OR_NETWORK, function(o)
                log:d(log:to_str(o))
            end)
        end),

        cc.MenuItemFont:create("Delete Snapshot"):onClicked(function()
            gpg.Snapshots:Delete('testing', function(o)
                log:d(log:to_str(o))
            end)
        end)

    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)

end

return SnapshotScene
