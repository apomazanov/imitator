#include "tcpclient.h"

TcpClient::TcpClient(QObject* parent)
{
    connect(this, SIGNAL(disconnected()),
            this, SLOT(deleteLater()));
    connect(this, SIGNAL(readyRead()),
            this, SLOT(slotReadData()));
}

void TcpClient::slotReadData()
{
    QByteArray buf = this->readAll();
    QString mess = QString::fromLocal8Bit(buf);
    cout << ">>" << mess.toStdString() << endl;
}
