#include "targetconstacceleration.h"

TargetConstAcceleration::TargetConstAcceleration(QMap<QString, QString> *targetConfig)
{
    cout << "acceleration" << endl;
    acceleration_sigma = targetConfig->value("acceleration_sigma").toDouble();
    acceleration_mu = targetConfig->value("acceleration_mu").toDouble();

    acceleration["ax"] = targetConfig->value("ax").toDouble();
    acceleration["ay"] = targetConfig->value("ay").toDouble();
    acceleration["az"] = targetConfig->value("az").toDouble();
}

void TargetConstAcceleration::update()
{

}
