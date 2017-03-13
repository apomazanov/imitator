#ifndef TARGETCONSTACCELERATION_H
#define TARGETCONSTACCELERATION_H

#include "basetarget.h"

class TargetConstAcceleration : public BaseTarget
{
public:
    explicit TargetConstAcceleration(QMap<QString, QString> *targetConfig = 0);

    double acceleration_sigma;
    double acceleration_mu;
    QMap<QString, double> acceleration;

    void update();
};

#endif // TARGETCONSTACCELERATION_H
