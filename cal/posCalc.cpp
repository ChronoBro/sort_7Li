#include <iostream>
#include <fstream>
#include "TGraph.h"
using namespace std;



void posCalc ()
{

  TCanvas * mycan = new TCanvas("mycan");
  mycan->Divide(4,4,.001,.001);
  TCanvas * mycan2 = new TCanvas("mycan2");
  mycan2->Divide(4,4,0.001,0.001);
  int no=0;
  ostringstream outstring;
  string name;
  TGraph * gr[32];
  TGraph * gr1;
  TGraph * gr2;

  ofstream ofile1("cal/posCorrect_slope_d.cal");
  ofstream ofile2("cal/posCorrect_intercept_d.cal");
  ofstream ofile3("cal/posCorrect_slope_a.cal");
  ofstream ofile4("cal/posCorrect_intercept_a.cal");

  float quadD[32];
  float quadA[32];
  float slopeD[32];
  float interceptD[32];
  float slopeA[32];
  float interceptA[32];
  float intSlopeD[32];
  float intIntD[32];
  float intSlopeA[32];
  float intIntA[32];

  float distRus=148;
  float distBlocksRus[32];
  float thetaRus[32];


  for(int blocks=0;blocks<32;blocks++)
    {
      distBlocksRus[blocks] =15.4296875+0.859375*blocks;
      thetaRus[blocks] = atan2(distBlocksRus[blocks],distRus)*180./3.1415927;
      //cout << "theta Rus Block" << blocks+1 << " = " << thetaRus[blocks] << endl;
    }

  for(no=0;no<32;no++)
    {
      outstring.str("");
      outstring << "/home/lithium7/unpacker/cal/blockCalCsid"<<no;
      name = outstring.str();
      name = name + ".cal";
      ifstream ifile1(name.c_str());
      if(!ifile1.is_open()){cout << "ERROR opening " << name << endl;}
      
      
      int l;
      int m;
      int n;
      int p=8;
      float help1[32];
      float help2[32];
      float help3[32];
      TF1 * fit1;
      TF1 * fit2;



      float theta[8]={6.48817,7.80675,9.11787,10.419,11.7094,12.9882,14.2532,15.5046};
      //float theta[7]={2.05126,2.543,3.0343,3.5252,4.0156,4.5054,4.9945};

 
      

      for (l=0;l<p;l++)
	{
	  
	  ifile1 >>  help1[l] >> help2[l];
	  
	}
      
      mycan->cd(no+1);
      gr[no] = new TGraph(p,theta,help1);
      gr[no]->Fit("pol2");
      fit1 = gr[no]->GetFunction("pol2");
      //fit1->SetParameter(2,0.000004);
      //fit1->SetParameter(1,0.00034);
      //fit1->SetParameter(0,0.034);
      quadD[no] = fit1->GetParameter(2);
      slopeD[no] = fit1->GetParameter(1);
      interceptD[no] = fit1->GetParameter(0);

      cout << "here1" << endl;
      gr[no]->Draw();
      mycan->Update();   

      //TMarker * mark;
      //mark=(TMarker*)mycan.WaitPrimitive("TMarker"); 
      //delete mark;
      //delete gr1; 
      
      mycan->cd(no);
      //TCanvas c2;
      gr2 = new TGraph(p,theta,help2);
      gr2->Fit("pol1");
      fit2 = gr2->GetFunction("pol1");
      intSlopeD[no] = fit2->GetParameter(1);
      intIntD[no] = fit2->GetParameter(0);
      
      //gr2->Draw();
      //      mycan.Update();
      //mark=(TMarker*)mycan.WaitPrimitive("TMarker"); 
      //delete mark;
   
      //delete gr2;


    }

  for(no=0;no<32;no++)
    {
      outstring.str("");
      outstring << "/home/lithium7/unpacker/cal/blockCalCsiA"<<no;
      name = outstring.str();
      name = name + ".cal";
      ifstream ifile1(name.c_str());
      if(!ifile1.is_open()){cout << "ERROR opening " << name << endl;}
      
      int l;
      int m;
      int n;
      int p=8;
      float help1[32];
      float help2[32];
      TF1 * fit1;
      TF1 * fit2;
      float theta[8]={6.48817,7.80675,9.11787,10.419,11.7094,12.9882,14.2532,15.5046};
      //float theta[7]={2.05126,2.543,3.0343,3.5252,4.0156,4.5054,4.9945};
      
      for (l=0;l<p;l++)
	{
	  
	  ifile1 >> help1[l] >> help2[l];
	  
	}
      
      mycan2->cd(no+1);
      gr1 = new TGraph(p,theta,help1);
      gr1->Fit("pol2");
      fit1 = gr1->GetFunction("pol2");
      //fit1->SetParameter(2,0.000004);
      //fit1->SetParameter(1,0.00034);
      //fit1->SetParameter(0,0.034);
      quadA[no] = fit1->GetParameter(2);
      slopeA[no] = fit1->GetParameter(1);
      interceptA[no] = fit1->GetParameter(0);
      
      gr1->Draw();
      //mycan.Update();
      //TMarker * mark;
      //mark=(TMarker*)mycan.WaitPrimitive("TMarker"); 
      //delete mark;      
      // delete gr1;
      // TCanvas c2;
      gr2 = new TGraph(p,thetaRus,help2);
      gr2->Fit("pol1");
      fit2 = gr2->GetFunction("pol1");
      intSlopeA[no] = fit2->GetParameter(1);
      intIntA[no] = fit2->GetParameter(0);
      
      //gr2->Draw();
      //mycan.Update();
      //mark=(TMarker*)mycan.WaitPrimitive("TMarker"); 
      //delete mark;

      //delete gr2;
    }


  
  for(int y=0;y<32;y++)
    {
      ofile1 << quadD[y] << "\t" << slopeD[y] << "\t" << interceptD[y] << endl;
      ofile2 << intSlopeD[y] << "\t" << intIntD[y] << endl;
      ofile3 << quadA[y] << "\t" << slopeA[y] << "\t" << interceptA[y] << endl;
      ofile4 << intSlopeA[y] << "\t" << intIntA[y] << endl;
      
    }
  

}
