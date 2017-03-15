#include "targetbase.h"

TargetBase::TargetBase(QMap<QString, QString> *targetConfig)
{
//    cout << "base" << endl;

    cart_coord["x"] = targetConfig->value("x0").toDouble();
    cart_coord["y"] = targetConfig->value("y0").toDouble();
    cart_coord["z"] = targetConfig->value("z0").toDouble();

    speed_for_coord["Vx"] = targetConfig->value("Vx").toDouble();
    speed_for_coord["Vy"] = targetConfig->value("Vy").toDouble();
    speed_for_coord["Vz"] = targetConfig->value("Vz").toDouble();

    sph_coord = translate_to_sph(cart_coord);

    if (targetConfig->keys().contains("gain_range") && targetConfig->keys().contains("gain_value"))
    {
        double on_range = targetConfig->value("gain_range").toDouble();
        double on_range_gain = targetConfig->value("gain_value").toDouble();
        get_gain = getOnRangeGain(on_range, on_range_gain);
    }
    else
        get_gain = getStaticGain();

    if (targetConfig->keys().contains("rsc_sigma"))
    {
        rsc_sigma = targetConfig->value("rsc_sigma").toDouble();
    }
}

QMap<QString, double> TargetBase::translate_to_sph(QMap<QString, double> dec)
{
    QMap<QString, double> temp;
    temp["r"] = qSqrt(qPow(dec.value("x"), 2) +
                      qPow(dec.value("y"), 2) +
                      qPow(dec.value("z"), 2));
    temp["pl"] = qAcos(dec.value("z") / temp.value("r"));
    temp["az"] = qAtan2(dec.value("y"), dec.value("x"));
    return temp;
}

double TargetBase::getOnRangeGain(double on_range, double on_range_gain)
{
    // Амплитуда равна Аопрн * (Rопрн / R) ** 2
    return on_range_gain * (qPow(on_range / getDistance(), 2));
}

double TargetBase::getStaticGain()
{
    return 100.0;
}

double TargetBase::getDistance()
{
    return sph_coord.value("r");
}

double TargetBase::getAzimuth()
{
    return sph_coord.value("az");
}

double TargetBase::getPlace()
{
    return sph_coord.value("pl");
}

double TargetBase::getRadialSpeed()
{
    return (cart_coord["x"] * speed_for_coord["Vx"] +
            cart_coord["y"] * speed_for_coord["Vy"] +
            cart_coord["z"] * speed_for_coord["Vz"]) / sph_coord["r"];
}

double TargetBase::getGain()
{
    return get_gain;
}

double TargetBase::getRsc()
{
    // Рэлей
    qsrand(QDateTime::currentMSecsSinceEpoch());
    double x = qrand() % 1;
    return rsc_sigma * qSqrt(-2.0 * qLn(x));
}

void TargetBase::timeDeltaSq()
{
    time_delta_sq = qPow(time_delta, 2);
}
