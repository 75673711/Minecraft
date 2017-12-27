#ifndef WORLD_H
#define WORLD_H

#include "commondefine.h"
#include "object/BaseObject.h"

#include <QList>

class ChunkObject;

class World
{
public:
    World();
    ~World();

    void AddObject(BaseObject* ptr_object);
    void AddChunk(ChunkObject* ptr_chunk);

    const QVector<QList<ChunkObject*>>& GetChunks() const { return chunk_vec_; }

private:
    QVector<QList<ChunkObject*>> chunk_vec_;
};

#endif // WORLD_H
