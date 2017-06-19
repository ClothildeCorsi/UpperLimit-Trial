#include "attenuation.h"

Attenuation::Attenuation(attenuationFcn model, Heliostat heliostat)
    :  attenuationFcn (model),Heliostat(heliostat)
{
}

//void Attenuation::setAttenuationModel(attenuationFcn &model)
//{
//    m_model = model;
//}

//double Attenuation::getAttenuationFactor()
//{
//    double slantRange = getSlantRange() / 1000.;
//    m_attenuationFactor = m_model(slantRange);
//}

double Attenuation::vittitoe(const double &slantRange)
{
    return (0.99326 - 0.1046 * slantRange + 0.017 * pow(slantRange, 2.0) - 0.002845 * pow(slantRange, 3.0));
}

double Attenuation::mirval(const double &slantRange)
{
    if (slantRange <= 1)
        return (0.99321 - 0.1176 * slantRange + 0.0197 * pow(slantRange, 2));
    else
        return qExp(0.1106 * slantRange);
}
