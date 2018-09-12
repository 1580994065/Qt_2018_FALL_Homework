#include <QCoreApplication>
#include <QDebug>
#include <array>
#include <QList>
#include<algorithm>

using namespace std;

#define  WORD_HI(xxx)  (((xxx) >> 24))         //取32位最高8位
#define  WORD_LHI(xxx)  (((xxx) >> 16)& 255)   //取32位次高8位
#define  WORD_HLO(xxx)  ((((xxx) >>8) & 255))  //取32位次低8位
#define  WORD_LO(xxx)  (((xxx) & 255))         //取32位最低8位

#define  MAX(x, y)  ( ((x) > (y)) ? (x) : (y) )//取最大值
#define  MIN(x, y)  ( ((x) < (y)) ? (x) : (y) )//取最小值

#define  at(x) values.at(x)                    //取数组中数

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    unsigned int test=0x12345678;               //测试数据
    QList<qint8> values;

    //向数组中添加各位数
    values<<WORD_HI(test);
    values<<WORD_LHI(test);
    values<<WORD_HLO(test);
    values<<WORD_LO(test);
    qDebug("原始值:0x%x==%d",test,test);       //显示原始数值
    qDebug("0x%x==%d 0x%x==%d 0x%x==%d 0x%x==%d",//显示各8位数值
           at(0),at(0),at(1),at(1),
           at(2),at(2),at(3),at(3));

    //比较各位数据
    qDebug("最高8位和次高8位最大值：0x%x(%d)"       //比较高位大小
           ,MAX(at(0),at(1)),MAX(at(0),at(1)));
    qDebug("最低8位和次低8位最大值：0x%x(%d)"       //比较低位大小
           ,MIN(at(2),at(3)),MAX(at(2),at(3)));


    //重新组合数据
    unsigned int new_test=at(1)
                          +(at(3)<<8)
                          +(at(0)<<16)
                          +(at(2)<<24);
    qDebug("重新组合后数值:0x%x(%d)",new_test,new_test);

    //排序数组
    qDebug("排序前：（%d,%d,%d,%d）"               //显示原序列
           ,at(0),at(1),at(2),at(3));
    sort(values.begin(),values.end(),greater<qint8>());
    qDebug("排序后：（%d,%d,%d,%d）"               //显示排序后序列
           ,at(0),at(1),at(2),at(3));
    return a.exec();
}
