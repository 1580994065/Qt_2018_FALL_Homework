#include <iostream>
#include <QCoreApplication>
#include<QDebug>

using namespace std;

typedef struct{
    string stu_num="";
    string name="";
    int subject1;
    int subject2;
}stu_data;

bool cmp_Name()
{


}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //form test datas
    stu_data data_1,data_2,data_3,data_4;
    //stu 1
    data_1.stu_num="1403130209";
    data_1.name="鲁智深";
    data_1.subject1=80;
    data_1.subject2=72;
    //stu 2
    data_2.stu_num="1403140101";
    data_2.name="林冲";
    data_2.subject1=82;
    data_2.subject2=76;
    //stu 3
    data_3.stu_num="1403140102";
    data_3.name="宋江";
    data_3.subject1=76;
    data_3.subject2=85;
    //stu4
    data_4.stu_num="1403140103";
    data_4.name="武松";
    data_4.subject1=88;
    data_4.subject2=80;
    //using vector to counect 4 struct
    vector<stu_data> data;
    data.push_back(data_1);
    data.push_back(data_2);
    data.push_back(data_3);
    data.push_back(data_4);

    //输出原数据
    cout<<"原数据:\n";
    for(vector<stu_data>::iterator m = data.begin(); m != data.end(); m++ )//m is temp struct
    {
        cout<<m->stu_num<<"     "<<m->name<<"     "<<m->subject1<<"     "<<m->subject2<<endl;
        //printf("%s    %s    %d     %d\n",m->stu_num,m->name,m->subject1,m->subject2);
    }

    sort(data.begin(),data.end(),cmp_Name());
    return a.exec();
}


