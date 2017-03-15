#ifndef WRITERFILE_H
#define WRITERFILE_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <iostream>
#include <complex>
using namespace std;

class WriterFile : public QObject
{
    Q_OBJECT
public:
    explicit WriterFile(int receive_array_len, int steps_in_frame, QString filename = "data_drop.bin");
    void newFrame();
    void write(double angle, complex<double> *data);
    void down();

private:
    QFile *datafile;
};

#endif // WRITERFILE_H
