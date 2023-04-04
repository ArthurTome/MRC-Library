#include "mrc_gui.h"
#include <QApplication>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mrc_gui w;
    w.resize(720, 480);
    w.show();

    return a.exec();
}
