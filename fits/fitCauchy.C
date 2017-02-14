#include "TF2.h"
#include "TH2.h"
#include "TMath.h"
#include "TSystem.h"
#include "matrix.h"
#include <iostream>
#include <fstream>

using namespace std;

Double_t Cauchy3(Double_t * x, Double_t * par)
{
  Double_t result;

  result = par[6]*TMath::BreitWigner(x[0],par[0],par[1]);
  result += par[7]*TMath::BreitWigner(x[0],par[2],par[3]);
  result += par[8]*TMath::BreitWigner(x[0],par[4],par[5]);

  return result;
}


Double_t Gaus3(Double_t * x, Double_t * par)
{
  Double_t result;

  result = par[6]*TMath::Gaus(x[0],par[0],par[1]);
  result += par[7]*TMath::Gaus(x[0],par[2],par[3]);
  result += par[8]*TMath::Gaus(x[0],par[4],par[5]);

  return result;
}


void fitCauchy()
{

  TCanvas * c1 = new TCanvas("mycan","mycan",800,600);
  TFile * data = new TFile("~/unpacker/sort.root");
  fstream file1;
  file1.open("gaus3.par");


  TH1F * dist = (TH1F*)data->Get("/corr/Li7/Li7_theta_reactCoM_12C")->Clone("1");

  Double_t fparams[9] = {6.,1.,12.,1.,18.,1.,20000,15000,10000};
  TF1 * f = new TF1("f",Cauchy3,0,180,9);
  TF1 * f2 = new TF1("f2",Gaus3,0,180,9);
  f2->SetParameters(fparams);
  f->SetParameters(fparams);
  dist->Fit("f2","M0");
  dist->Draw();
  f2->Draw("same");

  if(file1.is_open()) cout <<"file1 is open" << endl;
  else cout << "failed to load file1" << endl;

   for(int i=0;i<9;i++)
     {
       file1 << f2->GetParameter(i) << endl;
     }

  TCanvas * c2 = new TCanvas("mycan2","mycan2",800,600);
  TH1F * check = new TH1F("check","",125,0,40);

  for(int i =0;i<300000;i++)
    {
      float  r = f2->GetRandom();
      check->Fill(r);
    }

  check->Draw();
    
  Double_t  par[9];

  //  for(int i=0;i<9;i++)
  //{
  // file1 >> par[i] >> endl;
  //  cout << "par[" << i << "] = " << par[i] << endl;
  //}
  //cout << "what" << endl;
  //file1.close();

  return;
}
