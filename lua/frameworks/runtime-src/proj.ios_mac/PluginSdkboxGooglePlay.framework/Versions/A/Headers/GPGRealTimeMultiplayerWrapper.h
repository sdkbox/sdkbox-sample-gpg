/****************************************************************************

 Copyright (c) 2014-2016 SDKBOX Inc

 ****************************************************************************/


#pragma once

#include <string>
#include "GPGConstants.h"

namespace sdkbox {
    
    class GPGRealTimeMultiplayerWrapper {
    public:
        
        /**
         *
         * str_json_params : {
         *     type : 'quick_match' | 'ui' | 'ui_custom',
         *     quick_match_params? : {
         *          minimumAutomatchingPlayers : number,
         *          maximumAutomatchingPlayers : number,
         *          exclusiveBitMask? :          number
         *     },
         *     ui_params? : {
         *          minimumPlayers : number,
         *          maximumPlayers : number
         *     }
         *
         * }
         */
        static void CreateRealTimeRoom( int callback_id, const std::string& str_json_params );
        
    };

}
