#include "home.h"
#include <QApplication>
//#include "modbusRtu/modbusrtu.h"
#include <QTimer>
//ModbusRtu *rtu=new ModbusRtu();
// #include "testCase/testcase.h"
// testCase *test=new testCase();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    QCursor cursor(Qt::BlankCursor);
    //    QApplication::setOverrideCursor(cursor);
    //    QApplication::changeOverrideCursor(cursor);
    Home w;
    w.show();
//    QTimer timer;
////    rtu->connectDevice();
//    QObject::connect(&timer, &QTimer::timeout, [&]() {
//    });
//    timer.start(500);

    return a.exec();
}
