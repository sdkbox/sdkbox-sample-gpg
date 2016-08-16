LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libgpg
LOCAL_SRC_FILES := /Users/ibon/punchbox/test/gpg-sample2/js/frameworks/runtime-src/proj.android/gpg/lib/gnustl/$(TARGET_ARCH_ABI)/libgpg.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := hellojavascript/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/ide-support/SimpleConfigParser.cpp \
../../Classes/ide-support/RuntimeJsImpl.cpp \
../../Classes/PluginSdkboxGooglePlayJS.cpp \
../../Classes/PluginSdkboxGooglePlayJSHelper.cpp \
../../Classes/SDKBoxJSHelper.cpp

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid \
-llog

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
/Users/ibon/punchbox/test/gpg-sample2/js/frameworks/runtime-src/proj.android/gpg/include/ \
$(LOCAL_PATH)/..
LOCAL_WHOLE_STATIC_LIBRARIES := PluginSdkboxPlay \
sdkbox \
PluginSdkboxGooglePlay \
gpg-1

LOCAL_STATIC_LIBRARIES := cocos2d_js_static
LOCAL_STATIC_LIBRARIES += cocos2d_simulator_static

include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, $(LOCAL_PATH))

$(call import-module,scripting/js-bindings/proj.android/prebuilt-mk)
$(call import-module,tools/simulator/libsimulator/proj.android/prebuilt-mk)
$(call import-module, ./sdkbox)
$(call import-module, ./PluginSdkboxGooglePlay)
$(call import-module, ../gpg)
