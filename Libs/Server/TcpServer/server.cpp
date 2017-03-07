#include "server.h"

Server::Server(QObject *parent, int port) : QObject(parent)
{
    tcpServer = new QTcpServer();
    timRepeater = new QTimer();

    connect(tcpServer, SIGNAL(newConnection()),
            this, SLOT(slotNewConnection()));


    if (!tcpServer->listen(QHostAddress::Any, port))
    {
        cout << "Unable to start the server: "
             << QString(tcpServer->errorString()).toStdString() << endl;
        tcpServer->close();
        return;
    }
}

void Server::sendToClient(QTcpSocket* tcpClient, QByteArray data)
{
    tcpClient->write(data);
}

void Server::slotReadFromClient()
{
    QTcpSocket *tcpClient = (QTcpSocket*)sender();
    QByteArray buf = tcpClient->readAll();
    QString mess = QString::fromLocal8Bit(buf);
    cout << ">>> " << mess.toStdString() << endl;
}

void Server::slotNewConnection()
{
    QTcpSocket *tcpClient = tcpServer->nextPendingConnection();
    connect(tcpClient, SIGNAL(disconnected()),
            tcpClient, SLOT(deleteLater()));
    connect(tcpClient, SIGNAL(readyRead()),
            this,      SLOT(slotReadFromClient()));
    connect(tcpClient, SIGNAL(disconnected()),
            this     , SLOT(slotDisconnected()));

    QString mess = QString("New User: %1:%2")
            .arg(tcpClient->localAddress().toString())
            .arg(tcpClient->localPort());
    cout << mess.toStdString() << endl;

    QTcpSocket temp = *tcpClient;
    mapUsers.append(temp);

    QByteArray data = QByteArray::fromStdString(QString("Hello!").toStdString());
    sendToClient(tcpClient, data);

    timRepeater->start(2000);
}

void Server::slotTimerRepeaterTimeout()
{
    num++;
    QByteArray data = QByteArray::number(num);

}

void Server::slotDisconnected()
{
    QTcpSocket *tcpClient = (QTcpSocket*)sender();

    QString mess = QString("User %1:%2 disconnected")
            .arg(tcpClient->localAddress().toString())
            .arg(tcpClient->localPort());
    cout << mess.toStdString() << endl;
}
