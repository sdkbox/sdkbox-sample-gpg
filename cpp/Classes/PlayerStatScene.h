#pragma once

#include "BaseScene.h"

class PlayerStatScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(PlayerStatScene);

protected:

    virtual void onPrevScene(cocos2d::Ref *sender) override;

    virtual void onNextScene(cocos2d::Ref *sender) override;

    void FetchForPlayer(cocos2d::Ref *sender);
};

