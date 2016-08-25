
local gpg = require "app.views.sdkboxgpg"

local QuestScene = class("QuestScene", cc.load("mvc").ViewBase)

function QuestScene:onCreate()

    self._signed_in = false

    local label = cc.Label:createWithSystemFont("Back", "sans", 32)
    local back = cc.MenuItemLabel:create(label)
    back:onClicked(function()
        app:enterScene('MainScene')
    end)

    local size = label:getContentSize()
    local menu = cc.Menu:create(back)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    self:setupTestMenu()

    gpg.CallbackManager:addCallbackById(gpg.DefaultCallbacks.AUTH_ACTION_STARTED,  {self, QuestScene.onAuthStart})
    gpg.CallbackManager:addCallbackById(gpg.DefaultCallbacks.AUTH_ACTION_FINISHED, {self, QuestScene.onAuthFinished})

    local config = {ClientID="777734739048-cdkbeieil19d6pfkavddrri5o19gk4ni.apps.googleusercontent.com"}
    gpg:CreateGameServices(config)

end

function QuestScene:setupTestMenu()

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    self._signed_in = false

    self._sign_in_button = cc.MenuItemFont:create("Sign In"):onClicked(function()
        if not self._signed_in then
            gpg:StartAuthorizationUI()
        else
            gpg:SignOut()
            self._signed_in = false
        end
        self:updateSignIn(self._signed_in)
    end)

    self._show_all_ui_button = cc.MenuItemFont:create("Show All UI"):onClicked(function()
        gpg.Quests:ShowAllUI(function(q)
                dump(q)
            end)
    end)

    local menu = cc.Menu:create(
        self._sign_in_button,
        self._show_all_ui_button
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)
end

function QuestScene:onAuthStart(obj)
end

function QuestScene:onAuthFinished(obj)
    if obj.AuthStatus == 1 then
        self._signed_in = true
    end
    self:updateSignIn(self._signed_in)
end

function QuestScene:updateSignIn(show)
    if show then
        self._sign_in_button:setString("Sign Out")
        self._show_all_ui_button:setVisible(true)
    else
        self._sign_in_button:setString("Sign In")
        self._show_all_ui_button:setVisible(false)
    end
end

return QuestScene
