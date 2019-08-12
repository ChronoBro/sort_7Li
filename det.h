#ifndef det_
#define det_
#include <iostream>
#include <vector>
#include <cmath>
#include "TRandom.h"
#include "silicon.h"
#include "histo.h"
#include "correl.h"
#include "doppler.h"
#include <eigen3/Eigen/dense>

using namespace std;
using namespace Eigen;

/**
 *!\brief detector readout
 *
 * responsible for unpacking the data stream for physics events
 */


class det
{
 public:
  det(histo * Histo);
  ~det();
  bool unpack(unsigned short *point,int runno);
  silicon *Silicon;
  histo * Histo;
  TRandom * ran;
  void analyze(int event);

  int Event;

  int Run;

  correl Correl;
  void corr_7Li();
 

  int Nalphat;

  int CsImult;

  int N_IAS;
  int N7Li_ta;
  int N7Li;
  float xg,yg,zg;
  float xL,yL,zL;
  float thetag,phig;
  float thetaL,phiL,thetarel;
  float dot;
  float mag;
  int Rus_count;
  int S2_count;
  int RusS2_count;



 private:
  doppler *Doppler;
  int please;

};
#endif
