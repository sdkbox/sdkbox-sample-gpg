
if not json then
    require "cocos.cocos2d.json"
end
require "cocos.cocos2d.functions"

--
-- Constants
--

local P_DATA_SOURCE = 'data_source'

local P_SNP_CONFLICT_POLICY = 'conflict_policy'
local P_SNP_TITLE = 'title'
local P_SNP_FILE_NAME = 'filename'
local P_SNP_DESCRIPTION = 'description'
local P_SNP_PAGE_SIZE = 10

local P_LDB_ORDER= 'order'
local P_LDB_COLLECTION= 'collection'
local P_LDB_START= 'start'
local P_LDB_TIME_SPAN= 'time_span'
local P_LDB_METADATA= 'metadata'
local P_LDB_SCORE_PAGE_SIZE= 'max_items'

function __log(message)
    print(message)
end

function __dp(params, fields)
    if params == nil then
        error('setting def params in undefined object.')
    end
    for i, f in ipairs(fields) do
        __dp1(params, f)
    end
end

function __dp1(params, f)
    local function switch(n, ...)
      for _,v in ipairs {...} do
        if v[1] == n or v[1] == nil then
          return v[2]()
        end
      end
    end
    local function case(n,f)
      return {n,f}
    end
    local function default(f)
      return {nil,f}
    end
    switch (f,
        case (P_DATA_SOURCE, function()
            params[P_DATA_SOURCE] = params[P_DATA_SOURCE] or gpg.DataSource.CACHE_OR_NETWORK
        end),
        case (P_SNP_CONFLICT_POLICY, function()
            params[P_SNP_CONFLICT_POLICY] = params[P_SNP_CONFLICT_POLICY] or gpg.SnapshotConflictPolicy.DefaultConflictPolicy
        end),
        case (P_SNP_TITLE, function()
           params[P_SNP_TITLE] = params[P_SNP_TITLE] or 'title'
        end),
        case (P_SNP_DESCRIPTION, function()
           params[P_SNP_DESCRIPTION] = params[P_SNP_DESCRIPTION] or 'Default game description'
        end),
        case (P_SNP_PAGE_SIZE, function()
           params[P_SNP_PAGE_SIZE] = params[P_SNP_PAGE_SIZE] or 10
        end),
        case (P_LDB_COLLECTION, function()
            params[P_LDB_COLLECTION] = params[P_LDB_COLLECTION] or gpg.LeaderboardCollection.PUBLIC
        end),
        case (P_LDB_ORDER, function()
            params[P_LDB_ORDER] = params[P_LDB_ORDER] or gpg.LeaderboardOrder.LARGER_IS_BETTER
        end),
        case (P_LDB_START, function()
            params[P_LDB_START] = params[P_LDB_START] or gpg.LeaderboardStart.TOP_SCORES
        end),
        case (P_LDB_TIME_SPAN, function()
            params[P_LDB_TIME_SPAN] = params[P_LDB_TIME_SPAN] or gpg.LeaderboardTimeSpan.ALL_TIME
        end),
        case (P_LDB_METADATA, function()
            params[P_LDB_METADATA] = params[P_LDB_METADATA] or ''
        end),
        case (P_LDB_SCORE_PAGE_SIZE, function()
            params[P_LDB_SCORE_PAGE_SIZE] = params[P_LDB_SCORE_PAGE_SIZE] or 10
        end)
   )
end

local BaseStatus = {
    VALID = 1,
    VALID_BUT_STALE = 2,
    VALID_WITH_CONFLICT = 3,
    FLUSHED = 4,
    ERROR_LICENSE_CHECK_FAILED = -1,
    ERROR_INTERNAL = -2,
    ERROR_NOT_AUTHORIZED = -3,
    ERROR_VERSION_UPDATE_REQUIRED = -4,
    ERROR_TIMEOUT = -5,
    ERROR_CANCELED = -6,
    ERROR_MATCH_ALREADY_REMATCHED = -7,
    ERROR_INACTIVE_MATCH = -8,
    ERROR_INVALID_RESULTS = -9,
    ERROR_INVALID_MATCH = -10,
    ERROR_MATCH_OUT_OF_DATE = -11,
    ERROR_UI_BUSY = -12,
    ERROR_QUEST_NO_LONGER_AVAILABLE = -13,
    ERROR_QUEST_NOT_STARTED = -14,
    ERROR_MILESTONE_ALREADY_CLAIMED = -15,
    ERROR_MILESTONE_CLAIM_FAILED = -16,
    ERROR_REAL_TIME_ROOM_NOT_JOINED = -17,
    ERROR_LEFT_ROOM = -18
}

--
-- Google Play Services API
--

local gpg = {
    CallbackManager = {
        _id_index=1000,
        _callbacks={}
    },
    Quests = {},
    Events = {},
    Stats  = {},
    Achievements = {},
    Leaderboards = {},
    Snapshots = {},
    Realtime = {},
    Turnbased = {}
}

gpg.LeaderboardOrder = {
    LARGER_IS_BETTER = 1,
    SMALLER_IS_BETTER = 2,
    INVALID = -1
}

gpg.LeaderboardStart = {
    TOP_SCORES = 1,
    PLAYER_CENTERED = 2,
    INVALID = -1
}

gpg.LeaderboardTimeSpan = {
    DAILY = 1,
    WEEKLY = 2,
    ALL_TIME = 3,
    INVALID = -1
}

gpg.LeaderboardCollection = {
    PUBLIC = 1,
    SOCIAL = 2,
    INVALID = -1
}

gpg.AchievementType = {
    STANDARD = 1,
    INCREMENTAL = 2,
    INVALID = -1
}

gpg.AchievementState = {
    HIDDEN = 1,
    REVEALED = 2,
    UNLOCKED = 3,
    INVALID = -1
}

gpg.QuestFetchFlags = {
    UPCOMING    = 1,   -- 1 << 0,
    OPEN        = 2,   -- 1 << 1,
    ACCEPTED    = 4,   -- 1 << 2,
    COMPLETED   = 8,   -- 1 << 3,
    COMPLETED_NOT_CLAIMED = 16, -- 1 << 4,
    EXPIRED     = 32,  -- 1 << 5,
    ENDING_SOON = 64,  -- 1 << 6,
    FAILED      = 128, -- 1 << 7,
    ALL         = 255  -- -1
}

gpg.QuestState = {
    UPCOMING  = 1,
    OPEN      = 2,
    ACCEPTED  = 3,
    COMPLETED = 4,
    EXPIRED   = 5,
    FAILED    = 6,
    INVALID   = -1
}

gpg.QuestMilestoneState = {
    NOT_STARTED = 1, -- Note that this value is new in v1.2.
    NOT_COMPLETED = 2,
    COMPLETED_NOT_CLAIMED = 3,
    CLAIMED = 4,
    INVALID = -1
}

gpg.DefaultCallbacks = {
    DEFAULT_CALLBACKS_BEGIN = 1,
    AUTH_ACTION_STARTED = 1,
    AUTH_ACTION_FINISHED = 2,

    RTMP_ROOM_STATUS_CHANGED = 3,
    RTMP_CONNECTED_SET_CHANGED = 4,
    RTMP_P2P_CONNECTED = 5,
    RTMP_P2P_DISCONNECTED = 6,
    RTMP_PARTICIPANT_STATUS_CHANGED = 7,
    RTMP_DATA_RECEIVED = 8,

    TURN_BASED_MATCH_EVENT = 9,
    MULTIPLAYER_INVITATION_EVENT = 10,

    DEFAULT_CALLBACKS_END = 10
}

gpg.ResponseStatus = {
    VALID = BaseStatus.VALID,
    VALID_BUT_STALE = BaseStatus.VALID_BUT_STALE,
    ERROR_LICENSE_CHECK_FAILED = BaseStatus.ERROR_LICENSE_CHECK_FAILED,
    ERROR_INTERNAL = BaseStatus.ERROR_INTERNAL,
    ERROR_NOT_AUTHORIZED = BaseStatus.ERROR_NOT_AUTHORIZED,
    ERROR_VERSION_UPDATE_REQUIRED = BaseStatus.ERROR_VERSION_UPDATE_REQUIRED,
    ERROR_TIMEOUT = BaseStatus.ERROR_TIMEOUT
}

gpg.DataSource = {
    CACHE_OR_NETWORK = 1,
    NETWORK_ONLY = 2
}

gpg.AuthOperation = {
    SIGN_IN = 1,
    SIGN_OUT = 2
}

gpg.AuthStatus = {
    VALID = BaseStatus.VALID,
    ERROR_INTERNAL = BaseStatus.ERROR_INTERNAL,
    ERROR_NOT_AUTHORIZED = BaseStatus.ERROR_NOT_AUTHORIZED,
    ERROR_VERSION_UPDATE_REQUIRED = BaseStatus.ERROR_VERSION_UPDATE_REQUIRED,
    ERROR_TIMEOUT = BaseStatus.ERROR_TIMEOUT
}

gpg.LogLevel = {
    VERBOSE = 1,
    INFO = 2,
    WARNING = 3,
    ERROR = 4
}

gpg.ImageResolution = {
    ICON = 1,
    HI_RES = 2
}

gpg.SnapshotConflictPolicy = {
    MANUAL = 1,
    LONGEST_PLAYTIME = 2,
    LAST_KNOWN_GOOD = 3,
    MOST_RECENTLY_MODIFIED = 4,
    HIGHEST_PROGRESS = 5,
    DefaultConflictPolicy = 4
}

gpg.MatchStatus = {
  INVITED = 1,
  THEIR_TURN = 2,
  MY_TURN = 3,
  PENDING_COMPLETION = 4,
  COMPLETED = 5,
  CANCELED = 6,
  EXPIRED = 7
}

gpg.MatchResult = {
  DISAGREED = 1,
  DISCONNECTED = 2,
  LOSS = 3,
  NONE = 4,
  TIE = 5,
  WIN = 6
}

function gpg:CreateGameServices(config, start_callback, finished_callback)
    if start_callback ~= nil then
        gpg.CallbackManager:addCallbackById(gpg.DefaultCallbacks.AUTH_ACTION_STARTED,  start_callback)
    end
    if finished_callback ~= nil then
        gpg.CallbackManager:addCallbackById(gpg.DefaultCallbacks.AUTH_ACTION_FINISHED, finished_callback)
    end
    local cb = gpg.CallbackManager:addCallback(function(result)
        __log("CreateGameServices "..result)
    end)
    __log("About to CreateGameServices")
    sdkbox.GPGWrapper:CreateGameServices(cb, json.encode(config))
end

function gpg:StartAuthorizationUI()
    sdkbox.GPGWrapper:StartAuthorizationUI()
end

function gpg:SignOut()
    sdkbox.GPGWrapper:SignOut()
end

function gpg:IsSuccess(response_status)
    if response_status == self.ResponseStatus.VALID or response_status == self.ResponseStatus.VALID_BUT_STALE then
        return true
    end
    return false
end

--
-- Callback Manager
--

function gpg.CallbackManager:__nextIndex()
    local i = self._id_index
    self._id_index = i + 1
    return i
end

function gpg.CallbackManager:addCallbackById(id, callback)
    if (self._callbacks[id] == nil) then
        self._callbacks[id] = callback
    end
end

function gpg.CallbackManager:removeCallbackById(id)
    if (self._callbacks[id] ~= nil) then
        self._callbacks[id] = nil
    end
end

function gpg.CallbackManager:addCallback(callback)
    local index = self:__nextIndex()
    self:addCallbackById(index, callback)
    return index
end

function gpg.CallbackManager:nativeNotify(id, str_json)

    if (self._callbacks[id]) then

        local o = json.decode(str_json)

        local cb = self._callbacks[id]
        if type(cb) == 'function' then
            cb(o)
        else
            local this = cb[1]
            local func = cb[2]
            func(this, o)
        end

    end

    -- callbacks that are temporary one shot calls have to be removed.
    if (id >= 1000) then
        self._callbacks[id] = nil
        __log("Removed " .. id)
    end
end

function fixUTF8(s, replacement)
    local p, len, invalid = 1, #s, {}
    while p <= len do
        if     p == s:find("[%z\1-\127]", p) then p = p + 1
        elseif p == s:find("[\194-\223][\128-\191]", p) then p = p + 2
        elseif p == s:find(      "\224[\160-\191][\128-\191]", p)
            or p == s:find("[\225-\236][\128-\191][\128-\191]", p)
            or p == s:find(      "\237[\128-\159][\128-\191]", p)
            or p == s:find("[\238-\239][\128-\191][\128-\191]", p) then p = p + 3
        elseif p == s:find(      "\240[\144-\191][\128-\191][\128-\191]", p)
            or p == s:find("[\241-\243][\128-\191][\128-\191][\128-\191]", p)
            or p == s:find(      "\244[\128-\143][\128-\191][\128-\191]", p) then p = p + 4
        else
            s = s:sub(1, p-1)..replacement..s:sub(p+1)
            table.insert(invalid, p)
        end
    end
    return s, invalid
end

function cc.exports.__nativeNotify(id, str_json)
    local json, invalid = fixUTF8(str_json, " ")
    gpg.CallbackManager:nativeNotify(id, json)
end

--
-- Quests API
--

function gpg.Quests:Fetch(quest_id, callback)
    sdkbox.GPGQuestsWrapper:Fetch(gpg.CallbackManager:addCallback(callback), quest_id)
end

function gpg.Quests:ShowAllUI(callback)
    sdkbox.GPGQuestsWrapper:ShowAllUI(gpg.CallbackManager:addCallback(callback))
end

function gpg.Quests:ShowUI(quest_id, callback)
    sdkbox.GPGQuestsWrapper:ShowUI(gpg.CallbackManager:addCallback(callback), quest_id)
end

function gpg.Quests:FetchList(callback)
    --sdkbox.GPGQuestsWrapper:FetchList(gpg.CallbackManager:addCallback(callback))
end

function gpg.Quests:Accept(quest_id, callback)
    sdkbox.GPGQuestsWrapper:Accept(gpg.CallbackManager:addCallback(callback), quest_id)
end

function gpg.Quests:ClaimMilestone(milestone_id, callback)
    sdkbox.GPGQuestsWrapper:ClaimMilestone(gpg.CallbackManager:addCallback(callback), milestone_id)
end

--
-- Events API
--

function gpg.Events:Fetch(event_id, callback)
    sdkbox.GPGEventsWrapper:Fetch(gpg.CallbackManager:addCallback(callback), event_id)
end

function gpg.Events:FetchAll(callback)
    sdkbox.GPGEventsWrapper:Fetch(gpg.CallbackManager:addCallback(callback))
end

function gpg.Events:Increment(event_id)
    sdkbox.GPGEventsWrapper:Increment(event_id)
end

--
-- Stats API
--

function gpg.Stats:FetchForPlayer(callback)
    sdkbox.GPGStatsWrapper:FetchForPlayer(gpg.CallbackManager:addCallback(callback), 1)
end

--
-- Snapshots API
--

function gpg.Snapshots:ShowSelectUIOperation(allow_create, allow_delete, max_snapshots, title, callback)
    if title == nil then
        __log("error ShowSelectUIOperation : title is not specified")
        return
    end
    if max_snapshots == nil then
        __log("error ShowSelectUIOperation : max_snapshots is not specified")
        return
    end
    allow_create = allow_create or false
    allow_delete = allow_delete or false
    local params = {
        allow_create = allow_create,
        allow_delete = allow_delete,
        max_snapshots = max_snapshots,
        title = title
    }
    __dp(params, {P_SNP_TITLE, P_SNP_PAGE_SIZE})
    sdkbox.GPGSnapshotWrapper:ShowSelectUIOperation(gpg.CallbackManager:addCallback(callback), json.encode(params))
end

function gpg.Snapshots:Load(filename, conflict_policy, data_source, callback)
    if filename == nil then
        __log("error Load : filename is not specified")
        return
    end
    conflict_policy = conflict_policy or gpg.SnapshotConflictPolicy.DefaultConflictPolicy
    data_source = data_source or gpg.DataSource.CACHE_OR_NETWORK
    sdkbox.GPGSnapshotWrapper:Load(gpg.CallbackManager:addCallback(callback), filename, conflict_policy, data_source)
end

function gpg.Snapshots:Save(filename, conflict_policy, description, data, callback)
    if filename == nil then
        __log("error Save : filename is not specified")
        return
    end
    if data == nil then
        __log("error Save : data is not specified")
        return
    end
    description = description or P_SNP_DESCRIPTION
    conflict_policy = conflict_policy or gpg.SnapshotConflictPolicy.DefaultConflictPolicy
    local params = {
        filename = filename,
        conflict_policy = conflict_policy,
        description = description,
        data = data
    }
    __dp(params, {P_SNP_CONFLICT_POLICY, P_SNP_DESCRIPTION})
    sdkbox.GPGSnapshotWrapper:Save(gpg.CallbackManager:addCallback(callback), json.encode(params))
end

function gpg.Snapshots:FetchAll(data_source, callback)
    local params = {data_source}
    __dp(params, {P_DATA_SOURCE})
    sdkbox.GPGSnapshotWrapper:FetchAll(gpg.CallbackManager:addCallback(callback), json.encode(params))
end

function gpg.Snapshots:Delete(filename, callback)
    if filename == nil then
        __log("error Delete : filename not specified")
        return
    end
    sdkbox.GPGSnapshotWrapper:Delete(gpg.CallbackManager:addCallback(callback), filename)
end

--
-- Leaderboards API
--

function gpg.Leaderboards:Fetch(leaderboard_id, data_source, callback)
    if leaderboard_id == nil then
        __log("error Fetch : leaderboard_id not specified")
        return
    end
    local params = {
        data_source = data_source
    }
    __dp(params, {P_DATA_SOURCE})
    sdkbox.GPGLeaderboardWrapper:Fetch(gpg.CallbackManager:addCallback(callback), leaderboard_id, data_source)
end

function gpg.Leaderboards:FetchAll(data_source, callback)
    local params = {
        data_source = data_source
    }
    __dp(params, {P_DATA_SOURCE})
    sdkbox.GPGLeaderboardWrapper:FetchAll(gpg.CallbackManager:addCallback(callback), data_source)
end

function gpg.Leaderboards:FetchScoreSummary(leaderboard_id, data_source, time_span, collection, callback)
    if leaderboard_id == nil then
        __log("error FetchScoreSummary : leaderboard_id not specified")
        return
    end
    local params = {
        data_source = data_source,
        collection = collection,
        time_span = time_span
    }
    __dp(params, {P_DATA_SOURCE, P_LDB_COLLECTION, P_LDB_TIME_SPAN})
    sdkbox.GPGLeaderboardWrapper:FetchAll(gpg.CallbackManager:addCallback(callback), params.data_source, params.leaderboard_id, params.timeSpan, params.collection)
end

function gpg.Leaderboards:FetchAllScoreSummaries(leaderboard_id, data_source, callback)
    if leaderboard_id == nill then
        __log("error FetchAllScoreSumarries : leaderboard_id not specified")
        return
    end
    local params = {
        data_source = data_source
    }
    __dp(params, {P_DATA_SOURCE})
    sdkbox.GPGLeaderboardWrapper:FetchAllScoreSummaries(gpg.CallbackManager:addCallback(callback), params.data_source, leaderboard_id)
end

function gpg.Leaderboards:SubmitScore(leaderboard_id, score, metadata, callback)
    if leaderboard_id == nil or score == nil then
        __log("error SubmitScore : leaderboard_id and score cannot be nil")
        return
    end
    local params = {
        metadata = metadata
    }
    __dp(params, {P_LDB_METADATA})
    sdkbox.GPGLeaderboardWrapper:SubmitScore(gpg.CallbackManager:addCallback(callback), params.leaderboard_id, params.score, params.metadata)
end

function gpg.Leaderboards:ShowUI(leaderboard_id, callback)
    sdkbox.GPGLeaderboardWrapper:ShowUI(gpg.CallbackManager:addCallback(callback), leaderboard_id)
end

function gpg.Leaderboards:ShowAllUI(callback)
    sdkbox.GPGLeaderboardWrapper:ShowAllUI(gpg.CallbackManager:addCallback(callback))
end

function gpg.Leaderboards:FetchScorePage(leaderboard_id, data_source, start, time_span, collection, max_items, callback)
    if leaderboard_id == nil then
        __log("error FetchScorePage : leaderboard_id not specified")
        return
    end
    local params = {
        data_source = data_source,
        start = start,
        time_span = time_span,
        collection = collection,
        max_items = max_items
    }
    __dp(params, {P_DATA_SOURCE, P_LDB_START, P_LDB_TIME_SPAN, P_LDB_COLLECTION, P_LDB_SCORE_PAGE_SIZE})
    sdkbox.GPGLeaderboardWrapper:FetchScorePage(gpg.CallbackManager:addCallback(callback), params.leaderboard_id, params.data_source, params.start, params.time_span, params.collection, params.max_items)
end

function gpg.Leaderboards:FetchNextScorePage(data_source, max_items, callback)
    local params = {
        data_source = data_source,
        max_items = max_items
    }
    __dp(params, {P_DATA_SOURCE, P_LDB_SCORE_PAGE_SIZE})
    sdkbox.GPGLeaderboardWrapper:FetchNextScorePage(gpg.CallbackManager:addCallback(callback), params.data_source, params.max_items)
end

function gpg.Leaderboards:FetchPreviousScorePage(data_source, max_items, callback)
    local params = {
        data_source = data_source,
        max_items = max_items
    }
    __dp(params, {P_DATA_SOURCE, P_LDB_SCORE_PAGE_SIZE})
    sdkbox.GPGLeaderboardWrapper:FetchPreviousScorePage(gpg.CallbackManager:addCallback(callback), params.data_source, params.max_items)
end

--
-- Achievements API
--

function gpg.Achievements:Fetch(achievement_id, data_source, callback)
    local params = {
        data_source
    }
    __dp(params, {P_DATA_SOURCE})
    sdkbox.GPGAchievementWrapper:Fetch(gpg.CallbackManager:addCallback(callback), achievement_id, params.data_source)
end

function gpg.Achievements:FetchAll(data_source, callback)
    sdkbox.GPGAchievementWrapper:FetchAll(gpg.CallbackManager:addCallback(callback), data_source)
end

function gpg.Achievements:ShowAllUI()
    sdkbox.GPGAchievementWrapper:ShowAllUI(gpg.CallbackManager:addCallback(callback))
end

function gpg.Achievements:Increment(achievement_id, increment)
    increment = increment or 1
    sdkbox.GPGAchievementWrapper:Increment(achievement_id, increment)
end

function gpg.Achievements:SetStepsAtLeast(achievement_id, increment)
    increment = increment or 1
    sdkbox.GPGAchievementWrapper:SetStepsAtLeast(achievement_id, increment)
end

function gpg.Achievements:Reveal()
    sdkbox.GPGAchievementWrapper:Reveal(achievement_id)
end

function gpg.Achievements:Unlock()
    sdkbox.GPGAchievementWrapper:Unlock(achievement_id)
end

--
-- Turn Based Multiplayer
--

function gpg.Turnbased:CreateTurnBasedMatch(params, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:CreateTurnBasedMatch(gpg.CallbackManager:addCallback(callback), json.encode(params))
end

function gpg.Turnbased:DismissMatch(match_id)
    sdkbox.GPGTurnBasedMultiplayerWrapper:DismissMatch(match_id)
end

function gpg.Turnbased:FetchMatch(match_id, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:FetchMatch(gpg.CallbackManager:addCallback(callback), match_id)
end

function gpg.Turnbased:Rematch(match_id, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:Rematch(gpg.CallbackManager:addCallback(callback), match_id)
end

function gpg.Turnbased:CancelMatch(match_id, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:CancelMatch(gpg.CallbackManager:addCallback(callback), match_id)
end

function gpg.Turnbased:FetchMatches(callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:FetchMatches(gpg.CallbackManager:addCallback(callback))
end

function gpg.Turnbased:ShowMatchInboxUI(callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:ShowMatchInboxUI(gpg.CallbackManager:addCallback(callback))
end

function gpg.Turnbased:TakeMyTurn(match_id, participant_results_id, next_participant_id, data, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:TakeMyTurn(gpg.CallbackManager:addCallback(callback), match_id, participant_results_id, next_participant_id, data)
end

function gpg.Turnbased:FinishMatchDuringMyTurn(match_id, participant_results_id, data, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:FinishMatchDuringMyTurn(gpg.CallbackManager:addCallback(callback), match_id, participant_results_id, data)
end

function gpg.Turnbased:ConfirmPendingCompletion(match_id, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:ConfirmPendingCompletion(gpg.CallbackManager:addCallback(callback), match_id)
end

function gpg.Turnbased:LeaveMatchDuringTheirTurn(match_id, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:LeaveMatchDuringTheirTurn(gpg.CallbackManager:addCallback(callback), match_id)
end

function gpg.Turnbased:LeaveMatchDuringMyTurn(match_id, next_participant_id, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:LeaveMatchDuringMyTurn(gpg.CallbackManager:addCallback(callback), match_id, next_participant_id)
end

function gpg.Turnbased:AcceptInvitation(invitation_id, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:AcceptInvitation(gpg.CallbackManager:addCallback(callback), invitation_id)
end

function gpg.Turnbased:DeclineInvitation(invitation_id)
    sdkbox.GPGTurnBasedMultiplayerWrapper:DeclineInvitation(invitation_id)
end

function gpg.Turnbased:DismissInvitation(invitation_id)
    sdkbox.GPGTurnBasedMultiplayerWrapper:DismissInvitation(invitation_id)
end

function gpg.Turnbased:SynchronizeData()
    sdkbox.GPGTurnBasedMultiplayerWrapper:SynchronizeData()
end

function gpg.Turnbased:ShowPlayerSelectUI(min_players, max_players, allow_automatch, callback)
    sdkbox.GPGTurnBasedMultiplayerWrapper:ShowPlayerSelectUI(gpg.CallbackManager:addCallback(callback), min_players, max_players, allow_rematch)
end

function gpg.Turnbased:addMatchEventCallback(id, callback)
    if callback then
        gpg.CallbackManager:addCallbackById(id, callback)
    else
        gpg.CallbackManager:removeCallbackById(id, callback)
    end
end

function gpg.Turnbased:createParticipantResult(match_id, participant_id, placement, matchResult)
    local result_str = sdkbox.GPGTurnBasedMultiplayerWrapper:CreateParticipantResult(match_id, participant_id, placement, matchResult)
    return json.decode(result_str)
end

--
-- Realtime Multiplayer
--

gpg.Realtime._room_info = {
    room     = nil,
    listener = nil
}

function gpg.Realtime.__setRoomInfo(room, listener)

    local function __getDescriptor(room)
        gpg.Realtime._room_info.room = room
        return gpg.Realtime._room_info
    end
    
    gpg.CallbackManager:addCallbackById(DefaultCallbacks.RTMP_ROOM_STATUS_CHANGED,

        function(room)

            local descriptor = __getDescriptor(room)
            if (descriptor.listener) then
                descriptor.listener.onRoomStatusChanged(room)
            end
        end)

    gpg.CallbackManager:addCallbackById(DefaultCallbacks.RTMP_CONNECTED_SET_CHANGED,

        function(room)

            local descriptor = __getDescriptor(room)
            if (descriptor.listener) then
                descriptor.listener.onConnectedSetChanged(room)
            end
        end)

    gpg.CallbackManager:addCallbackById(DefaultCallbacks.RTMP_P2P_CONNECTED,
        function(result)

            local descriptor = __getDescriptor(result.room)
            if (descriptor.listener) then
                descriptor.listener.onP2PConnected(result.room, result.participant)
            end
        end)

    gpg.CallbackManager:addCallbackById(DefaultCallbacks.RTMP_P2P_DISCONNECTED,
        function(result)

            local descriptor = __getDescriptor(result.room)
            if (descriptor.listener) then
                descriptor.listener.onP2PDisconnected(result.room, result.participant)
            end
        end)

    gpg.CallbackManager:addCallbackById(DefaultCallbacks.RTMP_PARTICIPANT_STATUS_CHANGED,
        function(result)

            local descriptor = __getDescriptor(result.room)
            if (descriptor.listener) then
                descriptor.listener.onParticipantStatusChanged(result.room, result.participant)
            end
        end)

    gpg.CallbackManager:addCallbackById(DefaultCallbacks.RTMP_DATA_RECEIVED,
        function(result)
            local descriptor = __getDescriptor(result.room)
            if (descriptor.listener) then
                descriptor.listener.onDataReceived(
                    result.room,
                    result.participant,
                    result.data,
                    result.is_reliable)
            end
        end)
    
end

function gpg.Realtime.CreateRealTimeRoom(params, listener, callback)
    sdkbox.GPGRealTimeMultiplayerWrapper:CreateRealTimeRoom(gpg.CallbackManager:addCallback(function(o)
        if gpg.IsSuccess(o.result) then
            gpg.Realtime.__setRoomInfo(o.room, listener)
            callback(o)
        end
    end), json.encode(params))
end

function gpg.Realtime.LeaveRoom(room_id, callback)
    sdkbox.GPGRealTimeMultiplayerWrapper:LeaveRoom(gpg.CallbackManager:addCallback(callback), room_id)
end

function gpg.Realtime.ShowRoomInboxUI(callback)
    sdkbox.GPGRealTimeMultiplayerWrapper:ShowRoomInboxUI(gpg.CallbackManager:addCallback(callback))
end

function gpg.Realtime.FetchInvitations(callback)
    sdkbox.GPGRealTimeMultiplayerWrapper:FetchInvitations(gpg.CallbackManager:addCallback(callback))
end

function gpg.Realtime.AcceptInvitation(invitation_id, listener, callback)
    sdkbox.GPGRealTimeMultiplayerWrapper:AcceptInvitation(gpg.CallbackManager:addCallback(function (o)
        if gpg.IsSuccess(o.result) then
            gpg.Realtime.__setRoomInfo(o.room, listener)
            callback(o)
        end
    end), invitation_id)
end

function gpg.Realtime.DeclineInvitation(invitation_id)
    sdkbox.GPGRealTimeMultiplayerWrapper:DeclineInvitation(invitation_id)
end

function gpg.Realtime.DismissInvitation(invitation_id)
    sdkbox.GPGRealTimeMultiplayerWrapper:DismissInvitation(invitation_id)
end

function gpg.Realtime.SendReliableMessage(room_id, participant_id, data, callback)
    sdkbox.GPGRealTimeMultiplayerWrapper:SendReliableMessage(gpg.CallbackManager:addCallback(callback), room_id, participant_id, data)
end

function gpg.Realtime.SendUnreliableMessageToOthers(room_id, data)
    sdkbox.GPGRealTimeMultiplayerWrapper:SendUnreliableMessageToOthers(room_id, data)
end

function gpg.Realtime.SendUnreliableMessage(json_str)
    sdkbox.GPGRealTimeMultiplayerWrapper:SendUnreliableMessage(json_str)
end

--
-- end of API
--

return gpg
