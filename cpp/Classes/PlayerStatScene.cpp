//
// Created by NiTe Luo on 9/19/16.
//

#include "PlayerStatScene.h"
#include "Utils.h"
#include "QuestScene.h"

using namespace cocos2d;

cocos2d::Scene *PlayerStatScene::createScene()
{
    auto scene = Scene::create();

    auto layer = PlayerStatScene::create();

    scene->addChild(layer);

    return scene;
}

bool PlayerStatScene::init()
{
    if( !BaseScene::init())
    {
        return false;
    }

    setTitle("Player Stats");

    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");

    Menu* menu = Menu::create(
            MenuItemFont::create("Fetch For Player", CC_CALLBACK_1(PlayerStatScene::FetchForPlayer, this)),
            nullptr
    );

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);

    return true;
}

void PlayerStatScene::onPrevScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(QuestScene::createScene());
}

void PlayerStatScene::onNextScene(cocos2d::Ref *sender)
{
    BaseScene::onNextScene(sender);
}

void PlayerStatScene::FetchForPlayer(cocos2d::Ref *sender)
{
    _game_services->Stats().FetchForPlayer(
            gpg::DataSource::CACHE_OR_NETWORK,
            [this](const gpg::StatsManager::FetchForPlayerResponse& response) {
                if (IsSuccess(response.status)) {
                    this->_txtStat->setString( __printf("Days since last played: %ld.", (long)response.data.DaysSinceLastPlayed() ) );
                } else {
                    this->_txtStat->setString( __printf("Fetch for player error. code %d.", (int)response.status) );
                }

            });
}
