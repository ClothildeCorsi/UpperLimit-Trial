#include "field.h"

Field::Field(double width, double max, QVector3D aimingPoint)
{
    if (!max)
        m_field = nullptr;
    else
        m_length = static_cast<int>(2.0*max / width);

        // allocation
        m_field = new Heliostat*[m_length];
        for (int ligne = 0; ligne < m_length; ligne++)
        {
          m_field[ligne] = new Heliostat[m_length];

          // initialization
          for (int column = 0; column < m_length; column++)
          {
              m_field[ligne][column].setHeliostatCenter(-max + width/2.0 + ligne * width, -max + width/2.0 + column * width , 0.0);
              m_field[ligne][column].setAimingPoint(aimingPoint);
              m_field[ligne][column].printHeliostatInformation();
          }
        }
 }

double Field::totalAnnualEfficency(const double &latitude)
{
    double efficiency;
    double totalEfficiency = 0.0;
    for (int ligne = 0; ligne < m_length; ligne++)
    {
      for (int column = 0; column < m_length; column++)
      {
          efficiency = m_field[ligne][column].getAnnualEfficiency(latitude);
          std::cout << "Annual Eff = " << efficiency << '\n';
          totalEfficiency += efficiency;
      }
    }
    return totalEfficiency/(m_length * m_length);
}

Field::~Field() // destructor
{
    // Dynamically delete the array we allocated earlier
    delete[] m_field ;
    for (int i = 0; i < m_length; i++) {
        delete [] m_field[i];
    //    world[i] = 0;  // <- don't have to do this
    }
    delete [] m_field;  // <- because they won't exist anymore after this
    m_field = 0;

}
