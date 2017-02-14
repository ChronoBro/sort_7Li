#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include <fstream>
#include <sstream>

void eff()
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


  TCanvas * mycan1 = new TCanvas("mycan1","mycan1",900,600);
  TCanvas * mycan2 = new TCanvas("mycan2","mycan2",1200,800);

  //mycan.SetCanvasSize(800,800);
  TFile * data = new TFile("~/unpacker/sort.root");
  TFile * sim = new TFile("~/sim/sim.root");
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

  mycan1->cd(3);
  TH2F *  plot9Be_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be")->Clone("11");
  plot9Be_eff->Divide(eff);
  plot9Be_eff->Draw("colz");

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

  /*
  mycan2->cd(4);
  cosPsi_lo->Draw("PC");

  
  mycan2->cd(5);
  cosPsi_mid->Draw("PC");
  

  mycan2->cd(6);
  cosPsi_hi->Draw("PC");
  */
  
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
  
  /*
  TH1D * cosPsi_hi = hi_9Be->ProjectionX();
  TH2F * thing1 = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_R")->Clone("4");
  TH1D * cosPsi_hiEff = thing1->ProjectionX();
  TH2F * thing2 = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_P")->Clone("5");
  cosPsi_hiEff->Divide(thing2->ProjectionX());
  cosPsi_hiEff->Draw("PC");

  cosPsi_hi->Divide(cosPsi_hiEff);
  cosPsi_hi->Draw("PC");
  */





  return;
}
