#include <QDebug>
#include <QCoreApplication>
#include <QStringList>

#include "ntptest.h"

namespace my_np{
    const std::string ntp_server{"0.ua.pool.ntp.org"};
    const quint16 port{123};
    const quint16 interval{14}; // in ntpd start from 64sec and then correct this value. I use constant interval
}

NtpTest::NtpTest(int timeZone, QObject *parent)
    : QObject(parent)
    , m_timeZone(timeZone*3600)
    , m_timer(nullptr)
    , mInterval(my_np::interval)
{
    m_client = new NtpClient(QString(my_np::ntp_server.c_str()),my_np::port,this);
    connect(m_client, SIGNAL(replyReceived(QHostAddress,quint16,NtpReply)), this, SLOT(onReplyReceived(QHostAddress,quint16,NtpReply)));
    m_timer = new QTimer();
    m_timer->setInterval(mInterval*1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeEnd()));
}

void NtpTest::timeEnd() {
    //  the interval has ended, we repeat the time comparison
	
    this->run();
}

void NtpTest::run()
{
    emit sendMsg( "send request to ntp-server: " + QString(my_np::ntp_server.c_str())+", to its first ip: " + m_client->getIPofNTPserver());
    if ( m_client->sendRequest() ) {
        qDebug()<<"sendRequest works";
        m_timer->start();
        return;
    }
    qDebug()<<"sendRequest doen't work";  
}

void NtpTest::onReplyReceived( QHostAddress host, quint16 port, NtpReply reply )
{
    Q_UNUSED(host)
    Q_UNUSED(port)

    QDateTime Arrival{ QDateTime::currentDateTime() };

    QDateTime Receive{ reply.receiveTime() };
    QDateTime Originate{ reply.originTime() };
    QDateTime Transmit{ reply.transmitTime() };

    // difference = Receive — Originate — roundTripDelay/2
    qint64 diff  = Receive.msecsTo( Originate ) - reply.roundTripDelay()/2;

    emit differenceSignal( static_cast<int>( diff ) );
}

void NtpTest::setTimerInterval( QString interval ) {
    m_timer->stop();
    const int new_interval = interval.toInt();
    if (new_interval != 0 && new_interval > 0 ) {
        mInterval = new_interval;
        m_timer->setInterval( interval.toInt()*1000 );
        run();
        return;
    }
    emit wrongIntervalChangingSignal( mInterval );    //  send messsage to user - wrong interval - look in qml code
    run();
}

quint16 NtpTest::getTimerInterval() {
    return mInterval;
}
