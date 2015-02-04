LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := dragonbones_static

LOCAL_MODULE_FILENAME := libdragonbones

LOCAL_SRC_FILES := ../../../animation/Animation.cpp \
                   ../../../animation/AnimationState.cpp \
                   ../../../animation/TimelineState.cpp \
                   ../../../animation/WorldClock.cpp \
                   ../../../core/Armature.cpp \
                   ../../../core/Bone.cpp \
                   ../../../core/Object.cpp \
                   ../../../core/Slot.cpp \
                   ../../../events/EventData.cpp \
                   ../../../factories/BaseFactory.cpp \
                   ../../../parsers/BaseDataparser.cpp \
                   ../../../parsers/ConstValues.cpp \
                   ../../../parsers/XMLDataParser.cpp \
                   ../../../parsers/dbtinyxml2.cpp \
                   ../DBCCArmature.cpp \
                   ../DBCCArmatureNode.cpp \
                   ../DBCCFactory.cpp \
                   ../DBCCSlot.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../../.. \
$(LOCAL_PATH)/../../../../../../cocos/2d \
$(LOCAL_PATH)/../../../../../../external/lua/tolua \
$(LOCAL_PATH)/../../../../../../external/lua/luajit/include \
$(LOCAL_PATH)/../../../../../../cocos/scripting/lua-bindings/manual

LOCAL_EXPORT_C_INCLUDES := \
$(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../../.. 

LOCAL_CFLAGS += -fexceptions

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static

include $(BUILD_STATIC_LIBRARY)
