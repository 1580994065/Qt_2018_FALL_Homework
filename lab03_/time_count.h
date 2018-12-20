#ifndef TIME_COUNT_H
#define TIME_COUNT_H
#include <QTimer>

#define precision 10//10ms的精度

class QTimer;

class time_count:QObject
{
    Q_OBJECT

public:
    time_count();
    ~time_count();
    void init();//将计数值归零
    void start();
    void stop();
    qint64 getInterval();//获取计时器数值
private:
    QTimer *timer_count;
    qint64 count;
public slots:
    void atom_interval();//每过10ms进入
};

#endif // TIME_COUNT_H
