#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class TriangleWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit TriangleWindow(QWindow *parent = 0);
    ~TriangleWindow();

    virtual void render(QPainter*);
    virtual void render();
    virtual void initialize();
public slots:
    void renderNow();
protected:
    void exposeEvent(QExposeEvent*);
    void resizeEvent(QResizeEvent*);
private:
    bool m_update_pending;
    QOpenGLContext* m_context;
    QOpenGLPaintDevice* m_device;
};

#endif // TRIANGLEWINDOW_H
