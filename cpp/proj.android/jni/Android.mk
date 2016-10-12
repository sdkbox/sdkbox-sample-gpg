LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/AchievementScene.cpp \
../../Classes/BaseScene.cpp \
../../Classes/EventScene.cpp \
../../Classes/LeaderboardScene.cpp \
../../Classes/PlayerStatScene.cpp \
../../Classes/QuestScene.cpp \
../../Classes/SaveGameScene.cpp \
../../Classes/StateManager.cpp \
../../Classes/Utils.cpp \
../../Classes/json98.cpp \
../../Classes/NearbyConnectionsScene.cpp \
../../Classes/RealTimeMultiplayerScene.cpp \
../../Classes/TurnBasedMultiplayerScene.cpp \
../../Classes/PluginGPGCppHelper.cpp

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid \
-llog

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
./gpg/include/ \
$(LOCAL_PATH)/..

LOCAL_WHOLE_STATIC_LIBRARIES := sdkbox \
gpg-1 \
PluginGPG

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, $(LOCAL_PATH))

$(call import-module, ./sdkbox)
$(call import-module, ./gpg)
$(call import-module, ./prebuilt-mk)
$(call import-module, ./plugingpg)
