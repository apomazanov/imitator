#include "lord.h"

Lord::Lord() : QObject()
{
    cout << "Initializing..." << endl;
    ParamsRaw params("../Imitator/config.json");

    // TODO: настроить writer

    // TODO: Receiver

    _locator = new Locator(&params);

    sampling_timedelta = 1.0 / params.getParam("FREQUENCY").toDouble();
    output_data_type = params.getParam("WRITE_MODE");
    steps_total = params.getParam("LOCATOR_ENCODER_RESOLUTION").toDouble();

    // Прореживание
    if (params.ifContainsSimple("THINNING"))
    {
        step_with_thinning = 1 * params.getParam("THINNING").toDouble();
        steps_in_frame = steps_total / step_with_thinning;
    }
    else
    {
        angle_delta = (2 * M_PI) / params.getParam("LOCATOR_ENCODER_RESOLUTION").toDouble();
        // TODO: step_with_thinning
        // нужен Receiver
    }

    angle_delta = 2 * M_PI / steps_in_frame;
    world_time_delta = angle_delta / _locator->speed;

    // TODO: world_time
    // нужен Time

    // TODO: _receiver.time

    // Генерация списка целей
    _targets = new QList<TargetConstSpeed*>;
    for (int i = 0; i < params.getArraySize("TARGETS"); i++)
    {
        QMap<QString, QString> temp = params.getItemFromArray("TARGETS", i);
        TargetConstSpeed *target = new TargetConstSpeed(&temp);
        target->time_delta = world_time_delta;
        _targets->append(target);
    }
}
