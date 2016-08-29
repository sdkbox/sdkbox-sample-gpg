/****************************************************************************

 Copyright (c) 2014-2016 SDKBOX Inc

 ****************************************************************************/


#ifndef _SDKBOX_GPG_WRAPPED_OBJECT_
#define _SDKBOX_GPG_WRAPPED_OBJECT_

#include <string>
#include "GPGConstants.h"

/**
 * (ibon) TODO:
 * need to keep this classes separated because they automatically wrapped by bindings.
 * if i keep them in PluginSdkboxGooglePlay.h, the bidingins generator will fail. 
 * I can then instrument the bindings config to read this file.
 */

namespace sdkbox {
    class GPGWrapper
    {
    public:
        
        /**
         * options : json representation of the builder object options.
         */
        static void CreateGameServices( const std::string& json );
        static bool IsAuthorized();
        static void StartAuthorizationUI();
        static void SignOut();
        
        /**
         * Must be implemented per scripting language and native as empty function.
         * For js it is implemented in js/manual/PluginSdkboxGooglePlayJSHelper.cpp
         */
        static void NotifyToScripting( int id, const std::string& str_json );
    };

    class GPGLocalPlayerWrapper {
    public:
        
        static void Fetch( int id );
        static std::string AvatarUrl( int image_resolution );
        static std::string Name();
        static std::string Id();
        static bool HasLevelInfo();
        static int64_t CurrentXP();
        static int64_t LastLevelUpTime();
        static std::string Title();
        static std::string CurrentLevel();
        static std::string NextLevel();
    };
    
    class GPGSnapshotWrapper {
    public:
        
        /**
         * @param str_json  {
         *   allow_create : bool,
         *   allow_delete : bool,
         *   max_snapshots: number,
         *   title        : string
         * }
         */
        static void ShowSelectUIOperation( int callback_id, const std::string& str_json );
        static void Load( int callback_id, const std::string& filename, int snapshot_conflict_policy, int datasource );
        static void Save( int callback_id, const std::string& str_json );
        static void FetchAll( int callback_id, const std::string& str_json );
        static void Delete( int callback_id, const std::string& filename );
    };

    class GPGQuestsWrapper
    {
    public:

        static void Fetch          (int callback_id, const std::string& quest_id, int datasource = 1);
        static void FetchList      (int callback_id, int datasource = 1);
        static void Accept         (int callback_id, const std::string& quest_id);
        static void ClaimMilestone (int callback_id, const std::string& milestone_id);
        static void ShowAllUI      (int callback_id);
		static void ShowUI         (int callback_id, const std::string& quest_id);
    };

    class GPGEventsWrapper
    {
    public:

        static void Fetch     (int callback_id, const std::string& event_id, int datasource = 1);
        static void FetchAll  (int callback_id, int datasource = 1);
        static void Increment (const std::string& event_id, uint32_t steps = 1);
    };
}

#endif