#include "TextureAltas.h"

#include "Texture.h"

#include <QSize>

Texture* TextureAltas::ptr_texture_ = NULL;

void TextureAltas::load()
{
    if (ptr_texture_ == NULL)
    {
        ptr_texture_ = new Texture();
        ptr_texture_->load(QString(":/image/res/image/texture_atlas.png"));
    }
}

void TextureAltas::unload()
{
    if (ptr_texture_ != NULL)
    {
        delete ptr_texture_;
        ptr_texture_ = NULL;
    }
}

void TextureAltas::bind()
{
    ptr_texture_->bind();
}

void TextureAltas::unbind()
{
    ptr_texture_->unbind();
}

QVector<CGLfloat> TextureAltas::GetTextureCoordinates(int row, int column)
{
    static QSize image_size(512, 512);
    static QSize texture_size(16, 16);

    static int column_count = image_size.width() / texture_size.width();
    static int row_count = image_size.height() / texture_size.height();

    static float unit_width = 1.0f / column_count;

    if (row >= row_count || column >= column_count)
    {
        return {};
    }

    QVector<CGLfloat> vec;
    float y0 = 1.0 - row * unit_width;
    float x0 = column * unit_width;
    float y1 = y0 + unit_width;
    float x1 = x0 + unit_width;
    return {x0, y0, x1, y0, x1, y1, x1, y1, x0, y1, x0, y0};
}
