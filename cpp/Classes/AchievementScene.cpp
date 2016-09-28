#include "AchievementScene.h"
#include "Utils.h"
#include "LeaderboardScene.h"
#include "EventScene.h"

using namespace cocos2d;

cocos2d::Scene *AchievementScene::createScene()
{
    auto scene = Scene::create();

    auto layer = AchievementScene::create();

    scene->addChild(layer);

    return scene;
}

bool AchievementScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");

    setTitle("Achievement");

    Menu* menu = Menu::create(
            MenuItemFont::create( "ShowUI All", CC_CALLBACK_1(AchievementScene::achShowAllUI, this)),
            MenuItemFont::create( "Fetch all achievements", CC_CALLBACK_1(AchievementScene::achFetchAll, this)),
            MenuItemFont::create( "Fetch achievement", CC_CALLBACK_1(AchievementScene::achFetch, this)),
            MenuItemFont::create( "Increment", CC_CALLBACK_1(AchievementScene::achIncrement, this)),
            MenuItemFont::create( "Reveal", CC_CALLBACK_1(AchievementScene::achReveal, this)),
            MenuItemFont::create( "Set at least steps", CC_CALLBACK_1(AchievementScene::achSetAtLeastSteps, this)),
            MenuItemFont::create( "Unlock", CC_CALLBACK_1(AchievementScene::achUnlock, this)),
            nullptr);

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);
    
    return true;
}

void AchievementScene::onPrevScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(LeaderboardScene::createScene());
}

void AchievementScene::onNextScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(EventScene::createScene());
}

void AchievementScene::achShowAllUI(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Achievements().ShowAllUI(
                [this]( gpg::UIStatus status ) {
                    if ( IsSuccess(status) ) {
                        _txtStat->setString( "achievements show ui success." );
                    } else {
                        _txtStat->setString( __printf("achievements show ui error %d.", (int)status) );
                    }
                });
    }
}

void AchievementScene::achFetchAll(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Achievements().FetchAll( gpg::DataSource::CACHE_OR_NETWORK, [this](const gpg::AchievementManager::FetchAllResponse& res) {

            if ( IsSuccess( res.status ) ) {

                _txtStat->setString( __printf("ach ftch all. got info for %lu achievements.", res.data.size() ));
                for( auto achievement : res.data ) {
                    CCLOG("%s type:%d state:%d", achievement.Name().c_str(), (int)achievement.Type(), (int)achievement.State() );
                }
            } else {
                _txtStat->setString( __printf("achievements fetch all error %d.", (int)res.status) );
            }

        });
    }
}

void AchievementScene::achFetch(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Achievements().Fetch( gpg::DataSource::CACHE_OR_NETWORK, "CgkI6KjppNEWEAIQBQ", [this](const gpg::AchievementManager::FetchResponse& res) {

            if ( IsSuccess( res.status ) ) {
                gpg::Achievement achievement = res.data;
                _txtStat->setString( __printf("%s type:%d state:%d", achievement.Name().c_str(), (int)achievement.Type(), (int)achievement.State() ) );

            } else {
                _txtStat->setString( __printf("achievement all error %d.", (int)res.status) );
            }


        });
    }
}

void AchievementScene::achUnlock(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Achievements().Unlock( "CgkI6KjppNEWEAIQDg" );
        _txtStat->setString( "Unlock achievement" );
    }
}

void AchievementScene::achIncrement(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Achievements().Increment( "CgkI6KjppNEWEAIQDg", 2 );
        _txtStat->setString( "Increment achievement by 2" );
    }
}

void AchievementScene::achReveal(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Achievements().Increment( "CgkI6KjppNEWEAIQDg" );
        _txtStat->setString( "Reveal achievement" );
    }
}

void AchievementScene::achSetAtLeastSteps(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Achievements().SetStepsAtLeast( "CgkI6KjppNEWEAIQDg", 20 );
        _txtStat->setString( "Set steps for achievement" );
    }
}
