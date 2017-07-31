#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include <fstream>
#include <sstream>

void Be9Eff()
{
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  TStyle * Sty = (TStyle*)gROOT->FindObject("MyStyle");
  if(!Sty)
    {
      Sty = new TStyle("MyStyle","MyStyle");
    }
  Sty->SetOptTitle(0);
  Sty->SetOptStat(0);
  Sty->SetPalette(1,0);
  Sty->SetCanvasColor(10);
  Sty->SetCanvasBorderMode(0);
  Sty->SetFrameLineWidth(3);
  Sty->SetFrameFillColor(10);
  Sty->SetPadColor(10);
  Sty->SetPadTickX(1);
  Sty->SetPadTickY(1);
  Sty->SetPadBottomMargin(.17);
  Sty->SetPadTopMargin(.03);
  Sty->SetPadLeftMargin(.17);
  Sty->SetPadRightMargin(.13);
  Sty->SetHistLineWidth(3);
  Sty->SetHistLineColor(kBlack);
  Sty->SetFuncWidth(3);
  Sty->SetFuncColor(kRed);
  Sty->SetLineWidth(3);
  Sty->SetLabelSize(0.06,"xyz");
  Sty->SetLabelOffset(0.02,"y");
  Sty->SetLabelOffset(0.02,"x");
  Sty->SetLabelColor(kBlack,"xyz");
  Sty->SetTitleSize(0.06,"xyz");
  Sty->SetTitleOffset(1.5,"y");
  Sty->SetTitleOffset(1.1,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.03,"xz");
  Sty->SetTickLength(.02,"y");
  Sty->SetNdivisions(10,"x");
  Sty->SetNdivisions(10,"yz");
  Sty->SetEndErrorSize(0);
  Sty->SetMarkerStyle(8);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();

  TFile * data = new TFile("~/unpacker/elas.root");
  TFile * sim = new TFile("~/sim/sim.root");
  

  /*
  TCanvas * mycan1 = new TCanvas("mycan1","mycan1",900,600);
  TCanvas * mycan2 = new TCanvas("mycan2","mycan2",1200,800);

  //mycan.SetCanvasSize(800,800);
  gROOT->cd();
  mycan1->Divide(2,2);
  mycan2->Divide(3,3);


  mycan1->cd(1);
  TH2F * eff = (TH2F*)sim->Get("cosPsi_Chi_R")->Clone("6");
  eff->Divide((TH2F*)sim->Get("cosPsi_Chi_P"));
  eff->Draw("colz");
  eff->GetXaxis()->SetTitle("cos(#psi)");
  eff->GetYaxis()->SetTitle("#chi [deg]");
  eff->GetYaxis()->CenterTitle();
  eff->GetXaxis()->CenterTitle();

  
  TH2F * loEff = (TH2F*)sim->Get("cosPsi_Chi_smallAngle_R")->Clone("7");
  loEff->Divide((TH2F*)sim->Get("cosPsi_Chi_smallAngle_P"));

  TH2F * midEff = (TH2F*)sim->Get("cosPsi_Chi_midAngle_R")->Clone("8");
  midEff->Divide((TH2F*)sim->Get("cosPsi_Chi_midAngle_P"));

  TH2F * hiEff = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_R")->Clone("9");
  hiEff->Divide((TH2F*)sim->Get("cosPsi_Chi_hiAngle_P"));
  
  mycan1->cd(2);
  TH2F * plot9Be = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be")->Clone("10");
  plot9Be->Draw("colz");
  plot9Be->GetXaxis()->SetTitle("cos(#psi)");
  plot9Be->GetYaxis()->SetTitle("#chi [deg]");
  plot9Be->GetYaxis()->CenterTitle();
  plot9Be->GetXaxis()->CenterTitle();


  mycan1->cd(3);
  TH2F *  plot9Be_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be")->Clone("11");
  plot9Be_eff->Divide(eff);
  plot9Be_eff->Draw("colz");
  plot9Be_eff->GetXaxis()->SetTitle("cos(#psi)");
  plot9Be_eff->GetYaxis()->SetTitle("#chi [deg]");
  plot9Be_eff->GetYaxis()->CenterTitle();
  plot9Be_eff->GetXaxis()->CenterTitle();


  mycan1->cd(4);
  TH1D * cosPsi_9Be = plot9Be_eff->ProjectionX();
  //cosPsi_9Be->SetMarkerStyle(3);
  cosPsi_9Be->Draw("PC");
  cosPsi_9Be->GetYaxis()->SetRangeUser(0,23000);

  TH2F * small_9Be = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be_small_angle")->Clone("12");
  TH2F * mid_9Be = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be_mid_angle")->Clone("13");
  TH2F * hi_9Be = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be_large_angle")->Clone("14");

  mycan2->cd(4);
  TH1D * cosPsi_lo2 = small_9Be->ProjectionX();
 
  cosPsi_lo2->Draw("PC");
  TH2F * thing3 = (TH2F*)sim->Get("cosPsi_Chi_smallAngle_R")->Clone("15");
  TH1D * cosPsi_loEff = thing3->ProjectionX();
  TH2F * thing4 = (TH2F*)sim->Get("cosPsi_Chi_smallAngle_P")->Clone("16");
  cosPsi_loEff->Divide(thing4->ProjectionX());
  mycan2->cd(1);
  cosPsi_loEff->Draw("PC");

 
  mycan2->cd(5);
  TH1D * cosPsi_mid2 = mid_9Be->ProjectionX();

  cosPsi_mid2->Draw("PC");
  TH2F * thing5 = (TH2F*)sim->Get("cosPsi_Chi_midAngle_R")->Clone("17");
  TH1D * cosPsi_midEff = thing5->ProjectionX();
  TH2F * thing6 = (TH2F*)sim->Get("cosPsi_Chi_midAngle_P")->Clone("18");
  cosPsi_midEff->Divide(thing6->ProjectionX());
  mycan2->cd(2);
  cosPsi_midEff->Draw("PC");


  mycan2->cd(6);
  TH1D * cosPsi_hi2 = hi_9Be->ProjectionX();
  cosPsi_hi2->Draw("PC");
  TH2F * thing1 = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_R")->Clone("4");
  TH1D * cosPsi_hiEff = thing1->ProjectionX();
  TH2F * thing2 = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_P")->Clone("5");
  cosPsi_hiEff->Divide(thing2->ProjectionX());
  mycan2->cd(3);
  cosPsi_hiEff->Draw("PC");

 
  mycan2->cd(4);
  cosPsi_lo->Draw("PC");

  
  mycan2->cd(5);
  cosPsi_mid->Draw("PC");
  

  mycan2->cd(6);
  cosPsi_hi->Draw("PC");
  
  
  mycan2->cd(7);
  TH1D* cosPsi_lo = (TH1D*)cosPsi_lo2->Clone();
  cosPsi_lo->Divide(cosPsi_loEff);
  cosPsi_lo->Draw("PC");
  

  mycan2->cd(8);
  TH1D * cosPsi_mid = (TH1D*)cosPsi_mid2->Clone();
  cosPsi_mid->Divide(cosPsi_midEff);
  cosPsi_mid->Draw("PC");
  

  mycan2->cd(9);
  TH1D * cosPsi_hi = (TH1D*)cosPsi_hi2->Clone();
  cosPsi_hi->Divide(cosPsi_hiEff);
  cosPsi_hi->Draw("PC");
  

  TH1D * cosPsi_hi = hi_9Be->ProjectionX();
  TH2F * thing1 = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_R")->Clone("4");
  TH1D * cosPsi_hiEff = thing1->ProjectionX();
  TH2F * thing2 = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_P")->Clone("5");
  cosPsi_hiEff->Divide(thing2->ProjectionX());
  cosPsi_hiEff->Draw("PC");

  cosPsi_hi->Divide(cosPsi_hiEff);
  cosPsi_hi->Draw("PC");
  */


  
  TCanvas * c5 = new TCanvas("heyo","heyo",800,600);

  int k=181;
  ifstream file1("/Users/dhoff/Programs/AngCorr/elas_xsection_9Be.plot"); //apparently you need to write out the whole thing for ROOT
  ifstream file2("/Users/dhoff/Programs/AngCorr/inel1_xsection_9Be.plot");
  ifstream file3("/Users/dhoff/Programs/AngCorr/inel_xsection_9Be.plot");

  if(!file1.is_open())cout << "file1 not open" << endl;
  if(!file2.is_open())cout << "file2 not open" << endl;
  if(!file3.is_open())cout << "file3 not open" << endl;

  float * angle = new float[k];
  float  * elas = new float[k];
  float * inel = new float[k];
  float * inel1 = new float[k];
  float * elasTOT=0;

  float SCALER = 384205.;
  SCALER = 7261; //run 61 with Be
  SCALER = 1.; // don't have FC data for first mult=1 runs
  SCALER = 0.00009736; // taking into account target thickness and beam current should give results in millibarns 
  //*3 depending on definition of what's written down... also could vary beam current slightly to fit
  //WTF their right on top of each other, am I drunk or is that physics?  9/21/2016
  //also remember you made a scaler that multiplies
  //find this calculation on your desk DAN
  for(int i=0;i<k;i++)
    {
      file1 >> angle[i] >> elas[i];
      //file2 >> angle[i] >> inel[i];
      file3 >> angle[i] >> inel1[i];
      //elas[i] = elas[i]+inel1[k]; //only true when using the rotor model since I can't get the breakup model to work with two states...
      //elas[i] = elas[i];
      //inel[i] = inel1[i];
      //cout << elas[i] << endl;
      cout << angle[i] << " " << inel1[i] << endl;
    }


  TGraph * E = new TGraph(k,angle,elas);
  TGraph * I = new TGraph(k,angle,inel1);

  TH1F * eff1D = (TH1F*)sim->Get("theta_reactionCM_R")->Clone("26");
  TH1F * really = (TH1F*)sim->Get("theta_reactionCM_P")->Clone("me");
  eff1D->Divide(really);

  //eff1D->Draw();

  TH1F * Be1D = (TH1F*)data->Get("/corr/Li7/Li7_theta_reactCoM_9Be")->Clone("27");
  Be1D->Divide(eff1D);

  float binW;
  binW = Be1D->GetXaxis()->GetBinWidth(23)*3.14159/180.;

  for(int i=1;i<=125;i++)
    {
      float solidAng;
      float thetaC;
      thetaC = Be1D->GetBinCenter(i)*3.14159/180.;
      solidAng = 2*3.14159*(cos(thetaC-binW/2.) - cos(thetaC+binW/2.));
      float content = Be1D->GetBinContent(i);
      content = content/solidAng;//sin(Be1D->GetBinCenter(i)*3.14159/180.); //-->I've had the sin(theta) in there all along --> this is only an approximation of the solid angle (works because of binning)
      Be1D->SetBinContent(i,content*SCALER);
      if(Be1D->GetBinCenter(i)>24)Be1D->SetBinContent(i,0.);
    }
  

  Be1D->SetMarkerStyle(20);
  Be1D->Draw("P");
  I->SetMarkerStyle(3);
  I->Draw("same");
  Be1D->GetXaxis()->SetRangeUser(0,25);
  Be1D->GetXaxis()->SetTitle("#theta_{CM}");
  //Be1D->GetYaxis()->SetTitle("#frac{d#sigma(mb)}{d#Omega}");
  TLatex title;
  title.DrawLatex(-5,20,"#frac{d#sigma(mb)}{d#Omega}");
  Be1D->SetTitle("^{7}Li(7.2-) #sigma_{inel}");
  c5->SetLogy();

  TFile * sim2 = new TFile("~/elasSim/sim9Be/sim.root");

  TCanvas * c6 = new TCanvas("r","r",800,600);
  TH1F * effEl = (TH1F*)sim2->Get("theta_reactionCM_R")->Clone("65");
  TH1F * really2 = (TH1F*)sim2->Get("theta_reactionCM_P")->Clone("56");

  effEl->Divide(really2);

  TH1F * BeElas = (TH1F*)data->Get("/corr/Li7/7Li_elas_9Be")->Clone("45");
  BeElas->Divide(effEl);

  binW = BeElas->GetXaxis()->GetBinWidth(23)*3.14159/180.;
 
  for(int i=1;i<=125;i++)
    {
      float solidAng;
      float thetaC;
      thetaC = BeElas->GetBinCenter(i)*3.14159/180.;
      solidAng = 2*3.14159*(cos(thetaC-binW/2.) - cos(thetaC+binW/2.));

      float content = BeElas->GetBinContent(i);
      //cout << content << endl;
      content = content/solidAng;//sin(BeElas->GetBinCenter(i)*3.14159/180.);
      BeElas->SetBinContent(i,content*SCALER);
      if(BeElas->GetBinCenter(i)>7.5 && BeElas->GetBinCenter(i)<11)
	BeElas->SetBinContent(i,0.);
      if(BeElas->GetBinCenter(i) < 3.5)
	 BeElas->SetBinContent(i,0.);
    }

  BeElas->SetMarkerStyle(20);
  BeElas->Draw("P");
  BeElas->GetYaxis()->SetRangeUser(1.,100000);
  I->SetLineColor(2);
  E->SetMarkerStyle(3);
  E->Draw("same");
  I->Draw("same");
  Be1D->SetMarkerColor(2);
  Be1D->Draw("sameP");
  BeElas->GetXaxis()->SetRangeUser(0,25);
  BeElas->GetXaxis()->SetTitle("#theta_{CM}");
  title.DrawLatex(-5,200,"#frac{d#sigma(mb)}{d#Omega}");
  BeElas->SetTitle("^{7}Li(7.2-) #sigma_{el}");
  c6->SetLogy();



  TCanvas * c7 = new TCanvas("b","b",800,600);
  TH1F * relative = (TH1F*)data->Get("/corr/Li7/Li7_theta_reactCoM_9Be")->Clone("73");
  relative->Divide(eff1D);
  relative->Divide(BeElas);
  relative->SetMarkerStyle(20);
  relative->Draw("P");
  c7->SetLogy();
  relative->GetXaxis()->SetRangeUser(0,25);
  
  
  
  return;
}
