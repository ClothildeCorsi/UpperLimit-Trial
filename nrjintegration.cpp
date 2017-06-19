#include "nrjintegration.h"

NRJIntegration::NRJIntegration(QVector3D vectorTarget,double declination, double latitude, double attenuationFactor, double beta, double maxDNI)
    : m_vectorTarget(vectorTarget), m_declination(declination), m_latitude(latitude), m_attenuationFactor(attenuationFactor), m_Beta(beta), m_Io(maxDNI)
{
    m_cosDeclination = qCos(declination);
    m_sinDeclination = qSin(declination);
    m_cosLatitude = qCos(latitude);
    m_sinLatitude = qSin(latitude);
}

double NRJIntegration::operator()(double hourAngle) const
{

    hourAngle *= (qDegreesToRadians(15.0)/3600.0);
    double cosHourAngle = qCos(hourAngle);
    double sz = m_sinDeclination * m_sinLatitude + m_cosDeclination * m_cosLatitude * cosHourAngle;
    qreal dNI;
    if (sz > 0.00001)
        dNI = m_Io * qExp(- m_Beta / sz);
    else
        dNI = 0.0;
    QVector3D vectorSun = {(- m_cosDeclination * qSin(hourAngle)), (m_sinDeclination * m_cosLatitude - m_cosDeclination * m_sinLatitude * cosHourAngle), (m_sinDeclination * m_sinLatitude + m_cosDeclination * m_cosLatitude * cosHourAngle)};
    vectorSun += m_vectorTarget;
    double cosineFactor = 0.5 * vectorSun.length();
    return  (dNI * cosineFactor * m_attenuationFactor);
}
