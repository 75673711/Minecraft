#include "texture/Texture.h"

#include <QOpenGLFunctions_4_5_Core>
#include <QImage>

#include <QDebug>

Texture::Texture()
{

}


Texture::~Texture()
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    f->glDeleteTextures(1, &texture_id_);
}

void Texture::load(const QString& fileName)
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    f->glGenTextures(1, &texture_id_);
    f->glBindTexture(GL_TEXTURE_2D, texture_id_);
    // set the texture wrapping parameters
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    QImage image(fileName);
    QImage temp = image.convertToFormat(QImage::Format_RGBA8888);

    f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, temp.width(), temp.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, temp.constBits());
    //f->glGenerateMipmap(GL_TEXTURE_2D);

    f->glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    f->glBindTexture(GL_TEXTURE_2D, texture_id_);
}

void Texture::unbind()
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    f->glBindTexture(GL_TEXTURE_2D, 0);
}
