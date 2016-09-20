
#pragma once

#include "BaseScene.h"
#include "json98.h"

#define MAX_SAVES 8
#define SAVE_GAME_NAME "GameSaveCPP"
#define SAVE_GAME_DESC "A game save of cocos2d-x game"

class SaveGameScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(SaveGameScene);

protected:
    virtual void onPrevScene(cocos2d::Ref *sender) override;

    virtual void onNextScene(cocos2d::Ref *sender) override;

    void onSave(cocos2d::Ref *sender);
    void onLoad(cocos2d::Ref *sender);
    void onManage(cocos2d::Ref *sender);
    void onList(cocos2d::Ref *sender);
    void onDelete(cocos2d::Ref *sender);

    void onAddCoin(cocos2d::Ref *sender);

    void loadSave(const std::string& filename);
    void createSave(const std::string& filename, const std::string &description, const std::string& content, gpg::SnapshotConflictPolicy conflict_policy);

    void updateStats();

    cocos2d::Label* _hero_name;
    cocos2d::Label* _hero_level;
    cocos2d::Label* _hero_gold;
    json98::Json _game_data;
};