#ifndef BASERENDER_H
#define BASERENDER_H

#include "commondefine.h"

#include <QSize>

class CommonShader;
class BaseShader;
class BaseModel;
class Texture;
class BaseCamera;
class World;

class BaseRender
{
public:
    BaseRender();
    virtual ~BaseRender();

    void EnsureInit();

    void render(const QSize& view_size, BaseCamera* ptr_camera, World* ptr_world);

private:
    BaseModel* test_model;
    Texture* test_texture_;
    CommonShader* test_shader_;

    bool init_;
};

#endif // BASERENDER_H
