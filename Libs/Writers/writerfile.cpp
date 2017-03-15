#include "writerfile.h"

WriterFile::WriterFile(int receive_array_len, int steps_in_frame, QString filename)
{
    if (!QDir("data").exists())
        QDir().mkdir("data");
    datafile = new QFile();
    QStringList str_list = filename.split(".");
    datafile->setFileName(QString("data/%1(%2).%3")
                          .arg(str_list[0])
                          .arg(QDateTime::currentDateTime().toString("hh:mm:ss_dd.MM.yyyy"))
                          .arg(str_list[1]));
    if (!datafile->open(QFile::WriteOnly))
    {
        cout << "data_dpor file error" << endl;
        return;
    }


}
