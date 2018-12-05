#ifndef DATAWORKER_H
#define DATAWORKER_H

#include <QObject>
#include <QtSql>
#include <QSqlQuery>
#include <common.h>

class DataWorker : public QObject
{
    Q_OBJECT
public:
    explicit DataWorker(QObject *parent = nullptr);
    ~DataWorker();
    void search(QString search_arg,enum SEARCH_OPTION m_option);   //搜索
private:
    QSqlDatabase db;    //数据库对象
    QSqlQuery db_q;     //数据库操作对象
    QSqlQuery *test;
    QMap<QString,QStringList> m_data;   //存储得到的数据 有学生信息和课程信息
    QStringList column_map;             //与map配合使用，为列头 课程名称，成绩，学分 姓名，学号，年级，专业
    QString leveltrans(QStringList score,QStringList credit);//计算平均绩点
    QStringList file_input;

    void search_in_sql(QString search_arg,SEARCH_OPTION m_option);  //在sql中搜索
    void search_in_file(QString search_arg); //在文件中搜索
signals:
    void updat_chart(QMap<QString,QStringList> *m_data);//更新主界面图表
public slots:
    void mfile_input(QStringList inputdata);
};

#endif // DATAWORKER_H
