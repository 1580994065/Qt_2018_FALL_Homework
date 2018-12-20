#ifndef DATAWORKER_H
#define DATAWORKER_H

#include <QObject>
#include <QDateTime>

#define time_net_request_out 5000 //5s

class QNetworkAccessManager;
class QNetworkReply;
class QTimer;
class time_count;

/**
 * @brief dataWorker类
 *
 * dataWorker类负责数据的获取以及解析，
 * 当数据解析完成后，发送dataParseFinished信号，
 *
 */
class dataWorker : public QObject
{
    Q_OBJECT
public:
    explicit dataWorker(QObject *parent = 0);
    explicit dataWorker(QString date, QObject *parent = 0);
    ~dataWorker();
    void setRequestDate(QString newDate);
    void setRequestLocation(int index);
    QString requestDate();
    void doRequest();
    void getYrange(qreal* high,qreal* low);
    QString geturl();
protected:
    QString requestUrl();
    void httpGet(QString url);
    void initNetwork();
    void parseHTML(const QString sourceText);
    void parseData(const QString sourceText);
    void exportDataToFile(const QString dataText,QString head="weather");
    void Yrange();

protected slots:
    void httpsFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;         //!< 网络访问管理类对象
    QString _requestDate;                   //!< 请求年月
    QString _requestLocation;               //!< 请求地区

    QList<QDateTime> dataDate;              //!< 日期
    QList<qreal> dataHigh;                  //!< 最高温度，aqi
    QList<qreal> dataLow;                   //!< 最低温度，pm2.5

    qreal Yhigh=50;                            //y轴最大值
    qreal Ylow=0;                             //y轴最小值
    const QString splitter;                 //!< 数据分隔符
    const QString dataPath;                 //!< 数据保存路径
    QString url;                            //请求的url
    QTimer *m_timer_worning;                      //警告定时器
    time_count *m_timer_count;                    //计时器
signals:
    /**
     * @brief 数据解析完成信号
     * @param date 所获取数据年月列表
     * @param high 所获取数据最高温度列表
     * @param low 所获取数据最低温度列表
     *
     * 该信号在数据解析完成，将解析的数据以3个列表（QList）的形式作为信号参数发射，<br/>
     * 提醒界面开始更新图表数据。
     */
    void dataParseFinished(QList<QDateTime> date,QList<qreal> high, QList<qreal> low);

    /**
     * @brief httpRequestError
     *
     * @param error ： 错误信息
     *
     * http请求错误信号，当出现http请求错误时，发送该信号
     */
    void httpRequestError(QString error);

    /**
     * @brief dataParseError
     * @param error ： 错误信息
     *
     * 数据解析错误信号，当出现使用QXmlStreamReader解析数据错误时，发送该信号
     */
    void dataParseError(QString error);
    void statusFlash(QString file); //更新状态图片
public slots:
    void handleTimeout();
};


#endif // DATAWORKER_H
