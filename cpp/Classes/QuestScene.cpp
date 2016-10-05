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
            MenuItemFont::create("Fetch Quests", CC_CALLBACK_1(QuestScene::FetchList, this)),
            MenuItemFont::create("Show UI", CC_CALLBACK_1(QuestScene::ShowAllUI, this)),
            nullptr
    );
    
    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2 - 220, size.height/2 + 40);
    addChild(menu);
    
    _questNode = Node::create();
    _questNode->setPosition(size.width - 420, size.height/2 +40);
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

void QuestScene::ShowAllUI(cocos2d::Ref *sender)
{
    _game_services->Quests().ShowAllUI(
                                       [this](const gpg::QuestManager::QuestUIResponse& response)  {
                                       });
}

void QuestScene::updateQuests(const std::vector<gpg::Quest>& data)
{
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        _questData = data;
        
        for (int i = 0; i < _questData.size(); ++i)
        {
            auto it = _questData[i];
            auto lbl_name = Label::create( it.Name(), "", 20);
            lbl_name->setPosition(0, _currQuestNodeY);
            lbl_name->setTag(i);
            _questNode->addChild(lbl_name);
            
            auto btn_fetch = ui::Button::create("btn_green_normal.png");
            btn_fetch->setTitleText("Fetch");
            btn_fetch->setPosition(Vec2(80, _currQuestNodeY));
            btn_fetch->setTag(i);
            btn_fetch->addClickEventListener([=](Ref* sender){
                this->Fetch(sender);
            });
            _questNode->addChild(btn_fetch);
            
            auto btn_view = ui::Button::create("btn_green_normal.png");
            btn_view->setTitleText("View");
            btn_view->setPosition(Vec2(140, _currQuestNodeY));
            btn_view->setTag(i);
            btn_view->addClickEventListener([=](Ref* sender){
                this->ShowUI(sender);
            });
            _questNode->addChild(btn_view);
            
            auto btn_accept = ui::Button::create("btn_green_normal.png");
            btn_accept->setTitleText("Accept");
            btn_accept->setPosition(Vec2(200, _currQuestNodeY));
            btn_accept->setTag(i);
            btn_accept->addClickEventListener([=](Ref* sender){
                this->Accept(sender);
            });
            _questNode->addChild(btn_accept);
            
            auto btn_claim =  ui::Button::create("btn_green_normal.png");
            btn_claim->setTitleText("Claim");
            btn_claim->setPosition(Vec2(260, _currQuestNodeY));
            btn_claim->setTag(i);
            btn_claim->addClickEventListener([=](Ref* sender){
                this->ClaimMilestone(sender);
            });
            _questNode->addChild(btn_claim);
            
            _currQuestNodeY += 60;
        }
    });
}

void QuestScene::Fetch(cocos2d::Ref *sender)
{
    auto btn = (ui::Button*)sender;
    auto data = _questData[btn->getTag()];
    
    _game_services->Quests().Fetch(
                                   gpg::DataSource::CACHE_OR_NETWORK,
                                   data.Id(),
                                   [this](const gpg::QuestManager::FetchResponse& response)
                                   {
                                       if ( gpg::IsSuccess( response.status ) ) {
                                           this->_txtStat->setString( __printf("Fetch Quest success. Name: %s", response.data.Name().c_str()) );
                                       } else {
                                           this->_txtStat->setString( __printf("Fetch Quest error code %d.", (int)response.status) );
                                       }
                                   });
}

void QuestScene::Accept(cocos2d::Ref *sender)
{
    auto btn = (ui::Button*)sender;
    auto data = _questData[btn->getTag()];
    
    _game_services->Quests().Fetch(
            gpg::DataSource::CACHE_OR_NETWORK,
            data.Id(),
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
    auto btn = (ui::Button*)sender;
    auto data = _questData[btn->getTag()];
    
    _game_services->Quests().Fetch(
            gpg::DataSource::CACHE_OR_NETWORK,
            data.Id(),
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


void QuestScene::ShowUI(cocos2d::Ref *sender)
{
    auto btn = (ui::Button*)sender;
    auto data = _questData[btn->getTag()];
    
    _game_services->Quests().Fetch(
            gpg::DataSource::CACHE_OR_NETWORK,
            data.Id(),
            [this](const gpg::QuestManager::FetchResponse& response) {

                if ( IsSuccess(response.status) ) {
                    _game_services->Quests().ShowUI(
                            response.data,
                            [this](const gpg::QuestManager::QuestUIResponse& response)  {
                            });
                }
            });
}
