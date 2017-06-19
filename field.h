#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <cassert> // for assert()
#include "heliostat.h"

class Field : public Heliostat
{
protected:
    Heliostat ** m_field;
    int m_length;

public:
    Field(double width, double max, QVector3D aimingPoint);
    ~Field();

    double totalAnnualEfficency(const double &latitude);
};

#endif // FIELD_H
