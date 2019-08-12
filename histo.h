#ifndef histo_
#define histo_
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "TH1I.h"
#include "TH2I.h"
#include "TH3I.h"
#include "TFile.h"
#include "TDirectory.h"

using namespace std;

class histo
{
 protected:

  TFile * file; //!< output root file

  //correlations
  TDirectoryFile * dirCorr; //!< directory for correlations
  TDirectory * dir7Li; //!< direcotry for 13O correlations (12N +p)
  TDirectory * dir6Li;

  //S2
  TDirectoryFile * dirS2;
  TDirectory * dirS2Pies;
  TDirectory * dirS2PiesC;
  TDirectory * dirS2PiesLG;
  TDirectory * dirS2Rings;
  TDirectory * dirS2RingsC;
  TDirectory * dirS2RingsLG;
  TDirectory * dirSsum;
  //S2
  TDirectoryFile * dirRus;
  TDirectory * dirRPies;
  TDirectory * dirRPiesC;
  TDirectory * dirRPiesCM1;
  TDirectory * dirRRingsC;
  TDirectory * dirRPiesLG;
  TDirectory * dirRRings;
  TDirectory * dirRRingsLG;
  TDirectory * dirRsum;
  TDirectory * dirCsIRing;

  //CsI
  TDirectoryFile *dirCsI; //!< directory for the CsI info
  TDirectory * dirCsIRaw; //!< CsI energies
  TDirectory * dirCsITime; //!< CsI time
  TDirectory * dirCsIsum;
  TDirectory * dirCsItest;

  TDirectoryFile *dirdEE; //!< directory for the dEE maps



 public:
  histo();                  //!< constructor
  ~histo(){};
  void write(); //!< write the root spectra to file


  int NSPies;
  int NSRings;
  int NRPies;
  int NRRings;

  int NCsI;

  //S2

  TH1I ** S2PiesR;
  TH1I ** S2PiesC;
  TH1I ** S2PiesRLG;
  TH1I ** S2RingsR;
  TH1I ** S2RingsC;
  TH1I ** S2RingsRLG;

  //Russian

  TH1I ** RusPiesR;
  TH1I ** RusPiesRLG;
  TH1I ** RusRingsR;
  TH1I ** RusRingsRLG;

  TH1I ** RusPiesC;
  TH1I ** RusPiesCM1;
  TH1I ** RusPiesCLG;
  TH1I ** RusRingsC;
  TH1I ** RusRingsCLG;

  TH1I * RusPhi_gated;

  TH2I * E1E2pie;
  TH2I * E1E2ring;
  TH2I * ERPCSum;
  TH2I * ERRCSum;
  TH2I * ESPCSum;
  TH2I * ESRCSum;
  TH1I * p21p22Raw;
  TH1I * p22p21Raw;
  
  TH1I * RusPiesMult;
  TH1I * RusRingsMult;
  TH1I * S2PiesMult;
  TH1I * S2RingsMult;
  TH2I * RusRingvPie;
  TH2I * S2RingvPie;

  TH1I * RusPiesBlock1;
  TH1I * RusPiesBlock2;
  TH1I * RusPiesBlock3;
  TH1I * RusPiesBlock4;
  TH1I * RusPiesBlock5;
  TH1I * RusPiesBlock6;
  TH1I * RusPiesBlock7;
  TH1I * RusPiesBlock8;


  TH2I * HitMap;
  TH2I * HitMap1;
  TH2I * HitMap_perspective;


  TH1I * ECsIblock1;
  TH1I * ECsIblock2;
  TH1I * ECsIblock3;
  TH1I * ECsIblock4;
  TH1I * ECsIblock5;
  TH1I * ECsIblock6;
  TH1I * ECsIblock7;
  TH1I * ECsIblock8;

  TH1I * ESiblock1;
  TH1I * ESiblock2;
  TH1I * ESiblock3;
  TH1I * ESiblock4;
  TH1I * ESiblock5;
  TH1I * ESiblock6;
  TH1I * ESiblock7;
  TH1I * ESiblock8;
 
  TH1I * ECsIblock_raw1;
  TH1I * ECsIblock_raw2;
  TH1I * ECsIblock_raw3;
  TH1I * ECsIblock_raw4;
  TH1I * ECsIblock_raw5;
  TH1I * ECsIblock_raw6;
  TH1I * ECsIblock_raw7;
  TH1I * ECsIblock_raw8;

  TH1I * ECsI_sumenergy;
  TH1I * ECsI_Ta_loss;
  TH2I * TSi;
  TH2I * multPeakCheck;


  TH1I ** ECsI;
  TH1I ** TCsI;
  TH2I ** ETCsI_Rus;
  TH2I ** ETCsI_S2;


  TH1I * S2CsIMult;
  TH1I * RusCsIMult;
  TH1I * TotCsIMult;


    
  TH2I ** dEE;
  TH2I ** dEE_ta;
  TH2I * dEEtest;
  TH1I * ECsI_all_inc;
  TH1I * ECsI_raw_all;

  //correlations
  //7Li
  TH1I * Ex7Li_ta;
  TH1I * Ex6Li_da;
  TH1I * velCM7Li_ta;

  TH1I * ExTarget_9Be;
  TH1I * ExTarget_9Be_RUS;
  TH1I * ExTarget_9Be_S2;
  TH1I * ExTarget_9Be_RUSS2;

  TH1I * ExTarget_C;
  TH1I * ExTarget_C_RUS;
  TH1I * ExTarget_C_S2;
  TH1I * ExTarget_C_RUSS2;

  TH1I * ExTarget_Al;
  TH1I * ExTarget_Al_RUS;
  TH1I * ExTarget_Al_S2;
  TH1I * ExTarget_Al_RUSS2;
  
  TH2F * cosPsi_Chi_9Be;
  TH2F * cosPsi_Chi_12C;
  TH2F * cosPsi_Chi_27Al;
  TH2F * cosPsi_Chi_12C_2plus;

  TH2F * cosPsi_Chi_9Be_small_angle;
  TH2F * cosPsi_Chi_12C_small_angle;
  TH2F * cosPsi_Chi_27Al_small_angle;

  TH2F * cosPsi_Chi_9Be_mid_angle;
  TH2F * cosPsi_Chi_12C_mid_angle;
  TH2F * cosPsi_Chi_27Al_mid_angle;

  TH2F * cosPsi_Chi_9Be_large_angle;
  TH2F * cosPsi_Chi_12C_large_angle;
  TH2F * cosPsi_Chi_27Al_large_angle;

  
  TH2I * cosPsi_Chi_9Be_Rus;  
  TH2I * cosPsi_Chi_9Be_S2;  
  TH2I * cosPsi_Chi_9Be_RusS2;


  TH2I * cosPsi_Chi_12C_Rus;  
  TH2I * cosPsi_Chi_12C_S2;  
  TH2I * cosPsi_Chi_12C_RusS2;

  TH2I * cosPsi_Chi_27Al_Rus; 
  TH2I * cosPsi_Chi_27Al_S2; 
  TH2I * cosPsi_Chi_27Al_RusS2;
  

  TH1F * Li7_theta_CM_9Be;
  TH1F * Li7_theta_CM_12C;
  TH1F * Li7_theta_CM_27Al;

  TH1F * Li7_theta_reactCoM_9Be;
  TH1F * Li7_theta_reactCoM_12C;
  TH1F * Li7_theta_reactCoM_27Al;
  //TH1I * ExTarget_9Be_L1;
  //TH1I * ExTarget_9Be_L2;
  //TH1I * ExTarget_9Be_T;
  //TH1F * Li7_AbsElasXS;
  TH1F * ExTarget8Li;

  TH1I * Ex7Li_L1;
  TH1I * Ex7Li_L2;
  TH1I * Ex7Li_T;

  TH1I * Ex7Li_tRaS;
  TH1I * Ex7Li_aRtS;
  TH1I * Ex7Li_taR;
  TH1I * Ex7Li_taS;

  TH1I * Ex6Li_L1;
  TH1I * Ex6Li_L2;
  TH1I * Ex6Li_T;

  TH1I * ExTarget_10Be;

  /*
  TH1I * ExTarget_12C_L1;
  TH1I * ExTarget_12C_L2;
  TH1I * ExTarget_12C_T;

  TH1I * ExTarget_27Al_L1;
  TH1I * ExTarget_27Al_L2;
  TH1I * ExTarget_27Al_T;
  */
  TH2I * D2CsI;


  TH1I ** CsIRings;
  TH1I * gated_E_t_9Be;
  TH1I * gated_E_t_12C;
  TH1I * gated_E_t_27Al;

  TH1I * calib_diag1;
  TH1I * calib_diag2;
  TH1I * calib_diag3;

  TH1I * ExTarget_9Be_tRaS;
  TH1I * ExTarget_9Be_aRtS;

  TH1I * ExTarget_9Be_taR;
  TH1I * ExTarget_9Be_taS;

  TH1F * cosPsi_9Be;
  TH1F * cosPsi_12C;
  TH1F * cosPsi_27Al;


  TH1F * elas7Li_9Be;
  TH1F * elas7Li_12C;
  TH1F * elas7Li_27Al;
  TH1F * elas7Li_E_12C;
  TH1F * elas7Li_12C_pieCheck;
  TH1F * elas7Li_12C_labAngle;

  TH1F * elas7Li_12C_phiCut;
  
  TH1F * mult7Li;
  //6Li

  TH1I * Ex8Be;
  TH1I * Ex8BeT;
  TH1I * Ex8BeL1;
  TH1I * Ex8BeL2;

  TH1F * cosPsi_10Be;
  TH1F * cosPsi_10Be_Rus;
  TH1F * cosPsi_10Be_S2;
  TH1F * cosPsi_10Be_RusS2;

  TH2F * cosPsi_Chi_10Be;
  TH2F * cosPsi_Chi_10Be_Rus;
  TH2F * cosPsi_Chi_10Be_S2;
  TH2F * cosPsi_Chi_10Be_RusS2;
  

  TH1F * chi_9Be;
  TH1I * Ex6Li_Rus;
  TH1I * Ex6Li_S2;
  TH1I * Ex6Li_RusS2;

  /*
  TH1I * Ex6Li_RusT;
  TH1I * Ex6Li_RusL1;
  TH1I * Ex6Li_RusL2;

  TH1I * Ex6Li_S2T;
  TH1I * Ex6Li_S2L1;
  TH1I * Ex6Li_S2L2;

  TH1I * Ex6Li_RusS2T;
  TH1I * Ex6Li_RusS2L1;
  TH1I * Ex6Li_RusS2L2;
  */

  TH1I * TKE_H2;
  TH1I * TKE_A;
  TH1I * Li6_thetaCM;
  TH1I * Li6velCM;

};
#endif
