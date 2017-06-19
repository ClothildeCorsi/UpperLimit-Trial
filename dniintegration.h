#ifndef DNIINTEGRATION_H
#define DNIINTEGRATION_H

#include <QtMath>

class DNIIntegration
{
private:
    double m_declination;
    double m_latitude;
    double m_cosDeclination = 1;
    double m_sinDeclination = 1;
    double m_cosLatitude = 1;
    double m_sinLatitude = 1;
    double m_Io = 1110.0;
    double m_Beta = 0.11;
public:
    DNIIntegration(double declination, double latitude,double beta = 0.11, double maxDNI = 1110.0);
    double operator()(double hourAngle) const;
};

#endif // DNIINTEGRATION_H
