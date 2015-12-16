#include "blockswindow.h"
#include "startwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BlocksWindow w;

    w.show();
    w.lower();
    return app.exec();
}
