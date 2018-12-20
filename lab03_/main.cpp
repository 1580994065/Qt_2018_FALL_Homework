#include "mainwidget.h"
#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
     QApplication a(argc, argv);

    qSetMessagePattern("%{file}(%{line}): %{message}");             //!< 自定义qDebug的输出pattern
    qRegisterMetaType< QList<QDateTime> >("QList<QDateTime>");      //!< 注册自定义类型，在信号与槽中使用

//    //设置全局样式
//    QString fileDir=QCoreApplication::applicationDirPath()+"/flat_blue.qss";
//    QFile qss(fileDir);
//    qss.open(QFile::ReadOnly);
//    qDebug()<<qss.error();
//    qApp->setStyleSheet(qss.readAll());

    mainWidget w;
    w.show();

    return a.exec();
}
