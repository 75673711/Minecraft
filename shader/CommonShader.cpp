#include "CommonShader.h"

#include <QOpenGLFunctions_4_5_Core>

CommonShader::CommonShader(const char *vertex_shader, const char *fragment_shader):
    BaseShader(vertex_shader, fragment_shader)
{
    InitUniformLocations();
}

CommonShader::~CommonShader()
{

}

void CommonShader::setTime(float time)
{
    loadFloat(location_time_, time);
}

void CommonShader::setViewMatrix(const QMatrix4x4& matrix)
{
    loadMatrix4(location_view_matrix_, matrix);
}

void CommonShader::setModelMatrix(const QMatrix4x4& matrix)
{
    loadMatrix4(location_model_matrix_, matrix);
}

void CommonShader::setProjMatrix(const QMatrix4x4& matrix)
{
    loadMatrix4(location_proj_matrix_, matrix);
}

void CommonShader::InitUniformLocations()
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    location_time_ = f->glGetUniformLocation(getID(), "time");

    location_view_matrix_ = f->glGetUniformLocation(getID(), "viewMatrix");
    location_model_matrix_ = f->glGetUniformLocation(getID(), "modelMatrix");
    location_proj_matrix_ = f->glGetUniformLocation(getID(), "projMatrix");
}
