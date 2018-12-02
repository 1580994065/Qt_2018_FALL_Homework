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
}
