#include "TurnBasedMultiplayerScene.hpp"
#include "Utils.h"
#include "RealTimeMultiplayerScene.hpp"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "NearbyConnectionsScene.hpp"
#endif

using namespace cocos2d;

cocos2d::Scene *TurnBasedMultiplayerScene::createScene()
{
    auto scene = Scene::create();

    auto layer = TurnBasedMultiplayerScene::create();

    scene->addChild(layer);

    return scene;
}

bool TurnBasedMultiplayerScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");

    setTitle("Turn Based Multiplayer");

    Menu* menu = Menu::create(
                              MenuItemFont::create("Create TurnBased Match", CC_CALLBACK_1(TurnBasedMultiplayerScene::CreateTurnBasedMatch, this)),
                              MenuItemFont::create("Show Match Inbox UI", CC_CALLBACK_1(TurnBasedMultiplayerScene::ShowMatchInboxUI, this)),
//                              MenuItemFont::create("Accept Invitation", CC_CALLBACK_1(TurnBasedMultiplayerScene::AcceptInvitation, this)),
//                              MenuItemFont::create("Decline Invitation", CC_CALLBACK_1(TurnBasedMultiplayerScene::DeclineInvitation, this)),
//                              MenuItemFont::create("Dismiss Invitation", CC_CALLBACK_1(TurnBasedMultiplayerScene::DismissInvitation, this)),
                              MenuItemFont::create("Dismiss Match", CC_CALLBACK_1(TurnBasedMultiplayerScene::DismissMatch, this)),
                              MenuItemFont::create("Fetch Match", CC_CALLBACK_1(TurnBasedMultiplayerScene::FetchMatch, this)),
                              MenuItemFont::create("Take My Turn", CC_CALLBACK_1(TurnBasedMultiplayerScene::TakeMyTurn, this)),
                              MenuItemFont::create("Finish Match During MyTurn", CC_CALLBACK_1(TurnBasedMultiplayerScene::FinishMatchDuringMyTurn, this)),
                              MenuItemFont::create("Rematch", CC_CALLBACK_1(TurnBasedMultiplayerScene::Rematch, this)),
                              MenuItemFont::create("Leave Match", CC_CALLBACK_1(TurnBasedMultiplayerScene::LeaveMatch, this)),
                              MenuItemFont::create("CancelMatch", CC_CALLBACK_1(TurnBasedMultiplayerScene::CancelMatch, this)),
                              MenuItemFont::create("FetchMatches", CC_CALLBACK_1(TurnBasedMultiplayerScene::FetchMatches, this)),
                              MenuItemFont::create("Show Player Select UI", CC_CALLBACK_1(TurnBasedMultiplayerScene::ShowPlayerSelectUI, this)),
                              nullptr
                              );

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);

    return true;
}

void TurnBasedMultiplayerScene::onPrevScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(RealTimeMultiplayerScene::createScene());
}

void TurnBasedMultiplayerScene::onNextScene(cocos2d::Ref *sender)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    Director::getInstance()->replaceScene(NearbyConnectionsScene::createScene());
#else
    BaseScene::onNextScene(sender);
#endif
}

void TurnBasedMultiplayerScene::CreateTurnBasedMatch(cocos2d::Ref *sender) {
    auto config = gpg::TurnBasedMatchConfig::Builder()
    .SetMaximumAutomatchingPlayers(2)
    .SetMinimumAutomatchingPlayers(1)
    .Create();
    _game_services->TurnBasedMultiplayer()
    .CreateTurnBasedMatch(config,
                          [this](gpg::TurnBasedMultiplayerManager::TurnBasedMatchResponse const & response) {
                              if (gpg::IsSuccess(response.status)) {
                                  CCLOG("create turn based match success");
                                  this->_match = response.match;
                                  this->_myId = _match.PendingParticipant().Id();
                                  this->handleMatch(response.match);
                              } else {
                                  CCLOG("create turn based match failed:%d", response.status);
                              }
                          });
}

void TurnBasedMultiplayerScene::ShowMatchInboxUI(cocos2d::Ref *sender) {
    _game_services->TurnBasedMultiplayer()
    .ShowMatchInboxUI([this](gpg::TurnBasedMultiplayerManager::MatchInboxUIResponse const & response) {
        if (gpg::IsSuccess(response.status)) {
            CCLOG("show match inbox success");
            this->_match = response.match;
            this->handleMatch(response.match);
        } else {
            CCLOG("show match inbox failed:%d", response.status);
        }
    });
}

void TurnBasedMultiplayerScene::ShowPlayerSelectUI(cocos2d::Ref *sender) {
    _game_services->TurnBasedMultiplayer()
    .ShowPlayerSelectUI(1,
                        2,
                        true,
                        [](gpg::TurnBasedMultiplayerManager::PlayerSelectUIResponse const & response) {
                            if (gpg::IsSuccess(response.status)) {
                                CCLOG("show player select success");
                            } else {
                                CCLOG("show player select failed:%d", response.status);
                            }
                        });
}

void TurnBasedMultiplayerScene::AcceptInvitation(cocos2d::Ref *sender) {
    gpg::MultiplayerInvitation invitation;
    _game_services->TurnBasedMultiplayer()
    .AcceptInvitation(invitation,
                      [](gpg::TurnBasedMultiplayerManager::TurnBasedMatchResponse const & response) {
                          if (gpg::IsSuccess(response.status)) {
                              CCLOG("accept invitation success");
                          } else {
                              CCLOG("accept invitation failed:%d", response.status);
                          }
                      });
}

void TurnBasedMultiplayerScene::DeclineInvitation(cocos2d::Ref *sender) {
    gpg::MultiplayerInvitation invitation;
    _game_services->TurnBasedMultiplayer().DeclineInvitation(invitation);
}

void TurnBasedMultiplayerScene::DismissInvitation(cocos2d::Ref *sender) {
    gpg::MultiplayerInvitation invitation;
    _game_services->TurnBasedMultiplayer().DismissInvitation(invitation);
}

void TurnBasedMultiplayerScene::DismissMatch(cocos2d::Ref *sender) {
    _game_services->TurnBasedMultiplayer().DismissMatch(_match);
}

void TurnBasedMultiplayerScene::FetchMatch(cocos2d::Ref *sender) {
    if (!_match.Valid()) {
        CCLOG("Match is invalid");
        return;
    }
    _game_services->TurnBasedMultiplayer()
    .FetchMatch(_match.Id(),
                [](gpg::TurnBasedMultiplayerManager::TurnBasedMatchResponse const & resp) {
                    if (gpg::IsSuccess(resp.status)) {
                        CCLOG("fetch match success");
                    } else {
                        CCLOG("fetch match failed:%d", resp.status);
                    }
                });
}

void TurnBasedMultiplayerScene::TakeMyTurn(cocos2d::Ref *sender) {
    if (!_match.Valid()) {
        CCLOG("Match is invalid");
        return;
    }
    
    std::vector<uint8_t> match_data;
    auto result = _match.ParticipantResults().WithResult(_myId, 0, gpg::MatchResult::WIN);
    gpg::MultiplayerParticipant next_participant;
    _game_services->TurnBasedMultiplayer()
    .TakeMyTurn(_match,
                match_data,
                result,
                _match.SuggestedNextParticipant(),
                [](gpg::TurnBasedMultiplayerManager::TurnBasedMatchResponse const &resp) {
                    if (gpg::IsSuccess(resp.status)) {
                        CCLOG("take my turn success");
                    } else {
                        CCLOG("take my turn failed:%d", resp.status);
                    }
                });
}

void TurnBasedMultiplayerScene::FinishMatchDuringMyTurn(cocos2d::Ref *sender) {
    if (!_match.Valid()) {
        CCLOG("Match is invalid");
        return;
    }
    
    std::vector<uint8_t> match_data;
    auto result = _match.ParticipantResults().WithResult(_myId, 0, gpg::MatchResult::WIN);
    _game_services->TurnBasedMultiplayer()
    .FinishMatchDuringMyTurn(_match,
                             match_data,
                             result,
                             [](gpg::TurnBasedMultiplayerManager::TurnBasedMatchResponse const & resp) {
                                 if (gpg::IsSuccess(resp.status)) {
                                     CCLOG("finish match during my turn success");
                                 } else {
                                     CCLOG("finish match during my turn failed:%d", resp.status);
                                 }
                             });
}

void TurnBasedMultiplayerScene::Rematch(cocos2d::Ref *sender) {
    if (!_match.Valid()) {
        CCLOG("Match is invalid");
        return;
    }
    
    _game_services->TurnBasedMultiplayer()
    .Rematch(_match,
             [](gpg::TurnBasedMultiplayerManager::TurnBasedMatchResponse const & resp) {
                 if (gpg::IsSuccess(resp.status)) {
                     CCLOG("rematch success");
                 } else {
                     CCLOG("rematch failed:%d", resp.status);
                 }
             });
}

void TurnBasedMultiplayerScene::LeaveMatch(cocos2d::Ref *sender) {
    if (!_match.Valid()) {
        CCLOG("Match is invalid");
        return;
    }
    
    auto& tbmp =_game_services->TurnBasedMultiplayer();
    if (gpg::MatchStatus::MY_TURN == _match.Status()) {
        tbmp.LeaveMatchDuringMyTurn(_match,
                                _match.SuggestedNextParticipant(),
                                [](gpg::MultiplayerStatus status) {
                                    if (gpg::IsSuccess(status)) {
                                        CCLOG("leave match during my turn success");
                                    } else {
                                        CCLOG("leave match during my turn failed");
                                    }
                                });
    } else if (gpg::MatchStatus::THEIR_TURN == _match.Status()) {
        tbmp.LeaveMatchDuringTheirTurn(_match,
                               [](gpg::MultiplayerStatus status) {
                                   if (gpg::IsSuccess(status)) {
                                       CCLOG("leave match during their turn success");
                                   } else {
                                       CCLOG("leave match during their turn failed");
                                   }
                               });
    } else {
        CCLOG("leave match staus unandle:%d", _match.Status());
    }
}

void TurnBasedMultiplayerScene::CancelMatch(cocos2d::Ref *sender) {
    if (!_match.Valid()) {
        CCLOG("Match is invalid");
        return;
    }
    
    _game_services->TurnBasedMultiplayer()
    .CancelMatch(_match,
                 [](gpg::MultiplayerStatus status) {
                     if (gpg::IsSuccess(status)) {
                         CCLOG("cancel match success");
                     } else {
                         CCLOG("cancel match failed");
                     }
                 });
}

void TurnBasedMultiplayerScene::FetchMatches(cocos2d::Ref *sender) {
    if (!_match.Valid()) {
        CCLOG("Match is invalid");
        return;
    }
    
    _game_services->TurnBasedMultiplayer()
    .FetchMatches([](gpg::TurnBasedMultiplayerManager::TurnBasedMatchesResponse const & resp) {
        if (gpg::IsSuccess(resp.status)) {
            CCLOG("fetch matches success");
        } else {
            CCLOG("fetch matches failed:%d", resp.status);
        }
    });
}

void TurnBasedMultiplayerScene::handleMatch(gpg::TurnBasedMatch match) {
    switch (match.Status()) {
        case gpg::MatchStatus::INVITED: {
            break;
        }
        case gpg::MatchStatus::THEIR_TURN: {
            break;
        }
        case gpg::MatchStatus::MY_TURN: {
            this->_myId = _match.PendingParticipant().Id();
            break;
        }
        case gpg::MatchStatus::PENDING_COMPLETION: {
            break;
        }
        case gpg::MatchStatus::COMPLETED: {
            break;
        }
        case gpg::MatchStatus::CANCELED: {
            break;
        }
        case gpg::MatchStatus::EXPIRED: {
            break;
        }
        default: {
            break;
        }
    }
}
