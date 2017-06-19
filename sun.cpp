#include "sun.h"

Sun::Sun(QVector3D sunPosition = {0, 0, 0})
    : m_sunPosition(sunPosition)
{
    m_sunPosition.normalize();
}

void Sun::fromHourAngleAndDeclinationToVector(double latitude,double declination,double hourAngle)
{
    latitude = qDegreesToRadians(latitude);
    declination = qDegreesToRadians(declination);
    hourAngle = qDegreesToRadians(hourAngle * 15.0);
    double cosDeclination = qCos(declination);
    double sinDeclination = qSin(declination);
    double cosLatitude = qCos(latitude);
    double sinLatitude = qSin(latitude);
    double cosHourAngle = qCos(hourAngle);
    m_sunPosition.setX(-cosDeclination * qSin(hourAngle));
    m_sunPosition.setY(sinDeclination * cosLatitude - cosDeclination * sinLatitude * cosHourAngle);
    m_sunPosition.setZ(sinDeclination * sinLatitude + cosDeclination * cosLatitude * cosHourAngle);
}

void Sun::fromAzimuthElevationToVector(double azimuth,double elevation)
{
    azimuth = qDegreesToRadians(azimuth);
    elevation = qDegreesToRadians(elevation);
    m_sunPosition.setX(qCos(elevation) * qSin(azimuth));
    m_sunPosition.setY(qCos(elevation) * qCos(azimuth));
    m_sunPosition.setZ(qSin(elevation));
}

void Sun::printSunPosition()
{
    std::cout << "Sun position: ( ";
    for (int index = 0; index < 3; index++) std::cout << m_sunPosition[index] << " ";
    std::cout << ")\n";
}

double Sun::getSunrise(const double &latitude, const double &declination)
{
    return qFabs(qAcos(-qTan(declination) * qTan(latitude)));
}

