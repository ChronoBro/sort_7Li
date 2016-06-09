#include "histo.h"


histo::histo()
{

  ostringstream outstring;
  string name;

  NSPies = 16;
  NSRings = 48;

  NRPies = 64;
  NRRings = 32;

  NCsI = 32;

  //create root file
  file = new TFile ("sort.root","RECREATE");
  file->cd();

  //directories for Correl
  dirCorr = new TDirectoryFile("corr","corr");
  dir7Li = dirCorr->mkdir("Li7","Li7");
  dir6Li = dirCorr->mkdir("Li6","Li6");

  //Spectra for S2
  dirS2 = new TDirectoryFile("S2","S2");
  dirS2Pies = dirS2->mkdir("S2pies","S2pies");
  dirS2PiesC = dirS2->mkdir("S2piesC","S2piesC");
  dirS2PiesLG = dirS2->mkdir("S2piesLG","S2piesLG");
  dirS2Rings = dirS2->mkdir("S2rings","S2rings");
  dirS2RingsC = dirS2->mkdir("S2ringsC","S2ringsC");
  dirS2RingsLG = dirS2->mkdir("S2ringsLG","S2ringsLG");
  dirSsum = dirS2->mkdir("SSum","SSum");

  //Spectra for russian
  dirRus = new TDirectoryFile("rus","rus");
  dirRPies = dirRus->mkdir("Rpies","Rpies");
  dirRPiesC = dirRus->mkdir("RpiesC","RpiesC");
  dirRPiesCM1 = dirRus->mkdir("RpiesCM1","RpiesCM1");
  dirRRingsC = dirRus->mkdir("RringsC","RringsC");
  dirRPiesLG = dirRus->mkdir("RpiesLG","RpiesLG");
  dirRRings = dirRus->mkdir("Rrings","Rrings");
  dirRRingsLG = dirRus->mkdir("RringsLG","RringsLG");
  dirRsum = dirRus->mkdir("RSum","RSum");



   //CsI 
  dirCsI = new TDirectoryFile("CsI","CsI");
  dirCsIRaw = dirCsI->mkdir("CsIRaw","raw");
  dirCsITime = dirCsI->mkdir("CsITime","time");
  dirCsIsum = dirCsI->mkdir("CsISum","sum");
  dirCsItest= dirCsI->mkdir("CsItest","CsItest");
  dirCsIRing = dirCsI->mkdir("CsIRings","CsIRings");

 
 




  //delta E vs E
  dirdEE = new TDirectoryFile("dEE","dEE");





  ECsI = new TH1I*[NCsI];
  TCsI = new TH1I*[NCsI];
  dEE = new TH2I*[NCsI];
  dEE_ta = new TH2I*[NCsI];
  CsIRings = new TH1I*[48];

  for(int icsi = 0;icsi <NCsI;icsi++)
    {
      outstring.str("");
      outstring << "ECsI_" << icsi;
      name = outstring.str();
      dirCsIRaw->cd();
      ECsI[icsi] = new TH1I(name.c_str(),"",1024,0,4095);

      outstring.str("");
      outstring << "TCsI_" << icsi;
      name = outstring.str();
      dirCsITime->cd();
      TCsI[icsi] = new TH1I(name.c_str(),"",2000,-4000,4000);

      outstring.str("");
      outstring << "dEE_" << icsi;
      name = outstring.str();
      dirdEE->cd();

      dEE[icsi] = new TH2I(name.c_str(),"",1024,0,4095,1000,0,100);

      outstring.str("");
      outstring << "ta_" << icsi;
      name = outstring.str();
      dEE_ta[icsi] = new TH2I(name.c_str(),"",1024,0,4095,1000,0,30);


    }




  dirCsItest->cd();
  ECsIblock1 = new TH1I("ECsIblock1","",1000,0,100);  
  ECsIblock2 = new TH1I("ECsIblock2","",1000,0,100);  
  ECsIblock3 = new TH1I("ECsIblock3","",1000,0,100); 
  ECsIblock4 = new TH1I("ECsIblock4","",1000,0,100); 
  ECsIblock5 = new TH1I("ECsIblock5","",1000,0,100);  
  ECsIblock6 = new TH1I("ECsIblock6","",1000,0,100);  
  ECsIblock7 = new TH1I("ECsIblock7","",1000,0,100);  
  ECsIblock8 = new TH1I("ECsIblock8","",1000,0,100);
  ECsI_all_inc = new TH1I("ECsI_all_inc","",1000,0,100);
  ECsI_raw_all = new TH1I("ECsI_raw_all","",1024,0,4095);
  

  ECsIblock_raw1 = new TH1I("ECsIblock_raw1","",1024,0,4095);  
  ECsIblock_raw2 = new TH1I("ECsIblock_raw2","",1024,0,4095);  
  ECsIblock_raw3 = new TH1I("ECsIblock_raw3","",1024,0,4095); 
  ECsIblock_raw4 = new TH1I("ECsIblock_raw4","",1024,0,4095); 
  ECsIblock_raw5 = new TH1I("ECsIblock_raw5","",1024,0,4095);  
  ECsIblock_raw6 = new TH1I("ECsIblock_raw6","",1024,0,4095);  
  ECsIblock_raw7 = new TH1I("ECsIblock_raw7","",1024,0,4095);  
  ECsIblock_raw8 = new TH1I("ECsIblock_raw8","",1024,0,4095);  
  D2CsI = new TH2I("2DCsI","",1024,0,4095,1024,0,4095);
  dEEtest= new TH2I("dEEtest","",1024,0,4095,1000,0,30);
  TSi = new TH2I("TSi","",1024,0,4095,2000,-2000,6000);
  multPeakCheck = new TH2I("multPeakCheck","",1024,0,4095,8,0,8);

  dirCsIRing->cd();
  for(int i =0;i<48;i++)
    {
      outstring.str("");
      outstring << "CsIRings_" << i;
      name = outstring.str();
      CsIRings[i] = new TH1I(name.c_str(),"",1024,0,4095);

    }

  ETCsI_Rus= new TH2I*[16];
  ETCsI_S2= new TH2I*[16];

  for(int icsi = 0;icsi <16;icsi++)
    {
      outstring.str("");
      outstring << "ETCsI_Rus" << icsi;
      name = outstring.str();
      ETCsI_Rus[icsi] = new TH2I(name.c_str(),"",2000,-2000,2000,1024,0,4095);

      outstring.str("");
      outstring << "ETCsI_S2" << icsi;
      name = outstring.str();
      ETCsI_S2[icsi] = new TH2I(name.c_str(),"",2000,-2000,2000,1024,0,4095);
    }

  S2PiesR = new TH1I*[NSPies];
  S2PiesC = new TH1I*[NSPies];
  S2PiesRLG = new TH1I*[NSPies];
  S2RingsR = new TH1I*[NSRings];
  S2RingsC = new TH1I*[NSRings];
  S2RingsRLG = new TH1I*[NSRings];

  RusPiesR = new TH1I*[NRPies];
  RusPiesRLG = new TH1I*[NRPies];
  RusRingsR = new TH1I*[NRRings];
  RusRingsRLG = new TH1I*[NRRings];

  RusPiesC = new TH1I*[NRPies];
  RusPiesCM1 = new TH1I*[NRPies];
  RusPiesCLG = new TH1I*[NRPies];
  RusRingsC = new TH1I*[NRRings];
  RusRingsCLG = new TH1I*[NRRings];

  for (int ipie=0;ipie<NSPies;ipie++)
    {

      outstring.str("");
      outstring << "S2PieR_" << ipie;
      name = outstring.str();
      dirS2Pies->cd();
      S2PiesR[ipie] = new TH1I(name.c_str(),"",4000,0,16000);
      S2PiesR[ipie]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");

      outstring.str("");
      outstring << "S2PieC_" << ipie;
      name = outstring.str();
      dirS2PiesC->cd();
      S2PiesC[ipie] = new TH1I(name.c_str(),"",5000,0,100);
      S2PiesC[ipie]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");


      outstring.str("");
      outstring << "S2PieRLG_" << ipie;
      name = outstring.str();
      dirS2PiesLG->cd();
      S2PiesRLG[ipie] = new TH1I(name.c_str(),"",4000,0,16000);
      S2PiesRLG[ipie]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");


    }
  for (int iring=0;iring<NSRings;iring++)
    {

      outstring.str("");
      outstring << "S2RingR_" << iring;
      name = outstring.str();
      dirS2Rings->cd();
      S2RingsR[iring] = new TH1I(name.c_str(),"",4000,0,16000);
      S2RingsR[iring]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");

      outstring.str("");
      outstring << "S2RingC_" << iring;
      name = outstring.str();
      dirS2RingsC->cd();
      S2RingsC[iring] = new TH1I(name.c_str(),"",5000,0,100);
      S2RingsC[iring]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");


      outstring.str("");
      outstring << "S2RingRLG_" << iring;
      name = outstring.str();
      dirS2RingsLG->cd();
      S2RingsRLG[iring] = new TH1I(name.c_str(),"",4000,0,16000);
      S2RingsRLG[iring]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");


    }

  outstring.str("");
  outstring << "RusPieSumC";
  name = outstring.str();
  dirRsum->cd();
  ERPCSum = new TH2I(name.c_str(),"",64,-0.5,63.5,5000,0,100);
  ERPCSum->GetXaxis()->SetTitle("Rus Pie [det #]");
  ERPCSum->GetYaxis()->SetTitle("Hi Gain Energy [MeV]");

  outstring.str("");
  outstring << "RusRingSumC";
  name = outstring.str();
  dirRsum->cd();
  ERRCSum = new TH2I(name.c_str(),"",32,-0.5,31.5,5000,0,100);
  ERRCSum->GetXaxis()->SetTitle("Rus Ring [det #]");
  ERRCSum->GetYaxis()->SetTitle("Hi Gain Energy [MeV]");

  outstring.str("");
  outstring << "S2PieSumC";
  name = outstring.str();
  dirSsum->cd();
  ESPCSum = new TH2I(name.c_str(),"",16,-0.5,15.5,5000,0,100);
  ESPCSum->GetXaxis()->SetTitle("S2 Pie [det #]");
  ESPCSum->GetYaxis()->SetTitle("Hi Gain Energy [MeV]");

  outstring.str("");
  outstring << "S2RingSumC";
  name = outstring.str();
  dirSsum->cd();
  ESRCSum = new TH2I(name.c_str(),"",48,-0.5,47.5,5000,0,100);
  ESRCSum->GetXaxis()->SetTitle("S2 Ring [det #]");
  ESRCSum->GetYaxis()->SetTitle("Hi Gain Energy [MeV]");

  for (int ipie=0;ipie<NRPies;ipie++)
    {

      outstring.str("");
      outstring << "RusPieR_" << ipie;
      name = outstring.str();
      dirRPies->cd();
      RusPiesR[ipie] = new TH1I(name.c_str(),"",4000,0,16000);
      RusPiesR[ipie]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");

      outstring.str("");
      outstring << "RusPieC_" << ipie;
      name = outstring.str();
      dirRPiesC->cd();
      RusPiesC[ipie] = new TH1I(name.c_str(),"",5000,0,100);
      RusPiesC[ipie]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");

      outstring.str("");
      outstring << "RusPieCM1_" << ipie;
      name = outstring.str();
      dirRPiesCM1->cd();
      RusPiesCM1[ipie] = new TH1I(name.c_str(),"",5000,0,100);
      RusPiesCM1[ipie]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");


      outstring.str("");
      outstring << "RusPieRLG_" << ipie;
      name = outstring.str();
      dirRPiesLG->cd();
      RusPiesRLG[ipie] = new TH1I(name.c_str(),"",4000,0,16000);
      RusPiesRLG[ipie]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");

    }
  

  for(int iring = 0;iring<NRRings;iring++)
    {
      outstring.str("");
      outstring << "RusRingR_" << iring;
      name = outstring.str();
      dirRRings->cd();
      RusRingsR[iring] = new TH1I(name.c_str(),"",4000,0,16000);
      RusRingsR[iring]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");


      outstring.str("");
      outstring << "RusRingRLG_" << iring;
      name = outstring.str();
      dirRRingsLG->cd();
      RusRingsRLG[iring] = new TH1I(name.c_str(),"",4000,0,16000);
      RusRingsRLG[iring]->GetXaxis()->SetTitle("Hi Gain Energy [channel]");


      outstring.str("");
      outstring << "RusRingC_" << iring;
      name=outstring.str();
      dirRRingsC->cd();
      RusRingsC[iring] = new TH1I(name.c_str(),"",5000,0,100);
      RusRingsC[iring]->GetXaxis()->SetTitle("Hi Gain Energy [MeV]");


    }
  dirRsum->cd();
  E1E2pie = new TH2I("E1E2pie","",1000,0,16000,1000,0,16000);
  E1E2pie->GetXaxis()->SetTitle("Pie 5");
  E1E2pie->GetYaxis()->SetTitle("Pie 6");
  E1E2ring = new TH2I("E1E2ring","",1000,0,16000,1000,0,16000);
  E1E2ring->GetXaxis()->SetTitle("Pie 15");
  E1E2ring->GetYaxis()->SetTitle("Pie 16");

  RusPiesMult = new TH1I("RusPiesMult","",64,-0.5,63.5);
  RusRingsMult = new TH1I("RusRingsMult","",32,-0.5,31.5);
  HitMap = new TH2I("HitMap","",250,-50,50,250,-50,50); //Russian
  RusRingvPie = new TH2I("RusRingvPie","",1000,0,100,1000,0,100);



  dirSsum->cd();
  HitMap1 = new TH2I("HitMap1","",1200,-40,40,1200,-40,40); //S2
  S2PiesMult = new TH1I("S2PiesMult","",16,-0.5,15.5);
  S2RingsMult = new TH1I("S2RingsMult","",48,-0.5,47.5);
  S2RingvPie = new TH2I("S2RingvPie","",1000,0,100,1000,0,100);


  dirCsIsum->cd();
  S2CsIMult = new TH1I("S2CsIMult","",16,-0.5,15.5);
  RusCsIMult = new TH1I("RusCsIMult","",16,-0.5,15.5);
  TotCsIMult = new TH1I("TotCsIMult","",32,-0.5,31.5);



  //Li7
  dir7Li->cd();
  Ex7Li_ta = new TH1I("Ex7Li_ta","",300,0,15);
  Ex7Li_L1 = new TH1I("Ex7Li_L1","",300,0,15);
  Ex7Li_L2 = new TH1I("Ex7Li_L2","",300,0,15);
  Ex7Li_T = new TH1I("Ex7Li_T","",300,0,15);
  
  Ex7Li_tRaS = new TH1I("Ex7Li_tRaS","",300,0,15);
  Ex7Li_aRtS = new TH1I("Ex7Li_aRtS","",300,0,15);
  Ex7Li_taR = new TH1I("Ex7Li_taR","",300,0,15);
  Ex7Li_taS = new TH1I("Ex7Li_taS","",300,0,15);

  HitMap_perspective = new TH2I("HitMap","",250,-20,20,250,-13,13);



  velCM7Li_ta = new TH1I("velCM7Li_ta","",200,0,10);
  ExTarget_9Be = new TH1I("ExTarget_9Be","",720,-8,40);
  cosPsi_Chi_9Be = new TH2F("cosPsi_Chi_9Be","",50,-1,1,90,0,360);
  cosPsi_Chi_12C = new TH2F("cosPsi_Chi_12C","",50,-1,1,90,0,360);
  cosPsi_Chi_27Al = new TH2F("cosPsi_Chi_27Al","",50,-1,1,90,0,360);
  cosPsi_9Be = new TH1F("cosPsi_9Be","",50,-1,1);
  cosPsi_12C = new TH1F("cosPsi_12C","",50,-1,1);
  cosPsi_27Al = new TH1F("cosPsi_27Al","",50,-1,1);
  ExTarget_C = new TH1I("ExTarget_C","",720,-8,40);
  ExTarget_Al = new TH1I("ExTarget_Al","",720,-8,40);

  cosPsi_Chi_9Be_Rus = new TH2I("cosPsi_Chi_9Be_Rus","",50,-1,1,90,0,360);
  cosPsi_Chi_9Be_S2 = new TH2I("cosPsi_Chi_9Be_S2","",50,-1,1,90,0,360);
  cosPsi_Chi_9Be_RusS2 = new TH2I("cosPsi_Chi_9Be_RusS2","",50,-1,1,90,0,360);

  cosPsi_Chi_9Be_small_angle = new TH2F("cosPsi_Chi_9Be_small_angle","",50,-1,1,90,0,360);
  cosPsi_Chi_12C_small_angle = new TH2F("cosPsi_Chi_12C_small_angle","",50,-1,1,90,0,360);
  cosPsi_Chi_27Al_small_angle = new TH2F("cosPsi_Chi_27Al_small_angle","",50,-1,1,90,0,360);

  cosPsi_Chi_9Be_mid_angle = new TH2F("cosPsi_Chi_9Be_mid_angle","",50,-1,1,90,0,360);
  cosPsi_Chi_12C_mid_angle = new TH2F("cosPsi_Chi_12C_mid_angle","",50,-1,1,90,0,360);
  cosPsi_Chi_27Al_mid_angle = new TH2F("cosPsi_Chi_27Al_mid_angle","",50,-1,1,90,0,360);

  cosPsi_Chi_9Be_large_angle = new TH2F("cosPsi_Chi_9Be_large_angle","",50,-1,1,90,0,360);
  cosPsi_Chi_12C_large_angle = new TH2F("cosPsi_Chi_12C_large_angle","",50,-1,1,90,0,360);
  cosPsi_Chi_27Al_large_angle = new TH2F("cosPsi_Chi_27Al_large_angle","",50,-1,1,90,0,360);

  chi_9Be = new TH1F("chi_9Be","",90,0,360);


 
  /*
  cosPsi_Chi_12C_Rus = new TH2I("cosPsi_Chi_12C_Rus","",50,-1,1,90,0,360);
  cosPsi_Chi_12C_S2 = new TH2I("cosPsi_Chi_12C_S2","",50,-1,1,90,0,360);
  cosPsi_Chi_12C_RusS2 = new TH2I("cosPsi_Chi_12C_RusS2","",50,-1,1,90,0,360); 

  cosPsi_Chi_27Al_Rus = new TH2I("cosPsi_Chi_27Al_Rus","",50,-1,1,90,0,360);
  cosPsi_Chi_27Al_S2 = new TH2I("cosPsi_Chi_27Al_S2","",50,-1,1,90,0,360);
  cosPsi_Chi_27Al_RusS2 = new TH2I("cosPsi_Chi_27Al_RusS2","",50,-1,1,90,0,360);
  */

  Li7_theta_CM_9Be = new TH1F("Li7_theta_CM_9Be","",125,0,40);
  Li7_theta_CM_12C = new TH1F("Li7_theta_CM_12C","",125,0,40);
  Li7_theta_CM_27Al = new TH1F("Li7_theta_CM_27Al","",125,0,40);


  ExTarget_9Be_L2= new TH1I("ExTarget_9Be_L2","",480,-8,40);;
  ExTarget_9Be_L1= new TH1I("ExTarget_9Be_L1","",480,-8,40);;
  ExTarget_9Be_T= new TH1I("ExTarget_9Be_T","",480,-8,40);;

  ExTarget_12C_L2= new TH1I("ExTarget_12C_L2","",480,-8,40);;
  ExTarget_12C_L1= new TH1I("ExTarget_12C_L1","",480,-8,40);;
  ExTarget_12C_T= new TH1I("ExTarget_12C_T","",480,-8,40);;

  ExTarget_27Al_L2= new TH1I("ExTarget_27Al_L2","",480,-8,40);;
  ExTarget_27Al_L1= new TH1I("ExTarget_27Al_L1","",480,-8,40);;
  ExTarget_27Al_T= new TH1I("ExTarget_27Al_T","",480,-8,40);;

  gated_E_t_9Be = new TH1I("gated Triton p^2 9Be","",600,300,800);
  gated_E_t_12C = new TH1I("gated Triton p^2 12C","",600,300,800);
  gated_E_t_27Al = new TH1I("gated Triton p^2 27Al","",600,300,800);

  calib_diag1 = new TH1I("calibration diagnositics1","",5,0,5);
  calib_diag2 = new TH1I("calibration diagnositics2","",5,0,5);
  calib_diag3 = new TH1I("calibration diagnositics3","",5,0,5);

  ExTarget_9Be_tRaS = new TH1I("ExTarget_9Be_tRaS","",480,-8,40);
  ExTarget_9Be_aRtS = new TH1I("ExTarget_9Be_aRtS","",480,-8,40);
  ExTarget_9Be_taR = new TH1I("ExTarget_9Be_taR","",480,-8,40);
  ExTarget_9Be_taS = new TH1I("ExTarget_9Be_taS","",480,-8,40);


  dir6Li->cd();
  cosPsi_10Be = new TH1F("cosPsi_10Be","",50,-1,1);
  Ex6Li_da = new TH1I("Ex6Li_da","",300,0,15);
  Ex6Li_L1 = new TH1I("Ex6Li_L1","",300,0,15);
  Ex6Li_L2 = new TH1I("Ex6Li_L2","",300,0,15);
  Ex6Li_T = new TH1I("Ex6Li_T","",300,0,15);
  ExTarget_10Be = new TH1I("ExTarget_10Be","",720,-8,40);

  
  Ex6Li_Rus = new TH1I("Ex6Li_Rus","",300,0,15);
  Ex6Li_S2 = new TH1I("Ex6Li_S2","",300,0,15);
  Ex6Li_RusS2 = new TH1I("Ex6Li_RusS2","",300,0,15);

  Ex6Li_RusT = new TH1I("Ex6Li_RusT","",300,0,15);
  Ex6Li_RusL1 = new TH1I("Ex6Li_RusL1","",300,0,15);
  Ex6Li_RusL2 = new TH1I("Ex6Li_RusL2","",300,0,15);

  Ex6Li_S2T = new TH1I("Ex6Li_S2T","",300,0,15);
  Ex6Li_S2L1 = new TH1I("Ex6Li_S2L1","",300,0,15);
  Ex6Li_S2L2 = new TH1I("Ex6Li_S2L2","",300,0,15);

  Ex6Li_RusS2T = new TH1I("Ex6Li_RusS2T","",300,0,15);
  Ex6Li_RusS2L1 = new TH1I("Ex6Li_RusS2L1","",300,0,15);
  Ex6Li_RusS2L2 = new TH1I("Ex6Li_RusS2L2","",300,0,15);
  


}
//*********************************************
void histo::write()
{
  file->Write();

  cout << "histo written" << endl;
  /*
    for (int i=0;i<Ntele;i++)
    {
    delete red[i];
    }
    delete [] red;
  */
}
