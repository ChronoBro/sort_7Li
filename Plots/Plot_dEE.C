void Plot_dEE()
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



  TFile *in  = new TFile("/home/wudaq/unpacker/sort.root");
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
      mycan1 = new TCanvas("Mycan1","Russian",1200,1200);
      mycan1->Divide(4,4,0.000001,0.000001);
    }

  for(int i=0;i<16;i++)
    {
      gROOT->cd();
      mycan1->cd(i+1);
      outstring.str("");
      outstring << "dEE/dEE_"<<i;
      name = outstring.str();
      TH2I *dee= (TH2I*)gROOT->FindObject(Form("dee%i",i));
      if(!dee)
	{
	  cout << name.c_str() << endl;
	  dee = (TH2I*)in->Get(name.c_str())->Clone(Form("dee%i",i));

	}
      dee->Draw("col");
      dee->GetYaxis()->SetRangeUser(0.,60.);
      dee->SetMinimum(0.9);
    }

  TCanvas *mycan2 = (TCanvas*)gROOT->FindObject("Mycan2");
  if(!mycan2)
    {
      mycan2 = new TCanvas("Mycan2","S2",1200,1200);
      mycan2->Divide(4,4,0.000001,0.000001);
    }

  for(int i=16;i<32;i++)
    {
      gROOT->cd();
      mycan2->cd(i+1-16);
      outstring.str("");
      outstring << "dEE/dEE_"<<i;
      name = outstring.str();
      TH2I *dee= (TH2I*)gROOT->FindObject(Form("dee%i",i));
      if(!dee)
	{
	  cout << name.c_str() << endl;
	  dee = (TH2I*)in->Get(name.c_str())->Clone(Form("dee%i",i));

	}
      dee->Draw("col");
      //      dee->SetMinimum(0.9);
    }

  in->Close();

  return;
}
