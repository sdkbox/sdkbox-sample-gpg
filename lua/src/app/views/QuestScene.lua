
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
        gpg.Quests:ShowAllUI(function(o)
            --dump(o)
        end)
    end)

    self._fetch_list_button = cc.MenuItemFont:create("Fetch List"):onClicked(function()
        gpg.Quests:FetchList(function(o)
            if o.status == 1 then
                q = o.data[1]
                self._quest_id = q.Id
                print("Setting quest id to " .. q.Id)
                self._milestone_id = q.CurrentMilestone.Id
                print("Setting milestone id to " .. self._milestone_id)
            end
            --dump(o)
        end)
    end)

    self._quest_id = nil
    self._fetch_button = cc.MenuItemFont:create("Fetch"):onClicked(function()
        gpg.Quests:Fetch(self._quest_id, function(o)
            dump(o)
        end)
    end)

    self._increment_button = cc.MenuItemFont:create("Increment"):onClicked(function()
        gpg.Events:Increment("CgkI6KjppNEWEAIQDA")
    end)

    self._milestone_id = nil
    self._claim_milestone_button = cc.MenuItemFont:create("Claim Milestone"):onClicked(function()
        gpg.Quests:ClaimMilestone(self._milestone_id, function(o)
            dump(o)
        end)
    end)

    local menu = cc.Menu:create(
        self._sign_in_button,
        self._show_all_ui_button,
        self._fetch_list_button,
        self._fetch_button,
        self._increment_button,
        self._claim_milestone_button
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
        self._fetch_list_button:setVisible(true)
        self._fetch_button:setVisible(true)
        self._increment_button:setVisible(true)
        self._claim_milestone_button:setVisible(true)
    else
        self._sign_in_button:setString("Sign In")
        self._show_all_ui_button:setVisible(false)
        self._fetch_list_button:setVisible(false)
        self._fetch_button:setVisible(false)
        self._increment_button:setVisible(false)
        self._claim_milestone_button:setVisible(false)
    end
end

return QuestScene
