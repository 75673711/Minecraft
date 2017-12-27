#include "BaseShader.h"

#include <QOpenGLFunctions_4_5_Core>

BaseShader::BaseShader(const char* vertex_shader, const char* fragment_shader)
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    int vertexShader = f->glCreateShader(GL_VERTEX_SHADER);
    f->glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    f->glCompileShader(vertexShader);

    int fragmentShader = f->glCreateShader(GL_FRAGMENT_SHADER);
    f->glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    f->glCompileShader(fragmentShader);

    shader_id_ = f->glCreateProgram();
    f->glAttachShader(shader_id_, vertexShader);
    f->glAttachShader(shader_id_, fragmentShader);
    f->glLinkProgram(shader_id_);

    f->glDeleteShader(vertexShader);
    f->glDeleteShader(fragmentShader);
}

BaseShader::~BaseShader()
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    f->glDeleteProgram(shader_id_);
}

void BaseShader::bind()
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    f->glUseProgram(shader_id_);
}

void BaseShader::unbind()
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    f->glUseProgram(0);
}

void BaseShader::loadFloat(CGLuint location, CGLfloat value)
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    f->glUniform1f(location, value);
}

void BaseShader::loadVector2(CGLuint location, const QVector2D& vector)
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    f->glUniform2f(location, vector.x(), vector.y());
}

void BaseShader::loadMatrix4(CGLuint location, const QMatrix4x4& matrix)
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    f->glUniformMatrix4fv(location,  1, GL_FALSE, matrix.constData());
}
