#include "server.h"

Server::Server(QObject *parent, int port) : QObject(parent)
{
    tcpServer = new QTcpServer();
    timRepeater = new QTimer();

    connect(tcpServer,  SIGNAL(newConnection()),
            this,       SLOT(slotNewConnection()));
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

void Server::sendToClient(TcpClient *tcpClient, QByteArray data)
{
    tcpClient->write(data);
}

void Server::incomingConnection(int socketID)
{
    TcpClient *tcpClient = new TcpClient(this);
    tcpClient->setSocketDescriptor(socketID);
    cout << "new" << endl;
}

void Server::slotNewConnection()
{
//    TcpClient *tcpClient = new TcpClient(this);
//    int socketID = tcpServer->nextPendingConnection()->socketDescriptor();
//    tcpClient->setSocketDescriptor(socketID);

//    cout << "Socket = " << QString::number(socketID).toStdString() << endl;
//    mapUsers[socketID] = tcpClient;

////    connect(mapUsers[socketID], SIGNAL(disconnected()),
////            this,               SLOT(slotDisconnected()));

//    QByteArray data = QByteArray::fromStdString(QString("Hello!").toStdString());
//    sendToClient(tcpClient, data);
}

void Server::slotTimerRepeaterTimeout()
{
    QString m = QDateTime::currentDateTime().toString();
    QByteArray data = QByteArray::fromStdString(m.toStdString());
    foreach (int i, mapUsers.keys()) {
        sendToClient(mapUsers.value(i), data);
    }

}

//void Server::slotDisconnected()
//{
//    TcpClient *temp = (TcpClient*)sender();
//    int k = temp->socketDescriptor();
//    mapUsers.remove(k);
//}
