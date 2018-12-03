#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

enum SEARCH_OPTION search_option;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    search_option=STU_NUM;  //初始为学号搜索
    dataworker=new DataWorker();
    connect(dataworker,&DataWorker::updat_chart,this,&MainWindow::table_updata);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_search_clicked()
{  
    switch (search_option) {
    case STU_NAME:
        qDebug()<<"开始以姓名搜索";
        dataworker->search(ui->lineEdit_input->text(),STU_NAME);
        break;
    case STU_NUM:
        qDebug()<<"开始以学号搜索";
        dataworker->search(ui->lineEdit_input->text(),STU_NUM);
        break;
    default:
        break;
    }
}

void MainWindow::on_radioButton_num_clicked()
{
    search_option=STU_NUM;
}

void MainWindow::on_radioButton_name_clicked()
{
    search_option=STU_NAME;
}

void MainWindow::table_updata(QMap<QString, QStringList *> *m_data)
{
    qDebug()<<"更新图表";
    QString temp;

       //cellpadding规定单元边沿与其内容之间的空白。
       //align规定表格相对周围元素的对齐方式。
       //border规定表格边框的宽度。
       temp.append("<table border='1' cellpadding='10' align='center' >  <tr>    <td colspan='4'align='center' bgcolor='#9DCEFF' >");

       temp.append("学生成绩统计");

       temp.append("</td>      </tr>");
       temp.append(" <tr>   <td width='80' >序号</td>   <td>课程名称</td>   <td>成绩</td>    <td>学分</td>      </tr> ");
       for(int i=0;i<m_data->value("课程名称")->size();i++)
       {
           temp.append(" <tr>   <td> ");
           temp.append(QString::number(i+1));
           temp.append("</td>   <td>");
           temp.append(m_data->value("课程名称")->at(i));
           temp.append("</td>   <td>");
           temp.append(m_data->value("成绩")->at(i));
           temp.append("</td>   <td>");
           temp.append(m_data->value("学分")->at(i));
           temp.append("</td>    </tr> ");

       }
       temp.append("<tr bgcolor='#9DCEFF' >     <td colspan='4'align='center' >");
       temp.append("平均绩点为");
       temp.append(m_data->value("gpa")->at(0));
       temp.append("</td>      </tr></table>");
       ui->textEdit->clear();
       ui->textEdit->append(temp);
       qDebug("kais");
       ui->lineEdit_stu_name->setText(m_data->value("姓名")->at(0));
       qDebug()<<"ok";
       ui->lineEdit_stu_number->setText(m_data->value("学号")->at(0));
       ui->lineEdit_stu_major->setText(m_data->value("专业")->at(0));
       ui->lineEdit_stu_gread->setText(m_data->value("年级")->at(0)) ;
}
