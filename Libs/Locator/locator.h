#ifndef LOCATOR_H
#define LOCATOR_H

#include <QObject>
#include <QMap>
#include <QList>
#include <qmath.h>
#include <QtMath>
#include <iostream>
#include "../Utils/config_handler/paramsraw.h"
#include "Libs/Targets/targets.h"

using namespace std;

class Locator : public QObject
{
    Q_OBJECT
public:
    explicit Locator(ParamsRaw *params);


    double speed;
    double locator_angle;
    double locator_place;
    double locator_gain;
    double full_rotate_time;
    int receive_mode;
    double zero_x;
    double zero_z;
    QList<double> x_angles;
    QList<double> z_angles;
    QList<double> x_values;
    QList<double> z_values;

private:
    ParamsRaw* config;

    void createTableDNA();
    void createSimpleDNA();
    void spin(double world_time_delta);

    double findMinInList(QList<double> list);
    double interpolate(double point, double x1, double x2, double y1, double y2);

    double gainForTarget(TargetBase *target);
    double gainForTargetPlace(TargetBase *target);
    double gainForTargetAzimuth(TargetBase *target);
};

#endif // LOCATOR_H
