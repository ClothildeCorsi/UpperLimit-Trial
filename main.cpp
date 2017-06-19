#include <QCoreApplication>
#include <iostream>

#include "Field.h"
#include "Sun.h"

int main()
{
    QVector3D aimingPoint = {0.0, 0.0, 100.0};

    Field heliostatField(1,2,aimingPoint);

    double latitude = qDegreesToRadians(20.0);
    std::cout << "Annual Eff = " << heliostatField.totalAnnualEfficency(latitude) << '\n';

//    Sun sunPos1({10.0, 5.0, 8.0});
//    sunPos1.printSunPosition();

//    double declination1 = qDegreesToRadians(10.0);
//    double latitude1 = qDegreesToRadians(20.0);

//    Heliostat helio1 = {{5.0,25.0,0.0},{0.0, 0.0, 100.0}};

//    std::cout << "Daily NRJ = " << helio1.getDailyNRJ(declination1, latitude1) << '\n';
//    std::cout << "Annual Eff = " << helio1.getAnnualEfficiency(latitude1) << '\n';

//    double declination = qDegreesToRadians(-15.0);
//    double latitude = qDegreesToRadians(32.0);

//    Heliostat helio2 = {{56.0,105.0,0.0},{0.0, 0.0, 80.0}};

//    std::cout << "Daily NRJ = " << helio2.getDailyNRJ(declination, latitude) << '\n';
//    std::cout << "Annual Eff = " << helio2.getAnnualEfficiency(latitude) << '\n';

//    std::cout << "Daily NRJ = " << helio1.getDailyNRJ(declination, latitude) << '\n';
//    std::cout << "Annual Eff = " << helio1.getAnnualEfficiency(latitude) << '\n';

    return 0;
}
