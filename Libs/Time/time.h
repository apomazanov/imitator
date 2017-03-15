#ifndef TIME_H
#define TIME_H

#include <QObject>
#include <iostream>
using namespace std;

class Time : public QObject
{
    Q_OBJECT
public:
    explicit Time(double repeat_time, double arg_sampling_time, int directions_number, double direction_time);

    double getTime(int direction_number, int count_number);
    double getWorldTimeStep();

private:
    int n, k;
    double world_time_step;
    double sampling_time;
};

#endif // TIME_H
