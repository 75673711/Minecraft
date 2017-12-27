#include "CubeModel.h"

#include "texture/TextureAltas.h"

#include <QOpenGLFunctions_4_5_Core>

static QVector<CGLfloat> vertex_positions = {
    -0.5f, -0.5f, -0.5f,   //back
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,  // front
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  -0.5f,  0.5f,   // left
    -0.5f,  -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f,  0.5f,
    -0.5f,  -0.5f,  0.5f,

    0.5f,  -0.5f,  0.5f,   // right
    0.5f,  -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f,  0.5f,
    0.5f,  -0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

static QVector<CGLfloat> texture_coordinates = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
};

CubeModel::CubeModel()
{
    QVector<CGLfloat> texture_pos;
    texture_pos << TextureAltas::GetTextureCoordinates(0, 1);
    texture_pos << TextureAltas::GetTextureCoordinates(0, 1);
    texture_pos << TextureAltas::GetTextureCoordinates(0, 1);
    texture_pos << TextureAltas::GetTextureCoordinates(0, 1);
    texture_pos << TextureAltas::GetTextureCoordinates(0, 0);
    texture_pos << TextureAltas::GetTextureCoordinates(0, 2);

    addData(vertex_positions, texture_pos, {});
}

void CubeModel::Draw() const
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    f->glDrawArrays(GL_LINE_STRIP, 0, getIndicesCount());   // GL_LINE_STRIP  GL_TRIANGLES
}

CGLuint CubeModel::getIndicesCount() const
{
    return vertex_positions.count() / 3;
}
