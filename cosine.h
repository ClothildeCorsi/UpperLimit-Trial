#ifndef COSINE_H
#define COSINE_H

#include "heliostat.h"
#include "sun.h"

class Cosine : virtual public Heliostat, public Sun
{
protected:
    double m_cosineFactor = 0;

public:
    Cosine(Heliostat heliostat, Sun sun);

    double getCosineEfficiency();
};

#endif // COSINE_H
