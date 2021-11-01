/* This file is part of QNtp, a library that implements NTP protocol.
 *
 * Copyright (C) 2011 Alexander Fokin <apfokin@gmail.com>
 *
 * QNtp is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * QNtp is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License 
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with QNtp. If not, see <http://www.gnu.org/licenses/>. */

// this fily of QNtp lib is slightly modified by Dmitriy Rodin
#ifndef QNTP_NTP_CLIENT_H
#define QNTP_NTP_CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

#include "config.h"
#include "NtpReply.h"
#include "QNtp.h"

class QNTP_EXPORT NtpClient: public QObject {
  Q_OBJECT;

public:
  NtpClient(const QString& stringAddress, quint16 bindPort, QObject *parent = NULL);
  virtual ~NtpClient();
  bool sendRequest();
  QString getIPofNTPserver();

Q_SIGNALS:
  void replyReceived(const QHostAddress &address, quint16 port, const NtpReply &reply);

private Q_SLOTS:
  void readPendingDatagrams();

private:
  void init(const QHostAddress &bindAddress, quint16 bindPort);
  QUdpSocket *mSocket;
  QString mFirstIPofNTPserver;
  quint16 mPort;
};

#endif // QNTP_NTP_CLIENT_H
