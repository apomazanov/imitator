#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buf.clear();
    sock = new QTcpSocket();
    connect(sock, SIGNAL(readyRead()),
            this, SLOT(slotReadFromServer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_send_clicked()
{
    QString mess = ui->lineEdit_send->text();
    QByteArray d = QByteArray::fromStdString(mess.toStdString());
    sock->write(d);
    ui->lineEdit_send->clear();
}

void MainWindow::on_actionConnect_triggered()
{
    sock->connectToHost(ui->lineEdit_host->text(), ui->spinBox_port->value());
    ui->text_log->append(QString("Connected to host %1:%2")
                         .arg(ui->lineEdit_host->text())
                         .arg(QString::number(ui->spinBox_port->value())));
}

void MainWindow::on_actionDisconnect_triggered()
{
    sock->disconnectFromHost();
    ui->text_log->append(QString("Disconnected"));
}

void MainWindow::slotReadFromServer()
{
    buf = sock->readAll();
    QString mess = QString::fromLocal8Bit(buf);
    ui->text_log->append(QString(">>> %1")
                         .arg(mess));
    buf.clear();
}



