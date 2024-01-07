#include "home.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QCursor cursor(Qt::BlankCursor);
//    QApplication::setOverrideCursor(cursor);
//    QApplication::changeOverrideCursor(cursor);
    Home w;
    w.show();
    return a.exec();
}
