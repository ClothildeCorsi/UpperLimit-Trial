#include <iostream>
#include <iomanip>
#include "heliostat.h"

Heliostat::Heliostat (QVector3D heliostatCenter , QVector3D aimingPoint)
    : m_heliostatCenter(heliostatCenter), m_aimingPoint(aimingPoint)
{
}

void Heliostat::setHeliostatCenter(double xH, double yH, double zH)
{
    m_heliostatCenter.setX(xH);
    m_heliostatCenter.setY(yH);
    m_heliostatCenter.setZ(zH);
}

void Heliostat::setAimingPoint(double xA, double yA, double zA)
{
    m_aimingPoint.setX(xA);
    m_aimingPoint.setY(yA);
    m_aimingPoint.setZ(zA);
}

void Heliostat::setAimingPoint(const QVector3D &vector)
{
    m_aimingPoint.setX(vector.x());
    m_aimingPoint.setY(vector.y());
    m_aimingPoint.setZ(vector.z());
}

double Heliostat::getSlantRange()
{
    return (m_heliostatCenter - m_aimingPoint).length();
}

void Heliostat::printHeliostatInformation()
{
    using namespace std;
    cout << "Heliostat position: (";
    for (int index = 0; index < 3; index++) cout << m_heliostatCenter[index] << " ";
    cout << ")\n";
    cout << "Heliostat aiming point: (";
    for (int index = 0; index < 3; index++) cout << m_aimingPoint[index] << " ";
    cout << ")\n";
    cout << "Slant Range: " << getSlantRange() << "\n";
}

double Heliostat::getCosineFactor(const QVector3D &sunPosition)
{
    QVector3D temp = (m_aimingPoint - m_heliostatCenter);
    temp.normalize();
    temp += sunPosition;
    return 0.5 * temp.length();
}

double Heliostat::getAttenuationFactor()
{
    double slantRange = getSlantRange() / 1000.;
    return (0.99326 - 0.1046 * slantRange + 0.017 * pow(slantRange, 2.0) - 0.002845 * pow(slantRange, 3.0));
}

double Heliostat::solarDeclinationByDayNumber(const int &dayI)
{
    int dayN = (dayI+355) % 365;
    double omega = 2*3.1415926/360. * (dayN - 1);
    return (0.006918 - 0.399912 * qCos(omega) + 0.070257 * qSin(omega) - 0.006758 * qCos(omega) + 0.000907 * qSin(omega) - 0.002697 * qCos(omega) + 0.001480 * qSin(omega));
}

double Heliostat::getSunrise(const double &declination, const double &latitude)
{
    double sunRise = qFabs(qAcos(-qTan(declination) * qTan(latitude)));
    sunRise /= (qDegreesToRadians(15.0)/3600.0);
    return sunRise;
}

double Heliostat::integralNRJ(const double &declination, const double &sunRise, const double &latitude, const QVector3D &vectorTarget)
{
    NRJIntegration dayI(vectorTarget, declination, latitude, m_attenuationEfficiency);
    int evaluations;
    double errorEstimate;
    std::cout << std::setprecision(15);
    double dailyNRJ = 2.0 * DEIntegrator<NRJIntegration>::Integrate(dayI, -sunRise, 0.0, 1e-6, evaluations, errorEstimate);
    return dailyNRJ;
}

double Heliostat::getDailyNRJ(const double &declination, const double &latitude)
{
    m_attenuationEfficiency = getAttenuationFactor();
    QVector3D vectorTarget = (m_aimingPoint - m_heliostatCenter);
    vectorTarget.normalize();
    double sunRise = getSunrise(declination, latitude);
    double dailyNRJ = integralNRJ(declination, sunRise, latitude, vectorTarget);
    return dailyNRJ;
}

double Heliostat::integralDNI(const double &declination, const double &sunRise, const double &latitude)
{
    DNIIntegration dayI(declination, latitude);
    int evaluations;
    double errorEstimate;
    std::cout << std::setprecision(15);
    double dailyDNI = 2.0 * DEIntegrator<DNIIntegration>::Integrate(dayI, -sunRise, 0.0, 1e-6, evaluations, errorEstimate);
    return dailyDNI;
}

double Heliostat::getDailyDNI(const double &declination, const double &latitude)
{
    double sunRise = getSunrise(declination, latitude);
    double dailyDNI = integralDNI(declination, sunRise, latitude);
    return dailyDNI;
}

double Heliostat::getAnnualEfficiency(const double &latitude)
{
    m_attenuationEfficiency = getAttenuationFactor();
    QVector3D vectorTarget = (m_aimingPoint - m_heliostatCenter);
    vectorTarget.normalize();
    double annualNRJ = 0.0;
    double annualDNI = 0.0;
    double declination;
    double sunRise;
    for (int dayI = 1; dayI <= 182; dayI++ ) // loop over half the year
    {
        declination = solarDeclinationByDayNumber(dayI);
        sunRise = getSunrise(declination, latitude);
        annualNRJ += integralNRJ(declination, sunRise, latitude, vectorTarget);
        annualDNI += integralDNI(declination, sunRise, latitude);
    }
    annualNRJ *= 2.0;
    annualDNI *= 2.0;
    declination = solarDeclinationByDayNumber(183);
    sunRise = getSunrise(declination, latitude);
    annualNRJ += integralNRJ(declination, sunRise, latitude, vectorTarget);
    annualDNI += integralDNI(declination, sunRise, latitude);
    m_totalEfficiency = annualNRJ / annualDNI;
    return m_totalEfficiency;
}

double Heliostat::getAnnualDNI(const double &latitude)
{
    double annualDNI = 0.0;
    double declination;
    double sunRise;
    for (int dayI = 1; dayI <= 182; dayI++ ) // loop over half the year
    {
        declination = solarDeclinationByDayNumber(dayI);
        sunRise = getSunrise(declination, latitude);
        annualDNI += integralDNI(declination, sunRise, latitude);
    }
    annualDNI *= 2.0;
    declination = solarDeclinationByDayNumber(183);
    sunRise = getSunrise(declination, latitude);
    annualDNI += integralDNI(declination, sunRise, latitude);
    return annualDNI;
}
