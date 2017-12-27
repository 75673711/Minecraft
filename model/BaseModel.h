#ifndef BASEMODEL_H
#define BASEMODEL_H

#include "commondefine.h"

#include <QVector>

class BaseModel
{
public:
    BaseModel() = default;
    BaseModel(const QVector<CGLfloat>& vertexPositions,
          const QVector<CGLfloat>& textureCoordinates,
          const QVector<CGLuint> &indices);

    virtual ~BaseModel();

    void addData(const QVector<CGLfloat>& vertexPositions,
                 const QVector<CGLfloat>& textureCoordinates,
                 const QVector<CGLuint>&  indices);

    void bind() const;
    void unbind() const;

    virtual void Draw() const;
    virtual CGLuint getIndicesCount() const;

private:
    void addVBO(int dim, const QVector<CGLfloat>& data);
    void addEBO(const QVector<CGLuint>& indices);

    void ReleaseData();

    QVector<CGLuint> m_buffers;

    CGLuint m_vao = 0;
    CGLuint m_vboCount = 0;
    CGLuint m_indicesCount = 0;
};

#endif // BASEMODEL_H
