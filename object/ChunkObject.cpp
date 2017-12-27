#include "ChunkObject.h"

ChunkObject::ChunkObject() : BaseObject(BaseObject::Chunk)
{

}

ChunkObject::~ChunkObject()
{

}

QMatrix4x4 ChunkObject::GetModelMatrix() const
{
    return model_matrix_;
}

void ChunkObject::SetPosition(CGLfloat x, CGLfloat y, CGLfloat z)
{
    model_matrix_.translate(x, y, z);
}
