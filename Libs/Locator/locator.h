#ifndef LOCATOR_H
#define LOCATOR_H

#include <QObject>
#include <QMap>
#include <QList>
#include <qmath.h>
#include <QtMath>
#include <iostream>
#include "../Utils/config_handler/paramsraw.h"

using namespace std;

class Locator : public QObject
{
    Q_OBJECT
public:
    explicit Locator(QObject *parent = 0);


    double speed;
    double locator_angle;
    double locator_place;
    double locator_gain;
    double full_rotate_time;
    double receive_mode;
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
    void spin();

    double findMinInList(QList<double> list);

};

#endif // LOCATOR_H
