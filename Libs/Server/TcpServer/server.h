#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QList>
#include <iostream>

using namespace std;


class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0, int port = 4242);

private:
    QTcpServer *tcpServer;
    QTimer *timRepeater;
    QList<QTcpSocket> mapUsers;
    int num = 0;

    void sendToClient(QTcpSocket *tcpClient, QByteArray data);

private slots:
    void slotReadFromClient();
    void slotNewConnection();
    void slotTimerRepeaterTimeout();
    void slotDisconnected();
};

#endif // SERVER_H
