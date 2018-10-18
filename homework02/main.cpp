#include <QDebug>
#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QList>
namespace SK {
enum SortKind{
    col01    =   0x00000001<<0,         //!< 第1列
    col02    =   0x00000001<<1,         //!< 第2列
    col03    =   0x00000001<<2,         //!< 第3列
    col04    =   0x00000001<<3,         //!< 第4列
    col05    =   0x00000001<<4,         //!< 第5列
    col06    =   0x00000001<<5,         //!< 第6列
    col07    =   0x00000001<<6,         //!< 第7列
    col08    =   0x00000001<<7,         //!< 第8列
    col09    =   0x00000001<<8,         //!< 第9列
    col10    =   0x00000001<<9,         //!< 第10列
    col11    =   0x00000001<<10,        //!< 第11列
    col12    =   0x00000001<<11,        //!< 第12列
    col13    =   0x00000001<<12,        //!< 第13列
    col14    =   0x00000001<<13,        //!< 第14列
    col15    =   0x00000001<<14,        //!< 第15列
    col16    =   0x00000001<<15,        //!< 第16列
    col17    =   0x00000001<<16,        //!< 第17列
    col18    =   0x00000001<<17,        //!< 第18列
    col19    =   0x00000001<<18,        //!< 第19列
    col20    =   0x00000001<<19,        //!< 第20列
    col21    =   0x00000001<<20,        //!< 第21列
    col22    =   0x00000001<<21,        //!< 第22列
    col23    =   0x00000001<<22,        //!< 第23列
    col24    =   0x00000001<<23,        //!< 第24列
    col25    =   0x00000001<<24,        //!< 第25列
    col26    =   0x00000001<<25,        //!< 第26列
    col27    =   0x00000001<<26,        //!< 第27列
    col28    =   0x00000001<<27,        //!< 第28列
    col29    =   0x00000001<<28,        //!< 第29列
    col30    =   0x00000001<<29,        //!< 第30列
    col31    =   0x00000001<<30,        //!< 第31列
    col32    =   0x00000001<<31,        //!< 第32列
};
}

#define mycmp(a) (d1.stu_data.at(a-1)>=d2.stu_data.at(a-1))?  1:0

//存储数据，每行存储在qstringlist
typedef struct{
    QStringList stu_data;
} studData;

//使qdebug可输出studata结构体
QDebug operator<< (QDebug d, const studData &data) {
    for(int i=0;i<data.stu_data.size();i++)
    {
        d.noquote()<<data.stu_data.at(i);//无引号输出
    }
    qDebug()<<"";
    return d;
}

// 比较类，用于std::sort第三个参数
class myCmp {
public:
    myCmp(int selectedColumn) { this->currentColumn = selectedColumn; }
    bool operator() (const studData& d1,const studData& d2);
private:
    int currentColumn;
};

//重载mycmp
bool myCmp::operator()(const studData &d1, const studData &d2)
{
    bool result = false;
    quint32 sortedColumn = 0x00000001<<currentColumn;
    switch (sortedColumn) {
    case SK::col01:result=mycmp(1);break;
    case SK::col02:result=mycmp(2);break;
    case SK::col03:result=mycmp(3);break;
    case SK::col04:result=mycmp(4);break;
    case SK::col05:result=mycmp(5);break;
    case SK::col06:result=mycmp(6);break;
    case SK::col07:result=mycmp(7);break;
    case SK::col08:result=mycmp(8);break;
    case SK::col09:result=mycmp(9);break;
    case SK::col10:result=mycmp(10);break;
    case SK::col11:result=mycmp(11);break;
    case SK::col12:result=mycmp(12);break;
    case SK::col13:result=mycmp(13);break;
    case SK::col14:result=mycmp(14);break;
    case SK::col15:result=mycmp(15);break;
    case SK::col16:result=mycmp(16);break;
    case SK::col17:result=mycmp(17);break;
    case SK::col18:result=mycmp(18);break;
    case SK::col19:result=mycmp(19);break;
    case SK::col20:result=mycmp(20);break;
    case SK::col21:result=mycmp(21);break;
    case SK::col22:result=mycmp(22);break;
    case SK::col23:result=mycmp(23);break;
    case SK::col24:result=mycmp(24);break;
    case SK::col25:result=mycmp(25);break;
    case SK::col26:result=mycmp(26);break;
    case SK::col27:result=mycmp(27);break;
    case SK::col28:result=mycmp(28);break;
    case SK::col29:result=mycmp(29);break;
    case SK::col30:result=mycmp(30);break;
    case SK::col31:result=mycmp(31);break;
    case SK::col32:result=mycmp(32);break;
    default:;break;
    }
    return result;
}


class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    void readFile();//从文件读取数据
    void doSort();//对数据进行排序
    void display();//输出所有数据
    void output_file(int line);//输出数据到文件
private:
    QString file_open;//打开文件的地址
    QList<studData>   data;//存储每行数据
    QStringList    title;   //数据表头
};

// 请补全
ScoreSorter::ScoreSorter(QString dataFile){
    file_open=dataFile;
}

void ScoreSorter::readFile()
{
    //打开文件
    QFile mfile(file_open);
    if(!mfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open the file!"<<endl;
       }
    studData nowdata;//暂存每行数据
    QString titile_t(mfile.readLine());
        //读取表头
        title = titile_t.split(" ", QString::SkipEmptyParts);//对数据进行分割
        //读取每行数据
        while(!mfile.atEnd()) {
        QString str(mfile.readLine());
        nowdata.stu_data = str.split(" ", QString::SkipEmptyParts);
        //去除数据中的回车符
        if((nowdata.stu_data).last() == "\n")
        {
                nowdata.stu_data.removeLast();
        }
        if(nowdata.stu_data.size()==0)
                     continue;
        data.append(nowdata);        
    }
    mfile.close();
    qDebug()<<title.count();
    //display();
}
/**
 * @brief ScoreSorter::doSort
 * 对每一列进行排序
 */
void ScoreSorter::doSort()
{
    //对每列循环排序
    for(int i=1;i<title.count();i++)
        {
            myCmp cmp_temp(i-1);    //数字从左移0位开始
            std::sort(data.begin(),data.end(),cmp_temp);
            qDebug()<<"排序后输出，当前排序第 "<<i <<" 列：";
            qDebug().noquote()<<title;
            display();
            qDebug()<<"------------------------------------------------\n";
            output_file(i);//输出到文件
    }
}

/**
 * @brief ScoreSorter::display
 * 输出整个数据
*/
void ScoreSorter::display()
{
    for(int i=0;i<data.size();i++)
    {
        qDebug()<<data.at(i);
    }
}

void ScoreSorter::output_file(int line)
{
    QFile file("sorted_"+file_open);
    //以追加方式打开
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream<<QString("排序后输出，当前排序第").toUtf8()<<line <<QString(" 列：").toUtf8()<<"\n";
    //输出表头
    for(int i=0;i<title.count();i++)
        stream<<title.at(i)<<"\t";
    stream<<'\n';
    //输出数据
    for(int i=0;i<data.count();i++)
    {
        for(int j=0;j<title.count()-1;j++)
        {
            stream<<data.at(i).stu_data.at(j)<<"\t"<<"\t";
        }
        stream<<"\n";
    }
    file.close();
}

int main()
{
    //qInstallMessageHandler(myMessageOutput);  //无法使用qdebug
    QString datafile = "data.txt";

    // 如果排序后文件已存在，则删除之
    QFile f("sorted_"+datafile);
    if (f.exists()){
        f.remove();
    }
    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();
    char stop=getchar();//使输出暂时停止
    return 0;
}

