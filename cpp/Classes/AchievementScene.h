#pragma once

#include "BaseScene.h"

class AchievementScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(AchievementScene);

protected:

    virtual void onPrevScene(cocos2d::Ref *sender) override;

    virtual void onNextScene(cocos2d::Ref *sender) override;

    void achShowAllUI(cocos2d::Ref *sender);
    void achFetchAll(cocos2d::Ref *sender);
    void achFetch(cocos2d::Ref *sender);
    void achUnlock(cocos2d::Ref *sender);
    void achIncrement(cocos2d::Ref *sender);
    void achReveal(cocos2d::Ref *sender);
    void achSetAtLeastSteps(cocos2d::Ref *sender);
};
