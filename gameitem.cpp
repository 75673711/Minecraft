#include "gameitem.h"

#include "camera/FunkyCamera.h"
#include "world/World.h"

#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_5_Core>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QQuickWindow>

#include <QDebug>

GameItemRenderer::GameItemRenderer():
    running_(false),
    ptr_camera_(new FunkyCamera),
    ptr_world_(new World)
{
    UpdateDeltaTime(true);
}

GameItemRenderer::~GameItemRenderer()
{
    if (ptr_camera_ != NULL)
    {
        delete ptr_camera_;
        ptr_camera_ = NULL;
    }
}

void GameItemRenderer::synchronize(QQuickFramebufferObject* ptr_item)
{
    GameItem* ptr_game_item = dynamic_cast<GameItem*>(ptr_item);
    if  (ptr_game_item != NULL)
    {
        if  (ptr_game_item->need_synchronize_)
        {
            ptr_game_item->need_synchronize_  = false;

            running_ = ptr_game_item->running_;
        }

        ptr_game_item->update();
    }
}

void GameItemRenderer::render()
{
    UpdateDeltaTime();

    if  (running_)
    {
        QOpenGLFunctions_4_5_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();

        // 绘制透明物体先设置为false
        //f->glDepthMask(true);
        f->glEnable(GL_DEPTH_TEST);
        f->glEnable(GL_CULL_FACE);

        f->glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
        f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        base_render_.render(size_, ptr_camera_, ptr_world_);
    }
}

QOpenGLFramebufferObject* GameItemRenderer::createFramebufferObject(const QSize &size)
{
    ptr_camera_->SetViewSize(size);

    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}

/////////////////////////////////////////////////////////////////////////

GameItem::GameItem(QQuickItem *parent) : QQuickFramebufferObject(parent),
    running_(false),
    need_synchronize_(false),
    ptr_renderer_(NULL)
{
    update();
    setFiltersChildMouseEvents(true);
}

QQuickFramebufferObject::Renderer *GameItem::createRenderer() const
{
    if (ptr_renderer_ == NULL)
    {
        GameItem* ptr_this = (GameItem*)this;
        ptr_this->ptr_renderer_ = new GameItemRenderer();

        return ptr_renderer_;
    }

    Q_ASSERT(false);
    return NULL;
}

bool GameItem::childMouseEventFilter(QQuickItem *ptr_item, QEvent *ptr_event)
{
    if  (ptr_renderer_->ptr_camera_ != NULL)
    {
        switch (ptr_event->type())
        {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* ptr_mouse_event = static_cast<QMouseEvent*>(ptr_event);
            ptr_renderer_->ptr_camera_->SetMousePress(ptr_mouse_event->button() == Qt::LeftButton,
                                                      ptr_mouse_event->button() == Qt::RightButton,
                                                      ptr_mouse_event->localPos().x(),
                                                      ptr_mouse_event->localPos().y());
        }
            break;
        case QEvent::MouseMove:
        {
            QMouseEvent* ptr_mouse_event = static_cast<QMouseEvent*>(ptr_event);
            ptr_renderer_->ptr_camera_->SetMouseMove(ptr_mouse_event->x(),
                                                      ptr_mouse_event->y());
        }
            break;
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* ptr_mouse_event = static_cast<QMouseEvent*>(ptr_event);
            ptr_renderer_->ptr_camera_->SetMousePress(!(ptr_mouse_event->button() == Qt::LeftButton),
                                                      !(ptr_mouse_event->button() == Qt::RightButton),
                                                      ptr_mouse_event->localPos().x(),
                                                      ptr_mouse_event->localPos().y());
        }
            break;
        default:
            break;
        }
    }

    return QQuickFramebufferObject::childMouseEventFilter(ptr_item, ptr_event);
}

//void GameItem::mousePressEvent(QMouseEvent* ptr_event)
//{
//    qDebug() << "press";
//    if  (ptr_renderer_->ptr_camera_)
//    {
//        ptr_renderer_->ptr_camera_->SetMousePress(ptr_event->button() == Qt::LeftButton,
//                                                  ptr_event->button() == Qt::RightButton, ptr_event->localPos().x(), ptr_event->localPos().y());
//    }

//    QQuickItem::mousePressEvent(ptr_event);
//}

//void GameItem::mouseMoveEvent(QMouseEvent* ptr_event)
//{
//    qDebug() << "mouseMoveEvent";
//    if  (ptr_renderer_->ptr_camera_)
//    {
//        ptr_renderer_->ptr_camera_->SetMousePress(ptr_event->button() & Qt::LeftButton,
//                                                  ptr_event->button() & Qt::RightButton, ptr_event->localPos().x(), ptr_event->localPos().y());
//    }

//    QQuickItem::mouseMoveEvent(ptr_event);
//}

//void GameItem::mouseReleaseEvent(QMouseEvent* ptr_event)
//{
//    qDebug() << "mouseReleaseEvent";
//    if  (ptr_renderer_->ptr_camera_)
//    {
//        ptr_renderer_->ptr_camera_->SetMousePress(!(ptr_event->button() == Qt::LeftButton),
//                                                  !(ptr_event->button() == Qt::RightButton), ptr_event->localPos().x(), ptr_event->localPos().y());
//    }

//    QQuickItem::mouseReleaseEvent(ptr_event);
//}

void GameItem::keyPressEvent(QKeyEvent* ptr_event)
{
    if  (ptr_renderer_->ptr_camera_)
    {
        switch (ptr_event->key())
        {
        case Qt::Key_W:
        case Qt::Key_S:
        case Qt::Key_A:
        case Qt::Key_D:
        case Qt::Key_R:
        case Qt::Key_F:
            ptr_renderer_->ptr_camera_->SetKeyPress(ptr_event->key(), true);
            break;
        default:
            break;
        }
    }

    QQuickFramebufferObject::keyPressEvent(ptr_event);
}

void GameItem::keyReleaseEvent(QKeyEvent* ptr_event)
{
    if  (ptr_renderer_->ptr_camera_)
    {
        switch (ptr_event->key())
        {
        case Qt::Key_W:
        case Qt::Key_S:
        case Qt::Key_A:
        case Qt::Key_D:
        case Qt::Key_R:
        case Qt::Key_F:
            ptr_renderer_->ptr_camera_->SetKeyPress(ptr_event->key(), false);
            break;
        default:
            break;
        }
    }

    QQuickFramebufferObject::keyReleaseEvent(ptr_event);
}

void GameItem::Start()
{
    if (!running_)
    {
        setFocus(true);
        //        setAcceptHoverEvents(true);
        //        setAcceptedMouseButtons(Qt::AllButtons);
        //        setFlag(ItemAcceptsInputMethod, true);

        need_synchronize_ = true;

        running_ = true;

        update();
    }
}

void GameItem::Stop()
{
    if (running_)
    {
        need_synchronize_ = true;

        running_ = false;
    }
}
