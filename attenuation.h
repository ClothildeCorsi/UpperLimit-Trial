#ifndef ATTENUATION_H
#define ATTENUATION_H

#include <QtMath>
#include "heliostat.h"

typedef double (*attenuationFcn)(const double &);
class Attenuation: virtual public Heliostat
{
protected:
    attenuationFcn m_model = nullptr;
    double m_attenuationFactor = 0;

public:
    Attenuation(attenuationFcn model, Heliostat heliostat);

//    void setAttenuationModel(attenuationFcn &model);
 //   double getAttenuationFactor();
    double vittitoe(const double &slantRange);
    double mirval(const double &slantRange);
};

#endif // ATTENUATION_H
