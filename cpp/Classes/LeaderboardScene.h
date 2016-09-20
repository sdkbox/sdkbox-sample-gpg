#pragma once

#include "BaseScene.h"

class LeaderboardScene : public BaseScene {
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(LeaderboardScene);

protected:

    virtual void onPrevScene(cocos2d::Ref *sender) override;

    virtual void onNextScene(cocos2d::Ref *sender) override;

    void ldbFetch(cocos2d::Ref *sender);
    void ldbFetchAll(cocos2d::Ref *sender);
    void ldbFetchScorePage(cocos2d::Ref *sender);
    void ldbFetchNextScorePage(cocos2d::Ref *sender);
    void ldbFetchScoreSummary(cocos2d::Ref *sender);
    void ldbFetchScoreAllSummaries(cocos2d::Ref *sender);
    void ldbSubmitScore(cocos2d::Ref *sender);
    void ldbShowUI(cocos2d::Ref *sender);
    void ldbShowAllUI(cocos2d::Ref *sender);

    void __ldbFetchScorePageImpl( const gpg::ScorePage::ScorePageToken& token, int max_items, gpg::DataSource data_source);
};
