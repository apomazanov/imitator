#ifndef TARGETCONSTSPEED_H
#define TARGETCONSTSPEED_H

#include "basetarget.h"

class TargetConstSpeed : public BaseTarget
{
public:
    explicit TargetConstSpeed(QMap<QString, QString> *targetConfig);

    double speed_sigma;
    double speed_mu;

    void update();
};

#endif // TARGETCONSTSPEED_H
