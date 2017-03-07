#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QDateTime>
#include <iostream>
#include <QDebug>

#include "tcpclient.h"

using namespace std;


class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0, int port = 4242);

private:
    QTcpServer *tcpServer;
    QTimer *timRepeater;
    QMap<int, TcpClient*> mapUsers;

    void sendToClient(TcpClient *tcpClient, QByteArray data);
//    void incomingConnection(int socketID);

private slots:
    void slotNewConnection();
    void slotTimerRepeaterTimeout();
//    void slotDisconnected();
};

#endif // SERVER_H
