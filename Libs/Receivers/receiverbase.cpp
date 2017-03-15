#include "receiverbase.h"

ReceiverBase::ReceiverBase(ParamsRaw *receiverConfig)
{
    pulse_repeat_time = receiverConfig->getParam("PULSE_REPEAT_TIME").toDouble();
    sampling_time_delta = 1.0 / receiverConfig->getParam("FREQUENCY").toDouble();
    mu = 0;
    sigma = qSqrt(1.38e-23 * M_PI * 300 *
                  (1 + (receiverConfig->getParam("RECEIVER_NOISE").toDouble() - 1) *
                        receiverConfig->getParam("RECEIVER_TRACT").toDouble() *
                        receiverConfig->getParam("ANTENNA_TRACT").toDouble()
                   ));
    receive_array_len = pulse_repeat_time / sampling_time_delta;

    received_data = new complex<double>[receive_array_len];
    for (int i = 0; i < receive_array_len; i++)
        received_data[i] = complex<double>(0, 0);

    pulse_duration = receiverConfig->getParam("PULSE_DURATION").toDouble();
    wave_lambda = receiverConfig->getParam("LAMBDA").toDouble();
    signal_freq = 0;
    station_power = receiverConfig->getParam("STATION_POWER").toDouble();
    receiver_gain = receiverConfig->getParam("RECEIVER_GAIN").toDouble();
    receiver_mode = receiverConfig->getParam("RECEIVE_MODE").toInt();

//    attenuator = receiverConfig->value("STATION_ATTENUATOR").toDouble();
    int t = receiverConfig->getArraySize("STATION_ATTENUATOR");
    for (int i = 0; i < t; i++)
    {
        QMap<QString, double> tempd_map;
        QMap<QString, QString> temps_map = receiverConfig->getItemFromArray("STATION_ATTENUATOR", i);
        foreach (QString key, temps_map.keys()) {
            tempd_map[key] = temps_map.value(key).toDouble();
        }
        attenuator.append(tempd_map);
    }

    // Однозначная дальность обнаружения
    double uniq_range = 1.5e+8 * pulse_repeat_time;
    cout << "Uniq_range = " << uniq_range << endl;
}

double ReceiverBase::targetAmplitude(double loc_gain, TargetConstSpeed *target)
{
    if (receiver_mode == 0)
        // simple_target_amplitude
        // Используем опорные значения
        return loc_gain * target->getGain() * reduceSignal(target->getDistance());
    else
        // hard_target_apmlitude
        // Основное уравнение радиолокации
        // Амплитуда на входе локатора: корень квадратный из _calculate_input_power и делим на 50 Ом
        // Домнажаем на коэффициент усиления УПЧ (хр-ка приемника) и на коэффициент ослабление аттенюатора

        return (qSqrt(calculateInputPower(loc_gain, target)) / 2) *
                receiver_gain * reduceSignal(target->getDistance());
}

void ReceiverBase::blank()
{
    // Инициализирует массив, представляющий собой реализии на выходе АЦП. Длиной соответствует периоду ожидания
    // импульса, поделенного на период дескритизации.
    // Заполняет массив отсчетами шума, представляющего собой весь шумы антенно-приемного тракта.
    // Необходимо вызывать перед каждым началом приема
    QVector<double> temp_data = randomNormal();
    for (int i = 0; i < receive_array_len; i++)
    {
        received_data[i] = complex<double>(temp_data[i], temp_data[i]);
        received_data[i] *= receiver_gain;
    }
}

double ReceiverBase::reduceSignal(double distance)
{
    // Имитирует работу аттенюатора, ослабляет сигнал в зависимости от времени прихода
    double prev_value = attenuator[0].value("reduce");
    for (int i = 0; i < attenuator.count(); i++)
    {
        if (attenuator[i].value("range") > distance)
            return 1.0 / prev_value;
        else
            prev_value = attenuator[i].value("reduce");
    }
    return 1.0 / prev_value;
}

double ReceiverBase::calculateInputPower(double loc_gain, TargetConstSpeed *target)
{
    // Решает основное уравнение радиолокации для получения уровня принятого от цели сигнала
    return (station_power * target->getRsc() * qPow(loc_gain, 2) * qPow(wave_lambda, 2))/
            (qPow(4*M_PI, 3) * qPow(target->getDistance(), 4));
}

QVector<double> ReceiverBase::randomNormal()
{
    QVector<double> data;
    mt19937 generator;
    normal_distribution<double> distribution(mu, sigma);

    for (int i = 0; i < receive_array_len; i++)
        data.append(distribution(generator));

    return data;
}

complex<double> ReceiverBase::dopler(double t, double target_radial_speed)
{
    double dopler_freq = 2* target_radial_speed / wave_lambda;
    return exp(complex<double>(0.0, (-2) * M_PI * dopler_freq * t));
}

double ReceiverBase::heaviside(double x)
{
    if (x < 0.0)
        return 0.0;
    else
        return 1.0;
}

int ReceiverBase::mathCeil(double x)
{
    int floorx = floor(x);
    if ((x - floorx) > 0.0)
        return floorx + 1;
    else
        return floorx;
}

