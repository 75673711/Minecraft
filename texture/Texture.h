#ifndef TEXTURE_H
#define TEXTURE_H

#include "commondefine.h"

#include <QString>

class Texture
{
public:
    explicit Texture();
    ~Texture();

    void load(const QString& fileName);

    void bind();
    void unbind();

private:
    CGLuint texture_id_;
};

#endif // TEXTURE_H
