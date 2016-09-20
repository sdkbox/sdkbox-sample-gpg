#include "BaseScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StateManager.h"

USING_NS_CC;

Scene*BaseScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BaseScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BaseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");
    int defaultFontSize = 32;

    _btn_prevScene = ui::Button::create("green_sliderLeft.png");
    _btn_prevScene->setPosition(Point(100, 280));
    _btn_prevScene->setScale(2);
    _btn_prevScene->addClickEventListener(CC_CALLBACK_1(BaseScene::onPrevScene, this));
    addChild(_btn_prevScene);

    _btn_nextScene = ui::Button::create("green_sliderRight.png");
    _btn_nextScene->setPosition(Point(size.width - 50, 280));
    _btn_nextScene->setScale(2);
    _btn_nextScene->addClickEventListener(CC_CALLBACK_1(BaseScene::onNextScene, this));
    addChild(_btn_nextScene);

    _menu_item_connect = MenuItemFont::create("Sign In", CC_CALLBACK_1(BaseScene::onConnect, this));
    
    Menu* menu = Menu::create(
        _menu_item_connect,
        nullptr
    );
    
    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width - 100, size.height -50);
    addChild(menu);

    _txtTitle = Label::create("", defaultFont, defaultFontSize);
    _txtTitle->setPosition(size.width/2, size.height - 50);
    addChild(_txtTitle);

    _txtStat = Label::create("", defaultFont, defaultFontSize);
    _txtStat->setAnchorPoint(Point(0, 0));
    _txtStat->setPosition(Point(200, 30));
    addChild(_txtStat);
    
    _txtConnection = Label::create("", defaultFont, defaultFontSize);
    _txtConnection->setAnchorPoint(cocos2d::Point(0, 0));
    _txtConnection->setPosition(cocos2d::Point(size.width - 200, 65));
    addChild(_txtConnection);
    
    initGPG();
    
    return true;
}

void BaseScene::initGPG()
{
    StateManager::setCallback([this](gpg::AuthOperation op, gpg::AuthStatus st){
        updateConnectionStatus();
    });
    StateManager::Init(*CreatePlatformConfiguration("777734739048-cdkbeieil19d6pfkavddrri5o19gk4ni.apps.googleusercontent.com").get());
    
    _game_services = StateManager::GetGameServices();
    
    if(!StateManager::IsSignedIn())
    {
        StateManager::SignIn();
    }
    else
    {
        updateConnectionStatus();
    }

    //Initialize GPG signin automatically if possible
    //Note this approach only works with single scene senario
//    if(!_game_services)
//    {
//        _game_services = gpg::GameServices::Builder().SetOnAuthActionFinished([](gpg::AuthOperation op, gpg::AuthStatus st){
//            updateConnectionStatus();
//        }).SetDefaultOnLog( gpg::LogLevel::VERBOSE).EnableSnapshots().Create(*CreatePlatformConfiguration("777734739048-cdkbeieil19d6pfkavddrri5o19gk4ni.apps.googleusercontent.com").get());
//    }
//    else if (!_game_services->IsAuthorized())
//    {
//        _game_services->StartAuthorizationUI();
//    }
//    else
//    {
//        updateConnectionStatus();
//    }
}

void BaseScene::onConnect(Ref *sender)
{
    if (!_game_services)
    {
        return;
    }
    
    if (_game_services->IsAuthorized())
    {
        _game_services->SignOut();
    }
    else
    {
        _game_services->StartAuthorizationUI();
    }
    
    updateConnectionStatus();
}

void BaseScene::updateConnectionStatus()
{
    if (_game_services)
    {
        if (_game_services->IsAuthorized())
        {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([this](){
                _menu_item_connect->setString("Sign Out");
            });
            _txtConnection->setString("Connected");
            _txtStat->setString("Logged In");
        }
        else
        {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([this](){
                _menu_item_connect->setString("Sign In");
            });
            _txtConnection->setString("Disconnected");
            _txtStat->setString("Login Failed");
        }
    }
    else
    {
        _txtStat->setString("GPG not initialized");
    }
    
}


void BaseScene::setTitle(const std::string &title)
{
    _txtTitle->setString(title);
}
