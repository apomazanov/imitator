#ifndef BASETARGET_H
#define BASETARGET_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QtMath>
#include <qmath.h>
#include <iostream>


using namespace std;

class BaseTarget : public QObject
{
    Q_OBJECT
public:
    explicit BaseTarget(QMap<QString, QString> *targetConfig = 0);

    QMap<QString, double> cart_coord;
    QMap<QString, double> speed_for_coord;
    QMap<QString, double> sph_coord;
    double time_delta;
    double time_delta_sq;
//    double on_range;
//    double on_range_gain;
    double get_gain;
    double rsc_sigma;

private:
    QMap<QString, double> translate_to_sph(QMap<QString, double> dec);
    double getOnRangeGain(double on_range, double on_range_gain);
    double getStaticGain();
    double getDistance();
    double getAzimuth();
    double getPlace();
    double getRadialSpeed();
};

#endif // BASETARGET_H
