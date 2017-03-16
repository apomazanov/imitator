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

Server::~Server()
{
    cout << "closing" << endl;
}

void Server::broadcast(complex<double> *data, int data_size)
{

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
    cout << tcpClient->socketDescriptor() << " >>> " << mess.toStdString() << endl;
}

void Server::slotNewConnection()
{
    QTcpSocket *tcpClient = tcpServer->nextPendingConnection();

    int socketID = tcpClient->socketDescriptor();
    cout << "Socket = " << QString::number(socketID).toStdString() << endl;
    mapUsers[socketID] = tcpClient;

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
    QByteArray data = QByteArray::fromStdString(m.toStdString());
    foreach (int i, mapUsers.keys()) {
        sendToClient(mapUsers.value(i), data);
    }

}

void Server::slotDisconnected()
{
    foreach (int key, mapUsers.keys()) {
        if (mapUsers.value(key)->socketDescriptor() == -1)
        {
            cout << key << " disconnected" << endl;
            mapUsers.value(key)->close();
            mapUsers.value(key)->deleteLater();
            mapUsers.remove(key);
        }
    }
}
