void Plot_Summary()
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
  Sty->SetPadRightMargin(.01);
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
  Sty->SetTitleOffset(1.3,"y");
  Sty->SetTitleOffset(1.1,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.03,"xz");
  Sty->SetTickLength(.02,"y");
  Sty->SetNdivisions(5,"x");
  Sty->SetNdivisions(10,"yz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();


  TFile *in  = new TFile("/home/lithium7/unpacker/sort.root");
  if(!in->IsOpen())
    {
      cout << "No data here..." << endl;
      return;
    }
  gROOT->cd();


  ostringstream outstring;
  string name;

  TCanvas *mycan1 = (TCanvas*)gROOT->FindObject("Mycan1");
  if(!mycan1)
    {
      mycan1 = new TCanvas("Mycan1","Russian",600,600);
      mycan1->Divide(2,2,0.000001,0.000001);
    }

  mycan1->cd(1);
  TH2I * RSum = (TH2I*)gROOT->FindObject("RSum");
  if(!RSum)
    {
      RSum = (TH2I*)in->Get("rus/RSum/RusPieSumC");
      RSum->RebinY(10);
    }
  gPad->SetLogz();  
  RSum->Draw("Col");
  RSum->GetYaxis()->SetRangeUser(0,40);
  
  mycan1->cd(2);
  TH2I * RSum1 = (TH2I*)gROOT->FindObject("RSum1");
  if(!RSum1)
    {
      RSum1 = (TH2I*)in->Get("rus/RSum/RusRingSumC");
      RSum1->RebinY(10);
    }
  gPad->SetLogz();  
  RSum1->Draw("Col");
  RSum1->GetYaxis()->SetRangeUser(0,40);

  mycan1->cd(3);
  TH2I * SSum = (TH2I*)gROOT->FindObject("SSum");
  if(!SSum)
    {
      SSum = (TH2I*)in->Get("S2/SSum/S2PieSumC");
      SSum->RebinY(10);
    }
  gPad->SetLogz();  
  SSum->Draw("Col");
  SSum->GetYaxis()->SetRangeUser(0,40);
  
  mycan1->cd(4);
  TH2I * SSum1 = (TH2I*)gROOT->FindObject("SSum1");
  if(!SSum1)
    {
      SSum1 = (TH2I*)in->Get("S2/SSum/S2RingSumC");
      SSum1->RebinY(10);
    }
  gPad->SetLogz();  
  SSum1->Draw("Col");
  SSum1->GetYaxis()->SetRangeUser(0,40);


  return;
}
