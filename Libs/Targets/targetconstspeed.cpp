#include "targetconstspeed.h"

TargetConstSpeed::TargetConstSpeed(QMap<QString, QString> *targetConfig) : TargetBase(targetConfig)
{
//    cout << "speed" << endl;
    speed_sigma = targetConfig->value("speed_sigma").toDouble();
    speed_mu = targetConfig->value("mu").toDouble();
}

void TargetConstSpeed::update()
{
    // Передвигаем цель в соответствии с моделью движения


}
