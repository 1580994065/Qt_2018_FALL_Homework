#include "time_count.h"

time_count::time_count()
{
    timer_count=new QTimer;
    timer_count->setTimerType(Qt::PreciseTimer);//精确时钟

    count=0;
    connect(timer_count, SIGNAL(timeout()), this, SLOT(atom_interval()));
}

time_count::~time_count()
{
    timer_count->deleteLater();
}

void time_count::init()
{
    count=0;
}

void time_count::start()
{
    timer_count->start(precision);
}

void time_count::stop()
{
    timer_count->stop();
}

qint64 time_count::getInterval()
{
    return count*10;
}


void time_count::atom_interval()
{
    count++;
    timer_count->start(precision);//重新开启下一原子周期
}
