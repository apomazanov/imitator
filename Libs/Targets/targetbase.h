#ifndef BASETARGET_H
#define BASETARGET_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QtMath>
#include <qmath.h>
#include <iostream>
#include <QDateTime>

using namespace std;

class TargetBase : public QObject
{
    Q_OBJECT
public:
    explicit TargetBase(QMap<QString, QString> *targetConfig);

    QMap<QString, double> translate_to_sph(QMap<QString, double> dec);
    double getOnRangeGain(double on_range, double on_range_gain);
    double getStaticGain();
    double getDistance();
    double getAzimuth();
    double getPlace();
    double getRadialSpeed();
    double getGain();
    double getRsc();
    void timeDeltaSq();

    double time_delta;

private:
    QMap<QString, double> cart_coord;
    QMap<QString, double> speed_for_coord;
    QMap<QString, double> sph_coord;
    double time_delta_sq;
    double get_gain;
    double rsc_sigma;
};

#endif // BASETARGET_H
