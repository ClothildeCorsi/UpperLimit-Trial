#ifndef HELIOSTAT_H
#define HELIOSTAT_H

#include "nrjintegration.h"
#include "dniintegration.h"
#include "DEIntegrator.h"

class Heliostat
{
protected:
    QVector3D m_heliostatCenter;
    QVector3D m_aimingPoint;
    double m_totalEfficiency = 0.0;
    double m_cosineEfficenicy = 0.0;
    double m_attenuationEfficiency = 0.0;

public:
    Heliostat (QVector3D heliostatCenter = {0.0, 0.0, 0.0}, QVector3D aimingPoint = {0.0, 0.0, 0.0});

    void setHeliostatCenter(double xH, double yH, double zH);
    void setAimingPoint(double xA, double yA, double zA);
    void setAimingPoint(const QVector3D &vector);
    QVector3D getHeliostatCenter() const { return m_heliostatCenter; }
    QVector3D getAimingPoint() const { return m_aimingPoint; }
    double getSlantRange();
    void printHeliostatInformation();
    double getCosineFactor(const QVector3D &sunPosition);
    double getAttenuationFactor();
    double solarDeclinationByDayNumber(const int &dayI);
    double getSunrise(const double &declination, const double &latitude);
    double integralNRJ(const double &declination, const double &sunRise, const double &latitude, const QVector3D &vectorTarget);
    double getDailyNRJ(const double &declination, const double &latitude);
    double integralDNI(const double &declination, const double &sunRise, const double &latitude);
    double getDailyDNI(const double &declination, const double &latitude);
    double getAnnualEfficiency(const double &latitude);
    double getAnnualDNI(const double &latitude);
};

#endif // HELIOSTAT_H
