#ifndef NRJINTEGRATION_H
#define NRJINTEGRATION_H

#include <QtMath>
#include <QVector3D>

class NRJIntegration
{
private:
    QVector3D m_vectorTarget;
    double m_declination;
    double m_latitude;
    double m_attenuationFactor;
    float m_cosDeclination = 1;
    float m_sinDeclination = 1;
    float m_cosLatitude = 1;
    float m_sinLatitude = 1;
    double m_Io = 1110.0;
    double m_Beta = 0.11;

public:
    NRJIntegration(QVector3D vectorTarget,double declination, double latitude, double attenuationFactor, double beta = 0.11, double maxDNI = 1110.0);

    double operator()(double x) const;
};

#endif // NRJINTEGRATION_H
