
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
  //creating own palette, with good grayscale

  const Int_t Ncolors = 50;
  // Int_t LSDPalette[Ncolors];                 //C1   C2  C3
  // // Double_t red[3] = {1.00, 1.00, 0.5};    //{R1, R2, R3}
  // // Double_t green[3] = {0.80, 0.25, 0.05}; //{G1, G2, G3}
  // // Double_t blue[3] = {0.00, 0.05, 0.9};   //{B1, B2, B3}
  // Double_t Stop[3] = {0.00, 0.5, 1.0};       //C1-%->C2-%->C3

  // Double_t red[3] = {0.55, 1.00, 1.00};    //{R1, R2, R3}
  // Double_t green[3] = {0.00, 0.90, 0.25}; //{G1, G2, G3}
  // Double_t blue[3] = {0.85, 0.00, 0.05};   //{B1, B2, B3}
  
  
  // // // {1.00,1.00,0.5};
  // // // {0.8,0.25,0.05};
  // // // {0.00,0.05,0.9};
      
  // nt_t LSDColorTable = TColor::CreateGradientColorTable(3,Stop,red,green,blue,Ncolors);
  // for (int i=0;i<Ncolors;i++) LSDPalette[i] = LSDColorTable+i;
  // Sty->SetPalette(Ncolors,LSDPalette);

  Int_t MyPalette[Ncolors];
  Double_t Color1[3] = {0.05, 0.25, 1.00}; 
  Double_t Color2[3] = {0.05, 0.9, 1.00};
  Double_t Color3[3] = {0.4, 0.82, 0.00};
  Double_t Stop[3] = {0.00, 0.60, 1.00};
  Int_t MyColorTable = TColor::CreateGradientColorTable(3,Stop,Color1,Color2,Color3,Ncolors);
  for (int i=0;i<Ncolors;i++) MyPalette[i] = MyColorTable+i;
  //Sty->SetPalette(Ncolors,MyPalette);


   
  // Int_t ColePalette[Ncolors];
  // Double_t Color1[3] = {0.00, 0.00, 1.00};
  // Double_t Color2[3] = {0.00, 1.00, 0.00};
  // Double_t Color3[3] = {1.00, 0.00, 0.00};
  // Double_t Stop[3] = {0.00, 0.60, 1.00};
  // Int_t ColeColorTable = TColor::CreateGradientColorTable(3,Stop,Color1,Color2,Color3,Ncolors);
  // for (int i=0;i<Ncolors;i++) ColePalette[i] = ColeColorTable+i;
  // Sty->SetPalette(Ncolors,ColePalette);


  //Sty->SetPalette(1,0);
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
  Sty->SetLineWidth(3);
  Sty->SetLabelSize(0.085,"xyz");
  Sty->SetLabelFont(62);
  Sty->SetLabelOffset(0.02,"y");
  Sty->SetLabelOffset(0.02,"x");
  Sty->SetLabelColor(kBlack,"xyz");
  Sty->SetTitleSize(0.085,"xyz");
  Sty->SetTitleFont(62);
  Sty->SetTitleOffset(1.1,"y");
  Sty->SetTitleOffset(1,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.04,"xz");
  //Sty->SetTickWidth(.03,"xyz");
  Sty->SetTickLength(.02,"y");
  Sty->SetNdivisions(08,"x");
  Sty->SetNdivisions(08,"yz");
  Sty->SetEndErrorSize(0);
  Sty->SetMarkerStyle(8);
  //Sty->SetPalette(62);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();


  TCanvas * mycan1 = new TCanvas("mycan1","mycan1",1200,800);
  TCanvas * mycan2 = new TCanvas("mycan2","mycan2",1200,800);
  TCanvas * mycan3 = new TCanvas("mycan3","mycan3",1200,800);
  
  //mycan.SetCanvasSize(800,800);
  TFile * data = new TFile("~/unpacker/sortALLv2.root");
  TFile * data2 = new TFile("~/unpacker/sort.root");
  TFile * sim = new TFile("~/sim/sim.root");
  TFile * sim2 = new TFile("~/sim12C/sim.root");
  TFile * sim3 = new TFile("~/sim27Al/sim.root");
  TFile * sim6Li = new TFile("~/sim/sim6Li.root");
  gROOT->cd();
  mycan1->Divide(2,2);
  mycan2->Divide(2,2);
  mycan3->Divide(2,0); //Divide into(xpads,ypads)

  mycan3->cd(1);
  TH2F * eff10Be = (TH2F*)sim6Li->Get("cosPsi_Chi_R")->Clone("6");
  eff10Be->Divide((TH2F*)sim6Li->Get("cosPsi_Chi_P"));
  eff10Be->Draw("colz");
  eff10Be->GetXaxis()->SetTitle("cos(#psi)");
  eff10Be->GetYaxis()->SetTitle("#chi (deg)");
  eff10Be->GetYaxis()->CenterTitle();
  eff10Be->GetXaxis()->CenterTitle();
  
  
  mycan1->cd(1);
  TH2F * eff = (TH2F*)sim->Get("cosPsi_Chi_R")->Clone("6");
  eff->Divide((TH2F*)sim->Get("cosPsi_Chi_P"));
  // eff->Draw("colz");
  eff->GetXaxis()->SetTitle("cos(#psi)");
  eff->GetYaxis()->SetTitle("#chi (deg)");
  eff->GetYaxis()->CenterTitle();
  eff->GetXaxis()->CenterTitle();


  TH2F * eff12C = (TH2F*)sim2->Get("cosPsi_Chi_R")->Clone("6");
  eff12C->Divide((TH2F*)sim2->Get("cosPsi_Chi_P"));
  // eff->Draw("colz");
  eff12C->GetXaxis()->SetTitle("cos(#psi)");
  eff12C->GetYaxis()->SetTitle("#chi (deg)");
  eff12C->GetYaxis()->CenterTitle();
  eff12C->GetXaxis()->CenterTitle();

  TH2F * eff27Al = (TH2F*)sim3->Get("cosPsi_Chi_R")->Clone("6");
  eff27Al->Divide((TH2F*)sim3->Get("cosPsi_Chi_P"));
  // eff->Draw("colz");
  eff27Al->GetXaxis()->SetTitle("cos(#psi)");
  eff27Al->GetYaxis()->SetTitle("#chi (deg)");
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
  //gPad->SetPad(0.005,0.995,0.995,0.005);

  
  TH2F * plot9Be = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be")->Clone("10");
  plot9Be->Draw("colz");
  plot9Be->GetXaxis()->SetTitle("cos(#psi)");
  plot9Be->GetYaxis()->SetTitle("#chi (deg)");
  plot9Be->GetYaxis()->CenterTitle();
  plot9Be->GetXaxis()->CenterTitle();



  mycan1->cd(2);
  TH2F * plot12C = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_12C")->Clone("11");
  plot12C->Draw("colz");
  plot12C->GetXaxis()->SetTitle("cos(#psi)");
  plot12C->GetYaxis()->SetTitle("#chi (deg)");
  plot12C->GetYaxis()->CenterTitle();
  plot12C->GetXaxis()->CenterTitle();

  mycan1->cd(3);
  TH2F * plot27Al = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_27Al")->Clone("12");
  plot27Al->Draw("colz");
  plot27Al->GetXaxis()->SetTitle("cos(#psi)");
  plot27Al->GetYaxis()->SetTitle("#chi (deg)");
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
  gPad->SetPad(0,1,0.5,0.5);
  gPad->SetLeftMargin(0.2);
  gPad->SetRightMargin(0.15);
  gPad->SetTopMargin(0.05);
  gPad->SetBottomMargin(0.2);

  
  TH2F *  plot9Be_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be")->Clone("16");
  plot9Be_eff->Divide(eff);
  plot9Be_eff->Draw("colz");
  plot9Be_eff->GetXaxis()->SetTitle("cos(#psi)");
  plot9Be_eff->GetYaxis()->SetTitle("#chi (deg)");
  plot9Be_eff->GetYaxis()->CenterTitle();
  plot9Be_eff->GetXaxis()->CenterTitle();
  

  mycan2->cd(2);
  gPad->SetPad(0.5,1,1,0.5);
  gPad->SetLeftMargin(0.2);
  gPad->SetRightMargin(0.15);
  gPad->SetTopMargin(0.05);
  gPad->SetBottomMargin(0.2);
  
  
  TH2F *  plot12C_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_12C")->Clone("17");
  plot12C_eff->Divide(eff12C);
  plot12C_eff->Draw("colz");
  plot12C_eff->GetXaxis()->SetTitle("cos(#psi)");
  plot12C_eff->GetYaxis()->SetTitle("#chi (deg)");
  plot12C_eff->GetYaxis()->CenterTitle();
  plot12C_eff->GetXaxis()->CenterTitle();


  mycan2->cd(3);
  gPad->SetPad(0,0.5,0.55,0);
  gPad->SetLeftMargin(0.2);
  gPad->SetRightMargin(0.25);
  gPad->SetTopMargin(0.05);
  gPad->SetBottomMargin(0.2);

  TH2F *  plot27Al_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_27Al")->Clone("18");
  plot27Al_eff->Divide(eff27Al);
  plot27Al_eff->Draw("colz");
  plot27Al_eff->GetXaxis()->SetTitle("cos(#psi)");
  plot27Al_eff->GetYaxis()->SetTitle("#chi (deg)");
  plot27Al_eff->GetXaxis()->CenterTitle();
  plot27Al_eff->GetYaxis()->CenterTitle();

  mycan3->cd(2);
  TH2F *  plot10Be_eff = (TH2F*)data2->Get("/corr/Li6/cosPsi_Chi_10Be")->Clone("18");
  plot10Be_eff->Divide(eff27Al);
  plot10Be_eff->Draw("colz");
  plot10Be_eff->GetXaxis()->SetTitle("cos(#psi)");
  plot10Be_eff->GetYaxis()->SetTitle("#chi (deg)");
  plot10Be_eff->GetXaxis()->CenterTitle();
  plot10Be_eff->GetYaxis()->CenterTitle();

  TH1F * eff1 = (TH1F*)sim6Li->Get("cosPsi_R")->Clone("20");
  TH1F * eff2 = (TH1F*)sim6Li->Get("cosPsi_P")->Clone("22");
  TH1F * plot1D_10Be = (TH1F*)data2->Get("/corr/Li6/cosPsi_10Be")->Clone("21");

  eff1->Divide(eff2);
  plot1D_10Be->Divide(eff1);
  // mycan3->cd(1);
  // eff1->Draw();
  // mycan3->cd(2);
  // plot1D_10Be->Draw();
  
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

  eff12C->Draw("colz");

  /*
  plot27Al_eff->ProjectionX()->Draw("samePC");
  plot27Al_eff->ProjectionX()->SetLineColor(2);
  plot9Be_eff->ProjectionX()->SetMarkerStyle(21);
  plot9Be_eff->ProjectionX()->Draw("samePC");
  plot12C_eff->ProjectionX()->SetMarkerStyle(22);
  plot12C_eff->ProjectionX()->SetLineColor(3);
  plot12C_eff->ProjectionX()->Draw("samePC");
  */

  
  // mycan1->cd(3);
  // TH2F *  plot9Be_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_9Be")->Clone("11");
  // plot9Be_eff->Divide(eff);
  // plot9Be_eff->Draw("colz");
  // plot9Be_eff->GetXaxis()->SetTitle("cos(#psi)");
  // plot9Be_eff->GetYaxis()->SetTitle("#chi (deg)");
  // plot9Be_eff->GetYaxis()->CenterTitle();
  // plot9Be_eff->GetXaxis()->CenterTitle();


  // mycan1->cd(4);
  // TH1D * cosPsi_9Be = plot9Be_eff->ProjectionX();
  // //cosPsi_9Be->SetMarkerStyle(3);
  // cosPsi_9Be->Draw("PC");
  // cosPsi_9Be->GetYaxis()->SetRangeUser(0,23000);
  // */


}
