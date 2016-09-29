//
// Created by NiTe Luo on 9/19/16.
//

#include "QuestScene.h"
#include "EventScene.h"
#include "Utils.h"
#include "PlayerStatScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

cocos2d::Scene *QuestScene::createScene()
{
    auto scene = Scene::create();

    auto layer = QuestScene::create();

    scene->addChild(layer);

    return scene;
}

bool QuestScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");

    setTitle("Quest");

    Menu* menu = Menu::create(
            MenuItemFont::create("Fetch", CC_CALLBACK_1(QuestScene::Fetch, this)),
            MenuItemFont::create("Fetch List", CC_CALLBACK_1(QuestScene::FetchList, this)),
            MenuItemFont::create("Show UI", CC_CALLBACK_1(QuestScene::ShowUI, this)),
            MenuItemFont::create("Show All UI", CC_CALLBACK_1(QuestScene::ShowAllUI, this)),
            MenuItemFont::create("Accept", CC_CALLBACK_1(QuestScene::Accept, this)),
            MenuItemFont::create("Claim Milestone", CC_CALLBACK_1(QuestScene::ClaimMilestone, this)),
            nullptr
    );
    
    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);
    
    _questNode = Node::create();
    _questNode->setPosition(size.width - 220, size.height/2 +40);
    addChild(_questNode);
    
    _currQuestNodeY = 0;

    return true;
}

void QuestScene::onPrevScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(EventScene::createScene());
}

void QuestScene::onNextScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(PlayerStatScene::createScene());
}


void QuestScene::Fetch(cocos2d::Ref *sender)
{
    _game_services->Quests().Fetch(
            gpg::DataSource::CACHE_OR_NETWORK,
            "<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ",
            [this](const gpg::QuestManager::FetchResponse& response)
            {
                if ( gpg::IsSuccess( response.status ) ) {
                    this->_txtStat->setString( __printf("Fetch Quest success. Name: %s", response.data.Name().c_str()) );
                } else {
                    this->_txtStat->setString( __printf("Fetch Quest error code %d.", (int)response.status) );
                }
            });
}

void QuestScene::FetchList(cocos2d::Ref *sender)
{
    _game_services->Quests().FetchList(
            gpg::DataSource::CACHE_OR_NETWORK,
            [this](const gpg::QuestManager::FetchListResponse& response) {
                if (IsSuccess(response.status)) {
                    this->_txtStat->setString( __printf("Fetch Quest list got %lu quests.", response.data.size() ) );
                    this->updateQuests(response.data);
                } else {
                    this->_txtStat->setString( __printf("Fetch Quest list error. code %d.", (int)response.status) );
                }
            });
}

void QuestScene::updateQuests(const std::vector<gpg::Quest>& data)
{
    _questData = data;
    for (auto it = _questData.begin(); it != _questData.end(); ++it)
    {
        auto quest_item = CSLoader::createNode("quest_item.csb");
        quest_item->setPosition(0, _currQuestNodeY);
        _questNode->addChild(quest_item);
        
        _currQuestNodeY += 40;
    }
}

void QuestScene::Accept(cocos2d::Ref *sender)
{
    _game_services->Quests().Fetch(
            gpg::DataSource::CACHE_OR_NETWORK,
            "<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ",
            [this](const gpg::QuestManager::FetchResponse& response) {

                if ( gpg::IsSuccess( response.status ) ) {
                    _game_services->Quests().Accept(
                            response.data,
                            [this](const gpg::QuestManager::AcceptResponse& response) {

                                if (IsSuccess(response.status)) {
                                    this->_txtStat->setString( __printf("Quest Accept ok") );
                                } else {
                                    this->_txtStat->setString( __printf("Quest Accept error. code %d.", (int)response.status) );
                                }
                            });
                } else {
                    this->_txtStat->setString( __printf("Quest Accept error. At Fetch by id. code %d.", (int)response.status) );
                }
            });
}

void QuestScene::ClaimMilestone(cocos2d::Ref *sender)
{
    _game_services->Quests().Fetch(
            gpg::DataSource::CACHE_OR_NETWORK,
            "<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ",
            [this](const gpg::QuestManager::FetchResponse& response) {

                if ( IsSuccess(response.status) ) {

                    if ( response.data.CurrentMilestone().Valid() ) {
                        _game_services->Quests().ClaimMilestone(
                                response.data.CurrentMilestone(),
                                [this](const gpg::QuestManager::ClaimMilestoneResponse& response) {

                                    if (gpg::IsSuccess(response.status))  {
                                        this->_txtStat->setString( "ClaimMilestone success." );
                                    } else {
                                        this->_txtStat->setString( __printf("ClaimMilestone error. code %d.", (int)response.status) );
                                    }
                                });
                    } else {
                        this->_txtStat->setString( "ClaimMilestone error. Milestone not valid." );
                    }

                } else {
                    this->_txtStat->setString( __printf("ClaimMilestone error. At Fetch by id. code %d.", (int)response.status) );
                }
            });
}

void QuestScene::ShowAllUI(cocos2d::Ref *sender)
{
    _game_services->Quests().ShowAllUI(
            [this](const gpg::QuestManager::QuestUIResponse& response)  {
            });
}

void QuestScene::ShowUI(cocos2d::Ref *sender)
{
    _game_services->Quests().Fetch(
            gpg::DataSource::CACHE_OR_NETWORK,
            "<CgkI4PT5o5sDEAESDQoJCOio6aTRFhACEA0YAQ",
            [this](const gpg::QuestManager::FetchResponse& response) {

                if ( IsSuccess(response.status) ) {
                    _game_services->Quests().ShowUI(
                            response.data,
                            [this](const gpg::QuestManager::QuestUIResponse& response)  {
                            });
                }
            });
}
