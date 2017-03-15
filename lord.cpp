#include "lord.h"

Lord::Lord() : QObject()
{
    // Класс, управляющий всем происходяшим.
    // Считывает конфиг, создает экземпляры целей, локатор и приемник и писателя в файл
    // Метод run запускает моделирование мира

    cout << "Initializing..." << endl;
    ParamsRaw params("../Imitator/config.json");

    // Receiver
    _receiver = new ReceiverRadio(&params);

    // Locator
    _locator = new Locator(&params);

    // Writer
    _writer = new WriterFile(_receiver->receive_array_len, steps_in_frame);

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
        step_with_thinning = (int)(((_locator->speed) *
                              (_receiver->pulse_repeat_time) *
                              (params.getParam("PULSE_ACCUMULATION_RATE").toDouble()))
                                    / angle_delta);
        steps_in_frame = (int)(steps_total / step_with_thinning);
    }

    angle_delta = 2 * M_PI / steps_in_frame;
    world_time_delta = angle_delta / (_locator->speed);

    // Time
    world_time = new Time(_receiver->pulse_repeat_time,
                      _receiver->sampling_time_delta,
                      steps_in_frame,
                      world_time_delta);

    // Грязный хак, но приемнику нужно получать время
    _receiver->time = world_time;

    // Генерация списка целей
    _targets = new QList<TargetConstSpeed*>;
    for (int i = 0; i < params.getArraySize("TARGETS"); i++)
    {
        QMap<QString, QString> tar_map = params.getItemFromArray("TARGETS", i);
        TargetConstSpeed *target = new TargetConstSpeed(&tar_map);
        target->time_delta = world_time_delta;
        target->timeDeltaSq();
        _targets->append(target);
    }
}

void Lord::run()
{
    // Начинаем генерацию и продолжаем до тех пор, пока не прервут
    cout << "Total steps in frame: " << steps_in_frame << endl;
    cout << "Begin generation" << endl;
    while(true)
    {
        // Для интерактивности выводим текущий угол и его код
        cout << "Begin new overview" << endl;
        // Пишем заголовок кадра
        // writer.new_frame()
    }
}
