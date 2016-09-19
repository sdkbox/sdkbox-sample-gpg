#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <cocos/ui/UIButton.h>
#include "cocos2d.h"
#include "PluginSdkboxGooglePlay/PluginSdkboxGooglePlay.h"

class BaseScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;

    // implement the "static create()" method manually
    CREATE_FUNC(BaseScene);
    
    void updateConnectionStatus();
    
protected:
    gpg::GameServices* _game_services;

    cocos2d::Label * _txtStat;
    cocos2d::Label * _txtConnection;
    cocos2d::Label * _txtTitle;
    cocos2d::MenuItemFont* _menu_item_connect;
    cocos2d::ui::Button* _btn_nextScene;
    cocos2d::ui::Button* _btn_prevScene;

    void setTitle(const std::string& title);
    void onConnect(cocos2d::Ref *sender);
    virtual void onPrevScene(cocos2d::Ref *sender) {};
    virtual void onNextScene(cocos2d::Ref *sender) {};

    void initGPG();
};

#endif // __HELLOWORLD_SCENE_H__
