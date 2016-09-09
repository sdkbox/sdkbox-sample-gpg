
if not json then
    require "cocos.cocos2d.json"
end
if not gpg then
    gpg = require "app.views.sdkboxgpg"
end
local log = require "app.views.log"

local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()

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

    log:setup(self, 300, 18)

    local config = {ClientID="777734739048-cdkbeieil19d6pfkavddrri5o19gk4ni.apps.googleusercontent.com"}
    gpg:CreateGameServices(config, nil, {self, MainScene.onAuthFinished})

end

function MainScene:setupTestMenu()

    self._signed_in = false

    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    self._sign_in_button = cc.MenuItemFont:create("Sign In"):onClicked(function()
        if not self._signed_in then
            gpg:StartAuthorizationUI()
        else
            gpg:SignOut()
            self._signed_in = false
        end
        self:updateSignIn(self._signed_in)
    end)
    
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
        self._sign_in_button,
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

function MainScene:onAuthFinished(obj)
    if obj.AuthStatus == 1 then
        self._signed_in = true
    end
    self:updateSignIn(self._signed_in)
end

function MainScene:updateSignIn(show)
    if show then
        self._sign_in_button:setString("Sign Out")
    else
        self._sign_in_button:setString("Sign In")
    end
    self._snapshots:setVisible(show)
    self._quests:setVisible(show)
    self._achievements:setVisible(show)
    self._leaderboards:setVisible(show)
    self._playerstats:setVisible(show)
end

return MainScene
