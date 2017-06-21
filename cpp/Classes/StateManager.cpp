/* Copyright (c) 2014 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "StateManager.h"

#ifdef __APPLE__
//
//Logging for CoreFoundation
//
#include <CoreFoundation/CoreFoundation.h>
extern "C" void NSLog(CFStringRef format, ...);
const int32_t BUFFER_SIZE = 256;
#define LOGI(...) {char c[BUFFER_SIZE];\
    snprintf(c,BUFFER_SIZE,__VA_ARGS__);\
    CFStringRef str = CFStringCreateWithCString(kCFAllocatorDefault, c, kCFStringEncodingMacRoman);\
    NSLog(str);\
    CFRelease(str);\
    }
#else
#include "android/log.h"
#define DEBUG_TAG "TeapotNativeActivity"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, DEBUG_TAG, __VA_ARGS__))

#endif

std::string StateManager::PlayerID = "";
std::string StateManager::PlayerName = "";
bool StateManager::isSignedIn = false;
gpg::GameServices::Builder::OnAuthActionFinishedCallback StateManager::_callback = nullptr;
std::unique_ptr<gpg::GameServices> StateManager::gameServices;

void OnAuthActionFinished(gpg::AuthOperation op, gpg::AuthStatus status) {
    LOGI("OnAuthActionFinished");
}

void OnAuthActionStarted(gpg::AuthOperation op) {
    LOGI("OnAuthActionStarted");
    switch (op) {
        case gpg::AuthOperation::SIGN_IN:
        LOGI("Signing In");
            break;
        case gpg::AuthOperation::SIGN_OUT:
        LOGI("Signing Out");
            break;
    }
}

gpg::GameServices *StateManager::GetGameServices() {
    return gameServices.get();
}

void StateManager::SignIn() {
    if (!gameServices->IsAuthorized()) {
        LOGI("StartAuthorizationUI");
        gameServices->StartAuthorizationUI();
    }
}

void StateManager::SignOut() {
    if (gameServices->IsAuthorized()) {
        LOGI("SignOut");
        gameServices->SignOut();
    }
}

void StateManager::UnlockAchievement(const char *achievementId) {
    if (gameServices->IsAuthorized()) {
        LOGI("Achievement unlocked");
        gameServices->Achievements().Unlock(achievementId);
    }
}

void StateManager::SubmitHighScore(const char *leaderboardId, uint64_t score) {
    if (gameServices->IsAuthorized()) {
        LOGI("High score submitted");
        gameServices->Leaderboards().SubmitScore(leaderboardId, score);
    }
}

void StateManager::ShowAchievements(){
    if (gameServices->IsAuthorized()) {
        LOGI("Show achievement");
        gameServices->Achievements().ShowAllUI([](gpg::UIStatus const &status) {
            LOGI("Achievement shown");
        });
    }
}

void StateManager::ShowLeaderboard(const char *leaderboardId){
    if (gameServices->IsAuthorized()) {
        LOGI("Show leaderboard");
        gameServices->Leaderboards().ShowUI(leaderboardId, [](gpg::UIStatus const &status) {
            LOGI("Leaderboard shown");
        });
    }
}

static std::string getStatusString(gpg::AuthStatus st) {
    switch (st) {
        case gpg::AuthStatus::VALID: return "VALID"; break;
        case gpg::AuthStatus::ERROR_INTERNAL: return "ERROR_INTERNAL"; break;
        case gpg::AuthStatus::ERROR_NOT_AUTHORIZED: return "ERROR_NOT_AUTHORIZED"; break;
        case gpg::AuthStatus::ERROR_VERSION_UPDATE_REQUIRED: return "ERROR_VERSION_UPDATE_REQUIRED"; break;
        case gpg::AuthStatus::ERROR_TIMEOUT: return "ERROR_TIMEOUT"; break;

#if 0 // 2.3
        case gpg::AuthStatus::ERROR_NO_DATA: return "ERROR_NO_DATA"; break;
        case gpg::AuthStatus::ERROR_NETWORK_OPERATION_FAILED: return "ERROR_NETWORK_OPERATION_FAILED"; break;
        case gpg::AuthStatus::ERROR_APP_MISCONFIGURED: return "ERROR_APP_MISCONFIGURED"; break;
        case gpg::AuthStatus::ERROR_GAME_NOT_FOUND: return "ERROR_GAME_NOT_FOUND"; break;
        case gpg::AuthStatus::ERROR_INTERRUPTED: return "ERROR_INTERRUPTED"; break;
#endif
    }
    return "Unknown";
}

void StateManager::Init(gpg::PlatformConfiguration &pc) {
    LOGI("Initializing Services");
    if (!gameServices)
    {
        LOGI("Uninitialized services, so creating");
        gameServices = gpg::GameServices::Builder()
                .SetOnAuthActionFinished([](gpg::AuthOperation op, gpg::AuthStatus status){
                    LOGI("Sign in finished with a result of (%s)", getStatusString(status).c_str());
                    if( status == gpg::AuthStatus::VALID ){
                        gameServices->Players().FetchSelf([=](gpg::PlayerManager::FetchSelfResponse const &response) {
                            if (gpg::IsSuccess(response.status)) {
                                PlayerID = response.data.Id();
                                PlayerName = response.data.Name();
                            }
                        });
                        isSignedIn = true;
                    }
                    else{
                        isSignedIn = false;
                    }
                    if(_callback)
                    {
                        _callback( op, status);
                    }
                } )
                .SetOnMultiplayerInvitationEvent([](gpg::MultiplayerEvent evt, std::string msg, gpg::MultiplayerInvitation inv){
                })
                .EnableSnapshots()
                .SetDefaultOnLog(gpg::LogLevel::VERBOSE)
                .Create(pc);
    }
    LOGI("Created");
}

void StateManager::setCallback(gpg::GameServices::Builder::OnAuthActionFinishedCallback cb)
{
    _callback = cb;
}
