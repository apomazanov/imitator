#include "time.h"

Time::Time(double repeat_time, double arg_sampling_time, int directions_number, double direction_time)
{
    // Класс, предоставляющий отсчеты времени с учетом скорости вращения антенны и частоты АЦП
    // :param repeat_time: период повторения импульсов
    // :param sampling_time: период дескритизации АЦП
    // :param directions_number: количество различаемых угловых направлений (с учетом прореживания)
    // :param direction_time: время стояния в одном угловом направлении

    // Service vars
    n = repeat_time / arg_sampling_time;
    k = directions_number;

    world_time_step = direction_time;
    sampling_time = arg_sampling_time;
}

double Time::getTime(int direction_number, int count_number)
{
    // Функция возвращет значение времени по заданным значениям, если таких значений нет - возвращает IndexError
    // :param direction_number: номер углового направления
    // :param count_number: номер отсчета в массиве реаилизация принятого сигнала
    if ((k <= direction_number) || (n <= count_number))
    {
        cout << "getTime() index error" << endl;
        return 0;
    }
    else
        return ((direction_number * world_time_step) + (count_number * sampling_time));
}

double Time::getWorldTimeStep()
{
    // Функция возвращает значение периода моделированя мира
    return world_time_step;
}
