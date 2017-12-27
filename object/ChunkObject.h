#ifndef CHUNKOBJECT_H
#define CHUNKOBJECT_H

#include "BaseObject.h"

class ChunkObject : public BaseObject
{
public:
    enum TextureType {
        Grass = 0,
        TextureTypeCount
    };

public:
    ChunkObject();
    ~ChunkObject();

    void SetPosition(CGLfloat x, CGLfloat y, CGLfloat z);
    virtual QMatrix4x4 GetModelMatrix() const override;

    void SetTextureType(TextureType texture_type) { texture_type_ = texture_type; }
    TextureType GetTextureType() const { return texture_type_; }

private:
    TextureType texture_type_;
    QMatrix4x4 model_matrix_;
};

#endif // CHUNKOBJECT_H
