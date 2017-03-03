#include "trianglewindow.h"

#include <QCoreApplication>
#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>

TriangleWindow::TriangleWindow(QWindow *parent)
    : QWindow(parent)
    , m_update_pending(false)
    , m_context(0)
    , m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

TriangleWindow::~TriangleWindow()
{
    delete m_device;
}

void TriangleWindow::render(QPainter *painter)
{
    Q_UNUSED(painter)
}

void TriangleWindow::render()
{
    if(!m_device)
        m_device = new QOpenGLPaintDevice;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_device->setSize(size());
    QPainter painter(m_device);
    render(&painter);
}

void TriangleWindow::initialize()
{
    glClearColor(0.5, 0.5, 0.5, 1);
}

void TriangleWindow::renderNow()
{
    if (!isExposed())
        return;
    m_update_pending = false;
    bool needsInitialize = false;
    if (!m_context)
    {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }
    m_context->makeCurrent(this);
    if (needsInitialize)
    {
        initializeOpenGLFunctions();
        initialize();
    }
    render();
    m_context->swapBuffers(this);
}

void TriangleWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);
    if (isExposed())
        renderNow();
}

void TriangleWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if (isExposed())
        renderNow();
}
