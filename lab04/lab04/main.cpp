#include "mainwindow.h"
#include <QApplication>
#include "welcome.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    welcome w;

    w.setWindowTitle("学生数据查询");
    w.show();

    return a.exec();
}
