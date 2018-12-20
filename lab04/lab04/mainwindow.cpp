#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

enum SEARCH_OPTION search_option;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    search_option=STU_NUM;  //初始为学号搜索
    dataworker=new DataWorker();
    connect(dataworker,&DataWorker::updat_chart,this,&MainWindow::table_updata);
    this->show();
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

DataWorker *MainWindow::getDataworker()
{
    return dataworker;
}

void MainWindow::table_updata(QMap<QString, QStringList> *m_data)
{
    qDebug()<<"更新图表";
    qDebug()<<*m_data;
    QString temp;

       //cellpadding规定单元边沿与其内容之间的空白。
       //align规定表格相对周围元素的对齐方式。
       //border规定表格边框的宽度。
       temp.append("<table border='1' cellpadding='10' align='center' >  <tr>    <td colspan='4'align='center' bgcolor='#9DCEFF' >");

       temp.append("学生成绩统计");

       temp.append("</td>      </tr>");
       temp.append(" <tr>   <td width='80' >序号</td>   <td>课程名称</td>   <td>成绩</td>    <td>学分</td>      </tr> ");
       for(int i=0;i<m_data->value("课程名称").size();i++)
       {
           temp.append(" <tr>   <td> ");
           temp.append(QString::number(i+1));
           temp.append("</td>   <td>");
           temp.append(m_data->value("课程名称").at(i));
           temp.append("</td>   <td>");
           temp.append(m_data->value("成绩").at(i));
           temp.append("</td>   <td>");
           temp.append(m_data->value("学分").at(i));
           temp.append("</td>    </tr> ");

       }
       temp.append("<tr bgcolor='#9DCEFF' >     <td colspan='4'align='center' >");
       temp.append("平均绩点为:");
       temp.append(m_data->value("gpa").at(0));
       temp.append("</td>      </tr></table>");
       ui->textEdit->clear();

       ui->textEdit->append(temp);
       ui->lineEdit_stu_name->setText(m_data->value("姓名").at(0));
       ui->lineEdit_stu_number->setText(m_data->value("学号").at(0));
       ui->lineEdit_stu_major->setText(m_data->value("专业").at(0));
       ui->lineEdit_stu_gread->setText(m_data->value("年级").at(0)) ;
}
//添加数据
void MainWindow::on_pushButton_adddata_clicked()
{
    add=new add_student(dataworker->get_data());
    connect(add,&add_student::add_stu_data,dataworker,&DataWorker::do_add_stu_data);
    add->setWindowTitle("添加数据");
    add->show();
}

void MainWindow::on_pushButton_output_sql_clicked()
{
    QString path=QFileDialog::getSaveFileName(this,
                        tr("存储的数据库文件"),"", tr("sql Files(*.db)"));
    QFile file( path );
    if ( file.open(QIODevice::Append))
    {
        qDebug()<<"创建文件"<<path;
        file.close();
    }
    else
        return;//创建失败

   //Step2:打开数据库。
   QSqlDatabase db;
   db=QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName("localhost");
   db.setPort(3306);
   db.setUserName("root");
   db.setPassword("");
   db.setDatabaseName("test");
   if(!db.open())
   {
        QMessageBox::warning(NULL
                             , "warning"
                             , "打开数据库失败"
                             , QMessageBox::Yes);//打开失败跳出对话框
   }
   QSqlQuery db_q;
   db_q=QSqlQuery(db);//设置操作对象

   //获取所有表名
   QString m_qrl="SELECT TABLE_NAME FROM information_schema.TABLES where TABLE_SCHEMA='test'";

   if(!db_q.exec(m_qrl))
       {
           qDebug()<<db_q.lastError();
       }
       else
       {
           if(db_q.size()==0)
           {
               return ;
           }
            QStringList schema;//存储表名
           while(db_q.next())
           {
               schema<<db_q.value(0).toString();//存储表名
                qDebug()<<db_q.value(0).toString();
           }
           //遍历表
           for(int i=0;i<schema.size();i++)
           {
                db.open();
               QStringList column;//表的列名
               m_qrl=QString("select COLUMN_NAME from INFORMATION_SCHEMA.Columns where table_name='%1' and table_schema='test';")
                                .arg(schema.at(i));
               if(!db_q.exec(m_qrl))
                   {
                       qDebug()<<db_q.lastError();
                   }
                   else
                   {
                       if(db_q.size()==0)
                       {
                           return ;
                       }
                    while(db_q.next())
                    {
                        column<<db_q.value(0).toString();//存储表的列名
                        qDebug()<<db_q.value(0).toString();
                    }
                    QVector<QStringList> data;
                    m_qrl=QString("select * from %1 ;").arg(schema.at(i));
                    if(!db_q.exec(m_qrl))
                        {
                            qDebug()<<db_q.lastError();
                        }
                        else
                        {
                            if(db_q.size()==0)
                            {
                                return ;
                            }
                            //读取表中数据
                         while(db_q.next())
                         {
                             QStringList temp;
                             for(int i=0;i<column.size();i++)
                                 temp<<db_q.value(i).toString();
                             data.append(temp);
                         }

                        }
                    db.close();
                    qDebug()<<data;

                    //数据库转化
                    QSqlDatabase db_lite = QSqlDatabase::addDatabase("QSQLITE");
                     db_lite.setDatabaseName(path);
                        if(!db_lite.open())
                        {
                             QMessageBox::warning(NULL
                                                  , "warning"
                                                  , "打开lite数据库失败"
                                                  , QMessageBox::Yes);//打开失败跳出对话框
                        }

                    QSqlQuery db_lite_q;
                    db_lite_q=QSqlQuery(db_lite);//设置操作对象
                    m_qrl=QString("CREATE TABLE IF NOT EXISTS %1 (").arg(schema.at(i));
                    for(int k=0;k<(column.size()-1);k++)
                    {
                        m_qrl.append(column.at(k));
                        m_qrl.append(" varchar(20),");
                    }
                    m_qrl.append(column.at(column.size()-1));
                    m_qrl.append(" varchar(20) );");//语句组合结束
                    qDebug()<<m_qrl;
                    //db_lite_q.prepare(m_qrl);
                    if( !db_lite_q.exec(m_qrl) )
                        qDebug() << db_lite_q.lastError();
                      else
                        qDebug() << "Table created!";

                    //逐行读取，写入
                    for(int line=0;line<data.size();line++)
                    for(int k=0;k<column.size();k++)
                    {
                        m_qrl=QString("INSERT INTO %1 (%2) VALUES ('%3');").arg(schema.at(i),column.at(k),data.at(line).at(k));
                        qDebug()<<m_qrl;
                        if(!db_lite_q.exec(m_qrl))
                            {
                                qDebug()<<db_lite_q.lastError();
                                return ;
                            }
                    }
                    db_lite.close();
               }
           }
           qDebug()<<"导出成功";
       }



}
