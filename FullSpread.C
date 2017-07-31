void FullSpread()
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
  Sty->SetFrameLineWidth(2);
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
  Sty->SetLineWidth(2);
  Sty->SetLabelSize(0.055,"xyz");
  Sty->SetLabelFont(62);
  Sty->SetLabelOffset(0.02,"y");
  Sty->SetLabelOffset(0.02,"x");
  Sty->SetLabelColor(kBlack,"xyz");
  Sty->SetTitleSize(0.06,"xyz");
  Sty->SetTitleFont(62);
  Sty->SetTitleOffset(1.3,"y");
  Sty->SetTitleOffset(1.1,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.03,"xz");
  Sty->SetTickLength(.02,"y");
  Sty->SetNdivisions(08,"x");
  Sty->SetNdivisions(08,"yz");
  Sty->SetEndErrorSize(0);
  Sty->SetMarkerStyle(8);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();


  TCanvas * mycan1 = new TCanvas("mycan1","mycan1",1200,800);
  TCanvas * mycan2 = new TCanvas("mycan2","mycan2",1200,800);

  //mycan.SetCanvasSize(800,800);
  TFile * data = new TFile("~/unpacker/sortALLv2.root");
  TFile * sim = new TFile("~/sim/sim.root");
  TFile * sim2 = new TFile("~/sim12C/sim.root");
  TFile * sim3 = new TFile("~/sim27Al/sim.root");
  gROOT->cd();
  mycan1->Divide(2,2);
  mycan2->Divide(2,2);


  mycan1->cd(1);
  TH2F * eff = (TH2F*)sim->Get("cosPsi_Chi_R")->Clone("6");
  eff->Divide((TH2F*)sim->Get("cosPsi_Chi_P"));
  // eff->Draw("colz");
  eff->GetXaxis()->SetTitle("cos(#psi)");
  eff->GetYaxis()->SetTitle("#chi [deg]");
  eff->GetYaxis()->CenterTitle();
  eff->GetXaxis()->CenterTitle();


  TH2F * eff12C = (TH2F*)sim2->Get("cosPsi_Chi_R")->Clone("6");
  eff12C->Divide((TH2F*)sim2->Get("cosPsi_Chi_P"));
  // eff->Draw("colz");
  eff12C->GetXaxis()->SetTitle("cos(#psi)");
  eff12C->GetYaxis()->SetTitle("#chi [deg]");
  eff12C->GetYaxis()->CenterTitle();
  eff12C->GetXaxis()->CenterTitle();

  TH2F * eff27Al = (TH2F*)sim3->Get("cosPsi_Chi_R")->Clone("6");
  eff27Al->Divide((TH2F*)sim3->Get("cosPsi_Chi_P"));
  // eff->Draw("colz");
  eff27Al->GetXaxis()->SetTitle("cos(#psi)");
  eff27Al->GetYaxis()->SetTitle("#chi [deg]");
  eff27Al->GetYaxis()->CenterTitle();
  eff27Al->GetXaxis()->CenterTitle();


  TH1F * eff1D = (TH1F*)sim->Get("cosPsi_R")->Clone("eff1D");
  TH1F * eff1D2 = (TH1F*)sim->Get("cosPsi_P")->Clone("eff1D2");
  
  TH1F * eff1D_12C = (TH1F*)sim2->Get("cosPsi_R")->Clone("eff1D");
  TH1F * eff1D2_12C = (TH1F*)sim2->Get("cosPsi_P")->Clone("eff1D2");
  
  TH1F * eff1D_27Al = (TH1F*)sim3->Get("cosPsi_R")->Clone("eff1D");
  TH1F * eff1D2_27Al = (TH1F*)sim3->Get("cosPsi_P")->Clone("eff1D2");

   if(!eff1D->Divide(eff1D2) || !eff1D_12C->Divide(eff1D2_12C) || !eff1D_27Al->Divide(eff1D2_27Al))
    {
      cout << "Efficiency not calculated correctly" << endl;
      return;
    }


  
  
  TH2F * loEff = (TH2F*)sim->Get("cosPsi_Chi_smallAngle_R")->Clone("7");
  loEff->Divide((TH2F*)sim->Get("cosPsi_Chi_smallAngle_P"));

  TH2F * midEff = (TH2F*)sim->Get("cosPsi_Chi_midAngle_R")->Clone("8");
  midEff->Divide((TH2F*)sim->Get("cosPsi_Chi_midAngle_P"));

  TH2F * hiEff = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_R")->Clone("9");
  hiEff->Divide((TH2F*)sim->Get("cosPsi_Chi_hiAngle_P"));
  
  mycan1->cd(1);
  TH2F * plot9Be = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be")->Clone("10");
  plot9Be->Draw("colz");
  plot9Be->GetXaxis()->SetTitle("cos(#psi)");
  plot9Be->GetYaxis()->SetTitle("#chi [deg]");
  plot9Be->GetYaxis()->CenterTitle();
  plot9Be->GetXaxis()->CenterTitle();


  mycan1->cd(2);
  TH2F * plot12C = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_12C")->Clone("11");
  plot12C->Draw("colz");
  plot12C->GetXaxis()->SetTitle("cos(#psi)");
  plot12C->GetYaxis()->SetTitle("#chi [deg]");
  plot12C->GetYaxis()->CenterTitle();
  plot12C->GetXaxis()->CenterTitle();

  mycan1->cd(3);
  TH2F * plot27Al = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_27Al")->Clone("12");
  plot27Al->Draw("colz");
  plot27Al->GetXaxis()->SetTitle("cos(#psi)");
  plot27Al->GetYaxis()->SetTitle("#chi [deg]");
  plot27Al->GetXaxis()->CenterTitle();
  plot27Al->GetYaxis()->CenterTitle();


  mycan1->cd(4);
  TH1F * cosPsi_9Be = (TH1F*)data->Get("/corr/Li7/cosPsi_9Be")->Clone("13");
  TH1F * cosPsi_12C = (TH1F*)data->Get("/corr/Li7/cosPsi_12C")->Clone("14");
  TH1F * cosPsi_27Al = (TH1F*)data->Get("/corr/Li7/cosPsi_27Al")->Clone("15");
  

  cosPsi_27Al->SetLineColor(2);
  cosPsi_27Al->SetMarkerColor(2);
  cosPsi_27Al->Draw("P");
  cosPsi_27Al->GetYaxis()->SetRangeUser(0,13000);
  cosPsi_12C->SetLineColor(3);
  cosPsi_12C->SetMarkerColor(3);
  cosPsi_9Be->SetMarkerStyle(21);
  cosPsi_9Be->Draw("sameP");
  cosPsi_12C->SetMarkerStyle(22);
  cosPsi_12C->Draw("sameP");

  mycan2->cd(1);
  TH2F *  plot9Be_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be")->Clone("16");
  plot9Be_eff->Divide(eff);
  plot9Be_eff->Draw("colz");
  plot9Be_eff->GetXaxis()->SetTitle("cos(#psi)");
  plot9Be_eff->GetYaxis()->SetTitle("#chi [deg]");
  plot9Be_eff->GetYaxis()->CenterTitle();
  plot9Be_eff->GetXaxis()->CenterTitle();
  

  mycan2->cd(2);
  TH2F *  plot12C_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_12C")->Clone("17");
  plot12C_eff->Divide(eff12C);
  plot12C_eff->Draw("colz");
  plot12C_eff->GetXaxis()->SetTitle("cos(#psi)");
  plot12C_eff->GetYaxis()->SetTitle("#chi [deg]");
  plot12C_eff->GetYaxis()->CenterTitle();
  plot12C_eff->GetXaxis()->CenterTitle();


  mycan2->cd(3);
  TH2F *  plot27Al_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_27Al")->Clone("18");
  plot27Al_eff->Divide(eff27Al);
  plot27Al_eff->Draw("colz");
  plot27Al_eff->GetXaxis()->SetTitle("cos(#psi)");
  plot27Al_eff->GetYaxis()->SetTitle("#chi [deg]");
  plot27Al_eff->GetXaxis()->CenterTitle();
  plot27Al_eff->GetYaxis()->CenterTitle();

  mycan2->cd(4);

  // TH1D * cosPsi_Al = (TH1D*)plot27Al_eff->ProjectionX()->Clone("19");
  // TH1D * cosPsi_C = (TH1D*)plot12C_eff->ProjectionX()->Clone("20");
  // TH1D * cosPsi_Be = (TH1D*)plot9Be_eff->ProjectionX()->Clone("21");

  TH1F * cosPsi_Be = (TH1F*)data->Get("/corr/Li7/cosPsi_9Be")->Clone("13");
  TH1F * cosPsi_C = (TH1F*)data->Get("/corr/Li7/cosPsi_12C")->Clone("14");
  TH1F * cosPsi_Al = (TH1F*)data->Get("/corr/Li7/cosPsi_27Al")->Clone("15");
 
  cosPsi_Be->Divide(eff1D);
  cosPsi_C->Divide(eff1D_12C);
  cosPsi_Al->Divide(eff1D_27Al);
  
  cosPsi_Al->SetLineColor(2);
  cosPsi_Al->SetMarkerColor(2);
  cosPsi_Al->GetYaxis()->SetRangeUser(0,23000);
  cosPsi_Al->GetXaxis()->SetTitle("cos(#psi)");
  cosPsi_Al->GetXaxis()->CenterTitle();
  cosPsi_Al->GetYaxis()->SetTitle("[counts]");
  cosPsi_Al->GetYaxis()->CenterTitle();
  cosPsi_Al->Draw("P");
  cosPsi_Be->SetMarkerStyle(21);
  cosPsi_Be->Draw("sameP");
  cosPsi_C->SetLineColor(3);
  cosPsi_C->SetMarkerColor(3);
  cosPsi_C->SetMarkerStyle(22);
  cosPsi_C->Draw("sameP");
  

  /*
  plot27Al_eff->ProjectionX()->Draw("samePC");
  plot27Al_eff->ProjectionX()->SetLineColor(2);
  plot9Be_eff->ProjectionX()->SetMarkerStyle(21);
  plot9Be_eff->ProjectionX()->Draw("samePC");
  plot12C_eff->ProjectionX()->SetMarkerStyle(22);
  plot12C_eff->ProjectionX()->SetLineColor(3);
  plot12C_eff->ProjectionX()->Draw("samePC");
  */

  /*
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
  */


}
