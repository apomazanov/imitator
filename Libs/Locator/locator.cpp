#include "locator.h"

Locator::Locator(QObject *parent) : QObject(parent)
{
    config = new ParamsRaw(0, "../../config.json");

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
    receive_mode = config->getParam("RECEIVE_MODE").toDouble();

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
    locator_angle = (locator_angle + (speed * world_time_delta)) % 6.28;
}

double Locator::findMinInList(QList<double> list)
{
    double min = list[0];
    for (int i = 1; i < list.count(); i++)
        if (list[i] < min)
            min = list[i];
    return min;
}
