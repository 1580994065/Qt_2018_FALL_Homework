#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    w.setWindowTitle("学生数据查询");
    w.show();

    return a.exec();
}
