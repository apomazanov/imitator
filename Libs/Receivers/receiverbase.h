#ifndef RECEIVERBASE_H
#define RECEIVERBASE_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QVector>
#include <qmath.h>
#include <QtMath>
#include <iostream>
#include <complex>
#include <random>
#include "../Utils/config_handler/paramsraw.h"
#include "../Targets/targets.h"
#include "../Time/time.h"

using namespace std;

class ReceiverBase : public QObject
{
    Q_OBJECT
public:
    explicit ReceiverBase(ParamsRaw *receiverConfig);

    double targetAmplitude(double loc_gain, TargetConstSpeed *target);
    void blank();

    Time* time;
    double pulse_repeat_time;
    double sampling_time_delta;
    int receive_array_len;

protected:
    double mu;
    double sigma;

    // complex!!!
    complex<double> *received_data;

    double pulse_duration;
    double wave_lambda;
    double signal_freq;
    double station_power;
    QList<QMap<QString, double>> attenuator;
    double receiver_gain;
    int receiver_mode;
    double reduceSignal(double distance);
    double calculateInputPower(double loc_gain, TargetConstSpeed *target);
    QVector<double> randomNormal();
    complex<double> dopler(double t, double target_radial_speed);
    double heaviside(double x);
    int mathCeil(double x);
};

#endif // RECEIVERBASE_H
