void Plot_RPies()
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


  TFile *in  = new TFile("/home/wudaq/unpacker/sort.root");
  if(!in)
    {
      cout << "No data here..." << endl;
      return;
    }
  gROOT->cd();

  TCanvas *mycan1 = (TCanvas*)gROOT->FindObject("Mycan1");
  if(!mycan1)
    {
      mycan1 = new TCanvas("Mycan1","HG Raw 1",1200,1200);
      mycan1->Divide(4,4,0.000001,0.000001);
    }

  
  ostringstream outstring;
  string name;

  for(int i=0;i<16;i++)
    {

      mycan1->cd(i+1);
      outstring.str("");
      outstring << "rus/RpiesCM1/RusPieCM1_"<<i;
      name = outstring.str();
      TH1I *hist = (TH1I*)gROOT->FindObject(Form("RPie%i",i));
      if(!hist)
	{
	  hist = (TH1I*)in->Get(name.c_str())->Clone(Form("RPie%i",i));
	}

      hist->Draw();
      hist->GetXaxis()->SetRangeUser(2,7);
      gPad->SetLogy();


    }
  TCanvas *mycan2 = (TCanvas*)gROOT->FindObject("Mycan2");
  if(!mycan2)
    {
      mycan2 = new TCanvas("Mycan2","HG Raw 2",1200,1200);
      mycan2->Divide(4,4,0.000001,0.000001);
    }

  
  for(int i=16;i<32;i++)
    {

      mycan2->cd(i+1-16);
      outstring.str("");
      outstring << "rus/RpiesCM1/RusPieCM1_"<<i;
      name = outstring.str();
      TH1I *hist = (TH1I*)gROOT->FindObject(Form("RPie%i",i));
      if(!hist)
	{
	  hist = (TH1I*)in->Get(name.c_str())->Clone(Form("RPie%i",i));
	}

      hist->Draw();
      hist->GetXaxis()->SetRangeUser(2,7);
      gPad->SetLogy();


    }
  TCanvas *mycan3 = (TCanvas*)gROOT->FindObject("Mycan3");
  if(!mycan3)
    {
      mycan3 = new TCanvas("Mycan3","HG Raw 3",1200,1200);
      mycan3->Divide(4,4,0.000001,0.000001);
    }

  

  for(int i=32;i<48;i++)
    {

      mycan3->cd(i+1-32);
      outstring.str("");
      outstring << "rus/RpiesCM1/RusPieCM1_"<<i;
      name = outstring.str();
      TH1I *hist = (TH1I*)gROOT->FindObject(Form("RPie%i",i));
      if(!hist)
	{
	  hist = (TH1I*)in->Get(name.c_str())->Clone(Form("RPie%i",i));
	}

      hist->Draw();
      hist->GetXaxis()->SetRangeUser(2,7);
      gPad->SetLogy();


    }
  TCanvas *mycan4 = (TCanvas*)gROOT->FindObject("Mycan4");
  if(!mycan4)
    {
      mycan4 = new TCanvas("Mycan4","HG Raw 4",1200,1200);
      mycan4->Divide(4,4,0.000001,0.000001);
    }

  
  for(int i=48;i<64;i++)
    {

      mycan4->cd(i+1-48);
      outstring.str("");
      outstring << "rus/RpiesCM1/RusPieCM1_"<<i;
      name = outstring.str();
      TH1I *hist = (TH1I*)gROOT->FindObject(Form("RPie%i",i));
      if(!hist)
	{
	  hist = (TH1I*)in->Get(name.c_str())->Clone(Form("RPie%i",i));
	}

      hist->Draw();
      hist->GetXaxis()->SetRangeUser(2,7);
      gPad->SetLogy();


    }

  TCanvas *mycan5 = (TCanvas*)gROOT->FindObject("Mycan5");
  if(!mycan5)
    {
      mycan5 = new TCanvas("Mycan5","HG Raw 5",1200,1200);
      mycan5->Divide(4,4,0.000001,0.000001);
    }

  
  for(int i=0;i<16;i++)
    {

      mycan5->cd(i+1);
      outstring.str("");
      outstring << "rus/Rrings/RusRingR_"<<i;
      name = outstring.str();
      TH1I *hist = (TH1I*)gROOT->FindObject(Form("RRing%i",i));
      if(!hist)
	{
	  hist = (TH1I*)in->Get(name.c_str())->Clone(Form("RRing%i",i));
	}

      hist->Draw();
      hist->GetXaxis()->SetRangeUser(500,1200);
      gPad->SetLogy();


    }
  TCanvas *mycan6 = (TCanvas*)gROOT->FindObject("Mycan6");
  if(!mycan6)
    {
      mycan6 = new TCanvas("Mycan6","HG Raw 6",1200,1200);
      mycan6->Divide(4,4,0.000001,0.000001);
    }

  
  for(int i=16;i<32;i++)
    {

      mycan6->cd(i+1-16);
      outstring.str("");
      outstring << "rus/Rrings/RusRingR_"<<i;
      name = outstring.str();
      TH1I *hist = (TH1I*)gROOT->FindObject(Form("RRing%i",i));
      if(!hist)
	{
	  hist = (TH1I*)in->Get(name.c_str())->Clone(Form("RRing%i",i));
	}

      hist->Draw();
      hist->GetXaxis()->SetRangeUser(500,1200);
      gPad->SetLogy();


    }



  in->Close();
  return;
}
