#include "add_student.h"
#include "ui_add_student.h"

add_student::add_student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_student)
{
    ui->setupUi(this);
}

add_student::add_student(QMap<QString, QStringList> *data, QWidget *parent):
    QDialog(parent),
    ui(new Ui::add_student)
{
    ui->setupUi(this);
    mClass=data->value("预读课程");
    qDebug()<<mClass;
    ui->comboBox_class->addItems(mClass);//添加课程
}

add_student::~add_student()
{
    delete ui;
}
