
#include "PluginSdkboxGooglePlayLuaHelper.h"
#include "PluginSdkboxGooglePlay/PluginSdkboxGooglePlay.h"
#include "PluginSdkboxGooglePlay/SnapshotManager.h"
#include "PluginSdkboxGooglePlay/SdkboxGooglePlayWrappedObjects.h"
#include "SnapshotMetadataLuaHelper.h"
#include "SDKBoxLuaHelper.h"
#include <codecvt>
#include <cassert>

int register_all_PluginSdkboxGooglePlayLua_helper(lua_State* L) {
    return 1;
};

NativeLuaNotifierScheduler::NativeLuaNotifierScheduler(int id, const std::string& json)
	: _id(id)
	, _json(json)
{
}

void NativeLuaNotifierScheduler::schedule()
{
    retain();
    cocos2d::Director::getInstance()->getScheduler()->schedule(schedule_selector(NativeLuaNotifierScheduler::notity), this, 0, false);
    autorelease();
}

static char hexToDec(char hex)
{
    hex = toupper(hex);
    if (hex >= '0' && hex <= '9')
        return hex - '0';
    if (hex >= 'A' && hex <= 'F')
        return hex - 'A';
    assert(false);
    return -1;
}

static std::string convertEscapedUnicodeToUTF8(const std::string& input)
{
    const int hostInt = 1;
    const bool bLittleEndian = *(char*)&hostInt ? true : false;
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> conv;
    const char* p = input.c_str();
    const char* pEnd = p + input.size();
    std::string result;
    result.reserve(input.size());
    while (p < pEnd)
    {
        auto c = *p++;
        if (c == '\\' && *p == 'u')
        {
            ++p; // step past u
            uint16_t c16 = 0;
            if (bLittleEndian)
            {
                c16 |= hexToDec(*p++)<<12;
                c16 |= hexToDec(*p++)<<8;
                c16 |= hexToDec(*p++)<<4;
                c16 |= hexToDec(*p++);
            }
            else
            {
                c16 |= hexToDec(*p++);
                c16 |= hexToDec(*p++)<<4;
                c16 |= hexToDec(*p++)<<8;
                c16 |= hexToDec(*p++)<<12;
            }
            c = conv.to_bytes(c16)[0];
            if (c == 0)
                continue;
        }
        result += c;
    }
    return result;
}

void NativeLuaNotifierScheduler::notity(float dt)
{
    lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    lua_getglobal(L, "__nativeNotify");
    lua_pushinteger(L, _id);
    std::string sanitized = convertEscapedUnicodeToUTF8(_json);
    lua_pushstring(L, sanitized.c_str());
    lua_pcall(L, 2, 0, 0);
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    release();
}

void sdkbox::GPGWrapper::NotifyToScripting(int id, const std::string& str_json)
{
    NativeLuaNotifierScheduler* ns = new NativeLuaNotifierScheduler(id, str_json);
    ns->schedule();
}

