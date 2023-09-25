#include "mainwindow.h"
#include<login.h>
#include <QApplication>

int main(int argc, char *argv[])
{
//    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    login f;
//    f.show();
    return a.exec();
}
