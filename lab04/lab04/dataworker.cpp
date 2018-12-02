#include "dataworker.h"
#include <QMessageBox>

DataWorker::DataWorker(QObject *parent) : QObject(parent)
{
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
}

DataWorker::~DataWorker()
{
    db_q.clear();
    db.close();

}

void DataWorker::search(QString search_arg, SEARCH_OPTION m_option)
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
            }
            qDebug()<<db_q.next();

            QStringList sName,course_Name,scScores,courseCredit;
            while(db_q.next())
            {
                //sName<<db_q.value(0).toString();
                course_Name<<db_q.value(1).toString();
                scScores<<db_q.value(2).toString();
                courseCredit<< db_q.value(3).toString();
            }

            //构造map
            m_data.insert("课程名称",&sName);
            m_data.insert("成绩",&scScores);
            m_data.insert("学分",&courseCredit);
        }
        emit updat_chart(&m_data);//更新图表
//    //得到学生信息
//    m_qrl = QString("select * from t_stud_info %1").arg(str);

//       if(!db_q.exec(m_qrl))
//       {
//           qDebug()<<db_q.lastError();
//       }
//       else
//       {
//           while(db_q.next())
//           {
//               m_data.insert("学号",db_q.value(0).toString());
//               m_data.insert("姓名",db_q.value(1).toString());
//               m_data.insert("专业",db_q.value(2).toString());
//               m_data.insert("年级",db_q.value(3).toString());
//           }
//       }
}
