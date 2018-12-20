#include "welcome.h"
#include "ui_welcome.h"
#include <QFileDialog>
#include <QMessageBox>

enum RESOURCE resource; //查询数据来源选项

welcome::welcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
        QPalette pal = this->palette();
        pal.setBrush(backgroundRole(), QPixmap(":/back.jpg").scaled(this->size()));
        setPalette(pal);
}

welcome::~welcome()
{
    delete ui;
}
//sql搜索
void welcome::on_sql_source_button_clicked()
{
    resource=STU_SQL;
    this->close();//关闭welcome
    main_window=new MainWindow();//转入主界面
    main_window->setWindowTitle("学生数据查询");
}

//导入文件搜索
void welcome::on_file_source_button_clicked()
{
    resource=STU_FILE;

    QString path=QFileDialog::getOpenFileName(this,
                        tr("打开excel文件"),"", tr("csv Files(*.csv)"));
    QStringList  tempText;
    QFile file(path);

    if(path.isEmpty())
    {
        QMessageBox::information(NULL, tr("Info"), tr("文件路径为空"));
        return;
    }
    else{
        /*读取文件*/
           qDebug()<<path;
           if(!file.open(QIODevice::ReadOnly)){
               QMessageBox::critical(NULL,tr("错误"),tr("打开文件失败！"));
               return;
           }
           QTextStream in(&file);
           while(!in.atEnd()){
               tempText.append(in.readLine().trimmed());
           }
           file.close();
    }
    resource=STU_FILE;
    this->close();//关闭welcome
    main_window=new MainWindow();//转入主界面
    //发送信号，通知更新读取文件
    connect(this,&welcome::file_geted,main_window->getDataworker(),DataWorker::mfile_input);
    emit file_geted(tempText,path);
    main_window->setWindowTitle("学生数据查询");
}
