#include "RealTimeMultiplayerScene.hpp"
#include "Utils.h"

#include "PlayerStatScene.h"
#include "TurnBasedMultiplayerScene.hpp"

using namespace cocos2d;
using namespace std;

cocos2d::Scene *RealTimeMultiplayerScene::createScene()
{
    auto scene = Scene::create();

    auto layer = RealTimeMultiplayerScene::create();

    scene->addChild(layer);

    return scene;
}

void RealTimeMultiplayerScene::setRoom(gpg::RealTimeRoom const &room)
{
    _room = room;
    _txt_room->setString(room.Id());
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
                              MenuItemFont::create("Create/Join", CC_CALLBACK_1(RealTimeMultiplayerScene::CreateRoom, this)),
                              MenuItemFont::create("Invitations", CC_CALLBACK_1(RealTimeMultiplayerScene::ShowInvitations, this)),
                              MenuItemFont::create("Leave room", CC_CALLBACK_1(RealTimeMultiplayerScene::LeaveRoom, this)),
                              MenuItemFont::create("message reliable", CC_CALLBACK_1(RealTimeMultiplayerScene::SendReliableMsg, this)),
                              MenuItemFont::create("message unreliable", CC_CALLBACK_1(RealTimeMultiplayerScene::SendUnreliableMsg, this)),
                              nullptr
                              );

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);

    _txt_room = Label::create();
    _txt_room->setPosition(250, 200);
    _txt_room->setString("Room id here");
    addChild(_txt_room);

    _txt_message = Label::create();
    _txt_message->setPosition(250, 150);
    _txt_message->setString("Message here");
    addChild(_txt_message);

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

                           string msg;

                           if (gpg::MultiplayerStatus::VALID == response.status) {
                               msg = "Room created: ";
                               msg += response.room.Id();
                               _txtStat->setString(msg);
                               CCLOG("create room success");
                               setRoom(response.room);
                           } else {
                               msg = "Room failed: ";
                               msg += to_str(response.status);
                               _txtStat->setString(msg);
                               CCLOG("create room fail:%d", response.status);
                           }
                       });
}

void RealTimeMultiplayerScene::CreateRoom(cocos2d::Ref *sender) {
    _game_services->RealTimeMultiplayer().
    ShowPlayerSelectUI(MIN_AUTOMATCH_PLAYER,
                       MAX_AUTOMATCH_PLAYER,
                       true,
                       [this](gpg::RealTimeMultiplayerManager::PlayerSelectUIResponse const & response) {
                           if (gpg::UIStatus::VALID == response.status) {

                               auto config = gpg::RealTimeRoomConfig::Builder()
                                .PopulateFromPlayerSelectUIResponse(response).Create();

                               CreateRealtimeRoom(config);
                           }
                       });
}

void RealTimeMultiplayerScene::ShowInvitations(cocos2d::Ref *sender) {
    _game_services->RealTimeMultiplayer().
    ShowRoomInboxUI([this](gpg::RealTimeMultiplayerManager::RoomInboxUIResponse const & response) {
        if (gpg::IsSuccess(response.status)) {

            //Accept invitation
            auto result = _game_services->RealTimeMultiplayer().AcceptInvitationBlocking(response.invitation, this);
            _invitation = response.invitation;
            setRoom(result.room);
        }
    });
}

void RealTimeMultiplayerScene::LeaveRoom(cocos2d::Ref *sender) {
    if (!_room.Valid()) {
        CCLOG("room is invalid");
        return;
    }
    _game_services->RealTimeMultiplayer()
    .LeaveRoom(_room,
               [this](gpg::ResponseStatus const & status) {
                   if (gpg::ResponseStatus::VALID == status) {
                       _txtStat->setString("Left room");
                       _txt_room->setString("");
                       CCLOG("leave room success");
                   } else {
                       CCLOG("leave room fail");
                   }
               });
}

void RealTimeMultiplayerScene::SendReliableMsg(cocos2d::Ref *sender) {
    gpg::MultiplayerParticipant participant;
    for (auto part : _room.Participants()) {
        if (part.Id() != _room.CreatingParticipant().Id()) {
            participant = part;
        }
    }
    std::string msg = "this is a reliable msg";
    _game_services->RealTimeMultiplayer()
    .SendReliableMessage(_room,
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
    for (auto part : _room.Participants()) {
        if (part.Id() != _room.CreatingParticipant().Id()) {
            participants.push_back(part);
        }
    }
    
    std::string msg = "this is a unreliable msg";
    _game_services->RealTimeMultiplayer()
    .SendUnreliableMessage(_room, participants, std::vector<uint8_t>(msg.begin(), msg.end()));
}

/******************************************
 * If you don't want to use google's UI
 ******************************************/

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

void RealTimeMultiplayerScene::AcceptInvitation(cocos2d::Ref *sender) {
    if (!_invitation.Valid()) {
        CCLOG("invitation is invalid");
        return;
    }
    _game_services->RealTimeMultiplayer()
    .AcceptInvitation(_invitation,
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
    if (!_invitation.Valid()) {
        CCLOG("invitation is invalid");
        return;
    }
    _game_services->RealTimeMultiplayer().DeclineInvitation(_invitation);
}

void RealTimeMultiplayerScene::DismissInvitation(cocos2d::Ref *sender) {
    if (!_invitation.Valid()) {
        CCLOG("invitation is invalid");
        return;
    }
    _game_services->RealTimeMultiplayer().DismissInvitation(_invitation);
}


/******************************************
 * Google Play Service callback
 ******************************************/

//IRealTimeEventListener
void RealTimeMultiplayerScene::OnRoomStatusChanged(gpg::RealTimeRoom const &room)
{
    string msg = "Room Status: ";
    msg += to_str(room.Status());
    _txtStat->setString(msg);
    CCLOG("Room Status Change %d", room.Status());
}

void RealTimeMultiplayerScene::OnConnectedSetChanged(gpg::RealTimeRoom const &room)
{
    string msg = "Connection: ";
    msg += to_str(room.Status());
    _txtStat->setString(msg);
    CCLOG("Connection Change %d", room.Status());
}

void RealTimeMultiplayerScene::OnP2PConnected(gpg::RealTimeRoom const &room,
                    gpg::MultiplayerParticipant const &participant)
{
    string msg = "P2P Connected: ";
    msg += participant.DisplayName();
    _txtStat->setString(msg);
    CCLOG("P2P Connected %s : %s", room.Id().c_str(), participant.DisplayName().c_str());
}

void RealTimeMultiplayerScene:: OnP2PDisconnected(gpg::RealTimeRoom const &room,
                      gpg::MultiplayerParticipant const &participant)
{
    string msg = "P2P Disconnected: ";
    msg += participant.DisplayName();
    _txtStat->setString(msg);
    CCLOG("P2P Disconnected %s : %s", room.Id().c_str(), participant.DisplayName().c_str());
}

void RealTimeMultiplayerScene::OnParticipantStatusChanged(gpg::RealTimeRoom const &room,
                                gpg::MultiplayerParticipant const &participant)
{
    string msg = "Participant Change: ";
    msg += participant.DisplayName();
    _txtStat->setString(msg);
    CCLOG("Participant Status Change %s : %s", room.Id().c_str(), participant.DisplayName().c_str());
}

void RealTimeMultiplayerScene::OnDataReceived(gpg::RealTimeRoom const &room,
                    gpg::MultiplayerParticipant const &from_participant,
                    std::vector<uint8_t> data,
                    bool is_reliable)
{
    string msg = "DataReceived from: ";
    msg += from_participant.DisplayName();
    _txtStat->setString(msg);
    CCLOG("Recv Data %s : %s", from_participant.DisplayName().c_str(), (char*)data.data());
}


