#include "locator.h"

Locator::Locator(ParamsRaw *params) : QObject()
{
//    config = new ParamsRaw(0, "../../config.json");
    config = params;

    // Переводим в радианы
    speed = qDegreesToRadians(config->getParam("ROTATION_SPEED").toDouble());
    locator_angle = 0;
    locator_place = qDegreesToRadians(90.0);
    // Коэффициент усиления антенны = КПД * КИП * КНД * ДН
    locator_gain = config->getParam("DNA_KPD").toDouble() *
                   config->getParam("DNA_KIP").toDouble() *
                   4 * M_PI *
                   config->getParam("X_SIZE").toDouble() *
                   config->getParam("Z_SIZE").toDouble();
    locator_gain /= qPow(config->getParam("LAMBDA").toDouble(), 2);
    // Время одного оборота
    full_rotate_time = 360.0 / config->getParam("ROTATION_SPEED").toDouble();
    receive_mode = config->getParam("RECEIVE_MODE").toInt();

    // Создаем Simple или Table ДН
    int dna_type = config->getParam("DNA_TYPE").toInt();

    if (!dna_type)
    {
        // Simple
        createSimpleDNA();
    }
    else
    {
        // Table
        createTableDNA();
    }
}

void Locator::createTableDNA()
{
    /*
     *  Считывание табличной диаграммы направленности
     *  Ноль угла места в направлении оси z
     */
    int x_steps = config->getArraySize("DNA_TABLE_AZ");
    int z_steps = config->getArraySize("DNA_TABLE_PL");

    for (int i = 0; i < x_steps; i++)
    {
        x_values.append(config->getParam("DNA_TABLE_AZ", i, "value").toDouble());
        x_angles.append(qDegreesToRadians(config->getParam("DNA_TABLE_AZ", i, "angle").toDouble()));
    }

    for (int i = 0; i < z_steps; i++)
    {
        z_values.append(config->getParam("DNA_TABLE_PL", i, "value").toDouble());
        z_angles.append(qDegreesToRadians(config->getParam("DNA_TABLE_PL", i, "angle").toDouble()));
    }

    zero_x = qFabs(findMinInList(x_values));
    zero_z = qFabs(findMinInList(z_values));
}

void Locator::createSimpleDNA()
{
    /*
     *  Создание ДНА вида sin(x)/x
     *  Ноль угла места в направлении оси z
     */

    // Волновое число
    double wave_number = M_PI / config->getParam("LAMBDA").toDouble();

    // Пределы диаграммы
    zero_x = qDegreesToRadians(config->getParam("X_START").toDouble());
    zero_z = qDegreesToRadians(config->getParam("Z_START").toDouble());

    // Множители из формулы sin(x)/x
    double mul_x = wave_number * config->getParam("X_SIZE").toDouble();
    double mul_z = wave_number * config->getParam("Z_SIZE").toDouble();

    // Углы
    double step = config->getParam("SIMPLE_STEP").toDouble();

    for (double d = - zero_x; d < zero_x; d += step)
        x_angles.append(d);
    x_angles.append(zero_x);

    for (double d = - zero_z; d < zero_z; d += step)
        z_angles.append(d);
    z_angles.append(zero_z);

    // Значения (TODO: можно убрать)
    int q_x = x_angles.count();
    int q_z = z_angles.count();

    for (int i = 0; i < q_x; i++)
        x_values.append(0);

    for (int i = 0; i < q_z; i++)
        z_values.append(0);

    // Забиваем массивы расчитываемыми значениями
    for (int i = 0; i < q_x; i++)
        x_values[i] = qSin(mul_x * qSin(x_angles[i])) / (mul_x * qSin(x_angles[i]));

    for (int i = 0; i < q_z; i++)
        z_values[i] = qSin(mul_z * qSin(z_angles[i])) / (mul_z * qSin(z_angles[i]));
}

void Locator::spin(double world_time_delta)
{
    // Имитирует поворот ДНА
    // :world_time_delta время, выделенное для поворота или период с которым моделируется мир

    locator_angle = (locator_angle + (speed * world_time_delta));
    while (locator_angle >= 2*M_PI)
        locator_angle -= 2*M_PI;
}

double Locator::findMinInList(QList<double> list)
{
    double min = list[0];
    for (int i = 1; i < list.count(); i++)
        if (list[i] < min)
            min = list[i];
    return min;
}

double Locator::interpolate(double point, double x1, double x2, double y1, double y2)
{
    // Линейная интерполяция, метод Лагранжа

    double L = 0;
    double x[2] = {x1, x2};
    double y[2] = {y1, y2};

    for (int i = 0; i < 2; ++i)
        {
            double l = 1;
            for (int j = 0; j < 2; ++j)
                if (i != j)
                    l *= (point - x[j]) / (x[i] - x[j]);
            L += y[i] * l;
        }
    return L;
}

double Locator::gainForTarget(TargetBase *target)
{
    // Интерфейс для получения усиления ДНА для цели target

    if (receive_mode)
        return locator_gain * gainForTargetAzimuth(target);
    else
        return gainForTargetAzimuth(target);
}

double Locator::gainForTargetPlace(TargetBase *target)
{
    // Поиск усиления для цели по углу места. Интерполяция значения линейна

    double target_place = target->getPlace() - locator_place;
    if ((target_place > -zero_z) && (target_place < zero_z))
        for (int i = 1; i < z_angles.count(); i++)
            if (z_angles[i] >= target_place)
                return interpolate(target_place,
                                   z_angles[i - 1], // x1
                                   z_angles[i],     // x2
                                   z_values[i - 1], // y1
                                   z_values[i]);    // y2
    return 0;
}

double Locator::gainForTargetAzimuth(TargetBase *target)
{
    double target_azimuth = target->getAzimuth() - locator_angle;
    if ((target_azimuth > -zero_x) && (target_azimuth < zero_x))
        for (int i = 1; i < x_angles.count(); i++)
            if (x_angles[i] >= target_azimuth)
                return interpolate(target_azimuth,
                                   x_angles[i - 1], // x1
                                   x_angles[i],     // x2
                                   x_values[i - 1], // y1
                                   x_values[i]);    // y2
    return 0;
}
