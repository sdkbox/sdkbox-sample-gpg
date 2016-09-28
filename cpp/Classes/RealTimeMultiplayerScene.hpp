#pragma once

#include "BaseScene.h"
#include <gpg/gpg.h>

class RealTimeMultiplayerScene : public BaseScene, public gpg::IRealTimeEventListener
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    CREATE_FUNC(RealTimeMultiplayerScene);
    
protected:
    
    virtual void onPrevScene(cocos2d::Ref *sender) override;
    
    virtual void onNextScene(cocos2d::Ref *sender) override;
    
    void CreateRoomAutoMatch(cocos2d::Ref *sender);
    void CreateRoomSelect(cocos2d::Ref *sender);
    void ShowRoomInbox(cocos2d::Ref *sender);
    void FetchInvitations(cocos2d::Ref *sender);
    void LeaveRoom(cocos2d::Ref *sender);
    void AcceptInvitation(cocos2d::Ref *sender);
    void DeclineInvitation(cocos2d::Ref *sender);
    void DismissInvitation(cocos2d::Ref *sender);
    void SendReliableMsg(cocos2d::Ref *sender);
    void SendUnreliableMsg(cocos2d::Ref *sender);
    
    void CreateRealtimeRoom(gpg::RealTimeRoomConfig& config);

    //IRealTimeEventListener
    void OnRoomStatusChanged(gpg::RealTimeRoom const &room) override;
    void OnConnectedSetChanged(gpg::RealTimeRoom const &room) override;
    void OnP2PConnected(gpg::RealTimeRoom const &room,
                        gpg::MultiplayerParticipant const &participant) override;
    void OnP2PDisconnected(gpg::RealTimeRoom const &room,
                           gpg::MultiplayerParticipant const &participant) override;
    void OnParticipantStatusChanged(gpg::RealTimeRoom const &room,
                                    gpg::MultiplayerParticipant const &participant) override;
    void OnDataReceived(gpg::RealTimeRoom const &room,
                        gpg::MultiplayerParticipant const &from_participant,
                        std::vector<uint8_t> data,
                        bool is_reliable) override;
    
private:
    gpg::RealTimeRoom room;
    gpg::MultiplayerInvitation invitation;
};
