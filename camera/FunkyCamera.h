#ifndef FUNKYCAMERA_H
#define FUNKYCAMERA_H

#include "BaseCamera.h"

#include <QVector3D>

class FunkyCamera : public BaseCamera
{
public:
    FunkyCamera();

    virtual void SetViewSize(const QSize& view_size) override;

    virtual void SetMoveSpeed(float speed) override;
    virtual void SetRotateSpeed(float speed) override;

    virtual void SetMousePress(bool left, bool right, int x, int y) override;
    virtual void SetMouseMove(int x, int y) override;
    virtual void SetKeyPress(int key, bool pressed) override;

    virtual const QMatrix4x4& getViewMatrix();
    virtual const QMatrix4x4& getProjectionMatrix();

private:
    QMatrix4x4 view_matrix_;
    QMatrix4x4 project_matrix_;

    QVector3D camera_position_ = {0, 0, 1};
    QVector3D camera_front_ = {0, 0, -1};
    QVector3D camera_up_ = {0, 1, 0};

    float move_speed_ = 0.0;
    float rotate_speed_ = 0.5;

    bool left_ = false;
    bool right_ = false;
    bool front_ = false;
    bool back_ = false;
    bool up_ = false;
    bool down_ = false;

    bool need_update_position_ = false;

    bool right_press_ = false;
    int last_x_ = 0;
    int last_y_ = 0;
    // angle
    double yaw_ = -90.0;   // x-z
    double pitch_ = 0;   // y-xz
    float fov_ = 60.0;
};

#endif // FUNKYCAMERA_H
