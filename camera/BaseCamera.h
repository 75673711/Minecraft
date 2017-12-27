#ifndef BASECAMERA_H
#define BASECAMERA_H

#include "commondefine.h"

#include<QMatrix4x4>

class BaseCamera
{
public:
    BaseCamera();
    virtual ~BaseCamera();

    virtual void SetViewSize(const QSize& view_size) = 0;

    virtual void SetMoveSpeed(float speed) = 0;
    virtual void SetRotateSpeed(float speed) = 0;

    virtual void SetMousePress(bool left, bool right, int x, int y) = 0;
    virtual void SetMouseMove(int x, int y) = 0;
    virtual void SetKeyPress(int key, bool pressed) = 0;

    virtual const QMatrix4x4& getViewMatrix() = 0;
    virtual const QMatrix4x4& getProjectionMatrix() = 0;
};

#endif // BASECAMERA_H
