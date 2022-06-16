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

#include "XRCommon.h"

#include <functional>
#include <vector>

#ifdef XR_USE_GRAPHICS_API_VULKAN
#include "vulkan/vulkan_core.h"
#endif

namespace cc{
namespace xr{

class XrEntry {
public:
    static XrEntry* getInstance();

    virtual void initPlatformData(void* javaVM, void* activity) = 0;

    virtual void createXrInstance(const char* graphicsName) = 0;

    virtual void pauseXrInstance() = 0;

    virtual void resumeXrInstance() = 0;

    virtual void destroyXrInstance() = 0;

    virtual int getXrViewCount() = 0;

    virtual void initXrSwapchains() = 0;

    virtual bool isCreatedXrInstance() = 0;

#ifdef XR_USE_GRAPHICS_API_VULKAN
    virtual uint32_t getXrVkApiVersion(uint32_t defaultApiVersion) = 0;

    virtual void initXrSession(VkInstance vkInstance, VkPhysicalDevice vkPhyDevice, VkDevice vkDevice, uint32_t familyIndex) = 0;

    virtual void getSwapchainImages(std::vector<VkImage> &vkImages, void *ccSwapchainHandle) = 0;

    virtual VkInstance xrVkCreateInstance(const VkInstanceCreateInfo &instInfo, const PFN_vkGetInstanceProcAddr &addr) = 0;

    virtual VkPhysicalDevice getXrVkGraphicsDevice(const VkInstance &vkInstance) = 0;

    virtual VkResult xrVkCreateDevice(const VkDeviceCreateInfo *deviceInfo, const PFN_vkGetInstanceProcAddr &addr, const VkPhysicalDevice &vkPhysicalDevice, VkDevice* vkDevice) = 0;
#endif

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES
    virtual void initXrSession(PFNGLES3WLOADPROC gles3wLoadFuncProc, void *eglDisplay, void *eglConfig, void *eglDefaultContext) = 0;

    virtual unsigned int getXrFrameBuffer() = 0;

    virtual void attachXrFramebufferTexture2D() = 0;
#endif

    virtual std::vector<XRSwapchain> &getCocosXrSwapchains() = 0;

    virtual bool isSessionRunning() = 0;

    virtual bool frameStart() = 0;

    virtual void renderLoopStart(int i) = 0;

    virtual void renderLoopEnd(int i) = 0;

    virtual void frameEnd() = 0;

    virtual void setEventsCallback(XREventsCallback xrEventsCallback) = 0;

    virtual std::vector<float> computeViewProjection(uint32_t index, float nearZ, float farZ, float scaleF) = 0;

    virtual uint32_t getSwapchainImageIndex() = 0;

    virtual void setMultisamplesRTT(int num) = 0;

    virtual void setRenderingScale(float scale) = 0;

    virtual bool platformLoopStart() = 0;

    virtual bool platformLoopEnd() = 0;
};

} // namespace xr
} // namespace cc

#endif //H_XR_H
