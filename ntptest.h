#pragma once

#include <QObject>
#include <QHostAddress>
#include <QHostInfo>
#include <QTimer>

#include "qntp/QNtp.h"
#include "qntp/NtpClient.h"
#include "qntp/NtpReply.h"

class NtpTest : public QObject
{
    Q_OBJECT

public:
    explicit NtpTest(int timeZone = 0, QObject *parent = 0);

    // for run from QML = user interface:
    Q_INVOKABLE void run();
    Q_INVOKABLE void setTimerInterval(QString interval);
    Q_INVOKABLE quint16 getTimerInterval();

public slots:
    void timeEnd();

signals:
    void differenceSignal( int dif );
    void wrongIntervalChangingSignal( int prev_interval );
    void sendMsg( QString msg );

private slots:
    void onReplyReceived(QHostAddress host, quint16 port, NtpReply reply);

private:
    NtpClient * m_client;   // Client for NTP lib
    int m_timeZone;     // Timezone
    QTimer *m_timer;    // Timeout timer that waits for a set time interval = mInterval
    quint16 mInterval;  // Interval between sendRequest
};
