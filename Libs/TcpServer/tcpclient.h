#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <iostream>
using namespace std;

class TcpClient : public QTcpSocket
{
    Q_OBJECT

public:
    TcpClient(QObject *parent);

private slots:
    void slotReadData();
};

#endif // TCPCLIENT_H
