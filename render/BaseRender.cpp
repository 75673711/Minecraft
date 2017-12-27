#include "BaseRender.h"

#include "model/BaseModel.h"
#include "texture/Texture.h"
#include "shader/BaseShader.h"
#include "shader/CommonShader.h"
#include "camera/BaseCamera.h"
#include "model/CubeModel.h"
#include "texture/TextureAltas.h"
#include "world/World.h"
#include "object/ChunkObject.h"

#include <QOpenGLFunctions_4_5_Core>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QDateTime>
#include <QtMath>

#include <QDebug>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec2 aTexCoord;\n"
                                 "uniform float time;\n"
                                 "uniform mat4 modelMatrix;\n"
                                 "uniform mat4 viewMatrix;\n"
                                 "uniform mat4 projMatrix;\n"
                                 "out vec2 TexCoord;\n"
                                 "void main()\n"
                                 "{\n"
                                //"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 //"   gl_Position = vec4(aPos.x, aPos.y + sin(time / 200.0), aPos.z, 1.0);\n"
                                 "   gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
                                 "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec2 TexCoord;"
                                           "uniform sampler2D ourTexture;\n"
        //                                   "uniform sampler2D texture2;\n"
        "void main()\n"
        "{\n"
        //"FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "FragColor = texture(ourTexture, TexCoord);\n"
        //"   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);\n"
        "}\n\0";

BaseRender::BaseRender() :
    init_(false),
    test_model(NULL),
    test_texture_(NULL),
    test_shader_(NULL)
{
}

BaseRender::~BaseRender()
{
    if (init_)
    {
        init_ = false;

        delete test_model;
    }
}

void BaseRender::EnsureInit()
{
    if (!init_)
    {
        init_ = true;

        QVector<CGLfloat> vertex_positions  = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        QVector<CGLfloat> texture_coordinates = {
            1.0f, 1.0f, // top right
            1.0f, 0.0f, // bottom right
            0.0f, 0.0f, // bottom left
            0.0f, 1.0f  // top left
        };

        QVector<CGLuint> indices = {
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

        //test_model = new BaseModel(vertex_positions, texture_coordinates, indices);
        test_model = new CubeModel();

        //test_texture_ = new Texture;
        //test_texture_->load(QString(":/image/res/image/chick.png"));
        TextureAltas::load();

        test_shader_ = new CommonShader(vertexShaderSource, fragmentShaderSource);
    }
}

void BaseRender::render(const QSize &view_size, BaseCamera *ptr_camera, World *ptr_world)
{
    EnsureInit();

    QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    test_shader_->bind();

    qint64 msec = QDateTime::currentMSecsSinceEpoch();
    float temp = (msec % 10000);
    test_shader_->setTime(temp);

    test_model->bind();
    TextureAltas::bind();

    QMatrix4x4 model;
    QMatrix4x4 view = ptr_camera->getViewMatrix();
    QMatrix4x4 projection= ptr_camera->getProjectionMatrix();

    model.rotate(0.0f, 1.0, 0.0, 0.0);
    //view.translate(0.0, 0.0, -1.0);
    //projection.perspective(45.0f, (float)view_size.width() / (float)view_size.height(), 0.1f, 100.0f);

    test_shader_->setModelMatrix(model);
    test_shader_->setViewMatrix(view);
    test_shader_->setProjMatrix(projection);

    test_model->Draw();

    for (int i = 0; i < ptr_world->GetChunks().count(); ++i)
    {
        QList<ChunkObject*> chunk_list = ptr_world->GetChunks()[i];
        // bind texture
        for (int j = 0; j < chunk_list.count(); ++j)
        {
            test_shader_->setModelMatrix(chunk_list[j]->GetModelMatrix());
            test_model->Draw();
        }
    }

//    for (int floor = 0; floor < 10; ++floor)
//    {
//        int begin_x = -floor;
//        int begin_z = -floor;
//        int begin_y = -floor;

//        for (int i = begin_x; i <= floor; ++i)
//        {
//            for (int j = begin_z; j <= floor; ++j)
//            {
//                QMatrix4x4 model;
//                model.translate(i, floor, j);
//                test_shader_->setModelMatrix(model);
//                test_model->Draw();
//            }
//        }
//    }

    //f->glDrawArrays(GL_TRIANGLES, 0, 36);
    //f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //test_texture_->unbind();
    TextureAltas::unbind();
    test_model->unbind();
    test_shader_->unbind();

    static int fps = 0;
    static qint64 time = 0;
    qint64 temp_time  = QDateTime::currentSecsSinceEpoch();
    if  (time != temp_time)
    {
        time = temp_time;
        qDebug() << fps;
        fps = 0;
    }
    else
    {
        fps++;
    }
}
