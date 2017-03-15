#include "receiverradio.h"

ReceiverRadio::ReceiverRadio(ParamsRaw *receiverConfig) : ReceiverBase(receiverConfig)
{

}

void ReceiverRadio::receive(int direction_number, double target_loc_gain, TargetConstSpeed *target, double los_angle)
{
    // Прием простого радиоимпульса
    // :param los_angle: текущее угловое положение локатора
    // :param direction_number: номер углового направления
    // :param target_loc_gain: значение ДНА в направлении цели
    // :param target: объект типа Target

    // Задержка до прихода сигнала
    double tau = 2.0 * target->getDistance() / 3e+8;
    // Индекс приемного массива, с которого в него надо добавлять отсчеты принятого сигнала
    int down = floor((tau + pulse_duration) / sampling_time_delta);
    // Солнышко скроется, приемник закроется
    if (down < receive_array_len)
    {
        // Не закрылся, ищем когда закончим принимать отсчеты
        int up = mathCeil((tau + 2*pulse_duration) / sampling_time_delta);
        // Долго ли коротко ли, а не начнется ли новый импульс
        if (up > receive_array_len)
            up = receive_array_len;
        // Мы нашли значения в строке матрицы времени, когда у нас есть отсчеты сигнала
        // С помощью класса Time достаем эти моменты времени и считаем отсчеты
        double current_time = time->getTime(direction_number, 0) - tau;
        double target_radial_speed = target->getRadialSpeed() * qCos(los_angle - target->getAzimuth());
        complex<double> signal = harmSignalFunctionWithDopler(current_time, target_radial_speed) *
                                 targetAmplitude(target_loc_gain, target);

        for (int i = down; i <= up; i++)
            received_data[i] += signal;
    }
}

complex<double> ReceiverRadio::harmSignalFunction(double t)
{
    // Модель излученного сигнала
    // :param t: время, с
    // :return: отсчет сигнала в заданный момент времени
    return exp(complex<double>(0.0, 2*M_PI*signal_freq*t));
}

complex<double> ReceiverRadio::harmSignalFunctionWithDopler(double t, double target_radial_speed)
{
    // Модель принятого сигнала с допплеровским сдвигом частоты (время задержки вычитать при вызове)
    // :param t: время, с
    // :param target_radial_speed: радиальная скорость цели, м/с
    // :return: отсчет сигнала в заданный момент времени
    return harmSignalFunction(t) * dopler(t, target_radial_speed);
}
