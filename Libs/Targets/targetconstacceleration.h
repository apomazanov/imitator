#ifndef TARGETCONSTACCELERATION_H
#define TARGETCONSTACCELERATION_H

#include "targetbase.h"

class TargetConstAcceleration : public TargetBase
{
public:
    explicit TargetConstAcceleration(QMap<QString, QString> *targetConfig);

    double acceleration_sigma;
    double acceleration_mu;
    QMap<QString, double> acceleration;

    void update();
};

#endif // TARGETCONSTACCELERATION_H
