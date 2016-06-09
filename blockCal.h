#ifndef blockCal_
#define blockCal_
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;


class blockCal
{
 public:
  blockCal(string file1, string file2);
  ~blockCal();
  void getCal(int icsi, float theta);
  float getE(int icsi, float channel, float theta);
  double Eslope_quad[32];
  double Eslope_slope[32];
  double Eslope_int[32];
  double Eint_slope[32];
  double Eint_int[32];
  double calSlope;
  double calInt;
  double energy;
  
};
#endif
