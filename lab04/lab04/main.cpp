#include "mainwindow.h"
#include <QApplication>
#include "welcome.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    welcome w;

    //设置全局样式
            QFile qss(QString(QCoreApplication::applicationDirPath())+"/flat_blue.qss");
            qss.open(QFile::ReadOnly);
            qApp->setStyleSheet(qss.readAll());

    w.setWindowTitle("学生数据查询");
    w.show();

    return a.exec();
}
