#include "server.h"

Server::Server(QObject *parent, int port) : QObject(parent)
{
    tcpServer = new QTcpServer();
    timRepeater = new QTimer();

    connect(tcpServer, SIGNAL(newConnection()),
            this, SLOT(slotNewConnection()));
    connect(timRepeater, SIGNAL(timeout()),
            this,        SLOT(slotTimerRepeaterTimeout()));


    if (!tcpServer->listen(QHostAddress::Any, port))
    {
        cout << "Unable to start the server: "
             << QString(tcpServer->errorString()).toStdString() << endl;
        tcpServer->close();
        return;
    }

    timRepeater->start(2000);
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
//    QString mess = QString("New User: %1:%2")
//            .arg(tcpClient->localAddress().toString())
//            .arg(tcpClient->localPort());
//    cout << mess.toStdString() << endl;

    int socketID = tcpClient->socketDescriptor();
    cout << "Socket = " << QString::number(socketID).toStdString() << endl;
    mapUsers[socketID] = tcpClient;

//    connect(mapUsers[socketID], SIGNAL(disconnected()),
//            mapUsers[socketID], SLOT(deleteLater()));
    connect(mapUsers[socketID], SIGNAL(readyRead()),
            this,               SLOT(slotReadFromClient()));
    connect(mapUsers[socketID], SIGNAL(disconnected()),
            this,               SLOT(slotDisconnected()));

    QByteArray data = QByteArray::fromStdString(QString("Hello!").toStdString());
    sendToClient(tcpClient, data);
}

void Server::slotTimerRepeaterTimeout()
{
    QString m = QDateTime::currentDateTime().toString();
//    cout << m.toStdString() << endl;
    QByteArray data = QByteArray::fromStdString(m.toStdString());
    foreach (int i, mapUsers.keys()) {
        sendToClient(mapUsers.value(i), data);
    }

}

void Server::slotDisconnected()
{
    QTcpSocket *tcpClient = (QTcpSocket*)sender();
    int temp = tcpClient->socketDescriptor();
    cout << "temp = " << temp << endl;

    foreach (int i, mapUsers.keys()) {
        cout << "i = " << i << endl;
        if (i == temp)
        {
            mapUsers.value(i)->close();
            QString m = QString("User %1 disconnected").arg(i);
            cout << m.toStdString() << endl;
            break;
        }
    }

    mapUsers.remove(temp);
}
