#ifndef LORD_H
#define LORD_H

#include <QObject>
#include "Libs/Locator/locator.h"
#include "Libs/Targets/targets.h"
#include "Libs/Receivers/receivers.h"
#include "Libs/Writers/writers.h"

class Lord : public QObject
{
    Q_OBJECT
public:
    explicit Lord();

    void run();

private:
    Locator *_locator;
    // Receiver только Radio
    ReceiverRadio *_receiver;
    WriterFile *_writer;

    // Поддерживаются только цели с постоянной скоростью !!!
    QList<TargetConstSpeed*> *_targets;

    // Период дискретизации приемника
    double sampling_timedelta;
    // Тип записываемых данных (мб не нужно)
    QString output_data_type;
    // В кадре один оборот
    double steps_total;
    // Шаг прореживания
    int step_with_thinning;
    int steps_in_frame;

    double angle_delta;
    // Период моделирования мира
    double world_time_delta;
    // Глобальное время
    Time* world_time;
};

#endif // LORD_H
