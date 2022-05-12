/****************************************************************************
 Copyright (c) 2022-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#ifndef H_XR_H
#define H_XR_H

#include <functional>
#include <vector>

#ifdef XR_USE_GRAPHICS_API_VULKAN
#include "vulkan/vulkan_core.h"
#endif

struct CocosXrSwapchain {
    void* handle;
    uint32_t width;
    uint32_t height;
};

namespace cc{
namespace xr{

struct XrQuaternion{
    float x               = 0.f;
    float y               = 0.f;
    float z               = 0.f;
    float w               = 1.f;

    XrQuaternion() {}

    XrQuaternion(float xx, float yy, float zz, float ww)
            : x(xx),
              y(yy),
              z(zz),
              w(ww) {}

    XrQuaternion(const XrQuaternion &copy) {
        this->x = copy.x;
        this->y = copy.y;
        this->z = copy.z;
        this->w = copy.w;
    }
};

struct HandleInfo {
    float x               = 0.f;
    float y               = 0.f;
    float z               = 0.f;
    float value           = 0.f;
    XrQuaternion quaternion;

    HandleInfo() {}

    HandleInfo(float x, float y)
            : x(x),
              y(y) {}

    HandleInfo(float value)
            : value(value) {}

    HandleInfo(float x, float y, float z, const XrQuaternion &quaternion)
            : x(x),
              y(y),
              z(z),
              quaternion(quaternion) {}
};

struct HandleEvent {
    enum class Type {
        VIEW_POSE_ACTIVE_LEFT,
        HAND_POSE_ACTIVE_LEFT,
        TRIGGER_START_LEFT,
        TRIGGER_END_LEFT,
        TRIGGER_DOWN_LEFT,
        TRIGGER_UP_LEFT,
        THUMBSTICK_MOVE_LEFT,
        THUMBSTICK_MOVE_END_LEFT,
        THUMBSTICK_DOWN_LEFT,
        THUMBSTICK_UP_LEFT,
        GRIP_START_LEFT,
        GRIP_END_LEFT,
        BUTTON_X_DOWN,
        BUTTON_X_UP,
        BUTTON_Y_DOWN,
        BUTTON_Y_UP,
        MENU_DOWN,
        MENU_UP,
        VIEW_POSE_ACTIVE_RIGHT,
        HAND_POSE_ACTIVE_RIGHT,
        TRIGGER_START_RIGHT,
        TRIGGER_END_RIGHT,
        TRIGGER_DOWN_RIGHT,
        TRIGGER_UP_RIGHT,
        THUMBSTICK_MOVE_RIGHT,
        THUMBSTICK_MOVE_END_RIGHT,
        THUMBSTICK_DOWN_RIGHT,
        THUMBSTICK_UP_RIGHT,
        GRIP_START_RIGHT,
        GRIP_END_RIGHT,
        BUTTON_A_DOWN,
        BUTTON_A_UP,
        BUTTON_B_DOWN,
        BUTTON_B_UP,
        HOME_DOWN,
        HOME_UP,
        BACK_DOWN,
        BACK_UP,
        START_DOWN,
        START_UP,
        DPAD_TOP_DOWN,
        DPAD_TOP_UP,
        DPAD_BOTTOM_DOWN,
        DPAD_BOTTOM_UP,
        DPAD_LEFT_DOWN,
        DPAD_LEFT_UP,
        DPAD_RIGHT_DOWN,
        DPAD_RIGHT_UP,
        UNKNOWN
    };

    static const constexpr char *TypeNames[] = {
        "onViewPoseActiveLeft",
        "onHandPoseActiveLeft",
        "onTriggerStartLeft",
        "onTriggerEndLeft",
        "onTriggerDownLeft",
        "onTriggerUpLeft",
        "onThumbstickMoveLeft",
        "onThumbstickMoveEndLeft",
        "onThumbstickDownLeft",
        "onThumbstickUpLeft",
        "onGripStartLeft",
        "onGripEndLeft",
        "onButtonXDown",
        "onButtonXUp",
        "onButtonYDown",
        "onButtonYUp",
        "onMenuDown",
        "onMenuUp",
        "onViewPoseActiveRight",
        "onHandPoseActiveRight",
        "onTriggerStartRight",
        "onTriggerEndRight",
        "onTriggerDownRight",
        "onTriggerUpRight",
        "onThumbstickMoveRight",
        "onThumbstickMoveEndRight",
        "onThumbstickDownRight",
        "onThumbstickUpRight",
        "onGripStartRight",
        "onGripEndRight",
        "onButtonADown",
        "onButtonAUp",
        "onButtonBDown",
        "onButtonBUp",
        "onHomeDown",
        "onHomeUp",
        "onBackDown",
        "onBackUp",
        "onStartDown",
        "onStartUp",
        "onDpadTopDown",
        "onDpadTopUp",
        "onDpadBottomDown",
        "onDpadBottomUp",
        "onDpadLeftDown",
        "onDpadLeftUp",
        "onDpadRightDown",
        "onDpadRightUp",
        "unknown"
    };

    HandleInfo handleInfo;
    Type       type = Type::UNKNOWN;
};

typedef std::function<void (const xr::HandleEvent &handleEvent)> XrEventsCallback;

class XrEntrance {
public:
    static XrEntrance* getInstance();

    virtual void createXrInstance(const char* graphicsName, void* javaVM, void* activity) = 0;

    virtual void pauseXrInstance() = 0;

    virtual void resumeXrInstance() = 0;

    virtual void destroyXrInstance() = 0;

    virtual void initXrSession() = 0;

    virtual bool isCreatedXRinstance() = 0;

#ifdef XR_USE_GRAPHICS_API_VULKAN
    virtual void initXrSession(VkInstance vkInstance, VkPhysicalDevice vkPhyDevice, VkDevice vkDevice, uint32_t familyIndex) = 0;

    virtual void GetSwapchainImages(std::vector<VkImage> &vkImages, void *windowHandle, uint32_t &imageCount) = 0;

    virtual VkInstance XrVkCreateInstance(const VkInstanceCreateInfo &instInfo, const PFN_vkGetInstanceProcAddr &addr) = 0;

    virtual VkPhysicalDevice GetXrVkGraphicsDevice(const VkInstance &vkInstance) = 0;

    virtual VkResult XrVkCreateDevice(const VkDeviceCreateInfo *deviceInfo, const PFN_vkGetInstanceProcAddr &addr, const VkPhysicalDevice &vkPhysicalDevice, VkDevice* vkDevice) = 0;
#endif

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES
    virtual void SetOpenGLESConfig(void *eglDisplay, void *eglConfig, void *eglDefaultContext) = 0;
#endif

    virtual const std::vector<CocosXrSwapchain> &GetCocosXrSwapchain() = 0;

    virtual const CocosXrSwapchain &GetXrSwapchain() = 0;

    virtual bool IsSessionRunning() = 0;

    virtual bool PollEvents() = 0;

    virtual void PollActions() = 0;

    virtual void frameStart() = 0;

    virtual void renderLoopStart(int i) = 0;

    virtual void renderLoopEnd(int i) = 0;

    virtual void frameEnd() = 0;

    virtual void setEventsCallback(XrEventsCallback xrEventsCallback) = 0;

    virtual bool BeginRenderFrame() = 0;

    virtual std::vector<float> ComputeViewProjection(uint32_t index, float nearZ, float farZ, float scaleF) = 0;

    virtual std::vector<float> GetFov(uint32_t index) = 0;

    virtual void ByBeforeRenderFrame(int i) = 0;

    virtual void ByAfterRenderFrame(int i) = 0;

    virtual void EndRenderFrame() = 0;

    virtual uint32_t GetSwapchainImageIndexsByHandle(void* handle) = 0;
};

} // namespace cc
} // namespace xr

#endif //H_XR_H
