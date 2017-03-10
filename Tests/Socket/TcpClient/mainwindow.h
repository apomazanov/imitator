#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_send_clicked();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void slotReadFromServer();

private:
    Ui::MainWindow *ui;
    QTcpSocket *sock;
    QByteArray buf;
};

#endif // MAINWINDOW_H
