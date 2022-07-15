/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

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

#pragma once

#include "ar/IARAPI.h"
//#include "base/CommonDefines.h"

class _jobject;

namespace cc {
namespace ar {
/*
using JniMethodInfo = struct JniMethodInfo_ {
    JNIEnv *  env;
    jclass    classID;
    jmethodID methodID;
};
*/
class ARAndroidLib : public IARAPI {
public:
    ARAndroidLib();
    ~ARAndroidLib() override;
    void config(int featureMask) override;
    int getSupportMask() override;
    void start() override;
    void resume() override;
    void pause() override;
    void update() override;
    int getAPIState() override;
    void beforeUpdate() override;

    float* getCameraPose() override;
    float* getCameraViewMatrix() override;
    float* getCameraProjectionMatrix() override;
    float* getCameraTexCoords() override;
    void setCameraTextureName(int id) override;
    void* getCameraTextureRef() override;

    uint8_t* getCameraDepthBuffer() override;

    //void setPlaneFeatureEnable(bool isOn) override;
    int getAddedPlanesCount() override;
    int getRemovedPlanesCount() override;
    int getUpdatedPlanesCount() override;

    void enablePlane(bool enable) override;
    void setPlaneDetectionMode(int mode) override;
    void setPlaneMaxTrackingNumber(int count) override;

    void updatePlanesInfo() override;
    float* getAddedPlanesInfo() override;
    int* getRemovedPlanesInfo() override;
    float* getUpdatedPlanesInfo() override;
    int getInfoLength() override;

    int tryHitAttachAnchor(int planeIndex) override;
    float* getAnchorPose(int index) override;

    bool raycast(float xPx, float yPx) override;
    float* getRaycastPose() override;
    int getRaycastTrackableId() override;
    int getRaycastTrackableType() override;

    void enableSceneMesh(bool enable) override;
    float* getAddedSceneMesh() override;
    float* getUpdatedSceneMesh() override;
    int* getRemovedSceneMesh() override;
    int* requireSceneMesh() override;
    float* getSceneMeshVertices(int meshRef) override;
    int* getSceneMeshTriangleIndices(int meshRef) override;
    void endRequireSceneMesh() override;

    void enableImageTracking(bool enable) override;
    void addImageToLib(const std::string& imageName) override;
    void setMaxTrackingNumber(int number) override;
    float* getAddedImagesInfo() override;
    float* getUpdatedImagesInfo() override;
    float* getRemovedImagesInfo() override;

    void enableObjectTracking(bool enable) override;
    void addObjectToLib(const std::string& imageName) override;
    float* getAddedObjectsInfo() override;
    float* getUpdatedObjectsInfo() override;
    float* getRemovedObjectsInfo() override;

    void enableFaceTracking(bool enable) override;
    float* getAddedFacesInfo() override;
    float* getUpdatedFacesInfo() override;
    float* getRemovedFacesInfo() override;
    float* getFaceBlendShapesOf(int faceRef) override;

protected:
    _jobject* _impl;
    Pose* _cameraPose = new Pose();
    Matrix* _viewMatrix = new Matrix();
    Matrix* _projMatrix = new Matrix();
    TexCoords *_cameraTexCoords = new TexCoords();
    uint8_t* _cameraDepthBuffer{nullptr};
    void onBeforeUpdate();

    //float* _addedPlanesInfo = new float[60];
    float* _addedPlanesInfo = nullptr;
    int* _removedPlanesInfo = nullptr;
    //'float* _updatedPlanesInfo = new float[60];
    float* _updatedPlanesInfo = nullptr;
    int _infoLength = 0;

    float* _hitPose = new float[7];
    float* _anchorPose = new float[7];

    float* _sceneMeshVertices{nullptr};
    int* _sceneMeshIndices{nullptr};
    float* _addedSceneMeshInfo{nullptr};
    float* _updatedSceneMeshInfo{nullptr};
    int* _removedSceneMeshRefs{nullptr};
    int* _requiredSceneMeshRefs{nullptr};

    float* _addedImagesInfo{nullptr};
    float* _updatedImagesInfo{nullptr};
    float* _removedImagesInfo{nullptr};

    float* _addedObjsInfo{nullptr};
    float* _updatedObjsInfo{nullptr};
    float* _removedObjsInfo{nullptr};

    float* _addedFacesInfo{nullptr};
    float* _updatedFacesInfo{nullptr};
    float* _removedFacesInfo{nullptr};
};

} // namespace ar
} // namespace cc
