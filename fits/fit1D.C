#include "TF2.h"
#include "TH2.h"
#include "TMath.h"
#include "TSystem.h"
#include "matrix.h"

float fact(int n)
{
  if(n==0 || n==1) return 1;
  float result=1;
  for(int i=2;i<=n;i++)
    {
      result = i*result; 
    }
  return result;
}

Double_t ass_legend(int l, int m, Double_t x)
{
  // I will worry about negative values of m later
  // and also anything above l=3

  if(x>1 || x<-1){ cout << "Range Error in ass_legend" << endl; return 0;}

  if(l==0)
    {
      return 1;
    }
  else if(l==1)
    {
      if(m==0) return x;
      if(m==1) return -1*pow( 1- pow(x,2.) ,0.5);
    }
  else if(l==2)
    {
      if(m==0) return 0.5*(3*pow(x,2.)-1);
      if(m==1) return -3*x*pow(1 - pow(x,2.) ,0.5);
      if(m==2) return 3*(1-pow(x,2.));
    }
  else if(l==3)
    {
      if(m==0) return 0.5*x*(5*pow(x,2.)-3);
      if(m==1) return 1.5*(1-5*pow(x,2.))*pow(1- pow(x,2.) , 0.5);
      if(m==2) return 15*x*(1- pow(x,2.));
      if(m==3) {return -15*pow( 1 - pow(x,2.) ,1.5);}
    }
  else {cout << "ass_legend problem" << endl; return 0.;}
  return 0;
}

Double_t fun2(Double_t * x,Double_t * par)
{

  //matching with Bob's analysis may be a problem of sign conventions (ROOT conventions are not the same as mathworld (wolfram)!)

  //C_0,0
  Double_t result = par[0]*pow(ROOT::Math::assoc_legendre(3,0,x[0]),2);

  //C_1,1 & C_1,-1
  result = result + 2*2/fact(4)*pow(ROOT::Math::assoc_legendre(3,1,x[0]),2)*(par[1]-par[2]*cos(2*x[1]*3.1415927/180.));

  //C_2,2 & C_2,-2
  result = result + 2*1/fact(5)*pow(ROOT::Math::assoc_legendre(3,2,x[0]),2)*(par[3]+par[4]*cos(4*x[1]*3.1415927/180.));

  //C_3,3 & C_3,-3
  result = result + 2*1/fact(6)*pow(ROOT::Math::assoc_legendre(3,3,x[0]),2)*(par[5]-par[6]*cos(6*x[1]*3.1415927/180.));

  //C_3,2 -1 orig
  result = result + 4*par[7]*sqrt(fact(3-3)/fact(3+3))*ROOT::Math::assoc_legendre(3,2,x[0])*sqrt(fact(3-2)/fact(3+2))*ROOT::Math::assoc_legendre(3,3,x[0])*cos(x[1]*3.1415927/180.);

  //C_3,1
  result = result + 4*par[8]*sqrt(fact(3-3)/fact(3+3))*ROOT::Math::assoc_legendre(3,3,x[0])*sqrt(fact(3-1)/fact(3+1))*ROOT::Math::assoc_legendre(3,1,x[0])*cos(2*x[1]*3.1415927/180.);

  //C_3,0 -1 orig
  result = result + 4*par[9]*sqrt(fact(3-3)/fact(3+3))*ROOT::Math::assoc_legendre(3,3,x[0])*ROOT::Math::assoc_legendre(3,0,x[0])*cos(3*x[1]*3.1415927/180.);

  //C_3,-1
  result = result - 4*par[10]*sqrt(fact(3-3)/fact(3+3))*ROOT::Math::assoc_legendre(3,3,x[0])*sqrt(fact(3-1)/fact(3+1))*ROOT::Math::assoc_legendre(3,1,x[0])*cos(4*x[1]*3.1415927/180.);

  //C_3,-2 -1 orig
  result = result+4*par[11]*sqrt(fact(3-2)/fact(3+2))*ROOT::Math::assoc_legendre(3,3,x[0])*sqrt(fact(3-3)/fact(3+3))*ROOT::Math::assoc_legendre(3,2,x[0])*cos(5*x[1]*3.1415927/180.);

  //C_2,1 -1 orig
  result = result+4*par[12]*sqrt(fact(3-2)/fact(3+2))*ROOT::Math::assoc_legendre(3,2,x[0])*sqrt(fact(3-1)/fact(3+1))*ROOT::Math::assoc_legendre(3,1,x[0])*cos(x[1]*3.1415927/180.);

  //C_2,0
  result = result+4*par[13]*sqrt(fact(3-2)/fact(3+2))*ROOT::Math::assoc_legendre(3,2,x[0])*ROOT::Math::assoc_legendre(3,0,x[0])*cos(2*x[1]*3.1415927/180.);

  //C_2,-1 +1 orig
  result = result-4*par[14]*sqrt(fact(3-2)/fact(3+2))*ROOT::Math::assoc_legendre(3,2,x[0])*sqrt(fact(3-1)/fact(3+1))*ROOT::Math::assoc_legendre(3,1,x[0])*cos(3*x[1]*3.1415927/180.);

  //C_1,0 -1 orig
  result = result+4*par[15]*sqrt(fact(3-1)/fact(3+1))*ROOT::Math::assoc_legendre(3,1,x[0])*ROOT::Math::assoc_legendre(3,0,x[0])*cos(x[1]*3.1415927/180.);

  result = result*par[16]*7;

  return result;

}

Double_t fun3(Double_t * x,Double_t * par)
{

  //matching with Bob's analysis may be a problem of sign conventions (ROOT conventions are not the same as mathworld (wolfram)!)

  //C_0,0
  Double_t result = par[0]*pow(ass_legend(3,0,x[0]),2);

  //C_1,1 & C_1,-1
  result = result + 2*2/fact(4)*pow(ass_legend(3,1,x[0]),2)*(par[1]-par[2]*cos(2*x[1]*3.1415927/180.));

  //C_2,2 & C_2,-2
  result = result + 2*1/fact(5)*pow(ass_legend(3,2,x[0]),2)*(par[3]+par[4]*cos(4*x[1]*3.1415927/180.));

  //C_3,3 & C_3,-3
  result = result + 2*1/fact(6)*pow(ass_legend(3,3,x[0]),2)*(par[5]-par[6]*cos(6*x[1]*3.1415927/180.));

  //C_3,2 -1 orig
  result = result + 4*par[7]*sqrt(fact(3-3)/fact(3+3))*ass_legend(3,2,x[0])*sqrt(fact(3-2)/fact(3+2))*ass_legend(3,3,x[0])*cos(x[1]*3.1415927/180.);

  //C_3,1
  result = result + 4*par[8]*sqrt(fact(3-3)/fact(3+3))*ass_legend(3,3,x[0])*sqrt(fact(3-1)/fact(3+1))*ass_legend(3,1,x[0])*cos(2*x[1]*3.1415927/180.);

  //C_3,0 -1 orig
  result = result + 4*par[9]*sqrt(fact(3-3)/fact(3+3))*ass_legend(3,3,x[0])*ass_legend(3,0,x[0])*cos(3*x[1]*3.1415927/180.);

  //C_3,-1
  result = result - 4*par[10]*sqrt(fact(3-3)/fact(3+3))*ass_legend(3,3,x[0])*sqrt(fact(3-1)/fact(3+1))*ass_legend(3,1,x[0])*cos(4*x[1]*3.1415927/180.);

  //C_3,-2 -1 orig
  result = result+4*par[11]*sqrt(fact(3-2)/fact(3+2))*ass_legend(3,3,x[0])*sqrt(fact(3-3)/fact(3+3))*ass_legend(3,2,x[0])*cos(5*x[1]*3.1415927/180.);

  //C_2,1 -1 orig
  result = result+4*par[12]*sqrt(fact(3-2)/fact(3+2))*ass_legend(3,2,x[0])*sqrt(fact(3-1)/fact(3+1))*ass_legend(3,1,x[0])*cos(x[1]*3.1415927/180.);

  //C_2,0
  result = result+4*par[13]*sqrt(fact(3-2)/fact(3+2))*ass_legend(3,2,x[0])*ass_legend(3,0,x[0])*cos(2*x[1]*3.1415927/180.);

  //C_2,-1 +1 orig
  result = result-4*par[14]*sqrt(fact(3-2)/fact(3+2))*ass_legend(3,2,x[0])*sqrt(fact(3-1)/fact(3+1))*ass_legend(3,1,x[0])*cos(3*x[1]*3.1415927/180.);

  //C_1,0 -1 orig
  result = result+4*par[15]*sqrt(fact(3-1)/fact(3+1))*ass_legend(3,1,x[0])*ass_legend(3,0,x[0])*cos(x[1]*3.1415927/180.);

  result = result*par[16]*7;

  return result;

}


//should at some point try creating a histogram and setting the bin content to the function, it might make for a smoother plot


Double_t fun(Double_t * x, Double_t * par)
{

  Double_t result = par[0]*pow(ass_legend(3,0,x[0]),2);
  
  result = result + 2*2/fact(4)*pow(ass_legend(3,1,x[0]),2)*par[1];

  result = result + 2*1/fact(5)*pow(ass_legend(3,2,x[0]),2)*par[2];

  result = result + 2*1/fact(6)*pow(ass_legend(3,3,x[0]),2)*par[3];

  result = 7./2.*result*par[4];

  //cout << "result = " << result << endl;
  return result;
  

}

Double_t hey(Double_t * x, Double_t * par)
{
  Double_t result = ROOT::Math::assoc_legendre(3,3,x[0]);

  return result;

}

Double_t hey2(Double_t * x, Double_t * par)
{
  Double_t result = -15*pow(1-pow(x[0],2.) , 1.5);

  return result;

}



void fit1D()
{
  //matrix C(4,4);
  TCanvas * c1 = new TCanvas("mycan","mycan",800,600);
  TFile * data = new TFile("~/unpacker/sort.root");
  TFile * sim = new TFile("~/sim12C/sim.root");
  //gROOT->cd();
  gStyle->SetOptStat(0);
  //gStyle->SetPalette(55); //55 for rainbow, doesn't look too bad

  // TH2F * eff = (TH2F*)sim->Get("cosPsi_Chi_midAngle_R")->Clone("1");
  // TH2F * effD = (TH2F*)sim->Get("cosPsi_Chi_midAngle_P")->Clone("3");

  TH1F * eff1D = (TH1F*)sim->Get("cosPsi_midAngle_R")->Clone("eff1D");
  TH1F * eff1D2 = (TH1F*)sim->Get("cosPsi_midAngle_P")->Clone("eff1D2");

  
  if(!eff1D->Divide(eff1D2))
    {
      cout << "Efficiency not calculated correctly" << endl;
      return;
    }

  char angName[256];
  sprintf(angName,"%s","/corr/Li7/cosPsi_Chi_12C_mid_angle");
  TH2F * AngDist = (TH2F*)data->Get(angName)->Clone("ang2D");

  
  //TH2F * AngDist = (TH2F*)data->Get(angName)->Clone("");

  TH1D * projectionUse = AngDist->ProjectionX()->Clone("ang1D");
  //projectionUse->Sumw2();

  double * binErrors = new double[projectionUse->GetNbinsX()];

  for(int j=0;j<projectionUse->GetNbinsX();j++)
    {
      binErrors[j] = sqrt(projectionUse->GetBinContent(j))/eff1D->GetBinContent(j);
    }
 
  
  projectionUse->Divide(eff1D);

   for(int j=0;j<projectionUse->GetNbinsX();j++)
    {
      //binErrors[i] = sqrt(projectionUse->GetBinContent(i))/eff1D->GetBinContent(i);
      projectionUse->SetBinError(j,binErrors[j]);
    }
 

   projectionUse->Sumw2();
  
  //TCanvas * c1 = new TCanvas("1D_angDist","",800,600);

  Double_t fparam2[5] = {0.028,0.051,0.022,0.512,10.};
  TF1 * f = new TF1("f",fun,-1,1,5);
  f->SetParameters(fparam2);
  projectionUse->Fit("f","M");
  f->SetLineColor(5);
  f->Draw("C");
  f->GetXaxis()->SetTitle("cos(#psi)");
  f->GetXaxis()->CenterTitle();
  projectionUse->SetMarkerStyle(8);
  projectionUse->GetYaxis()->SetRangeUser(0,1600);
  
  projectionUse->Draw("samePE0");
  
  

  TFile f1("fit1D.root","RECREATE");
  projectionUse->Write();
  eff1D->Write();
  AngDist->Write();
  
  float h=0.01;
  float * y1 = new float[200];
  float * y2 = new float[200];
  float * y3 = new float[200];
  float * y4 = new float[200];
  float * x1 = new float[200];

  

  for(int j= 0;j<200;j++)
    {
      float x2 = -1+(j+1)*h;
      //cout << "x = " << x2 << " ";
      x1[j] = x2;
      y1[j] = 7./2.*f->GetParameter(4)*pow(ass_legend(3,0,x2),2.)*f->GetParameter(0);
      y2[j] = 7./2.*f->GetParameter(4)*2*2/fact(4)*pow(ass_legend(3,1,x2),2)*f->GetParameter(1);
      y3[j] = 7./2.*f->GetParameter(4)*2*1/fact(5)*pow(ass_legend(3,2,x2),2)*f->GetParameter(2);
      y4[j] = 7./2.*f->GetParameter(4)*2*1/fact(6)*pow(ass_legend(3,3,x2),2)*f->GetParameter(3);
      //cout << "y4 = " << ass_legend(3,3,x2) << endl;
    }
  
  //cout << "x[200] = " << x1[199] << endl;
  


  TGraph * gr1 = new TGraph(200,x1,y1);
  gr1->SetLineWidth(2);
  TGraph * gr2 = new TGraph(200,x1,y2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(6);
  TGraph * gr3 = new TGraph(200,x1,y3);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(3);
  TGraph * gr4 = new TGraph(200,x1,y4);
  gr4->SetLineWidth(2);
  gr4->SetLineColor(4);

  gr1->Draw("sameC");
  //gr1->GetYaxis()->SetRangeUser(-15,15);
  gr2->Draw("sameC");
  gr3->Draw("sameC");
  gr4->Draw("sameC");

  float rhoL[4];
  float rhoS[4];

  float rhoSEr[4];
  float rhoLEr[4];
  
  rhoL[3] = f->GetParameter(3); //index matches value of L, but screws up my matrix unless I go backwards
  rhoL[2] = f->GetParameter(2);
  rhoL[1] = f->GetParameter(1);
  rhoL[0] = f->GetParameter(0);
  
  rhoLEr[3] = f->GetParError(3);
  rhoLEr[2] = f->GetParError(2);
  rhoLEr[1] = f->GetParError(1);
  rhoLEr[0] = f->GetParError(0);
 

  
  // normalize values
  float TOT= rhoL[0]+2*rhoL[1]+2*rhoL[2]+2*rhoL[3];

//   for(int i=0;i<4;i++)
//     {
//       if(i==0)TOT = rhoL[0];
//       TOT = TOT+ 2*rhoL[i];
//     }
    

  cout << endl;
  for(int i=0;i<4;i++)
    {
      rhoL[i] = rhoL[i]/TOT;
      rhoLEr[i] = rhoLEr[i]/TOT;
      cout << "rho 3_" << i << " = " << rhoL[i] << endl;
    }

  cout << endl <<  "density matrix check, TOT = " << rhoL[0]+2*rhoL[1]+2*rhoL[2]+2*rhoL[3] << endl;

  // could solve by inverting a matrix of Clebsch Gordon Coeffecients or by back substition of matrix (since the bottom half is empty)
  // If I could get my matrix class working and put an inversion function into it then I would just use the inverse method (one day...)
  // I barely remember how I solved this, should check equation from Bob's paper...

  // solving spin state density matrix values (diagnoal values) by back substitution below


  rhoS[0] = 7./8.*rhoL[0];
  rhoS[1] = 7./5.*(rhoL[1]-3./8.*rhoL[0]);
  rhoS[2] = 7./6.*(rhoL[2]-2./7.*rhoS[1]);
  rhoS[3] = rhoL[3] - rhoS[2]/7.;

  rhoSEr[0] = 7./8.*rhoLEr[0];
  rhoSEr[1] = 7./5.*(rhoLEr[1]-3./8.*rhoLEr[0]);
  rhoSEr[2] = 7./6.*(rhoLEr[2]-2./7.*rhoSEr[1]);
  rhoSEr[3] = rhoLEr[3] - rhoSEr[2]/7.;


  
  cout << endl;
  cout << "rho S_0.5 = " << rhoS[0] << endl;
  cout << "rho S_1.5 = " << rhoS[1] << endl;
  cout << "rho S_2.5 = " << rhoS[2] << endl;
  cout << "rho S_3.5 = " << rhoS[3] << endl;

  float x_1[7] = {-3,-2,-1,0,1,2,3};
  float y_1[7] = {rhoL[3],rhoL[2],rhoL[1],rhoL[0],rhoL[1],rhoL[2],rhoL[3]};

  float x_2[8] = {-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5};
  float y_2[8] = {rhoS[3],rhoS[2],rhoS[1],rhoS[0],rhoS[0],rhoS[1],rhoS[2],rhoS[3]};
  float y_2Error[8] = {rhoSEr[3],rhoSEr[2],rhoSEr[1],rhoSEr[0],rhoSEr[0],rhoSEr[1],rhoSEr[2],rhoSEr[3]};

  TCanvas * c4 = new TCanvas("mycan2","mycan2",800,600);

  TGraph * bar1 = new TGraph(7,x_1,y_1);
  bar1->Draw("AB");
  bar1->GetXaxis()->SetTitle("m");
  bar1->GetYaxis()->SetTitle(" #rho^{l}_{m,m} ");
  bar1->SetTitle("");

  TCanvas * c5 = new TCanvas("mycan3","mycan3",800,600);

  TGraph * bar2 = new TGraph(8,x_2,y_2);
  bar2->Draw("AB");
  bar2->GetXaxis()->SetTitle("m*");
  bar2->GetYaxis()->SetTitle(" #rho^{l}_{m*,m*} " );
  bar2->SetTitle("");

  double alignment=0.;
  double alError=0.;
  
  const int Nj = 8;
  double xs[Nj];
  //double ys[Nj];
  double jstar = 7./2.;
  for (int i=0;i<Nj;i++) 
    {
      xs[i] = -jstar + i;
      //double sstar = 7./2.;
      //double mstar2 = i-sstar;
      double mstar2 = pow(xs[i],2.);
      double factor = 3*mstar2-jstar*(jstar+1);
      factor = factor/(jstar*(2*jstar - 1));
      factor = factor*y_2[i];
      //cout << "factor = " << factor << endl;
      //cout << "y_2[i] = " << y_2[i] << endl;
      alError + = factor/y_2[i]*y_2Error[i];
      alignment += factor;
    }

  cout << endl << "alignment = " << alignment << endl;
  cout << "error = " << alError << endl;

  
}
