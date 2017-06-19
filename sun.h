#ifndef SUN_H
#define SUN_H

#include <QVector3D>
#include <QtMath>
#include <iostream>

class Sun
{
protected:
    QVector3D m_sunPosition;

public:
    Sun(QVector3D sunPosition);

    QVector3D getPosition() const { return m_sunPosition; }
    void fromHourAngleAndDeclinationToVector(double latitude, double declination, double hourAngle);
    void fromAzimuthElevationToVector( double azimuth, double elevation);
    void printSunPosition();
    double getSunrise(const double &latitude, const double &declination);
};

#endif // SUN_H
