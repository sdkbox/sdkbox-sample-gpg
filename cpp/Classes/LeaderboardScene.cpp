
#include "LeaderboardScene.h"
#include "Utils.h"
#include "SaveGameScene.h"
#include "AchievementScene.h"

using namespace cocos2d;

static std::unique_ptr<gpg::ScorePage> _currentScorePage = nullptr;

cocos2d::Scene *LeaderboardScene::createScene()
{
    auto scene = Scene::create();

    auto layer = LeaderboardScene::create();

    scene->addChild(layer);

    return scene;
}

bool LeaderboardScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");

    setTitle("Leaderboard");

    Menu* menu = Menu::create(
            MenuItemFont::create( "Get All", CC_CALLBACK_1(LeaderboardScene::ldbFetchAll, this)),
            MenuItemFont::create( "Get 'Best Gamers'", CC_CALLBACK_1(LeaderboardScene::ldbFetch, this)),
            MenuItemFont::create( "Fetch score page 'Best Gamers'", CC_CALLBACK_1(LeaderboardScene::ldbFetchScorePage, this)),
            MenuItemFont::create( "Fetch next score page", CC_CALLBACK_1(LeaderboardScene::ldbFetchNextScorePage, this)),
            MenuItemFont::create( "ShowUI 'Best Gamers'", CC_CALLBACK_1(LeaderboardScene::ldbShowUI, this)),
            MenuItemFont::create( "ShowUI All", CC_CALLBACK_1(LeaderboardScene::ldbShowAllUI, this)),
            MenuItemFont::create( "Fetch summary 'Best Gamers'", CC_CALLBACK_1(LeaderboardScene::ldbFetchScoreSummary, this)),
            MenuItemFont::create( "Fetch all summaries", CC_CALLBACK_1(LeaderboardScene::ldbFetchScoreAllSummaries, this)),
            MenuItemFont::create( "Submit score 'Best Gamers'", CC_CALLBACK_1(LeaderboardScene::ldbSubmitScore, this)),
            nullptr
    );

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);

    return true;
}

void LeaderboardScene::onPrevScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(SaveGameScene::createScene());
}

void LeaderboardScene::onNextScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(AchievementScene::createScene());
}

/************************
 Leaderboard callbacks
 ***********************/


void LeaderboardScene::ldbFetch(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Leaderboards().Fetch(
                gpg::DataSource::CACHE_OR_NETWORK,
                "CgkI6KjppNEWEAIQAg",  // Best gamers leaderboard
                [this]( const gpg::LeaderboardManager::FetchResponse& response ) {

                    gpg::ResponseStatus res = response.status;
                    if ( IsSuccess(res) ) {
                        _txtStat->setString( __printf( "Leaderboard info ok. id=%s", response.data.Name().c_str() ) );
                    } else {

                        _txtStat->setString( __printf("Leaderboard info error %d.", (int)res) );
                    }
                });
    }
}

void LeaderboardScene::ldbFetchAll(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Leaderboards().FetchAll(
                gpg::DataSource::CACHE_OR_NETWORK,
                [this]( const gpg::LeaderboardManager::FetchAllResponse& response ) {

                    gpg::ResponseStatus res = response.status;
                    if ( IsSuccess(res) ) {

                        std::string str;
                        for( gpg::Leaderboard l : response.data ) {
                            CCLOG( "Leaderboard: id=%s name=%s", l.Id().c_str(), l.Name().c_str() );
                            str += l.Name() + " - ";
                        }

                        _txtStat->setString( str );

                    } else {
                        _txtStat->setString( __printf("All Leaderboard info error %d.", (int)res) );
                    }

                });
    }
}


void LeaderboardScene::__ldbFetchScorePageImpl(const gpg::ScorePage::ScorePageToken &token, int max_items, gpg::DataSource data_source)
{
    _game_services->Leaderboards().FetchScorePage(data_source, token, max_items,
            [this](const gpg::LeaderboardManager::FetchScorePageResponse& res) {

                if ( IsSuccess( res.status ) ) {

                    gpg::ScorePage page = res.data;

                    std::string str("Player id in page: ");
                    for( auto e : page.Entries() ) {
                        str+= __printf( "[%s,%lu]", e.PlayerId().c_str(), e.Score().Value() );
                    }
                    _txtStat->setString( str );

                    _currentScorePage = std::unique_ptr<gpg::ScorePage>( new gpg::ScorePage(page) );

                } else {
                    _currentScorePage= nullptr;
                    _txtStat->setString( __printf("Fetch score page error %d.", (int)res.status) );
                }
            });
}

void LeaderboardScene::ldbFetchScorePage(cocos2d::Ref *sender)
{
    if ( _game_services ) {

        gpg::ScorePage::ScorePageToken token = _game_services->Leaderboards().ScorePageToken(
                "CgkI6KjppNEWEAIQAg",
                gpg::LeaderboardStart::TOP_SCORES,
                gpg::LeaderboardTimeSpan::ALL_TIME,
                gpg::LeaderboardCollection::PUBLIC );

        __ldbFetchScorePageImpl( token, 10, gpg::DataSource::CACHE_OR_NETWORK );
    }
}

void LeaderboardScene::ldbFetchNextScorePage(cocos2d::Ref *sender)
{
    if ( _game_services && _currentScorePage ) {
        if ( _currentScorePage->HasNextScorePage() ) {
            __ldbFetchScorePageImpl( _currentScorePage->NextScorePageToken(), 10, gpg::DataSource::CACHE_OR_NETWORK );
        } else {
            _txtStat->setString("There's no next score page.");
        }
    }
}

void LeaderboardScene::ldbFetchScoreSummary(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Leaderboards().FetchScoreSummary(
                gpg::DataSource::CACHE_OR_NETWORK,
                "CgkI6KjppNEWEAIQAg",
                gpg::LeaderboardTimeSpan::ALL_TIME,
                gpg::LeaderboardCollection::PUBLIC,
                [this](const gpg::LeaderboardManager::FetchScoreSummaryResponse& response){

                    if ( IsSuccess(response.status) ) {
                        gpg::ScoreSummary summary = response.data;
                        gpg::Score s = summary.CurrentPlayerScore();

                        _txtStat->setString( __printf("Score summary: pos=%lu", s.Rank() ) );

                    } else {
                        _txtStat->setString( __printf("Fetch score summary error %d.", (int)response.status) );
                    }

                });
    }
}

void LeaderboardScene::ldbFetchScoreAllSummaries(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Leaderboards().FetchAllScoreSummaries(
                gpg::DataSource::CACHE_OR_NETWORK,
                "CgkI6KjppNEWEAIQAg",
                [this](const gpg::LeaderboardManager::FetchAllScoreSummariesResponse& response){

                    if ( IsSuccess(response.status) ) {
                        _txtStat->setString( __printf("Got %lu summaries info.", response.data.size()) );
                    } else {
                        _txtStat->setString( __printf("Fetch all score summaries error %d.", (int)response.status) );
                    }

                });
    }
}

void LeaderboardScene::ldbSubmitScore(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        // submit score has no result callback.
        _game_services->Leaderboards().SubmitScore("CgkI6KjppNEWEAIQAg", 15001);
        _txtStat->setString( "Score submitted" );
    }
}

void LeaderboardScene::ldbShowUI(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Leaderboards().ShowUI(
                "CgkI6KjppNEWEAIQAg",
                [this]( gpg::UIStatus status ) {
                    if ( IsSuccess(status) ) {
                        _txtStat->setString( "show ui success." );
                    } else {
                        _txtStat->setString( __printf("show ui error %d.", (int)status) );
                    }
                });
    }
}

void LeaderboardScene::ldbShowAllUI(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Leaderboards().ShowAllUI(
                [this]( gpg::UIStatus status ) {
                    if ( IsSuccess(status) ) {
                        _txtStat->setString( "show ui success." );
                    } else {
                        _txtStat->setString( __printf("show ui error %d.", (int)status) );
                    }
                });
    }
}
