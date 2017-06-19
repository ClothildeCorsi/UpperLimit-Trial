#include "dniintegration.h"

DNIIntegration::DNIIntegration(double declination, double latitude,double beta, double maxDNI)
    : m_declination(declination), m_latitude(latitude), m_Beta(beta), m_Io(maxDNI)
{
    m_cosDeclination = qCos(declination);
    m_sinDeclination = qSin(declination);
    m_cosLatitude = qCos(latitude);
    m_sinLatitude = qSin(latitude);
}

double DNIIntegration::operator()(double hourAngle) const
{
    hourAngle *= (qDegreesToRadians(15.0)/3600.0);
    double sz = m_sinDeclination * m_sinLatitude + m_cosDeclination * m_cosLatitude * qCos(hourAngle);
    qreal dNI;
    if (sz > 0.00001)
        dNI = m_Io * qExp(- m_Beta / sz);
    else
        dNI = 0.0;
    return dNI;
}
