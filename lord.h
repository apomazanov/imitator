#ifndef LORD_H
#define LORD_H

#include <QObject>
#include "Libs/Locator/locator.h"
#include "Libs/Targets/targets.h"

class Lord : public QObject
{
    Q_OBJECT
public:
    explicit Lord();

private:
    Locator *_locator;
    // Receiver *_receiver;

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
    double world_time;
};

#endif // LORD_H
