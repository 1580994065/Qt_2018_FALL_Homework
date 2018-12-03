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
            m_data.insert("课程名称",&course_Name);
            m_data.insert("成绩",&scScores);
            m_data.insert("学分",&courseCredit);
            QStringList temp;
            temp.append(leveltrans(m_data.value("成绩"),m_data.value("学分")));
            m_data.insert("gpa",&temp);
            emit updat_chart(&m_data);//更新图表
        }

    //得到学生信息
    m_qrl = QString("select * from t_stud_info %1").arg(str);

       if(!db_q.exec(m_qrl))
       {
           qDebug()<<db_q.lastError();
       }
       else
       {
           QStringList temp1,temp2,temp3,temp4;
           while(db_q.next())
           {
               temp1.append(db_q.value(0).toString());
               temp2.append(db_q.value(1).toString());
               temp3.append(db_q.value(2).toString());
               temp4.append(db_q.value(3).toString());
               m_data.insert("学号",&temp1);
               m_data.insert("姓名",&temp2);
               m_data.insert("专业",&temp3);
               m_data.insert("年级",&temp4);
           }
       }
}

QString DataWorker::leveltrans(QStringList *score,QStringList *credit)
{

    QStringList leaveList;
    leaveList<<"优秀"<<"良好"<<"中等"<<"及格"<<"不及格"<<"缓考"<<"旷考";
    double myPoint=0;
    double sum=0;
    for(int i=0;i<score->size();i++)
    {
        QString toscore=score->at(i);
        QString mycredit=credit->at(i);
        if (leaveList.contains(score->at(i)))
        {
            switch (leaveList.indexOf(score->at(i)))
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
