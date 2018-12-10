#include "dataworker.h"
#include <QMessageBox>

extern enum RESOURCE resource; //查询数据来源选项

DataWorker::DataWorker(QObject *parent) : QObject(parent)
{
    switch (resource) {
    case STU_SQL:
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

        db_q=QSqlQuery(db);//设置操作对象

        break;
    case STU_FILE:

        break;
    default:
        break;
    }

}

DataWorker::~DataWorker()
{
    db_q.clear();
    db.close();

}

void DataWorker::search(QString search_arg, SEARCH_OPTION m_option)
{

    switch (resource) {
    case STU_SQL:
        qDebug()<<"在sql中搜索";
        search_in_sql(search_arg,m_option);
        break;
    case STU_FILE:
        qDebug()<<"在文件中搜索";
        search_in_file(search_arg);
        break;
    default:
        break;
    }

}

QMap<QString, QStringList> *DataWorker::get_data()
{
    return &m_data;
}

//sql内搜索
void DataWorker::search_in_sql(QString search_arg,SEARCH_OPTION m_option)
{
     QString str;
    switch(m_option)
    {
    case STU_NAME:str=QString("where sName ='%1'").arg(search_arg);break;
    case STU_NUM:str=QString("where sNumber ='%1'").arg(search_arg);break;
    default:break;
    }
    QString m_qrl=QString("select t_stud_info.sName as '姓名',t_courses.courseName as '课程名称',"
                         "t_stud_course_info.scScores as '成绩',t_courses.courseCredit as '学分' "
                         "from "
                         "(t_stud_course_info inner join t_courses on t_stud_course_info.scCourseID = t_courses.courseID) "
                         "inner join t_stud_info on t_stud_info.sNumber = t_stud_course_info.scNumber "
                         "%1 "
                         "order by t_stud_course_info.scNumber "
                         ";").arg(str);

    if(!db_q.exec(m_qrl))
        {
            qDebug()<<db_q.lastError();
        }
        else
        {
            if(db_q.size()==0)
            {
                QMessageBox::warning(NULL
                                     , "warning"
                                     , "未查询到数据"
                                     , QMessageBox::Yes);//查询失败跳出对话框
                return ;
            }

            QStringList course_Name,scScores,courseCredit;
            while(db_q.next())
            {
                course_Name<<db_q.value(1).toString();
                scScores<<db_q.value(2).toString();
                courseCredit<< db_q.value(3).toString();
            }

            //构造map
            m_data.insert("课程名称",course_Name);
            m_data.insert("成绩",scScores);
            m_data.insert("学分",courseCredit);
            QStringList temp;
            temp.append(leveltrans(m_data.value("成绩"),m_data.value("学分")));
            m_data.insert("gpa",temp);
        }

    //得到学生信息
    m_qrl = QString("select sNumber,sName,sMajor,sClass from t_stud_info %1").arg(str);

       if(!db_q.exec(m_qrl))
       {
           qDebug()<<db_q.lastError();
       }
       else
       {
            QStringList temp1,temp2,temp3,temp4;
            db_q.next();
               temp1.append(db_q.value(0).toString());
               temp2.append(db_q.value(1).toString());
               temp3.append(db_q.value(2).toString());
               temp4.append(db_q.value(3).toString());
               m_data.insert("学号",temp1);
               m_data.insert("姓名",temp2);
               m_data.insert("专业",temp3);
               m_data.insert("年级",temp4);
       }
       emit updat_chart(&m_data);//更新图表
}

void DataWorker::search_in_file(QString search_arg)
{
    QString temp;
    //遍历搜索
    for(int i=0;i<file_input.size();i++)
    {
        temp=file_input.at(i);
        if(temp.contains(search_arg))
        {

            QStringList stu_num,stu_name,stu_major,stu_grade;

            QStringList split_list=temp.split(",",QString::SkipEmptyParts);
            stu_num.append(split_list.at(1));
            stu_name.append(split_list.at(2));
            stu_major.append(split_list.at(3));
            stu_grade.append(split_list.at(4));
            m_data.insert("学号",stu_num);
            m_data.insert("姓名",stu_name);
            m_data.insert("专业",stu_major);
            m_data.insert("年级",stu_grade);

             QStringList course_Name,scScores,courseCredit;
            //读取表头
            QStringList split_title=file_input.at(1).split(",",QString::SkipEmptyParts);
            //动态增加成绩
            for(int i=0;i<(split_title.size()-5);i++)
            {
                course_Name.append(split_title.at(5+i));
                scScores.append(split_list.at(5+i));
                courseCredit.append("未知");
            }
            m_data.insert("课程名称",course_Name);
            m_data.insert("成绩",scScores);
            m_data.insert("学分",courseCredit);
            m_data.insert("gpa",QStringList("未知"));
            qDebug()<<m_data;
            emit updat_chart(&m_data);//更新图表
            return;
        }
    }

    //遍历结束，没有查询到
    QMessageBox::warning(NULL
                         , "warning"
                         , "未查询到数据"
                         , QMessageBox::Yes);//查询失败跳出对话框
}
QString DataWorker::leveltrans(QStringList score,QStringList credit)
{

    QStringList leaveList;
    leaveList<<"优秀"<<"良好"<<"中等"<<"及格"<<"不及格"<<"缓考"<<"旷考";
    double myPoint=0;
    double sum=0;
    for(int i=0;i<score.size();i++)
    {
        QString toscore=score.at(i);
        QString mycredit=credit.at(i);
        if (leaveList.contains(score.at(i)))
        {
            switch (leaveList.indexOf(score.at(i)))
            {
            case 0:                     // 优秀
                toscore= "95";
                break;
            case 1:                     // 良好
                toscore="85";
                break;
            case 2:                     // 中等
                toscore="75";
                break;
            case 3:                     // 及格
                toscore="65";
                break;
            case 4:                     // 不及格
                toscore="50";
                break;
            case 5:                     // 缓考
                toscore="0";
                //valid =0;
                break;
            case 6:                     // 旷考
                toscore="0";
                break;
            default:
                break;
            }
        }
        if(!toscore.toDouble())
            myPoint+=0;
        else
            myPoint+=((toscore.toDouble()/10-5)*mycredit.toDouble());

        sum+=mycredit.toDouble();

    }
    //qDebug()<<myPoint<<sum;
    double avg=myPoint/sum;
    QString s = QString::number(avg);
    return s;
}



void DataWorker::mfile_input(QStringList inputdata,QString path)
{
    file_path=path;
    file_input=inputdata;
    QStringList mclass=file_input.at(1).split(",",QString::SkipEmptyParts);

    for(int i=0;i<5;i++)
    mclass.removeFirst();//只保留课程

    m_data.insert("预读课程",mclass);//提供给添加数据界面使用
}

//添加数据，信号来自add_student界面
void DataWorker::do_add_stu_data(QStringList *mClass, QMap<QString, QString> *add_data)
{

    switch (resource) {
    case STU_FILE:
    {
        QFile file(file_path);
        QTextStream out(&file);
              int line=0;
              if (!file.open(QIODevice::ReadWrite | QIODevice::Text| QIODevice::Append))
                  return;
              out<<"后加,"<<line<<","<<add_data->value("学号")<<","<<add_data->value("姓名")
                <<","<<add_data->value("专业")<<","<<add_data->value("班级")<<",";
              for(int i=0;i<mClass->size();i++)
              {
                  out<<add_data->value(mClass->at(i));
                  if(i<(mClass->size()-1))    //最后一个不输出,
                      out<<",";
                  else
                      out<<"\n";
              }
    }
        break;
    case STU_SQL:
    {
        QString sql_code;
        //添加学生信息
        sql_code=QString("insert into t_stud_info (sNumber,sName,sMajor,sClass)"
                         "values ('%1','%2','%3','%4');").arg(add_data->value("学号"),
                                                             add_data->value("姓名"),
                                                             add_data->value("专业"),
                                                             add_data->value("年级"));
        if(!db_q.exec(sql_code))
                    {
                        qDebug()<<db_q.lastError();
                        QMessageBox::warning(NULL
                                             , "warning"
                                             , "添加失败"
                                             , QMessageBox::Yes);//失败跳出对话框
                        return;
                    }


        //添加课程信息
        for(int i=0;i<mClass->size();i++)
                {
                    QString courseID;
                    sql_code = QString("select courseID from t_courses where courseName='%1';").arg(mClass->at(i));

                    if(!db_q.exec(sql_code))
                    {
                        qDebug()<<db_q.lastError();
                    }
                    else
                    {
                        while(db_q.next())
                        {
                            courseID=db_q.value(0).toString();

                        }
                    }

                    sql_code = QString("insert into t_stud_course_info"
                                       "(scNumber,scCourseID,scScores)"
                                       " values ('%1','%2','%3');").arg(add_data->value("学号")
                                                                       ,courseID
                                                                       ,add_data->value(mClass->at(i)));

                    if(!db_q.exec(sql_code))
                    {
                        qDebug()<<db_q.lastError();
                    }
                    else
                    {
                        qDebug()<<"插入成功";
                    }
                 }
    }
        break;
    default:
        break;
    }
    m_data=*new QMap<QString,QStringList>;
    m_data.insert("姓名",QStringList(add_data->value("姓名")));
    m_data.insert("学号",QStringList(add_data->value("学号")));
    m_data.insert("专业",QStringList(add_data->value("专业")));
    m_data.insert("年级",QStringList(add_data->value("年级")));

    m_data.insert("课程名称",*mClass);
    //添加成绩
    QStringList m_score;
    for(int i=0;i<mClass->size();i++)
        m_score.append(add_data->value(mClass->at(i)));
    m_data.insert("成绩",m_score);

    QString sql_code;
    QStringList m_credit;//各个课程学分
    for(int i=0;i<mClass->size();i++)
    {
        sql_code=QString("SELECT courseCredit FROM t_courses where courseName='%1';").arg(mClass->at(i));

    if(!db_q.exec(sql_code))
                {
                    qDebug()<<db_q.lastError();
                    QMessageBox::warning(NULL
                                         , "warning"
                                         , "添加失败"
                                         , QMessageBox::Yes);//失败跳出对话框
                    return;
                }
    else    //
    {
        while(db_q.next())
        {
            m_credit<<db_q.value(0).toString();
        }
    }
    }
    m_data.insert("学分",m_credit);
    m_data.insert("gpa",QStringList(leveltrans(m_score,m_credit)));
    emit updat_chart(&m_data);//更新图表
}
