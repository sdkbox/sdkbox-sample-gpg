#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "gpg/achievement.h"
#include "gpg/achievement_manager.h"
#include "gpg/game_services.h"
#include "gpg/leaderboard.h"
#include "gpg/leaderboard_manager.h"
#include "gpg/player_manager.h"
#include "gpg/types.h"
#include "gpg/builder.h"
#include "gpg/debug.h"
#include "gpg/default_callbacks.h"
#include "gpg/leaderboard_manager.h"
#include "gpg/platform_configuration.h"
#include "gpg/player_manager.h"
#include "gpg/score_page.h"



class StateManager {

public:
    static void Init(gpg::PlatformConfiguration &pc);
    static void setCallback(gpg::GameServices::Builder::OnAuthActionFinishedCallback cb);
    static gpg::GameServices *GetGameServices();
    static void SignIn();
    static void SignOut();
    static void UnlockAchievement(const char *achievementId);
    static void SubmitHighScore(const char *leaderboardId, uint64_t score);
    static void ShowAchievements();
    static void ShowLeaderboard(const char *leaderboardId);
    static bool IsSignedIn() { return isSignedIn; }
private:
    static bool isSignedIn;
    static std::unique_ptr<gpg::GameServices> gameServices;
    static gpg::GameServices::Builder::OnAuthActionFinishedCallback _callback;
};


#endif // STATE_MANAGER_HPP