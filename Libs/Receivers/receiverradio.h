#ifndef RECEIVERRADIO_H
#define RECEIVERRADIO_H

#include "receiverbase.h"


class ReceiverRadio : public ReceiverBase
{
public:
    ReceiverRadio(ParamsRaw *receiverConfig);

    void receive(int direction_number, double target_loc_gain, TargetConstSpeed *target, double los_angle);

    complex<double> harmSignalFunction(double t);
    complex<double> harmSignalFunctionWithDopler(double t, double target_radial_speed);
};

#endif // RECEIVERRADIO_H
