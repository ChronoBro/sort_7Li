void Plot_Rings()
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
  //Sty->SetPalette(8,0);
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


  float Maxs[48] ={0.};

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
      mycan1 = new TCanvas("Mycan1","HG Raw 1",1200,1200);
      mycan1->Divide(4,4,0.000001,0.000001);
    }

  for(int i=0;i<16;i++)
    {
      gROOT->cd();
      mycan1->cd(i+1);
      outstring.str("");
      outstring << "S2/S2rings/S2RingR_"<<i;
      name = outstring.str();
      TH1I *Ring = (TH1I*)gROOT->FindObject(Form("Ring%i",i));
      if(!Ring)
	{
	  cout << name.c_str() << endl;
	  Ring = (TH1I*)in->Get(name.c_str())->Clone(Form("Ring%i",i));
	  cout << "HEY" << endl;
	}
      Ring->Draw();
      Ring->GetXaxis()->SetRangeUser(350,900);
      
      cout << i << " " << Ring->GetMaximum() << endl;
      int max = Ring->GetMaximumBin();

      cout << max << " " << Ring->Integral(max-10,max+10) << endl;
      Maxs[i] =Ring->Integral(max-10,max+10);
    }

  TCanvas *mycan2 = (TCanvas*)gROOT->FindObject("Mycan2");
  if(!mycan2)
    {
      mycan2 = new TCanvas("Mycan2","HG Raw 2",1200,1200);
      mycan2->Divide(4,4,0.000001,0.000001);
    }

  for(int i=16;i<32;i++)
    {

      mycan2->cd(i-15);
      outstring.str("");
      outstring << "S2/S2rings/S2RingR_"<<i;
      name = outstring.str();
      TH1I *Ring = (TH1I*)gROOT->FindObject(Form("Ring%i",i));
      if(!Ring)
	{
	  Ring = (TH1I*)in->Get(name.c_str())->Clone(Form("Ring%i",i));
	}
      Ring->Draw();
      Ring->GetXaxis()->SetRangeUser(350,900);

      cout << i << " " << Ring->GetMaximum() << endl;
      int max = Ring->GetMaximumBin();
      Maxs[i] = Ring->Integral(max-10,max+10);

    }

  TCanvas *mycan3 = (TCanvas*)gROOT->FindObject("Mycan3");
  if(!mycan3)
    {
      mycan3 = new TCanvas("Mycan3","HG Raw 3",1200,1200);
      mycan3->Divide(4,4,0.000001,0.000001);
    }

  for(int i=32;i<48;i++)
    {

      mycan3->cd(i-31);
      outstring.str("");
      outstring << "S2/S2rings/S2RingR_"<<i;
      name = outstring.str();
      TH1I *Ring = (TH1I*)gROOT->FindObject(Form("Ring%i",i));
      if(!Ring)
	{
	  Ring = (TH1I*)in->Get(name.c_str())->Clone(Form("Ring%i",i));
	}
      Ring->Draw();
      Ring->GetXaxis()->SetRangeUser(350,900);
      
      
      cout << i << " " << Ring->GetMaximum() << endl;
      int max = Ring->GetMaximumBin();
      Maxs[i] = Ring->Integral(max-10,max+10);

    }


  TCanvas *mycan4 = (TCanvas*)gROOT->FindObject("Mycan4");
  if(!mycan4)
    {
      mycan4 = new TCanvas("Mycan4","HG Raw 4",1200,1200);

    }

  mycan4->cd(1);

  float is[48];
  for(int i=0;i<48;i++)
    {
      is[i] = i+1;
    }

  TGraph *mygraph = new TGraph(48,is,Maxs);
  mygraph->Draw("AP");
  mygraph->SetMarkerStyle(20);


  return;
}
