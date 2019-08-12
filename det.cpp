#include "det.h"

#include <fstream>

#include <iostream>



//*********************************************************
  /**
   * Constructor
   */
det::det(histo * Histo0)
{
  Histo = Histo0;
  ran = new TRandom;
  Silicon = new silicon(ran,Histo);

  Rus_count=0;
  S2_count=0;
  RusS2_count=0;

 

}
//************************************************
  /**
   * destructor
   */
det::~det()
{
  delete Silicon;
  delete ran;
}
//*************************************************************
  /**
   * unpacks a physics event from the data stream
   \param point0 - pointer to location in data stream
  */
bool det::unpack(unsigned short *point,int runno)
{
  Silicon->reset();


  //cout << runno << endl;

  unsigned short  words = *point++;


  Run = runno;
  
  bool stat = false;
  stat = Silicon->unpack(point,runno);
  if (!stat) return stat;
  
  return stat;


}
//*********************************

void det::analyze(int event)
{
  // cout << "in det::analyze" << endl;
  Correl.Reset();

  Event = event;

  float Nsol =0;
  int mult  =0;
  CsImult = 0;

  if(Silicon->Telescope[0]->Pie.Nstore==1)
    {
      int ipie = Silicon->Telescope[0]->Pie.Order[0].strip;
      float penergy = Silicon->Telescope[0]->Pie.Order[0].energy;
      Histo->RusPiesCM1[ipie]->Fill(penergy);
    }
  
  for(int itele=0;itele<2;itele++)
    {
      if(Silicon->Telescope[itele]->Csi.Nstore==0)
	continue;
      for(int i = 0;i<1;i++)//Silicon->Telescope[itele]->Csi.Nstore;i++)  
	{
	  if(itele ==0)
	    {
	      Histo->ETCsI_Rus[Silicon->Telescope[itele]->Csi.Order[i].strip]->Fill(Silicon->Telescope[itele]->Csi.Order[i].time,Silicon->Telescope[itele]->Csi.Order[i].energyR);
	    }
	  else if(itele==1)
	    {
	      Histo->ETCsI_S2[Silicon->Telescope[itele]->Csi.Order[i].strip]->Fill(Silicon->Telescope[itele]->Csi.Order[i].time,Silicon->Telescope[itele]->Csi.Order[i].energyR);
	    }
	  else 
	    {
	      cout << "ERROR!" << endl;
	    }
	}
    }

 

  // trying to tease out source of double peaks in S2 CsI's, here I'm checking if there are any correlation between double peaks and multiplicity, i.e. if a Rus CsI fires as well does it shift the S2
  int rusmult = Silicon->Telescope[0]->Csi.Nstore;
  int S2mult = Silicon->Telescope[1]->Csi.Nstore;
  int icsi = Silicon->Telescope[1]->Csi.Order[0].strip+16;
  int ipie = Silicon->Telescope[1]->Pie.Order[0].strip;
  int iring = Silicon->Telescope[1]->Ring.Order[0].strip;

  int j=Silicon->Telescope[0]->Pie.Nstore;
  int k= Silicon->Telescope[1]->Pie.Nstore;

  /*
  if(j==0 && k!=0)
    {
      for(int i=0;i<Silicon->Telescope[1]->Pie.Nstore;i++)
	    {
	      if(Silicon->Telescope[1]->Pie.Order[i].energy >3)k--;
	      if(k==0)  Histo->RusPiesMult->Fill(Silicon->Telescope[0]->Pie.Nstore+Silicon->Telescope[1]->Pie.Nstore);
	    }
    }
  else if(j!=0 && k==0)
    {
      for(int i=0;i<Silicon->Telescope[0]->Pie.Nstore;i++)
	{
	  if(Silicon->Telescope[0]->Pie.Order[i].energy >3)j--;
	  if(j==0) Histo->RusPiesMult->Fill(Silicon->Telescope[0]->Pie.Nstore+Silicon->Telescope[1]->Pie.Nstore);
	}

    }
  else
    {
      for(int i=0;i<Silicon->Telescope[0]->Pie.Nstore;i++)
	{
	  if(Silicon->Telescope[0]->Pie.Order[i].energy >3)j--;
	  if(j==0)
	    {
	      for(int i=0;i<Silicon->Telescope[1]->Pie.Nstore;i++)
		{
		  if(Silicon->Telescope[1]->Pie.Order[i].energy >3)k--;
		  if(k==0)  Histo->RusPiesMult->Fill(Silicon->Telescope[0]->Pie.Nstore+Silicon->Telescope[1]->Pie.Nstore);
		}
	    }
	}
    }
  */

	// if(Silicon->Telescope[0]->Pie.Order[0].energy > 3 || Silicon->Telescope[1]->Pie.Order[0].energy > 3)
	// {
  Histo->RusPiesMult->Fill(j);
  Histo->RusRingsMult->Fill(Silicon->Telescope[0]->Ring.Nstore);
  // if((Silicon->Telescope[0]->Pie.Nstore+Silicon->Telescope[1]->Pie.Nstore)>1){cout << "Rus E = " << Silicon->Telescope[0]->Pie.Order[0].energy << endl << "Rus pie = " << Silicon->Telescope[0]->Pie.Order[0].strip << endl;cout << "S2 E = " <<Silicon->Telescope[1]->Pie.Order[0].energy << endl <<"S2 pie = " << Silicon->Telescope[1]->Pie.Order[0].strip << endl;}
      // }
  // if(Silicon->Telescope[1]->Pie.Order[0].energy > 3)
    //  {
  Histo->S2PiesMult->Fill(Silicon->Telescope[1]->Pie.Nstore);
  Histo->S2RingsMult->Fill(Silicon->Telescope[1]->Ring.Nstore);
  // }

  Histo->S2CsIMult->Fill(Silicon->Telescope[1]->Csi.Nstore);
  Histo->RusCsIMult->Fill(Silicon->Telescope[0]->Csi.Nstore);



  if(icsi==Silicon->Telescope[1]->Csicheck)//&&S2mult==1)
    {

      for(int i=0;i<S2mult;i++)
	{
	  int mult = rusmult+S2mult;
	  
	  if(iring==1||iring==4)Histo->multPeakCheck->Fill(Silicon->Telescope[1]->Csi.Order[i].energyR,mult);
	}
    }


  for (int itele=0;itele<2;itele++)
    {
      CsImult += Silicon->Telescope[itele]->Csi.Nstore;
      //      if(Silicon->Telescope[itele]->Csi.Nstore==0) continue; //FIX
      Silicon->Telescope[itele]->analyze(Event);
      Nsol = Silicon->Telescope[itele]->Nsolution;


      
      for(int ii=0;ii<Nsol;ii++)
	{
	  if(Silicon->Telescope[itele]->Solution[ii].iZ>0)
	    {
	      Correl.load(&Silicon->Telescope[itele]->Solution[ii]);
	      mult++;
	    }
	}
    }
  
  Histo->TotCsIMult->Fill(CsImult);


  if(mult >= 1) //I am throwing away a TON of elastic data because of this shit here...woo 9/14/2016
    {
      corr_7Li();
    }

  // if(mult==1){
  //   corr_7Li();
  // }

}



void det::corr_7Li()
{

  /* 

  need to make diagnoistics-is there position dependence in CsI? (for a couple CsI plot energy distribution of each ring)...

  should check pie calibrations->did this with alpha source at TAMU 8/2015

  how might i correct for the beam spot? (clearly off center from S2 hitmap)
  
  should also check if forward fragments reconstruct differently than backward fragments
    this is really a check of Rus vs S2

  just a reminder but an efficient way to change targets (based on run number) would be great. If tied to run number then I would only have to make the code once!-> done 10/2015

  need to do diagnostics on the multihit subroutine i.e. make sure all those events are actually being processed!->was a problem, should be fixed now 12/2015

  very seriously consider putting markers in the code to see where the hell its going...

  need to check loss files (pretty sure not fixed as of 12/2015)->done 12/2015->was error in Ta.loss  but fixed 6/2016
  
  need to make sure PID is working properly->seems to be problems aof 12/2015

  Figure out contributions of correlations from different telescopes of the detector array->done 12/2015

  figure out incomplete charge collection issues 

  Make effeciency map->sorta done 12/2015 but might need some work from calibrations....

  Check Z-lines especially for S2->established 12/2015, clearly some problems->Not a problem now 7/2016

  Consider making a class for all the calculations(should do for practice 1/2016), or just make functions.

  */
  double cosBeta; //beta is angle of triton with z-axis in CM frame of 7Li system->Check findErel code in correl
  double ptr[3];
  double pa[3];
  double vtr[3];
  double va[3];
  double relV[3];
  double PTR2;
  double PA2;
  double cosPsi;
  double chi;
  //speed of light in cm/ns = 29.98
  double etr;
  double ea;
  double Ex_target=0;;
  double et;
  double ek;
  double pt[3];
  double vt[3];
  double ppt=0;
  float momC[3];
  float velC[3];
  
  int target_no = Silicon->Telescope[0]->target;
  int useful=0;

  if(Correl.mult7Li>=1)
    {
      N7Li++;
      //if(Correl.mult7Li>1) //cout << "Rare Double 7Li events" << endl;
      Histo->mult7Li->Fill(Correl.mult7Li-0.5);
      //cout << Correl.mult7Li << endl;
      //Correl.findErel(target_no);
      
      float mass_target=0;
      if(target_no==1)mass_target=9;
      if(target_no==2)mass_target=12;
      if(target_no==3)mass_target=27;

      float EPA0 = 24.2;  
      float Pbeam2_mean = sqrt(pow((EPA0+931.478)*7.,2)-pow(7.*931.478,2));
      //float Ecm = (EPA0+931.478)*7. + mass_target*931.478;
      //float pcm = Pbeam2_mean;
      //float vCM = pcm/Ecm*30.;

      double Emane = (EPA0+931.478)*7 + mass_target*931.478;
      double Ecm = pow( pow(Emane,2.)-pow(Pbeam2_mean,2.) , 0.5); //Ecm = sqrt( (E1+E2)^2-(p1+p2)^2 )
      
      //reaction center of mass velocity
      // float Ecm = (EPA0+931.478)*7. + mass_target*931.478;
      float pcm = Pbeam2_mean;
      float vCM = Pbeam2_mean/Ecm*30. * mass_target/7.; //pcm = plab*m2/Ecm, want velocity of 7Li

      if(target_no==1)velC[2] = 6.66;//6.62038;//6.66214;//6.63562;//6.66214 //7Li beam after going through half the target...need to make this target dependent!
      if(target_no==2)velC[2] = 6.66053;
      if(target_no==3)velC[2] = 6.66187;
      velC[1]=0.;
      velC[0]=0.;

      ptr[0]=Correl.Li7[0]->Mvect[0];
      ptr[1]=Correl.Li7[0]->Mvect[1];
      ptr[2]=Correl.Li7[0]->Mvect[2];
      //cout  << ptr[2] << endl;
      //cout  << ptr[1] << endl;
      //cout << ptr[0] << endl;
      //cout << Correl.Li7[0]->energyTot << endl; 
      PTR2 = pow(ptr[0],2)+pow(ptr[1],2)+pow(ptr[2],2);

      //cout << "Correl.thetaCM = " << Correl.thetaCM*180./3.14159 << endl;
      //cout << "Correl.thetaReactionCM = " << Correl.thetaReactCoM*180./3.14159 << endl;

      
      double theta = Correl.Li7[0]->theta;
      double phi = Correl.Li7[0]->phi;
      
      
      double energyTot = sqrt( pow(931.478*7,2)+PTR2 );
      
      float velReactionCoM[3] ={0,0,velC[2]-vCM}; //since close to newtonian this works, relativist will have 1/(1-velC*vCM/c^2)
      //float velReactionCoM[3] = {-B[0]/Bmag*(velC[2]-vCM),-B[1]/Bmag*(velC[2]-vCM),-B[2]/Bmag*(velC[2]-vCM)};
      float  * momCoM;
      momCoM = Correl.Kinematics.transformMom((float*)ptr,velReactionCoM,energyTot,momC);
      float momTot = sqrt(pow(momCoM[0],2.)+pow(momCoM[1],2.)+pow(momCoM[2],2.));
      float mu = mass_target/(mass_target+7);
      double thetaReactCoM2 = atan(pcm*sin(theta)/(pcm*cos(theta)-7*931.478*pcm/Emane));//acos(momCoM[2]/momTot); //non-relativistic expression
      double thetaReactCoM = acos(momCoM[2]/momTot);

      //thetaReactCoM = thetaReactCoM2;
      
      double lightCsI = Correl.Li7[0]->energyR;

      Histo->elas7Li_12C_pieCheck->Fill(Correl.Li7[0]->ipie);

      //double y = 149.*sin(theta)*sin(phi);
      //double x = 149.*sin(theta)*cos(phi);

      // if(y<0.4 && y > -0.4)
      // 	cout << "y = " << y << " phi = " << phi*180./3.14159 <<  endl;
      
      //float velReactionCoM[3] ={0,0,vCM};
      //float  * momCoM;
      //momCoM = Kinematics.transformMom(Mtot,velReactionCoM,energyTot,momC);
      //float momTot = sqrt(pow(momCoM[0],2.)+pow(momCoM[1],2.)+pow(momCoM[2],2.));
      //float mu = mas_target/(mass_target+7);
      //float thetaReactCoM=0;
      if(target_no==1)
	{
	  //thetaReactCoM = atan(pcm*sin(Correl.Li7[0]->theta)/(pcm*cos(Correl.Li7[0]->theta)-7*931.478*pcm/Ecm));//acos(momCoM[2]/momTot);
	 Histo->elas7Li_9Be->Fill(thetaReactCoM2*180/3.14159);
	}
      if(target_no==2)
	{
	  //thetaReactCoM = atan(pcm*sin(Correl.Li7[0]->theta)/(pcm*cos(Correl.Li7[0]->theta)-7*931.478*pcm/Ecm));//acos(momCoM[2]/momTot);
	  Histo->elas7Li_E_12C->Fill(Correl.Li7[0]->energyR);
	  if(lightCsI >2600){
	    Histo->elas7Li_12C->Fill(thetaReactCoM2*180./3.14159,1/sin(thetaReactCoM2));
	    Histo->elas7Li_12C_labAngle->Fill(theta*180./3.14159);
	  }
	  // if(lightCsI > 2600 && y < 0.05 && y>-0.05 && x<0){ //&& phi*180./3.14159 > 350 && phi*180./3.14159 < 10){
	  //   Histo->elas7Li_12C_phiCut->Fill(thetaReactCoM2*180./3.14159);
	  // }
	}
      if(target_no==3)
	{
	  //thetaReactCoM = atan(pcm*sin(Correl.Li7[0]->theta)/(pcm*cos(Correl.Li7[0]->theta)-7*931.478*pcm/Ecm));//acos(momCoM[2]/momTot);
	 Histo->elas7Li_27Al->Fill(thetaReactCoM2*180/3.14159);
	}
  


    }
  if(Correl.multAlpha==2)
    {
      float Q8Be = -.09184;
      Correl.zeroMask();
      Correl.maskAlpha[0]=1; //1 or 0 depending if you want to add that particle to the array for reconstruction
      Correl.maskAlpha[1]=1;
      Correl.makeArray(1);
      float Erel_8Be = Correl.findErel(target_no);
      float Ex = Erel_8Be + Q8Be;

      if(Correl.alpha[0]->itele==0 && Correl.alpha[1]->itele==0){please=1;useful=3;}
      if(Correl.alpha[0]->itele==1 && Correl.alpha[1]->itele==1){please=2;useful=4;}
      if(Correl.alpha[0]->itele==1 && Correl.alpha[1]->itele==0){please=3;useful=1;}
      if(Correl.alpha[0]->itele==0 && Correl.alpha[1]->itele==1){please=3;useful=2;}

      Histo->Ex8Be->Fill(Ex);
      //if(please==1)Histo->Ex6Li_Rus->Fill(Ex);
      //if(please==2)Histo->Ex6Li_S2->Fill(Ex);
      //if(please==3)Histo->Ex6Li_RusS2->Fill(Ex);
      /*
      ptr[0]=Correl.alpha[0]->MomCM[0];
      ptr[1]=Correl.alpha[0]->MomCM[1];
      ptr[2]=Correl.alpha[0]->MomCM[2];
      PTR2 = pow(ptr[0],2)+pow(ptr[1],2)+pow(ptr[2],2);
      etr = sqrt(pow(931.478*2,2)+PTR2);
      */

      pa[0]=Correl.alpha[0]->MomCM[0];
      pa[1]=Correl.alpha[0]->MomCM[1];
      pa[2]=Correl.alpha[0]->MomCM[2];
      PA2 = pow(pa[0],2)+pow(pa[1],2)+pow(pa[2],2);
      ea = sqrt(pow(931.478*4,2)+PA2);
      
      cosBeta = pa[2]/sqrt(PA2);

      if(cosBeta>0.5)Histo->Ex8BeL2->Fill(Ex);
      if(cosBeta<-0.5)Histo->Ex8BeL1->Fill(Ex);
      if(cosBeta>-0.5&&cosBeta<0.5)Histo->Ex8BeT->Fill(Ex);

      pt[0] = -Correl.alpha[0]->Mvect[0] - Correl.alpha[1]->Mvect[0];
      pt[1] = -Correl.alpha[0]->Mvect[1] - Correl.alpha[1]->Mvect[1];
      pt[2] = 1489.22-Correl.alpha[0]->Mvect[2] - Correl.alpha[1]->Mvect[2];
      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));


      if(target_no==1 && Ex>-5 && Ex<0.18)
	{
	  et = sqrt(pow(931.478*8.022,2)+pow(ppt,2));
	  ek = et - 8.022*931.478;
	  
	  Ex_target = 24.2*7.-Correl.alpha[0]->Ekin-Correl.alpha[1]->Ekin-ek-.368; //.368 is total Q-value
	  Histo->ExTarget8Li->Fill(Ex_target);
	  //Histo->Li6_thetaCM->Fill(Correl.thetaCM*180/3.1415927);
	  //Histo->Li6velCM->Fill(Correl.velocityCM);
	}


      

    }


  if(Correl.multH2 == 1 && Correl.multAlpha ==1)
    {



      float Q6Li = 1.4743;
      Correl.zeroMask();
      Correl.mask2H[0]=1;
      Correl.maskAlpha[0]=1;
      Correl.makeArray(1);
      Correl.velC[2]=7.1;
      float Erel_6Li = Correl.findErel(target_no);
      float Ex = Erel_6Li+Q6Li;

      if(Correl.alpha[0]->itele==0 && Correl.H2[0]->itele==0){please=1;useful=3;}
      if(Correl.alpha[0]->itele==1 && Correl.H2[0]->itele==1){please=2;useful=4;}
      if(Correl.alpha[0]->itele==1 && Correl.H2[0]->itele==0){please=3;useful=1;}
      if(Correl.alpha[0]->itele==0 && Correl.H2[0]->itele==1){please=3;useful=2;}

      ptr[0]=Correl.H2[0]->MomCM[0];
      ptr[1]=Correl.H2[0]->MomCM[1];
      ptr[2]=Correl.H2[0]->MomCM[2];
      PTR2 = pow(ptr[0],2)+pow(ptr[1],2)+pow(ptr[2],2);
      etr = sqrt(pow(931.478*2,2)+PTR2);
      
      //Histo->TKE_H2->Fill(Silicon->Telescope[Correl.H2[0]->itele]->Csi.Order[0].energy);//(etr-931.478*2);
      // Histo->TKE_A->Fill(Silicon->Telescope[Correl.alpha[0]->itele]->Csi.Order[0].energy);
      //cout << "TKE H2 = "  << etr - 931.478*2 << endl;

      cosBeta = ptr[2]/sqrt(PTR2);

      pa[0]=Correl.alpha[0]->MomCM[0];
      pa[1]=Correl.alpha[0]->MomCM[1];
      pa[2]=Correl.alpha[0]->MomCM[2];
      PA2 = pow(pa[0],2)+pow(pa[1],2)+pow(pa[2],2);
      ea = sqrt(pow(931.478*4,2)+PA2);
      //Histo->TKE_A->Fill(ea-931.478*4);
      //cout << "TKE A = " << ea - 931.478*4 << endl;


      Histo->Ex6Li_da->Fill(Ex);
      if(cosBeta>0.5)Histo->Ex6Li_L2->Fill(Ex);
      if(cosBeta<-0.5)Histo->Ex6Li_L1->Fill(Ex);
      if(cosBeta>-0.5&&cosBeta<0.5)Histo->Ex6Li_T->Fill(Ex);

      /*
      if(please==1)
	{
	  Histo->Ex6Li_Rus->Fill(Ex);
	  if(cosBeta>0.5)Histo->Ex6Li_RusL2->Fill(Ex);
	  if(cosBeta<-0.5)Histo->Ex6Li_RusL1->Fill(Ex);
	  if(cosBeta>-0.5&&cosBeta<0.5)Histo->Ex6Li_RusT->Fill(Ex);	  
	}

      if(please==2)
	{
	  Histo->Ex6Li_S2->Fill(Ex);
	  if(cosBeta>0.5)Histo->Ex6Li_S2L2->Fill(Ex);
	  if(cosBeta<-0.5)Histo->Ex6Li_S2L1->Fill(Ex);
	  if(cosBeta>-0.5&&cosBeta<0.5)Histo->Ex6Li_S2T->Fill(Ex);
	}

      if(please==3)
	{
	  Histo->Ex6Li_RusS2->Fill(Ex);
	  if(cosBeta>0.5)Histo->Ex6Li_RusS2L2->Fill(Ex);
	  if(cosBeta<-0.5)Histo->Ex6Li_RusS2L1->Fill(Ex);
	  if(cosBeta>-0.5&&cosBeta<0.5)Histo->Ex6Li_RusS2T->Fill(Ex);
	}
      */   

      pt[0] = -Correl.alpha[0]->Mvect[0] - Correl.H2[0]->Mvect[0];
      pt[1] = -Correl.alpha[0]->Mvect[1] - Correl.H2[0]->Mvect[1];
      pt[2] = 1489.22-Correl.alpha[0]->Mvect[2] - Correl.H2[0]->Mvect[2];
      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));

      if(target_no==1)
	{
	  et = sqrt(pow(931.478*10.,2)+pow(ppt,2));
	  ek = et - 10.*931.478;
	  
	  Ex_target = 24.*7.-Correl.alpha[0]->Ekin-Correl.H2[0]->Ekin-ek-Q6Li;
	  Histo->ExTarget_10Be->Fill(Ex_target);
	  Histo->Li6_thetaCM->Fill(Correl.thetaCM*180/3.1415927);
	  Histo->Li6velCM->Fill(Correl.velocityCM);
	}

      if(Ex>1.9&&Ex<2.65)
	{
	  for(int i=0;i<3;i++)
	    {
	      vtr[i]= ptr[i]*pow(29.98,2)/etr;
	      va[i] = pa[i]*pow(29.98,2)/ea;
	      relV[i] = vtr[i]-va[i];	

	    }


	  double mrelV = sqrt(pow(relV[0],2)+pow(relV[1],2)+pow(relV[2],2));
	  double trelV = sqrt(pow(relV[1],2)+pow(relV[0],2));
	  
	  cosPsi = relV[2]/mrelV;
	  chi = (atan2(relV[1],relV[0])-Correl.phiCM)*180/3.1415927;
          if (chi < 0) chi+=360.;
	  if (chi >  360) chi-=360.;
	  if(target_no==1)
	    { 
	      if(Ex_target>-3.&&Ex_target<1.)
		{
		  Histo->cosPsi_Chi_10Be->Fill(cosPsi,chi);
		  Histo->cosPsi_10Be->Fill(cosPsi);//(cosPsi);
		  if(please==1){Histo->cosPsi_10Be_Rus->Fill(cosBeta);Histo->cosPsi_Chi_10Be_Rus->Fill(cosPsi,chi);}//(cosPsi);
		  else if(please==2){Histo->cosPsi_10Be_S2->Fill(cosBeta);Histo->cosPsi_Chi_10Be_S2->Fill(cosPsi,chi);}//(cosPsi);
		  else if(please==3){Histo->cosPsi_10Be_RusS2->Fill(cosBeta);Histo->cosPsi_Chi_10Be_RusS2->Fill(cosPsi,chi);}//(cosPsi);
		}
	    }
	}



    }


  if(Correl.multH3 == 1 && Correl.multAlpha ==1)
    {


	  

      //can use these if statements to generate angular correlation contriubution of each telescope
      if(Correl.alpha[0]->itele==0 && Correl.H3[0]->itele==0){Rus_count++;please=1;useful=3;}
      if(Correl.alpha[0]->itele==1 && Correl.H3[0]->itele==1){S2_count++;please=2;useful=4;}
      if(Correl.alpha[0]->itele==1 && Correl.H3[0]->itele==0){RusS2_count++;please=3;useful=1;}
      if(Correl.alpha[0]->itele==0 && Correl.H3[0]->itele==1){RusS2_count++;please=3;useful=2;}

 

      N7Li_ta++;
      float Q7Li = 2.468;
      Correl.zeroMask();
      Correl.mask3H[0]=1;
      Correl.maskAlpha[0]=1;
      Correl.makeArray(1);
      float Erel_7Li = Correl.findErel(target_no);
      float Ex = Erel_7Li+Q7Li;
      Histo->Ex7Li_ta->Fill(Erel_7Li+Q7Li);

      if(Ex>4.0 && Ex<5.0)
	{

	  if(target_no==1)
	    {
	      pt[0] = -Correl.alpha[0]->Mvect[0] - Correl.H3[0]->Mvect[0];
	      pt[1] = -Correl.alpha[0]->Mvect[1] - Correl.H3[0]->Mvect[1];
	      pt[2] = 1497.45-Correl.alpha[0]->Mvect[2] - Correl.H3[0]->Mvect[2];
	      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));


	      /* //I believe this code below was screwing up my target excitation energy spectrum because I changed pt!
	      double Ecm = sqrt( pow(24*7.+(7+9)*931.478,2.) - pow(Correl.momentumCM,2.) );
	      pt[0] = -Correl.momC[0];
	      pt[1] = -Correl.momC[1];
	      pt[2] = -Correl.momC[2];
	      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));
	      //cout << Ecm << endl;
	      double Ep = sqrt( pow(ppt,2.) + pow(7*931.478+4.63,2.) );
	      double Et = Ecm-Ep;	    
	      */


	      
	      et = sqrt(pow(931.478*9.,2)+pow(ppt,2));
	      double vvt = ppt/et*pow(29.98,2);
	      for (int i=0;i<3;i++) vt[i]=vvt/ppt*pt[i];
	      //double Ein = (24+931.478)&7.;
	      //double Etot = Ein + 9*931.478;
	      //double p =  pow( pow(Ein,2.)- pow(7*931.478,2.) ,0.5);
	      //double vcm = pin/Etot;
	      ek = et - 9.*931.478;
	      Ex_target = 24.2*7.-Correl.alpha[0]->Ekin-Correl.H3[0]->Ekin-ek-Q7Li; //first number is energy of beam after passing through half of target

	      //Ex_target = sqrt( pow(Et,2.)-pow(ppt,2.) ) - 9.*931.478;
	      //for some reason the above line gives correct shape of spectra but it's "stretched" for some reason
	      //I will try Bob's method and see if it has the same problem 9/23/2016
	      //cout << Ex_target << endl;
	      //Just realizing now that this is non-relativistic calculation done in LAB frame 9/23/2016
	      //Will try implementing a SR formulation
	      // Histo->ExTarget_9Be->Fill(Ex_target);
	      //	  cout << "made it to target energy Be" << endl;
	      Histo->velCM7Li_ta->Fill(Correl.velocityCM);
	      // if(Correl.thetaCM > 0.0084)
	      //       Histo->Li7_theta_CM_9Be->Fill(Correl.thetaCM*180./3.1415927,1./sin(Correl.thetaCM));
	      Histo->Li7_theta_CM_9Be->Fill(Correl.thetaCM*180/3.14159);
	      Histo->Li7_theta_reactCoM_9Be->Fill(Correl.thetaReactCoM*180/3.14159);
	      //cout << 1./sin(Correl.thetaCM) << endl;
	      pt[0] = Correl.H3[0]->Mvect[0];
	      pt[1] = Correl.H3[0]->Mvect[1];
	      pt[2] = Correl.H3[0]->Mvect[2];
	      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));
	      // cout << ppt << endl;
	      //	      Histo->gated_E_t_9Be->Fill(ppt);
	      //if(ppt<650)
	      Histo->ExTarget_9Be->Fill(Ex_target);
	    }
	  
	  
	  
	  if(target_no==2)
	    {
	      pt[0] = -Correl.alpha[0]->Mvect[0] - Correl.H3[0]->Mvect[0];
	      pt[1] = -Correl.alpha[0]->Mvect[1] - Correl.H3[0]->Mvect[1];
	      pt[2] = 1497.45-Correl.alpha[0]->Mvect[2] - Correl.H3[0]->Mvect[2];
	      //pt[2] = 1488.-Correl.alpha[0]->Mvect[2] - Correl.H3[0]->Mvect[2];
	      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));

	      /*
	      double Ecm = sqrt( pow(24*7.+(7+12)*931.478,2.) - pow(Correl.momentumCM,2.) );
	      pt[0] = -Correl.momC[0];
	      pt[1] = -Correl.momC[1];
	      pt[2] = -Correl.momC[2];
	      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));
	      //cout << Ecm << endl;
	      double Ep = sqrt( pow(ppt,2.) + pow(7*931.478+4.63,2.) );
	      double Et = Ecm-Ep;	    
	      */	      

	      et = sqrt(pow(931.478*12.,2)+pow(ppt,2));
	      double vvt = ppt/et*pow(29.98,2);
	      for (int i=0;i<3;i++) vt[i]=vvt/ppt*pt[i];
	      ek = et - 12.*931.478;
	      Ex_target = 24.19*7.-Correl.alpha[0]->Ekin-Correl.H3[0]->Ekin-ek-Q7Li;
	      Ex_target = 24.2*7.-Correl.alpha[0]->Ekin-Correl.H3[0]->Ekin+(14.908-2.424-14.949)+12*931.478;
	      Ex_target = sqrt( pow(Ex_target,2.) - pow(ppt,2.) ) - 12*931.478;
	      //cout << Ex_target << endl;
	      //Ex_target = sqrt( pow(Et,2.)-pow(ppt,2.) ) - 12.*931.478;	      
	      // cout << "made it to target energy C" << endl;
	      //  cout << "target energy = " << Ex_target << endl;
	      if(Correl.thetaCM > 0.0084)
		Histo->Li7_theta_CM_12C->Fill(Correl.thetaCM*180./3.1415927);//,1./sin(Correl.thetaCM));
	      Histo->Li7_theta_reactCoM_12C->Fill(Correl.thetaReactCoM*180/3.14159,1./sin(Correl.thetaReactCoM));
	      //Histo->Li7_theta_reactCoM_12C->Fill(Correl.cosThetaC*180/3.14159);
	      //cout << Correl.thetaReactCoM-Correl.cosThetaC << endl;
	      pt[0] = Correl.H3[0]->Mvect[0];
	      pt[1] = Correl.H3[0]->Mvect[1];
	      pt[2] = Correl.H3[0]->Mvect[2];
	      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));
	      //	      Histo->gated_E_t_12C->Fill(ppt);
	      Histo->ExTarget_C->Fill(Ex_target);
	    }
	  
	  
	  
	  if(target_no==3)
	    {
	      pt[0] = -Correl.alpha[0]->Mvect[0] - Correl.H3[0]->Mvect[0];
	      pt[1] = -Correl.alpha[0]->Mvect[1] - Correl.H3[0]->Mvect[1];
	      pt[2] = 1497.45-Correl.alpha[0]->Mvect[2] - Correl.H3[0]->Mvect[2];
	      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));
	      
	      et = sqrt(pow(931.478*27.,2)+pow(ppt,2));
	      double vvt = ppt/et*pow(29.98,2);
	      for (int i=0;i<3;i++) vt[i]=vvt/ppt*pt[i];
	      ek = et - 27.*931.478;
	      Ex_target = 24.2*7.-Correl.alpha[0]->Ekin-Correl.H3[0]->Ekin-ek-Q7Li; //need to fix first number 12/2015      
	      // cout << "made it to target energy C" << endl;
	      //  cout << "target energy = " << Ex_target << endl;
	      if(Correl.thetaCM > 0.0084)
		Histo->Li7_theta_CM_27Al->Fill(Correl.thetaCM*180./3.1415927);//,1./sin(Correl.thetaCM));
	      Histo->Li7_theta_reactCoM_27Al->Fill(Correl.thetaReactCoM*180/3.14159);
	      pt[0] = Correl.H3[0]->Mvect[0];
	      pt[1] = Correl.H3[0]->Mvect[1];
	      pt[2] = Correl.H3[0]->Mvect[2];
	      ppt = sqrt(pow(pt[0],2)+pow(pt[1],2)+pow(pt[2],2));
	      //	      Histo->gated_E_t_27Al->Fill(ppt);
	      Histo->ExTarget_Al->Fill(Ex_target);
	    }
	} 



      //attempt at relative velocity of fragments for 7Li*



      //consider restricting these to angles >2 degrees

      ptr[0]=Correl.H3[0]->MomCM[0];
      ptr[1]=Correl.H3[0]->MomCM[1];
      ptr[2]=Correl.H3[0]->MomCM[2];
      PTR2 = pow(ptr[0],2)+pow(ptr[1],2)+pow(ptr[2],2);
      etr = sqrt(pow(931.478*3,2)+PTR2);
      
      cosBeta = ptr[2]/sqrt(PTR2);
      
      pa[0]=Correl.alpha[0]->MomCM[0];
      pa[1]=Correl.alpha[0]->MomCM[1];
      pa[2]=Correl.alpha[0]->MomCM[2];
      PA2 = pow(pa[0],2)+pow(pa[1],2)+pow(pa[2],2);
      ea = sqrt(pow(931.478*4,2)+PA2);



      if(cosBeta>0.5)Histo->Ex7Li_L2->Fill(Ex);
      if(cosBeta<-0.5)Histo->Ex7Li_L1->Fill(Ex);
      if(cosBeta>-0.5&&cosBeta<0.5)Histo->Ex7Li_T->Fill(Ex);

      //if(target_no==1)
      //{
      if(useful==1)Histo->Ex7Li_tRaS->Fill(Ex);
      if(useful==2)Histo->Ex7Li_aRtS->Fill(Ex);
      if(useful==3)Histo->Ex7Li_taR->Fill(Ex);
      if(useful==4)Histo->Ex7Li_taS->Fill(Ex);
      //}

      if(Ex > 4 && Ex <5)//gating on "ground state" peak and 7/2- state of 7Li
	{

	  for(int i=0;i<3;i++)
	    {
	      vtr[i]= ptr[i]*pow(29.98,2)/etr;
	      va[i] = pa[i]*pow(29.98,2)/ea;
	      relV[i] = vtr[i]-va[i];	

	    }


	  double mrelV = sqrt(pow(relV[0],2)+pow(relV[1],2)+pow(relV[2],2));
	  double trelV = sqrt(pow(relV[1],2)+pow(relV[0],2));



	  cosPsi = relV[2]/mrelV;
	  // cout << "CosPsi 1 = " << cosPsi << endl;
	  // cosPsi = ptr[2]/sqrt(PTR2); // calculating this with the center of mass momentum should give the exact same results // and it is! GREAT!
	  //cout << "CosPsi 2 = " << cosPsi << endl;
	  chi = (atan2(relV[1],relV[0])-Correl.phiCM)*180/3.1415927;
	  //cout << "Chi 1 = " << chi << endl;
	  //chi = (atan2(ptr[1],ptr[0])-Correl.phiCM)*180/3.1415927; 
	  //cout << "Chi 2 = " << chi << endl;
          if (chi < 0) chi+=360.;
	  if (chi >  360) chi-=360.;
	  //if (chi < 0 && chi > -180)chi+=360.;

	  //want to rotate the quantization axis by some amount in the reaction plane: 8/16/2017
	  //will have to confirm with Bob but I think this can be defined by 7Li momentum and beam-axis
	  //Psi and Chi are defined by the reaction plane, Psi is the angle in the reaction plane so only need to rotate that value
	  //remember have to rotate backwards to get angle (probably doesn't matter if symmetric)
	  //x = cos(Psi), y = sin(Psi)

	  //x' = x*cos(theta_rot) + y*sin(theta_rot);

	  double theta_rot = 0.; //in degrees
	  theta_rot = theta_rot*3.1415927/180.;
	  double psi = acos(cosPsi);
	  double x1,y1,z1;
	  x1 = cos(chi)*sin(psi);
	  y1 = sin(chi)*sin(psi);
	  z1 = cos(psi);
	  
	  double x2,y2,z2;
	  //for rotation about y-axis (in reaction-plane)
	  x2 = x1*cos(theta_rot)+z1*sin(theta_rot);
	  y2 = y1;
	  z2 = -x1*sin(theta_rot)+z1*cos(theta_rot);
    
	  //for rotation about x-axis (out of reaction-plane)
	  x2 = x1;
	  y2 = y1*cos(theta_rot) - z1*sin(theta_rot);
	  z2 = y1*sin(theta_rot) + z1*cos(theta_rot);
    

	  
	  //cosPsi = cosPsi*cos(theta_rot)+ sin( acos(cosPsi) )*sin(theta_rot);
	  cosPsi = z2;
	  
	  if(target_no==1)
	    {
	      //if(Ex_target>1.1)
	      if(Ex_target>-10&&Ex_target<1.5)
		{
		  Histo->cosPsi_Chi_9Be->Fill(cosPsi,chi);
		  Histo->cosPsi_9Be->Fill(cosPsi);
		  if(please==1)Histo->cosPsi_Chi_9Be_Rus->Fill(cosPsi,chi);
		  if(please==2)Histo->cosPsi_Chi_9Be_S2->Fill(cosPsi,chi);
		  if(please==3)Histo->cosPsi_Chi_9Be_RusS2->Fill(cosPsi,chi);
		  if(Correl.thetaReactCoM*180./3.1415927<1)
		    Histo->cosPsi_Chi_9Be_small_angle->Fill(cosPsi,chi);
		  if(Correl.thetaReactCoM*180./3.1415927>1&&Correl.thetaReactCoM*180./3.1415927<3)
		    Histo->cosPsi_Chi_9Be_mid_angle->Fill(cosPsi,chi);
		  if(Correl.thetaReactCoM*180./3.1415927>15)
		    Histo->cosPsi_Chi_9Be_large_angle->Fill(cosPsi,chi);
		  Histo->chi_9Be->Fill(chi);
		  
		  
		}
	      //if(cosBeta>0.5){Histo->ExTarget_9Be_L2->Fill(Ex_target);Histo->calib_diag1->Fill(please);}
	      //if(cosBeta<-0.5){Histo->ExTarget_9Be_L1->Fill(Ex_target);Histo->calib_diag2->Fill(please);}
	      //if(cosBeta>-0.5&&cosBeta<0.5){Histo->ExTarget_9Be_T->Fill(Ex_target);Histo->calib_diag3->Fill(please);}

	      if(useful==1)Histo->ExTarget_9Be_tRaS->Fill(Ex_target);
	      if(useful==2)Histo->ExTarget_9Be_aRtS->Fill(Ex_target);
	      if(useful==3)Histo->ExTarget_9Be_taR->Fill(Ex_target);
	      if(useful==4)Histo->ExTarget_9Be_taS->Fill(Ex_target);


	    }

	  
	  if(target_no==2)
	    {
	      //if(Ex_target>3&&Ex_target<7){
	      if(Ex_target>-10&&Ex_target<3){
		
		  Histo->cosPsi_Chi_12C->Fill(cosPsi,chi);
		  Histo->cosPsi_12C->Fill(cosPsi);
		  if(Correl.thetaReactCoM*180./3.1415927<0)
		    Histo->cosPsi_Chi_12C_small_angle->Fill(cosPsi,chi);
		  if(Correl.thetaReactCoM*180./3.1415927>5 &&Correl.thetaReactCoM*180./3.1415927<15)
		    Histo->cosPsi_Chi_12C_mid_angle->Fill(cosPsi,chi);
		  if(Correl.thetaReactCoM*180./3.1415927>15)
		    Histo->cosPsi_Chi_12C_large_angle->Fill(cosPsi,chi);		
		}
	      if(Ex_target>3 && Ex_target<6)
		{
		  Histo->cosPsi_Chi_12C_2plus->Fill(cosPsi,chi);
		}
	      /*
	      if(please==1)Histo->cosPsi_Chi_12C_Rus->Fill(cosPsi,chi);
	      if(please==2)Histo->cosPsi_Chi_12C_S2->Fill(cosPsi,chi);
	      if(please==3)Histo->cosPsi_Chi_12C_RusS2->Fill(cosPsi,chi);
	      */
	      // if(cosBeta>0.5)Histo->ExTarget_12C_L2->Fill(Ex_target);
	      //if(cosBeta<-0.5)Histo->ExTarget_12C_L1->Fill(Ex_target);
	      //if(cosBeta>-0.5&&cosBeta<0.5)Histo->ExTarget_12C_T->Fill(Ex_target);

	    }

	  if(target_no==3)
	    {
	      //if(Ex_target>1){
	      if(Ex_target>-10&&Ex_target<2)
		{
		  Histo->cosPsi_Chi_27Al->Fill(cosPsi,chi);
		  Histo->cosPsi_27Al->Fill(cosPsi);
		  if(Correl.thetaReactCoM*180./3.1415927<5)
		    Histo->cosPsi_Chi_27Al_small_angle->Fill(cosPsi,chi);
		  if(Correl.thetaReactCoM*180./3.1415927>3.5 && Correl.thetaReactCoM*180./3.1415927<30)
		    Histo->cosPsi_Chi_27Al_mid_angle->Fill(cosPsi,chi);
		  if(Correl.thetaReactCoM*180./3.1415927>15)
		    Histo->cosPsi_Chi_27Al_large_angle->Fill(cosPsi,chi);
		}
	      /*
	      if(please==1)Histo->cosPsi_Chi_27Al_Rus->Fill(cosPsi,chi);
	      if(please==2)Histo->cosPsi_Chi_27Al_S2->Fill(cosPsi,chi);
	      if(please==3)Histo->cosPsi_Chi_27Al_RusS2->Fill(cosPsi,chi);
	      */
	      //if(cosBeta>0.5)Histo->ExTarget_27Al_L2->Fill(Ex_target);
	      //if(cosBeta<-0.5)Histo->ExTarget_27Al_L1->Fill(Ex_target);
	      //if(cosBeta>-0.5&&cosBeta<0.5)Histo->ExTarget_27Al_T->Fill(Ex_target);

	    }
	  

	}


       //target excitation energy
       
      /*
      double pt[3];
      pt[0] = -Correl.proton[0]->Mvect[0] - Correl.proton[1]->Mvect[0] 
               - Correl.Be7[0]->Mvect[0];
      pt[1] = -Correl.proton[0]->Mvect[1] - Correl.proton[1]->Mvect[1]                 - Correl.Be7[0]->Mvect[1];
       pt[2] = 3175.58 // momentum in beam -Correl.proton[0]->Mvect[2] - Correl.proton[1]->Mvect[2] 
               - Correl.Be7[0]->Mvect[2];      


      double ppt = sqrt(pow(pt[0],2) + pow(pt[1],2)+pow(pt[2],2));
       double et = sqrt(pow(931.478*9.,2) + pow(ppt,2));
      double vvt = ppt/et*30.; //target velocity
      double vt[3];
       for (int i=0;i<3;i++) vt[i] = vvt/ppt*pt[i];
      double ek = et - 9.*931.478;
      double Ex_target = 64.38*9.//E/A of beam at center of the target - Correl.proton[0]->Ekin - 
         Correl.proton[1]->Ekin - Correl.Be7[0]->Ekin - ek - Q9C;
       Histo->ExTarget_9C_2p7Be->Fill(Ex_target);

      */

    }
}
