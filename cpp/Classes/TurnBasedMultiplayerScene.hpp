#pragma once

#include "BaseScene.h"

class TurnBasedMultiplayerScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(TurnBasedMultiplayerScene);

protected:

    virtual void onPrevScene(cocos2d::Ref *sender) override;

    virtual void onNextScene(cocos2d::Ref *sender) override;

    void CreateTurnBasedMatch(cocos2d::Ref *sender);
    void ShowMatchInboxUI(cocos2d::Ref *sender);
    void ShowPlayerSelectUI(cocos2d::Ref *sender);
    void AcceptInvitation(cocos2d::Ref *sender);
    void DeclineInvitation(cocos2d::Ref *sender);
    void DismissInvitation(cocos2d::Ref *sender);
    void DismissMatch(cocos2d::Ref *sender);
    void FetchMatch(cocos2d::Ref *sender);
    void TakeMyTurn(cocos2d::Ref *sender);
    void FinishMatchDuringMyTurn(cocos2d::Ref *sender);
    void Rematch(cocos2d::Ref *sender);
    void LeaveMatch(cocos2d::Ref *sender);
    void CancelMatch(cocos2d::Ref *sender);
    void FetchMatches(cocos2d::Ref *sender);
    
    void handleMatch(gpg::TurnBasedMatch match);
private:
    gpg::TurnBasedMatch _match;
    std::string _myId;
};


