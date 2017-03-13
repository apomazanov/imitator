#include "targetconstspeed.h"

TargetConstSpeed::TargetConstSpeed(QMap<QString, QString> *targetConfig)
{
    cout << "speed" << endl;
    speed_sigma = targetConfig->value("speed_sigma").toDouble();
    speed_mu = targetConfig->value("mu").toDouble();;
}

void TargetConstSpeed::update()
{

}
