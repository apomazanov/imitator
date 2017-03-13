#include "basetarget.h"

BaseTarget::BaseTarget(QMap<QString, QString> *targetConfig)
{
    cout << "base" << endl;
//    cart_coord["x"] = targetConfig->value("x0").toDouble();
//    cart_coord["y"] = targetConfig->value("y0").toDouble();
//    cart_coord["z"] = targetConfig->value("z0").toDouble();

//    speed_for_coord["Vx"] = targetConfig->value("Vx").toDouble();
//    speed_for_coord["Vy"] = targetConfig->value("Vy").toDouble();
//    speed_for_coord["Vz"] = targetConfig->value("Vz").toDouble();

//    sph_coord = translate_to_sph(cart_coord);

////    time_delta = targetConfig->value("world_time_delta").toDouble();
//    time_delta = 456;
//    time_delta_sq = qPow(time_delta, 2);

//    if (targetConfig->keys().contains("gain_range") && targetConfig->keys().contains("gain_value"))
//    {
//        double on_range = targetConfig->value("gain_range").toDouble();
//        double on_range_gain = targetConfig->value("gain_value").toDouble();
//        get_gain = getOnRangeGain(on_range, on_range_gain);
//    }
//    else
//        get_gain = getStaticGain();

//    if (targetConfig->keys().contains("rsc_sigma"))
//    {
//        rsc_sigma = targetConfig->value("rsc_sigma").toDouble();
//    }
}

QMap<QString, double> BaseTarget::translate_to_sph(QMap<QString, double> dec)
{
    QMap<QString, double> temp;
    temp["r"] = qSqrt(qPow(dec.value("x"), 2) +
                      qPow(dec.value("y"), 2) +
                      qPow(dec.value("z"), 2));
    temp["pl"] = qAcos(dec.value("z") / temp.value("r"));
    temp["az"] = qAtan2(dec.value("y"), dec.value("x"));
    return temp;
}

double BaseTarget::getOnRangeGain(double on_range, double on_range_gain)
{
    // Амплитуда равна Аопрн * (Rопрн / R) ** 2
    return on_range_gain * (qPow(on_range / getDistance(), 2));
}

double BaseTarget::getStaticGain()
{
    return 100.0;
}

double BaseTarget::getDistance()
{
    return sph_coord.value("r");
}

double BaseTarget::getAzimuth()
{
    return sph_coord.value("az");
}

double BaseTarget::getPlace()
{
    return sph_coord.value("pl");
}

double BaseTarget::getRadialSpeed()
{
    return (cart_coord["x"] * speed_for_coord["Vx"] +
            cart_coord["y"] * speed_for_coord["Vy"] +
            cart_coord["z"] * speed_for_coord["Vz"]) / sph_coord["r"];
}
