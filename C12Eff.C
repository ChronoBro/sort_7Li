void C12Eff()
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
  Sty->SetPadTopMargin(.13);
  Sty->SetPadLeftMargin(.17);
  Sty->SetPadRightMargin(.13);
  Sty->SetHistLineWidth(2);
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
  //Sty->SetMarkerSize(0.5);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();

 
  TCanvas * mycan1 = new TCanvas("mycan1","mycan1",900,600);
  TCanvas * mycan2 = new TCanvas("mycan2","mycan2",1200,800);
  TCanvas * mycan3 = new TCanvas("mycan3","mycan3",800,1200);
  //mycan.SetCanvasSize(800,800);
  TFile * data = new TFile("~/unpacker/sortALLv2.root");
  TFile * sim = new TFile("~/sim12C/sim.root");
  TFile * sim2 = new TFile("~/elasSim/sim12C/sim.root");
  gROOT->cd();
  mycan1->Divide(2,2);
  mycan2->Divide(3,3);
  mycan3->Divide(2,2);

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
  TH2F * plot12C = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_12C")->Clone("10");
  plot12C->Draw("colz");
  plot12C->GetXaxis()->SetTitle("cos(#psi)");
  plot12C->GetYaxis()->SetTitle("#chi [deg]");
  plot12C->GetYaxis()->CenterTitle();
  plot12C->GetXaxis()->CenterTitle();

  mycan1->cd(3);
  TH2F *  plot12C_eff = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_12C")->Clone("11");
  plot12C_eff->Divide(eff);
  plot12C_eff->Draw("colz");
  plot12C_eff->GetXaxis()->SetTitle("cos(#psi)");
  plot12C_eff->GetYaxis()->SetTitle("#chi [deg]");
  plot12C_eff->GetYaxis()->CenterTitle();
  plot12C_eff->GetXaxis()->CenterTitle();

  mycan1->cd(4);
  TH1D * cosPsi_12C = plot12C_eff->ProjectionX();
  //cosPsi_12C->SetMarkerStyle(3);
  cosPsi_12C->Draw("PC");
  cosPsi_12C->GetYaxis()->SetRangeUser(0,23000);

  TH2F * small_12C = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_12C_small_angle")->Clone("12");
  TH2F * mid_12C = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_12C_mid_angle")->Clone("13");
  TH2F * hi_12C = (TH2F*)data->Get("/corr/Li7/cosPsi_Chi_12C_large_angle")->Clone("14");

  mycan2->cd(4);
  TH1D * cosPsi_lo2 = small_12C->ProjectionX();
 
  cosPsi_lo2->Draw("PC");
  TH2F * thing3 = (TH2F*)sim->Get("cosPsi_Chi_smallAngle_R")->Clone("15");
  //TH1D * cosPsi_loEff = thing3->ProjectionX();
  TH2F * thing4 = (TH2F*)sim->Get("cosPsi_Chi_smallAngle_P")->Clone("16");
  thing3->Divide(thing4);
  //cosPsi_loEff->Divide(thing4->ProjectionX());
  TH1D * cosPsi_loEff = thing3->ProjectionX();
  mycan2->cd(1);
  cosPsi_loEff->Draw("PC");
  
 
  mycan2->cd(5);
  TH1D * cosPsi_mid2 = mid_12C->ProjectionX();

  cosPsi_mid2->Draw("PC");
  TH2F * thing5 = (TH2F*)sim->Get("cosPsi_Chi_midAngle_R")->Clone("17");
  TH1D * cosPsi_midEff = thing5->ProjectionX();
  TH2F * thing6 = (TH2F*)sim->Get("cosPsi_Chi_midAngle_P")->Clone("18");
  cosPsi_midEff->Divide(thing6->ProjectionX());
  mycan2->cd(2);
  cosPsi_midEff->Draw("PC");


  mycan2->cd(6);
  TH1D * cosPsi_hi2 = hi_12C->ProjectionX();
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
  TFile fileRoot ("C12Eff.root","RECREATE");
  
  mycan2->cd(7);
  TH1D* cosPsi_lo = (TH1D*)cosPsi_lo2->Clone();
  cosPsi_lo->Sumw2();
  small_12C->Divide(thing3);
  cosPsi_lo->Divide(cosPsi_loEff);
  cosPsi_lo->Draw("PC");
  //small_12C->ProjectionX()->Draw("P");
  cosPsi_lo->Write();

  
  mycan2->cd(8);
  TH1D * cosPsi_mid = (TH1D*)cosPsi_mid2->Clone();
  cosPsi_mid->Divide(cosPsi_midEff);
  cosPsi_mid->Draw("PC");
  cosPsi_mid->Write();

  mycan2->cd(9);
  TH1D * cosPsi_hi = (TH1D*)cosPsi_hi2->Clone();
  cosPsi_hi->Divide(cosPsi_hiEff);
  cosPsi_hi->Draw("PC");
  cosPsi_hi->Write();
  
  /*
  TH1D * cosPsi_hi = hi_12C->ProjectionX();
  TH2F * thing1 = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_R")->Clone("4");
  TH1D * cosPsi_hiEff = thing1->ProjectionX();
  TH2F * thing2 = (TH2F*)sim->Get("cosPsi_Chi_hiAngle_P")->Clone("5");
  cosPsi_hiEff->Divide(thing2->ProjectionX());
  cosPsi_hiEff->Draw("PC");

  cosPsi_hi->Divide(cosPsi_hiEff);
  cosPsi_hi->Draw("PC");
  */

  int bins;

  mycan3->cd(1);
  TH1I * Ex7Li = (TH1I*)data->Get("/corr/Li7/Ex7Li_ta")->Clone("20");
  Ex7Li->Draw("PC");
  Ex7Li->GetXaxis()->SetRangeUser(0,12);

  bins = Ex7Li->GetNbinsX();
  float * x1 = new float[bins];
  float * y1 = new float[bins];

  for(int i=0;i<bins;i++)
    {
      x1[i] = Ex7Li->GetBinContent(i+1);
      y1[i] = Ex7Li->GetBinCenter(i+1);
      //cout << "x = " << x[i] << endl;
      // cout << "y = " << y[i] << endl;
    }

  TGraph * gr1 = new TGraph(bins,x1,y1);
  gr1->Draw("AC");
  gr1->GetYaxis()->SetRangeUser(0,10);

  delete x1;
  delete y1;
  


  mycan3->cd(2);
  TH1I * Ex9Be = (TH1I*)data->Get("/corr/Li7/ExTarget_9Be")->Clone("21");
  Ex9Be->Draw("PC");
  Ex9Be->GetXaxis()->SetRangeUser(-2,9);

  bins = Ex9Be->GetNbinsX();
  float * x2 = new float[bins];
  float * y2 = new float[bins];

  for(int i=0;i<bins;i++)
    {
      x2[i] = Ex9Be->GetBinContent(i+1);
      y2[i] = Ex9Be->GetBinCenter(i+1);
      //cout << "x = " << x[i] << endl;
      // cout << "y = " << y[i] << endl;
    }

  TGraph * gr2 = new TGraph(bins,x2,y2);
  gr2->Draw("AC");
  gr2->GetYaxis()->SetRangeUser(-2,9);

  delete x2;
  delete y2;

  mycan3->cd(3);
  TH1I * Ex12C = (TH1I*)data->Get("/corr/Li7/ExTarget_C")->Clone("22");
  Ex12C->Draw("PC");
  Ex12C->GetXaxis()->SetRangeUser(-2,11);

  bins = Ex12C->GetNbinsX();
  float * x3 = new float[bins];
  float * y3 = new float[bins];

  for(int i=0;i<bins;i++)
    {
      x3[i] = Ex12C->GetBinContent(i+1);
      y3[i] = Ex12C->GetBinCenter(i+1);
      //cout << "x = " << x[i] << endl;
      // cout << "y = " << y[i] << endl;
    }

  TGraph * gr3 = new TGraph(bins,x3,y3);
  gr3->Draw("AC");
  gr3->GetYaxis()->SetRangeUser(-2,12);

  delete x3;
  delete y3;

  mycan3->cd(4);
  TH1I * Ex27Al = (TH1I*)data->Get("/corr/Li7/ExTarget_Al")->Clone("23");
  // Ex27Al->Draw("PC");
 

  bins = Ex27Al->GetNbinsX();
  float * x = new float[bins];
  float * y = new float[bins];

  for(int i=0;i<bins;i++)
    {
      x[i] = Ex27Al->GetBinContent(i+1);
      y[i] = Ex27Al->GetBinCenter(i+1);
      // cout << "x = " << x[i] << endl;
      //cout << "y = " << y[i] << endl;
    }

  TGraph * gr = new TGraph(bins,x,y);
  gr->Draw("AC");
  gr->GetYaxis()->SetRangeUser(-2,5);

  delete x;
  delete y;
  
  TCanvas * c5 = new TCanvas("heyo","heyo",800,600);
  TH1F * eff1D = (TH1F*)sim->Get("theta_reactionCM_R")->Clone("26");
  TH1F * really = (TH1F*)sim->Get("theta_reactionCM_P")->Clone("me");
  eff1D->Divide(really);

  eff1D->Draw();

  TH1F * Be1D = (TH1F*)data->Get("/corr/Li7/Li7_theta_reactCoM_12C")->Clone("Li7_C12_inel_xs");

  Be1D->Divide(eff1D);
  Be1D->Draw("P");

  
  //Be1D.Write();
  
  int k=181;
  ifstream file1("/Users/dhoff/Programs/AngCorr/elas_xsection_12C.plot"); //apparently you need to write out the whole thing for ROOT
  ifstream file2("/Users/dhoff/Programs/AngCorr/inel_xsection_12C.plot");
  ifstream file3("/Users/dhoff/Programs/AngCorr/inel1_xsection_12C.plot");

  
  float * angle = new float[k];
  float  * elas = new float[k];
  float * inel = new float[k];
  float * inel1 = new float[k];
  float * elasTOT=0;
  
  
  float SCALER = 321471.;
  SCALER=1.;
  //SCALER= 0.000046196*100.;

  for(int i=0;i<k;i++)
    {
      file1 >> angle[i] >> elas[i];
      file2 >> angle[i] >> inel[i];
      file3 >> angle[i] >> inel1[i];
      //elas[i] = elas[i]+inel1[k]; //only true when using the rotor model since I can't get the breakup model to work with two states...
      //elas[i] = elas[i];
      //inel[i] = inel1[i];
      //cout <<  elas[i] << endl;
      //cout <<  inel1[i] << endl;
    }


  TGraph * E = new TGraph(k,angle,elas);
  TGraph * I = new TGraph(k,angle,inel);

  
  float binW = Be1D->GetXaxis()->GetBinWidth(2);
  for(int i=1;i<=125;i++)
    {
      float solidAng;
      float thetaC;
      thetaC = Be1D->GetBinCenter(i)*3.14159/180.;
      solidAng = 2*3.14159*(cos(thetaC-binW/2.) - cos(thetaC+binW/2.));
      float content = Be1D->GetBinContent(i);
      content = content/solidAng;///sin(Be1D->GetBinCenter(i)*3.14159/180.);
      Be1D->SetBinContent(i,content*SCALER);
      Be1D->SetBinError(i,sqrt(content)/solidAng);
    }
  

  Be1D->SetMarkerStyle(20);
  Be1D->Draw("P");
  I->SetLineColor(2);
  I->Draw("same");
  Be1D->GetXaxis()->SetRangeUser(0,20);
  Be1D->GetXaxis()->SetTitle("#theta_{CM}");
  Be1D->SetTitle("^{7}Li(7.2-) #sigma_{inel}");

  //Be1D.Write();
  
  c5->SetLogy();



  TCanvas * c6 = new TCanvas("r","r",800,600);
  TH1F * effEl = (TH1F*)sim2->Get("theta_reactionCM_R")->Clone("65");
  TH1F * really2 = (TH1F*)sim2->Get("theta_reactionCM_P")->Clone("56");

  effEl->Divide(really2);

  TH1F * BeElas = (TH1F*)data->Get("/corr/Li7/7Li_elas_12C")->Clone("Li7_C12_el_xs");
  BeElas->Divide(effEl);

  binW = BeElas->GetXaxis()->GetBinWidth(2);
  for(int i=1;i<=125;i++)
    {
      float solidAng;
      float thetaC;
      thetaC = BeElas->GetBinCenter(i)*3.14159/180.;
      solidAng = 2*3.14159*(cos(thetaC-binW/2.) - cos(thetaC+binW/2.));
      float content = BeElas->GetBinContent(i);
      //cout << content << endl;
      content = content/solidAng;//sin(BeElas->GetBinCenter(i)*3.14159/180.);
      //content = content/sin(thetaC);
      BeElas->SetBinContent(i,content*SCALER);
      if(BeElas->GetBinCenter(i)>8 && BeElas->GetBinCenter(i)<11)
	BeElas->SetBinContent(i,0.);
      if(BeElas->GetBinCenter(i)<2.8)
	BeElas->SetBinContent(i,0.);
    }

  //BeElas.Write();
  
  BeElas->SetMarkerStyle(20);
  BeElas->Draw("P");
  E->Draw("same");
  BeElas->GetXaxis()->SetRangeUser(0,24);
  BeElas->GetXaxis()->SetTitle("#theta_{CM}");
  BeElas->SetTitle("^{7}Li(7.2-) #sigma_{el}");
  c6->SetLogy();
  //BeElas.Write();

  TCanvas * c7 = new TCanvas("b","b",800,600);
  TH1F * relative = (TH1F*)data->Get("/corr/Li7/Li7_theta_reactCoM_12C")->Clone("73");
  relative->Divide(eff1D);
  relative->Divide(BeElas);
  relative->SetMarkerStyle(20);
  relative->Draw("P");
  c7->SetLogy();
  relative->GetXaxis()->SetRangeUser(0,25);

  TFile * f = new TFile("C12XS.root","RECREATE");
  BeElas->Write();
  Be1D->Write();

  ofstream output1("C12elasXS.dat");
  ofstream output2("C12inelXS.dat");
		   
  for(int i=0;i<125;i++)
    {
      if(BeElas->GetBinContent(i)!=0)
	{
	  output1 << BeElas->GetBinCenter(i) << " " << BeElas->GetBinContent(i) << endl;
	}

      if(Be1D->GetBinContent(i)!=0)
	{
	  output2 << Be1D->GetBinCenter(i) << " " << Be1D->GetBinContent(i) << endl;
	}

    }
  
  fileRoot.Write();

  return;
}
