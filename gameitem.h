#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QQuickFramebufferObject>

#include "render/BaseRender.h"

class BaseCamera;
class World;

class GameItemRenderer : public QQuickFramebufferObject::Renderer
{
public:
    GameItemRenderer();
    ~GameItemRenderer();
    void synchronize(QQuickFramebufferObject* ptr_item) Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;

    BaseCamera* ptr_camera_;
    World* ptr_world_;

    bool running_;

    QSize size_;
    BaseRender base_render_;

};

class GameItem : public QQuickFramebufferObject
{
    Q_OBJECT
    friend class GameItemRenderer;
public:
    explicit GameItem(QQuickItem *parent = 0);

    QQuickFramebufferObject::Renderer *createRenderer() const Q_DECL_OVERRIDE;

protected:
    virtual void keyPressEvent(QKeyEvent* ptr_event) override;
    virtual void keyReleaseEvent(QKeyEvent* ptr_event) override;

    bool childMouseEventFilter(QQuickItem* ptr_item, QEvent* ptr_event) override;

signals:

public slots:
    void Start();
    void Stop();

private:
    bool running_;

    bool need_synchronize_;

    GameItemRenderer* ptr_renderer_;
};

#endif
