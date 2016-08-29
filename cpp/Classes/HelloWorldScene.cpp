#include <PluginSdkboxGooglePlay/SdkboxGooglePlayWrappedObjects.h>

#include "HelloWorldScene.h"


#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#else
#include <io.h>
#include <WS2tcpip.h>
#endif

USING_NS_CC;

static const int MAX_SNAPSHOTS = 8;
static std::unique_ptr<gpg::GameServices> _game_services;
static std::unique_ptr<gpg::Player> _local_player;
static std::unique_ptr<gpg::ScorePage> _currentScorePage = nullptr;
static bool _signed_in = false;

static const std::string GAME_NAME = "native_game";
static const std::string GAME_DESCRIPTION = "A native game description";

static std::vector<uint8_t> str_to_vector( const std::string& str ) {
    return std::vector<uint8_t>( str.begin(), str.end() );
}

static std::string vec_to_string( const std::vector<uint8_t>& v ) {
    return std::string(v.begin(), v.end());
}

void sdkbox::GPGWrapper::NotifyToScripting( int id, const std::string& str_json ) {
}

static std::string __printf( const char* format, ... ) {
    char b[256];
    va_list args;
    va_start (args, format);
    vsnprintf (b,256,format, args);
    va_end( args );
    
    return std::string(b);
}




using namespace sdkbox;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size size = CCDirector::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");
    int defaultFontSize = 32;

    _menu_item_connect = MenuItemFont::create("Sign In/Out",    CC_CALLBACK_1(HelloWorld::connect, this));
    
    Menu* menu = Menu::create(
                      _menu_item_connect,
                      MenuItemFont::create("Show SnapshotUI", CC_CALLBACK_1(HelloWorld::showSnapshotUI, this)),
                      MenuItemFont::create("Fetch all games", CC_CALLBACK_1(HelloWorld::fetchAllSnapshotGames, this)),
                      MenuItemFont::create( std::string("Delete ") + GAME_NAME, CC_CALLBACK_1(HelloWorld::deleteSnapshotGame, this)),
                              
                      MenuItemFont::create( "ldb: Get All", CC_CALLBACK_1(HelloWorld::ldbFetchAll, this)),
                      MenuItemFont::create( "ldb: Get 'Best Gamers'", CC_CALLBACK_1(HelloWorld::ldbFetch, this)),
                      MenuItemFont::create( "ldb: Fetch score page 'Best Gamers'", CC_CALLBACK_1(HelloWorld::ldbFetchScorePage, this)),
                      MenuItemFont::create( "ldb: Fetch next score page", CC_CALLBACK_1(HelloWorld::ldbFetchNextScorePage, this)),
                      MenuItemFont::create( "ldb: ShowUI 'Best Gamers'", CC_CALLBACK_1(HelloWorld::ldbShowUI, this)),
                      MenuItemFont::create( "ldb: ShowUI All", CC_CALLBACK_1(HelloWorld::ldbShowAllUI, this)),
                      MenuItemFont::create( "ldb: Fetch summary 'Best Gamers'", CC_CALLBACK_1(HelloWorld::ldbFetchScoreSummary, this)),
                      MenuItemFont::create( "ldb: Fetch all summaries", CC_CALLBACK_1(HelloWorld::ldbFetchScoreAllSummaries, this)),
                      MenuItemFont::create( "ldb: Submit score 'Best Gamers'", CC_CALLBACK_1(HelloWorld::ldbSubmitScore, this)),
                              
                      MenuItemFont::create( "ach: ShowUI All", CC_CALLBACK_1(HelloWorld::achShowAllUI, this)),
                      MenuItemFont::create( "ach: Fetch all achievements", CC_CALLBACK_1(HelloWorld::achFetchAll, this)),
                      MenuItemFont::create( "ach: Fetch achievement", CC_CALLBACK_1(HelloWorld::achFetch, this)),
                      MenuItemFont::create( "ach: Increment", CC_CALLBACK_1(HelloWorld::achIncrement, this)),
                      MenuItemFont::create( "ach: Reveal", CC_CALLBACK_1(HelloWorld::achReveal, this)),
                      MenuItemFont::create( "ach: Set at least steps", CC_CALLBACK_1(HelloWorld::achSetAtLeastSteps, this)),
                      MenuItemFont::create( "ach: Unlock", CC_CALLBACK_1(HelloWorld::achUnlock, this)),
                      nullptr
    );

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);
        
    _txtStat = Label::create("No action yet.", "fonts/Marker Felt.ttf",32);
    _txtStat->setAnchorPoint(cocos2d::Point(0, 0));
    _txtStat->setPosition(cocos2d::Point(10, 10));
    addChild(_txtStat);
    
    _txtC = Label::create("Disconnected", "fonts/Marker Felt.ttf",32);
    _txtC->setAnchorPoint(cocos2d::Point(0, 0));
    _txtC->setPosition(cocos2d::Point(10, 45));
    addChild(_txtC);

    
    sdkbox::PluginSdkboxGooglePlay::init();
    
    __initGPG();

    return true;
}

void HelloWorld::__initGPG() {
    
    if ( !_game_services || !_game_services->IsAuthorized() ) {
        _game_services = gpg::GameServices::Builder()
                .SetDefaultOnLog( gpg::LogLevel::VERBOSE )
                .SetOnAuthActionStarted([this](gpg::AuthOperation op) {
                    
                    
                })
                .SetOnAuthActionFinished([this](gpg::AuthOperation op, gpg::AuthStatus status) {
                    
                    if ( status==gpg::AuthStatus::VALID ) {
                        _signed_in = true;
                        
                        _game_services->Players().FetchSelf([this](const gpg::PlayerManager::FetchSelfResponse &response){
                            _local_player = std::unique_ptr<gpg::Player>(new gpg::Player(response.data));
                            _txtC->setString( std::string("Connected as: ") + _local_player->Name() );
                        });
                        
                    } else {
                        _signed_in = false;
                        _txtC->setString("");
                        _txtStat->setString("");
                    }
                    
                })
                .EnableSnapshots()
                .Create( *CreatePlatformConfiguration("777734739048-cdkbeieil19d6pfkavddrri5o19gk4ni.apps.googleusercontent.com").get() );
    } else {
        
        if ( _game_services ) {
            _game_services->SignOut();
        }
    }
}

void HelloWorld::connect(cocos2d::CCObject *sender) {
    if ( _game_services->IsAuthorized() ) {
        _game_services->SignOut();
    } else {
        _game_services->StartAuthorizationUI();
    }
}

void HelloWorld::showSnapshotUI(cocos2d::CCObject *sender) {
    
    if ( _game_services ) {
        _game_services->Snapshots().ShowSelectUIOperation( true, true, MAX_SNAPSHOTS, "Snapshots title",
              [this](gpg::SnapshotManager::SnapshotSelectUIResponse const & response) {
                  
                    if (IsSuccess(response.status)) {
                        if (response.data.Valid()) {
                            // load a game.
                            // SnapshotMetadata
                            gpg::SnapshotMetadata snapshot = response.data;
                            std::string filename = snapshot.FileName();
                            CCLOGINFO("Load game: %s with description: %s", filename.c_str(), snapshot.Description().c_str());
                            __loadGameContents( filename );
                          
                      } else {
                          // create game
                          std::string game_contents = "{\"a\":\"abcd\",\"b\":false,\"c\":{\"d\":[9,6,\"a\"],\"e\":{},\"f\":5432,\"g\":1}}";
                          __createGame( GAME_NAME, GAME_DESCRIPTION, str_to_vector(game_contents), gpg::SnapshotConflictPolicy::MOST_RECENTLY_MODIFIED );
                      }
                    } else {
                      // error receiving info
                      CCLOGINFO("Error in snapshot select ui: %d", (int)response.status);
                  }
              });
        
    }
    
    
}

/**
 * Load a game contents and print it as string on the console.
 * Scripting js/lua, expect to save games as strings (preferably serialized json objects), but native can do any binary payload.
 */
void HelloWorld::__loadGameContents(const std::string &filename) {
    if ( _game_services ) {
        _game_services->Snapshots().Open(
                 gpg::DataSource::CACHE_OR_NETWORK,
                 filename,
                 gpg::SnapshotConflictPolicy::MOST_RECENTLY_MODIFIED,
                 [this](gpg::SnapshotManager::OpenResponse const & response) {
                     gpg::SnapshotManager::ReadResponse responseRead = _game_services->Snapshots().ReadBlocking(response.data);
                     
                     if ( responseRead.status == gpg::ResponseStatus::VALID ) {
                         std::string gamecontents = vec_to_string(responseRead.data);
                         _txtStat->setString( "Loaded game contents success. see console" );
                         CCLOG( "Loaded game contents: ");
                         CCLOG( "%s", gamecontents.c_str() );
                     } else {
                         _txtStat->setString("Error loading game contents.");
                     }
                     
                 });
    }
    
}

void HelloWorld::__createGame(
          const std::string& filename,
          const std::string& description,
          std::vector<uint8_t> data,
          gpg::SnapshotConflictPolicy conflict_policy ) {
    
    if ( _game_services ) {
        
        _game_services->Snapshots().Open(
                filename,
                conflict_policy,
                [this, filename, description, data](gpg::SnapshotManager::OpenResponse const &response) {

                    if (IsSuccess(response.status)) {

                        gpg::SnapshotMetadata metadata = response.data;

                        gpg::SnapshotMetadataChange::Builder builder;
                        gpg::SnapshotMetadataChange metadata_change = builder
                                .SetDescription( description )
                                // .SetCoverImageFromPngData(pngData)
                                .Create();

                        _game_services->Snapshots().Commit( metadata, metadata_change, data,
                                   [this, filename]( const gpg::SnapshotManager::CommitResponse &commit_response ) {
                                       _txtStat->setString( std::string("Create game ") + filename + " success." );
                                   });
                        
                    } else {
                        // Handle snapshot open error here
                        char buff[256];
                        sprintf( buff, "Crete game error: %d.", (int)response.status );
                        _txtStat->setString( std::string(buff) );
                    }
                });
        
    }
}

void HelloWorld::deleteSnapshotGame(cocos2d::CCObject *sender) {
    
    if ( _game_services ) {
        
        gpg::SnapshotConflictPolicy conflict_policy = gpg::SnapshotConflictPolicy::HIGHEST_PROGRESS;
        
        _game_services->Snapshots().Open(
                GAME_NAME,
                conflict_policy,
                [this](gpg::SnapshotManager::OpenResponse const &response) {

                        if (IsSuccess(response.status)) {
                            _game_services->Snapshots().Delete( response.data );
                            _txtStat->setString( std::string(GAME_NAME) + " delete success.");
                        } else {
                            _txtStat->setString( std::string(GAME_NAME) + " delete error.");
                            CCLOG("Delete error, code: %d", (int)response.status);
                        }
                });
    }
    
}

void HelloWorld::fetchAllSnapshotGames(cocos2d::CCObject *sender ) {

    if ( _game_services ) {
        
        _game_services->Snapshots().FetchAll(
                gpg::DataSource::CACHE_OR_NETWORK,
                [this]( const gpg::SnapshotManager::FetchAllResponse& response ) {

                        if ( IsSuccess(response.status) ) {
                            
                            _txtStat->setString( __printf( "Loaded %;u snapshots metadata. See console for details.", response.data.size()) );

                            CCLOG("Loaded %lu snapshots metadata.", response.data.size());
                            for( auto snapshotmetadata : response.data ) {
                                CCLOG("  %s: %s.", snapshotmetadata.FileName().c_str(), snapshotmetadata.Description().c_str() );
                            }
                        } else {
                            _txtStat->setString("Load snapshots error.");
                        }
                });
    }
}


void HelloWorld::ldbFetch(cocos2d::CCObject *sender) {
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

void HelloWorld::ldbFetchAll(cocos2d::CCObject *sender) {
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

void HelloWorld::__ldbFetchScorePageImpl(
         const gpg::ScorePage::ScorePageToken& token,
         int max_items,
         gpg::DataSource data_source ) {
    
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


void HelloWorld::ldbFetchScorePage(cocos2d::CCObject *sender) {
    if ( _game_services ) {
        
        gpg::ScorePage::ScorePageToken token = _game_services->Leaderboards().ScorePageToken(
                 "CgkI6KjppNEWEAIQAg",
                 gpg::LeaderboardStart::TOP_SCORES,
                 gpg::LeaderboardTimeSpan::ALL_TIME,
                 gpg::LeaderboardCollection::PUBLIC );
        
        __ldbFetchScorePageImpl( token, 10, gpg::DataSource::CACHE_OR_NETWORK );
    }
}

void HelloWorld::ldbFetchNextScorePage(cocos2d::CCObject *sender) {
    if ( _game_services && _currentScorePage ) {
        if ( _currentScorePage->HasNextScorePage() ) {
            __ldbFetchScorePageImpl( _currentScorePage->NextScorePageToken(), 10, gpg::DataSource::CACHE_OR_NETWORK );
        } else {
            _txtStat->setString("There's no next score page.");
        }
    }
}

void HelloWorld::ldbFetchScoreSummary(cocos2d::CCObject *sender) {
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

void HelloWorld::ldbFetchScoreAllSummaries(cocos2d::CCObject *sender) {
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

void HelloWorld::ldbSubmitScore(cocos2d::CCObject *sender) {
    if ( _game_services ) {
        // submit score has no result callback.
        _game_services->Leaderboards().SubmitScore("CgkI6KjppNEWEAIQAg", 15001);
    }
}

void HelloWorld::ldbShowUI(cocos2d::CCObject *sender) {
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

void HelloWorld::ldbShowAllUI(cocos2d::CCObject *sender) {
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



void HelloWorld::achShowAllUI(cocos2d::CCObject *sender) {
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

void HelloWorld::achFetchAll(cocos2d::CCObject *sender) {
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

void HelloWorld::achFetch(cocos2d::CCObject *sender) {
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

void HelloWorld::achReveal(cocos2d::CCObject *sender) {
    if ( _game_services ) {
        _game_services->Achievements().Increment( "CgkI6KjppNEWEAIQDg" );
    }
}

void HelloWorld::achUnlock(cocos2d::CCObject *sender) {
    if ( _game_services ) {
        _game_services->Achievements().Unlock( "CgkI6KjppNEWEAIQDg" );
    }
}

void HelloWorld::achIncrement(cocos2d::CCObject *sender) {
    if ( _game_services ) {
        _game_services->Achievements().Increment( "CgkI6KjppNEWEAIQDg", 2 );
    }
}

void HelloWorld::achSetAtLeastSteps(cocos2d::CCObject *sender) {
    if ( _game_services ) {
        _game_services->Achievements().SetStepsAtLeast( "CgkI6KjppNEWEAIQDg", 20 );
    }
    
}


