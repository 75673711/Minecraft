#ifndef BASESHADER_H
#define BASESHADER_H

#include "commondefine.h"

#include <QString>
#include <QVector2D>
#include <QMatrix4x4>

class BaseShader
{
public:
    BaseShader(const char* vertex_shader, const char* fragment_shader);
    virtual ~BaseShader();

    void bind();
    void unbind();

    CGLuint getID() const
    {
        return shader_id_;
    }

    void loadFloat(CGLuint location, CGLfloat value);
    void loadVector2(CGLuint location, const QVector2D& vector);
    void loadMatrix4(CGLuint location, const QMatrix4x4& matrix);

private:
    CGLuint shader_id_;
};

#endif // BASESHADER_H
