#ifndef COMMONSHADER_H
#define COMMONSHADER_H

#include "BaseShader.h"

class CommonShader : public BaseShader
{
public:
    CommonShader(const char* vertex_shader, const char* fragment_shader);
    ~CommonShader();

    void setTime(float time);

    void setViewMatrix(const QMatrix4x4& matrix);
    void setModelMatrix(const QMatrix4x4& matrix);
    void setProjMatrix(const QMatrix4x4& matrix);

protected:
    void InitUniformLocations();

private:
    CGLuint location_time_;
    CGLuint location_view_matrix_;
    CGLuint location_model_matrix_;
    CGLuint location_proj_matrix_;
};

#endif // COMMONSHADER_H
