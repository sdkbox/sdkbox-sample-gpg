#include "EventScene.h"
#include "AchievementScene.h"
#include "Utils.h"
#include "QuestScene.h"

using namespace cocos2d;

cocos2d::Scene *EventScene::createScene()
{
    auto scene = Scene::create();

    auto layer = EventScene::create();

    scene->addChild(layer);

    return scene;
}

bool EventScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");

    setTitle("Event");

    Menu* menu = Menu::create(
            MenuItemFont::create("Fetch", CC_CALLBACK_1(EventScene::Fetch, this)),
            MenuItemFont::create("Fetch All", CC_CALLBACK_1(EventScene::FetchAll, this)),
            MenuItemFont::create("Increment event by 2", CC_CALLBACK_1(EventScene::Increment, this)),
            nullptr
    );

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);
    
    return true;
}

void EventScene::onPrevScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(AchievementScene::createScene());
}

void EventScene::onNextScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(QuestScene::createScene());
}

void EventScene::Fetch(cocos2d::Ref *sender)
{
    _game_services->Events().Fetch(
            gpg::DataSource::CACHE_OR_NETWORK,
            "CgkI6KjppNEWEAIQDA",
            [this](const gpg::EventManager::FetchResponse& response) {

                if (IsSuccess(response.status)) {
                    this->_txtStat->setString( __printf("Fetch success. name:%s, count:%d", response.data.Name().c_str(), response.data.Count() ) );
                } else {
                    this->_txtStat->setString( __printf("Fetch error. code %d.", (int)response.status) );
                }
            });
}

void EventScene::FetchAll(cocos2d::Ref *sender)
{
    _game_services->Events().FetchAll(
            gpg::DataSource::CACHE_OR_NETWORK,
            [this](const gpg::EventManager::FetchAllResponse& response) {

                if (IsSuccess(response.status)) {
                    this->_txtStat->setString( __printf("Fetch all got %lu events.", response.data.size() ) );
                } else {
                    this->_txtStat->setString( __printf("Fetch all error. code %d.", (int)response.status) );
                }
            });
}

void EventScene::Increment(cocos2d::Ref *sender)
{
    if (_game_services) {
        _game_services->Events().Increment("CgkI6KjppNEWEAIQDA", 2);
        this->_txtStat->setString( "Call w/o callback. Check by Fetch." );
    }
}
