LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

GAF_LIB_SOURCES := $(LOCAL_PATH)

LOCAL_MODULE := gafplayer_static

LOCAL_MODULE_FILENAME := libgafplayer

CLASSES_FILES := $(wildcard $(GAF_LIB_SOURCES)/*.cpp)
LOCAL_SRC_FILES := $(CLASSES_FILES:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := \
$(GAF_LIB_SOURCES) \
$(LOCAL_PATH)/ShadersPrecompiled \
$(LOCAL_PATH)/../../cocos \
$(LOCAL_PATH)/../../cocos/2d \
$(LOCAL_PATH)/../../external/lua/tolua \
$(LOCAL_PATH)/../../external/lua/luajit/include \
$(LOCAL_PATH)/../../cocos/scripting/lua-bindings/manual

LOCAL_EXPORT_C_INCLUDES := \
$(GAF_LIB_SOURCES)

include $(BUILD_STATIC_LIBRARY)
