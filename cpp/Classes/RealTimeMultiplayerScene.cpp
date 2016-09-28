#include "RealTimeMultiplayerScene.hpp"
#include "Utils.h"

#include "PlayerStatScene.h"
#include "TurnBasedMultiplayerScene.hpp"

using namespace cocos2d;

cocos2d::Scene *RealTimeMultiplayerScene::createScene()
{
    auto scene = Scene::create();

    auto layer = RealTimeMultiplayerScene::create();

    scene->addChild(layer);

    return scene;
}

bool RealTimeMultiplayerScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");

    setTitle("Real Time Multiplayer");

    Menu* menu = Menu::create(
                              MenuItemFont::create("CreateRoom automatch", CC_CALLBACK_1(RealTimeMultiplayerScene::CreateRoomAutoMatch, this)),
                              MenuItemFont::create("CreateRoom select", CC_CALLBACK_1(RealTimeMultiplayerScene::CreateRoomSelect, this)),
                              MenuItemFont::create("Invitations UI", CC_CALLBACK_1(RealTimeMultiplayerScene::ShowRoomInbox, this)),
                              MenuItemFont::create("Fetch invitations", CC_CALLBACK_1(RealTimeMultiplayerScene::FetchInvitations, this)),
                              MenuItemFont::create("Leave room", CC_CALLBACK_1(RealTimeMultiplayerScene::LeaveRoom, this)),
                              MenuItemFont::create("Accept invitation", CC_CALLBACK_1(RealTimeMultiplayerScene::AcceptInvitation, this)),
                              MenuItemFont::create("Decline invitation", CC_CALLBACK_1(RealTimeMultiplayerScene::DeclineInvitation, this)),
                              MenuItemFont::create("Dismiss invitation", CC_CALLBACK_1(RealTimeMultiplayerScene::DismissInvitation, this)),
                              MenuItemFont::create("message reliable", CC_CALLBACK_1(RealTimeMultiplayerScene::SendReliableMsg, this)),
                              MenuItemFont::create("message unreliable", CC_CALLBACK_1(RealTimeMultiplayerScene::SendUnreliableMsg, this)),
                              nullptr
                              );

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);

    return true;
}

void RealTimeMultiplayerScene::onPrevScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(PlayerStatScene::createScene());
}

void RealTimeMultiplayerScene::onNextScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(TurnBasedMultiplayerScene::createScene());
}

void RealTimeMultiplayerScene::CreateRealtimeRoom(gpg::RealTimeRoomConfig& config) {
    _game_services->RealTimeMultiplayer().
    CreateRealTimeRoom(config,
                       this,
                       [this](gpg::RealTimeMultiplayerManager::RealTimeRoomResponse const & response) {
                           if (gpg::MultiplayerStatus::VALID == response.status) {
                               CCLOG("create room success");
                               this->room = response.room;
                           } else {
                               CCLOG("create room fail:%d", response.status);
                           }
                       });
}
void RealTimeMultiplayerScene::CreateRoomAutoMatch(cocos2d::Ref *sender) {
    auto config = gpg::RealTimeRoomConfig::Builder()
    .SetMaximumAutomatchingPlayers(1)
    .SetMinimumAutomatchingPlayers(1)
    .Create();
    CreateRealtimeRoom(config);
}

void RealTimeMultiplayerScene::CreateRoomSelect(cocos2d::Ref *sender) {
    auto builder = new gpg::RealTimeRoomConfig::Builder();
    builder->SetMaximumAutomatchingPlayers(1);
    builder->SetMinimumAutomatchingPlayers(1);
    gpg::RealTimeRoomConfig config = builder->Create();
    _game_services->RealTimeMultiplayer().
    ShowPlayerSelectUI(1,
                       1,
                       true,
                       [this](gpg::RealTimeMultiplayerManager::PlayerSelectUIResponse const & response) {
                           if (gpg::UIStatus::VALID == response.status) {
                               CCLOG("show player select ui success");
                               auto config = gpg::RealTimeRoomConfig::Builder()
                                .PopulateFromPlayerSelectUIResponse(response).Create();

                               CreateRealtimeRoom(config);
                           } else {
                               CCLOG("show player select ui fail");
                           }
                       });
    delete builder;
}

void RealTimeMultiplayerScene::ShowRoomInbox(cocos2d::Ref *sender) {
    _game_services->RealTimeMultiplayer().
    ShowRoomInboxUI([this](gpg::RealTimeMultiplayerManager::RoomInboxUIResponse const & response) {
        if (gpg::UIStatus::VALID == response.status) {
            CCLOG("show room inbox ui success");
            this->invitation = response.invitation;
        } else {
            CCLOG("show room inbox ui fail");
        }
    });
}

void RealTimeMultiplayerScene::FetchInvitations(cocos2d::Ref *sender) {
    _game_services->RealTimeMultiplayer()
    .FetchInvitations([](gpg::RealTimeMultiplayerManager::FetchInvitationsResponse const & response) {
        if (gpg::ResponseStatus::VALID == response.status) {
            CCLOG("fetch invitation success");
        } else {
            CCLOG("fetch invitation fail");
        }
    });
}

void RealTimeMultiplayerScene::LeaveRoom(cocos2d::Ref *sender) {
    if (!room.Valid()) {
        CCLOG("room is invalid");
        return;
    }
    _game_services->RealTimeMultiplayer()
    .LeaveRoom(room,
               [this](gpg::ResponseStatus const & status) {
                   if (gpg::ResponseStatus::VALID == status) {
                       CCLOG("leave room success");
                   } else {
                       CCLOG("leave room fail");
                   }
               });
}

void RealTimeMultiplayerScene::AcceptInvitation(cocos2d::Ref *sender) {
    if (!invitation.Valid()) {
        CCLOG("invitation is invalid");
        return;
    }
    _game_services->RealTimeMultiplayer()
    .AcceptInvitation(invitation,
                      this,
                      [](gpg::RealTimeMultiplayerManager::RealTimeRoomResponse const & response) {
                          if (gpg::MultiplayerStatus::VALID == response.status) {
                              CCLOG("accept invitation success");
                          } else {
                              CCLOG("accept invitation fail");
                          }
                      });
}

void RealTimeMultiplayerScene::DeclineInvitation(cocos2d::Ref *sender) {
    if (!invitation.Valid()) {
        CCLOG("invitation is invalid");
        return;
    }
    _game_services->RealTimeMultiplayer().DeclineInvitation(invitation);
}

void RealTimeMultiplayerScene::DismissInvitation(cocos2d::Ref *sender) {
    if (!invitation.Valid()) {
        CCLOG("invitation is invalid");
        return;
    }
    _game_services->RealTimeMultiplayer().DismissInvitation(invitation);
}

void RealTimeMultiplayerScene::SendReliableMsg(cocos2d::Ref *sender) {
    gpg::MultiplayerParticipant participant;
    for (auto part : room.Participants()) {
        if (part.Id() != room.CreatingParticipant().Id()) {
            participant = part;
        }
    }
    std::string msg = "this is a reliable msg";
    _game_services->RealTimeMultiplayer()
    .SendReliableMessage(room,
                         participant,
                         std::vector<uint8_t>(msg.begin(), msg.end()),
                         [](gpg::MultiplayerStatus const & status) {
                             if (gpg::MultiplayerStatus::VALID == status) {
                                 CCLOG("send reliable msg success");
                             } else {
                                 CCLOG("send reliable msg fail");
                             }
                         });
}

void RealTimeMultiplayerScene::SendUnreliableMsg(cocos2d::Ref *sender) {
    std::vector<gpg::MultiplayerParticipant> participants;
    for (auto part : room.Participants()) {
        if (part.Id() != room.CreatingParticipant().Id()) {
            participants.push_back(part);
        }
    }
    
    std::string msg = "this is a unreliable msg";
    _game_services->RealTimeMultiplayer()
    .SendUnreliableMessage(room, participants, std::vector<uint8_t>(msg.begin(), msg.end()));
}


//IRealTimeEventListener
void RealTimeMultiplayerScene::OnRoomStatusChanged(gpg::RealTimeRoom const &room) {
    CCLOG("Room Status Change %d", room.Status());
}

void RealTimeMultiplayerScene::OnConnectedSetChanged(gpg::RealTimeRoom const &room) {
    CCLOG("Connection Change %d", room.Status());
}

void RealTimeMultiplayerScene::OnP2PConnected(gpg::RealTimeRoom const &room,
                    gpg::MultiplayerParticipant const &participant) {
    CCLOG("P2P Connected %s : %s", room.Id().c_str(), participant.DisplayName().c_str());
}

void RealTimeMultiplayerScene:: OnP2PDisconnected(gpg::RealTimeRoom const &room,
                      gpg::MultiplayerParticipant const &participant) {
    CCLOG("P2P Disconnected %s : %s", room.Id().c_str(), participant.DisplayName().c_str());
}

void RealTimeMultiplayerScene::OnParticipantStatusChanged(gpg::RealTimeRoom const &room,
                                gpg::MultiplayerParticipant const &participant) {
    CCLOG("Participant Status Change %s : %s", room.Id().c_str(), participant.DisplayName().c_str());
}

void RealTimeMultiplayerScene::OnDataReceived(gpg::RealTimeRoom const &room,
                    gpg::MultiplayerParticipant const &from_participant,
                    std::vector<uint8_t> data,
                    bool is_reliable) {
    CCLOG("Recv Data %s : %s", from_participant.DisplayName().c_str(), (char*)data.data());
}


