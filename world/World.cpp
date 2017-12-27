#include "World.h"

#include "object/ChunkObject.h"

World::World()
{
    chunk_vec_ = QVector<QList<ChunkObject*>>(ChunkObject::TextureTypeCount, QList<ChunkObject*>());

    for (int floor = 0; floor < 5; ++floor)
    {
        int begin_x = -floor;
        int begin_z = -floor;

        for (int i = begin_x; i <= floor; ++i)
        {
            for (int j = begin_z; j <= floor; ++j)
            {
                ChunkObject* ptr_chunk = new ChunkObject;
                ptr_chunk->SetPosition(i, floor, j);
                ptr_chunk->SetTextureType(ChunkObject::Grass);
                AddChunk(ptr_chunk);
            }
        }
    }
}

World::~World()
{
    for (int i = 0; i < chunk_vec_.count(); ++i)
    {
        qDeleteAll(chunk_vec_[i]);
    }
}

void World::AddChunk(ChunkObject* ptr_chunk)
{
    chunk_vec_[ptr_chunk->GetTextureType()].append(ptr_chunk);
}

void World::AddObject(BaseObject* ptr_object)
{
    switch (ptr_object->GetType())
    {
    case BaseObject::Chunk:
    {
        ChunkObject* ptr_chunk = static_cast<ChunkObject*>(ptr_object);
        AddChunk(ptr_chunk);
    }
        break;
    default:
        break;
    }
}
