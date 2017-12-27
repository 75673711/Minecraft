#include "BaseModel.h"

#include <QOpenGLFunctions_4_5_Core>

BaseModel::BaseModel(const QVector<CGLfloat>& vertexPositions,
                     const QVector<CGLfloat>& textureCoordinates,
                     const QVector<CGLuint>&  indices)
{

    addData(vertexPositions, textureCoordinates, indices);
}

BaseModel::~BaseModel()
{
    ReleaseData();
}

void BaseModel::ReleaseData()
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    if (m_vao != 0)
    {
        f->glDeleteVertexArrays(1, &m_vao);
    }

    if (m_buffers.count() > 0)
    {
        f->glDeleteBuffers(m_buffers.size(), m_buffers.data());
    }
}

void BaseModel::addData(const QVector<GLfloat>& vertexPositions,
                        const QVector<GLfloat>& textureCoordinates,
                        const QVector<GLuint>&  indices)
{
    ReleaseData();

    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    m_indicesCount = indices.size();
    f->glGenVertexArrays(1, &m_vao);
    f->glBindVertexArray(m_vao);

    addVBO(3, vertexPositions);
    addVBO(2, textureCoordinates);
    addEBO(indices);

    f->glBindVertexArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseModel::bind() const
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    f->glBindVertexArray(m_vao);
}

void BaseModel::unbind() const
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    f->glBindVertexArray(0);
}

void BaseModel::Draw() const
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    f->glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, 0);
}

CGLuint BaseModel::getIndicesCount() const
{
    return m_indicesCount;
}

void BaseModel::addVBO(int dim, const QVector<CGLfloat>& data)
{
    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    GLuint vbo;
    f->glGenBuffers(1, &vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    f->glBufferData(GL_ARRAY_BUFFER,
                    data.size() * sizeof(data[0]),
            data.data(),
            GL_STATIC_DRAW);
    f->glVertexAttribPointer(m_vboCount,
                             dim,
                             GL_FLOAT,
                             GL_FALSE,
                             0,
                             (GLvoid*) 0);

    f->glEnableVertexAttribArray(m_vboCount++);

    m_buffers.push_back(vbo);
}


void BaseModel::addEBO(const QVector<CGLuint>& indices)
{
    if (indices.count() > 0)
    {
        QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

        GLuint ebo;
        f->glGenBuffers(1, &ebo);
        // todo:why dont need bindbuffer 0 ?
        f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        f->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                        indices.size() * sizeof (indices[0]),
                indices.data(),
                GL_STATIC_DRAW);
        m_buffers.push_back(ebo);
    }
}
