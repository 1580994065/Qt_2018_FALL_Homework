#include "add_student.h"
#include "ui_add_student.h"
#include "common.h"

extern enum RESOURCE resource; //查询数据来源选项

add_student::add_student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_student)
{
    ui->setupUi(this);
    add_data.insert("姓名",QString(""));
    add_data.insert("学号",QString(""));
    add_data.insert("专业",QString(""));
    add_data.insert("年级",QString(""));
    add_data.insert("入学年份",QString(""));
    add_data.insert("联系电话",QString(""));
}

add_student::add_student(QMap<QString, QStringList> *data, QWidget *parent):
    QDialog(parent),
    ui(new Ui::add_student)
{
    ui->setupUi(this);
    //设置字体
    ui->textEdit->setCurrentFont(QFont("Times", 15, QFont::Bold));
    //初始化课程
    switch (resource) {
    case STU_FILE:
        mClass=data->value("预读课程");
        break;
    case STU_SQL:
        mClass<<"复变函数"<<"毛泽东思想和中国特色社会主义理论体系概论"<<"大学物理B-2"<<"大学体育-3"
             <<"模拟电子线路"<<"信号与系统"<<"模拟电子线路课程设计";
        break;
    default:
        break;
    }

    qDebug()<<mClass;
    ui->comboBox_class->addItems(mClass);//添加课程
    //初始化map
    for(int i=0;i<mClass.size();i++)
    {
        add_data.insert(mClass.at(i),QString(""));//动态添加课程
    }
    add_data.insert("姓名",QString(""));
    add_data.insert("学号",QString(""));
    add_data.insert("专业",QString(""));
    add_data.insert("年级",QString(""));
    add_data.insert("入学年份",QString(""));
    add_data.insert("联系电话",QString(""));
}

add_student::~add_student()
{
    delete ui;
}

void add_student::update_textView()
{
    ui->lineEdit_score->clear();
    ui->textEdit->clear();
    if(!add_data.value("姓名").isEmpty())
    {
        ui->textEdit->append(QString("姓名："+add_data.value("姓名")));
    }
    if(!add_data.value("学号").isEmpty())
    {
        ui->textEdit->append(QString("学号："+add_data.value("学号")));
    }
    if(!add_data.value("专业").isEmpty())
    {
        ui->textEdit->append(QString("专业："+add_data.value("专业")));
    }
    if(!add_data.value("年级").isEmpty())
    {
        ui->textEdit->append(QString("年级："+add_data.value("年级")));
    }
    if(!add_data.value("入学年份").isEmpty())
    {
        ui->textEdit->append(QString("入学年份："+add_data.value("入学年份")));
    }
    if(!add_data.value("联系电话").isEmpty())
    {
        ui->textEdit->append(QString("联系电话："+add_data.value("联系电话")));
    }
    for(int i=0;i<mClass.size();i++)
    {
        //更新预览，循环课程名，查询是否为空
        if(!add_data.value(mClass.at(i)).isEmpty())
            ui->textEdit->append(QString(mClass.at(i)+"："+add_data.value(mClass.at(i))));
    }
}

void add_student::on_lineEdit_name_editingFinished()
{
    add_data["姓名"]=ui->lineEdit_name->text();
    update_textView();
}

void add_student::on_lineEdit_num_editingFinished()
{
    add_data["学号"]=ui->lineEdit_num->text();
    update_textView();
}

void add_student::on_lineEdit_major_editingFinished()
{
    add_data["专业"]=ui->lineEdit_major->text();
    update_textView();
}

void add_student::on_lineEdit_grade_editingFinished()
{
    add_data["年级"]=ui->lineEdit_grade->text();
    update_textView();
}

void add_student::on_lineEdit_score_editingFinished()
{
    add_data[ui->comboBox_class->currentText()]=ui->lineEdit_score->text();
    update_textView();
}

void add_student::on_buttonBox_accepted()
{

    emit add_stu_data(&mClass,&add_data);
}

void add_student::on_lineEdit_year_editingFinished()
{
    add_data["入学年份"]=ui->lineEdit_year->text();
    update_textView();
}

void add_student::on_lineEdit_tel_editingFinished()
{
    add_data["联系电话"]=ui->lineEdit_tel->text();
    update_textView();
}
