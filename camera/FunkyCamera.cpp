#include "FunkyCamera.h"

#include <QtMath>
#include <QDebug>

FunkyCamera::FunkyCamera()
{
    view_matrix_.translate(camera_position_ * -1);
}

void FunkyCamera::SetViewSize(const QSize& view_size)
{
    QMatrix4x4 projection;
    projection.perspective(45.0f, (float)view_size.width() / (float)view_size.height(), 0.1f, 1000.0f);

    project_matrix_ = projection;
}

void FunkyCamera::SetMoveSpeed(float speed)
{
    move_speed_ = speed;
}

void FunkyCamera::SetRotateSpeed(float speed)
{
    rotate_speed_ = speed;
}

void FunkyCamera::SetMousePress(bool left, bool right, int x, int y)
{
    if (right)
    {
        right_press_ = true;
        last_x_ = x;
        last_y_ = y;
    }
    else
    {
        right_press_ = false;
    }
}

void FunkyCamera::SetMouseMove(int x, int y)
{
    if (right_press_)
    {
        double real_x = (double)(x - last_x_) * rotate_speed_;
        double real_y = (double)(y - last_y_) * rotate_speed_;

        yaw_ += real_x;
        pitch_ += real_y;

        if(pitch_ > 89.0f)
          pitch_ =  89.0f;
        if(pitch_ < -89.0f)
          pitch_ = -89.0f;

        camera_front_.setX(qCos(qDegreesToRadians(pitch_)) * qCos(qDegreesToRadians(yaw_)));
        camera_front_.setY(qSin(qDegreesToRadians(pitch_)));
        camera_front_.setZ(qCos(qDegreesToRadians(pitch_)) * qSin(qDegreesToRadians(yaw_)));
        camera_front_.normalize();

        last_x_ = x;
        last_y_ = y;

        view_matrix_ = QMatrix4x4();
        view_matrix_.lookAt(camera_position_,  camera_position_ + camera_front_, camera_up_);
    }
}

void FunkyCamera::SetKeyPress(int key, bool pressed)
{
    __int64 delta_time = GetDeltaTime();

    switch (key)
    {
    case Qt::Key_W:
        front_ = pressed;
        break;
    case Qt::Key_S:
        back_ = pressed;
        break;
    case Qt::Key_A:
        left_ = pressed;
        break;
    case Qt::Key_D:
        right_ = pressed;
        break;
    case Qt::Key_R:
        up_ = pressed;
        break;
    case Qt::Key_F:
        down_ = pressed;
        break;
        break;
    default:
        break;
    }

    need_update_position_ = front_ || back_ || left_ || right_ || up_ || down_;
}

const QMatrix4x4& FunkyCamera::getViewMatrix()
{
    if (need_update_position_)
    {
        __int64 delta_time = GetDeltaTime();
        move_speed_ = delta_time * 0.005;

        if (front_)
        {
            camera_position_ += move_speed_ * camera_front_;
        }

        if (back_)
        {
            camera_position_ -= move_speed_ * camera_front_;
        }

        if (left_)
        {
            camera_position_ -= QVector3D::crossProduct(camera_front_, camera_up_).normalized() * move_speed_;
        }

        if (right_)
        {
            camera_position_ += QVector3D::crossProduct(camera_front_, camera_up_).normalized() * move_speed_;
        }

        if (up_)
        {
            camera_position_ -= move_speed_ * camera_up_;
        }

        if (down_)
        {
            camera_position_ += move_speed_ * camera_up_;
        }

        view_matrix_ = QMatrix4x4();
        view_matrix_.lookAt(camera_position_,  camera_position_ + camera_front_, camera_up_);
    }

    return view_matrix_;
}

const QMatrix4x4& FunkyCamera::getProjectionMatrix()
{
    return project_matrix_;
}
