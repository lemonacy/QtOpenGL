#include "trianglewindow.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    QSurfaceFormat format;
    format.setSamples(4);

    TriangleWindow w;
    w.setFormat(format);
    w.resize(640, 480);
    w.show();

    return a.exec();
}
