#pragma once

#include "BaseScene.h"

class QuestScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(QuestScene);

protected:
    
    int _currQuestNodeY;
    std::vector<gpg::Quest> _questData;
    cocos2d::Node* _questNode;
    
    void updateQuests(const std::vector<gpg::Quest>& data);

    virtual void onPrevScene(cocos2d::Ref *sender) override;

    virtual void onNextScene(cocos2d::Ref *sender) override;

    void Fetch(cocos2d::Ref *sender);
    void FetchList(cocos2d::Ref *sender);
    void Accept(cocos2d::Ref *sender);
    void ClaimMilestone(cocos2d::Ref *sender);
    void ShowAllUI(cocos2d::Ref *sender);
    void ShowUI(cocos2d::Ref *sender);
};


