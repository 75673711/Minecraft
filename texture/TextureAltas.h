#ifndef TEXTUREALTAS_H
#define TEXTUREALTAS_H

#include "commondefine.h"

#include <QVector>

class Texture;

class TextureAltas
{
public:
    static void load();
    static void unload();

    static void bind();
    static void unbind();

    static QVector<CGLfloat> GetTextureCoordinates(int row, int column);

private:
    static Texture* ptr_texture_;
};

#endif // TEXTUREALTAS_H
