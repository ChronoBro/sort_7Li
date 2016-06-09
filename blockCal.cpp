#include "blockCal.h"
#include "math.h"


blockCal::blockCal(string name1, string name2)
{

  ifstream file1(name1.c_str());
  ifstream file2(name2.c_str());
  for(int i=0;i<32;i++)
    {
      file1 >> Eslope_quad[i] >> Eslope_slope[i] >> Eslope_int[i];
      file2 >> Eint_slope[i] >> Eint_int[i];

    }
  file1.close();
  file2.close();
  file1.clear();
  file2.clear();

}

blockCal::~blockCal()
{

}

void blockCal::getCal(int icsi, float theta)
{
  calSlope = Eslope_quad[icsi]*pow(theta,2.)+Eslope_slope[icsi]*theta+Eslope_int[icsi];
  calInt = Eint_slope[icsi]*theta+Eint_int[icsi];
  return;

}

float blockCal::getE(int icsi, float channel, float theta)
{
  getCal(icsi, theta);
  energy = calSlope*channel+calInt;
  return energy;

}
