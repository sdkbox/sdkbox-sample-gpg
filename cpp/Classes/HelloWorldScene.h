#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PluginSdkboxGooglePlay/PluginSdkboxGooglePlay.h"

class HelloWorld : public cocos2d::Layer
{
protected:
    cocos2d::Label * _txtStat;
    cocos2d::Label * _txtC;
    
    cocos2d::MenuItemFont* _menu_item_connect;
    
    void __initGPG();
    void __loadGameContents( const std::string& filename );
    void __createGame( const std::string& filename,
                       const std::string& description,
                       std::vector<uint8_t> data,
                       gpg::SnapshotConflictPolicy conflict_policy );
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void runtests(int fd, const std::string& args);

    void connect(cocos2d::CCObject *sender);
    void showSnapshotUI( cocos2d::CCObject* sender );
    void fetchAllSnapshotGames( cocos2d::CCObject* sender );
    void deleteSnapshotGame( cocos2d::CCObject* sender );
    
    /// leaderboards
    
    void ldbFetch(cocos2d::CCObject *sender);
    void ldbFetchAll(cocos2d::CCObject *sender);
    
    void __ldbFetchScorePageImpl( const gpg::ScorePage::ScorePageToken& token, int max_items, gpg::DataSource data_source);
    void ldbFetchScorePage(cocos2d::CCObject *sender);
    void ldbFetchNextScorePage(cocos2d::CCObject *sender);
    void ldbFetchScoreSummary(cocos2d::CCObject *sender);
    void ldbFetchScoreAllSummaries(cocos2d::CCObject *sender);
    void ldbSubmitScore(cocos2d::CCObject *sender);
    void ldbShowUI(cocos2d::CCObject *sender);
    void ldbShowAllUI(cocos2d::CCObject *sender);
};

#endif // __HELLOWORLD_SCENE_H__
