
if not json then
    require "cocos.cocos2d.json"
end
local gpg = require "app.views.sdkboxgpg"

local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()

    print("Sample Startup")

    self._signed_in = false

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

    gpg.CallbackManager:addCallbackById(gpg.DefaultCallbacks.AUTH_ACTION_STARTED,  self.onAuthStart)
    gpg.CallbackManager:addCallbackById(gpg.DefaultCallbacks.AUTH_ACTION_FINISHED, self.onAuthFinished)

end

function MainScene:setupTestMenu()
    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    -- init plugin

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("Sign In"):onClicked(function()
            if not self._signed_in then
                self._signed_in = true
                print("signing in")

                local config = {ClientID="777734739048-cdkbeieil19d6pfkavddrri5o19gk4ni.apps.googleusercontent.com"}
                local s = json.encode(config)
                print(s)
                sdkbox.PluginSdkboxGooglePlay:CreateGameServices(s)

                sdkbox.PluginSdkboxGooglePlay:StartAuthorizationUI()
            end
        end),
        cc.MenuItemFont:create("Sign Out"):onClicked(function()
            if self._signed_in then
                self._signed_in = false
                print("signing out")
            end
        end)
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)
end

function MainScene:onAuthStart(obj)
    print("onAuthStart")
end

function MainScene:onAuthFinished(obj)
    print("onAuthFinished")
end

return MainScene
