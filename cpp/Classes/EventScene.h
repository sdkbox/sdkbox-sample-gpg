#pragma once

#include "BaseScene.h"

class EventScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(EventScene);

protected:

    virtual void onPrevScene(cocos2d::Ref *sender) override;

    virtual void onNextScene(cocos2d::Ref *sender) override;
    
    void Fetch(cocos2d::Ref *sender);
    void FetchAll(cocos2d::Ref *sender);
    void Increment(cocos2d::Ref *sender);
};


