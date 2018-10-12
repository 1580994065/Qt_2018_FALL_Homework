#include <iostream>
#include <QCoreApplication>
#include <QVector>
#include<QDebug>

using namespace std;

/*brief: the unit of data is a struct called stu_struct
 *      I use vector to link data
 *      then using the std::sort funcion to sort data
 *problems solving: the compatibility of data output is a big problem
 *                  firstly I want to use qdebug to output qstring,unsolved
 *                  then cout,text in chaos,change code to GBK can solve this
 *                  but qdebug still can't.
 *                  finaly i figure out that encode file with UTF-8 can output
 *                  with qdebug.
*/


typedef struct{
    QString stu_num="";
    QString name="";
    qint64 subject1;
    qint64 subject2;
}stu_data;

void display(QVector<stu_data> *data);
bool cmp_name(stu_data a,stu_data b);
bool cmp_subject1(stu_data a,stu_data b);
bool cmp_subject2(stu_data a,stu_data b);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //form test datas
    stu_data data_1,data_2,data_3,data_4;
    //stu 1
    data_1.stu_num="1403130209";data_1.name="鲁智深";data_1.subject1=80;data_1.subject2=72;
    //stu 2
    data_2.stu_num="1403140101";data_2.name="林冲";data_2.subject1=82;data_2.subject2=76;
    //stu 3
    data_3.stu_num="1403140102";data_3.name="宋江";data_3.subject1=76;data_3.subject2=85;
    //stu4
    data_4.stu_num="1403140103";data_4.name="武松";data_4.subject1=88;data_4.subject2=80;

    //using vector to counect 4 struct
    QVector<stu_data> data;
    data.push_back(data_1);
    data.push_back(data_2);
    data.push_back(data_3);
    data.push_back(data_4);

    //display orginal data
    qDebug()<<"原数据:\n";
    display(&data);

    //sort of name
    QVector<stu_data> sort_name=data;
    sort(sort_name.begin(),sort_name.end(),cmp_name);
    qDebug()<<"按姓名排序:\n";
    display(&sort_name);

    //sort of subject1
    QVector<stu_data> sort_subject1=data;
    sort(sort_subject1.begin(),sort_subject1.end(),cmp_subject1);
    qDebug()<<"按课程一排序：\n";
    display(&sort_subject1);

    //sort of subject2
    QVector<stu_data> sort_subject2=data;
    sort(sort_subject2.begin(),sort_subject2.end(),cmp_subject2);
    qDebug()<<"按课程二排序：\n";
    display(&sort_subject2);

    return a.exec();
}

/**
 * @brief display
 * display data
 * @param data
 * pointer of struct data
 */
void display(QVector<stu_data> *data)
{
    qDebug()<<"学号"<<"             "<<"姓名"<<"       "<<"课程1"<<"  "<<"课程2\n";
    for(QVector<stu_data>::iterator m = data->begin(); m != data->end(); m++ )//m is temp struct
    {
        qDebug()<<m->stu_num<<"     "<<m->name<<"     "<<m->subject1<<"     "<<m->subject2<<"\n";
        //printf("%s    %s    %d     %d\n",m->stu_num,m->name,m->subject1,m->subject2);
    }
    cout<<endl;
}

/**
 * @brief cmp_name
 * especially used by sort function
 * @param a stu_data struct
 * @param b stu_data struct
 * @return 0 or 1
 */
bool cmp_name(stu_data a,stu_data b)
{
   if(a.name>=b.name)
   {
       return 0;
   }
   else
   {
       return 1;
   }
}

/**
 * @brief cmp_subject1
 * especially used by sort function
 * @param a stu_data struct
 * @param b stu_data struct
 * @return 0 or 1
 */
bool cmp_subject1(stu_data a,stu_data b)
{
    if(a.subject1>=b.subject1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief cmp_subject2
 * especially used by sort function
 * @param a stu_data struct
 * @param b stu_data struct
 * @return 0 or 1
 */
bool cmp_subject2(stu_data a,stu_data b)
{
    if(a.subject2>=b.subject2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

