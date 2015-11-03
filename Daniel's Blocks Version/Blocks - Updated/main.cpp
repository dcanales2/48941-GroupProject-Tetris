#include "blockswindow.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BlocksWindow w;
    w.show();


    return app.exec();
}
