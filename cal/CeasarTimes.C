void CeasarTimes()
{


  TFile myfile("../sort.root");
  // ofstream ofile("ceasar_time.cal");

  ostringstream outstring;
  string name;

  double Peaks[192] = {0.};
  double p1= 35.;
  int const num_par = 8;

  for(int ic = 0;ic<192;ic++)
    {
      myfile.cd();
      outstring.str("");
      if (ic < 10)      outstring << "ceasar/timeC/TC00" << ic;
      else if (ic < 100) outstring << "ceasar/timeC/TC0" << ic;
      else outstring << "ceasar/timeC/TC" << ic;
      name = outstring.str();

      TH1I *myhist = (TH1I*)myfile.Get(name.c_str());


      int N = myhist->GetEntries();

      cout << ic << " "  << N << endl;
      myhist->Draw();
      myhist->GetXaxis()->SetRangeUser(10,1000);
      c1->Modified();
      c1->Update();
      if (N > 10)
	{ 
	  TMarker * mark;
	  mark=(TMarker*)c1->WaitPrimitive("TMarker"); 
	  double bkg_lo = mark->GetX();
	  delete mark;  
	  mark=(TMarker*)c1->WaitPrimitive("TMarker");
	  double bkg_hi = mark->GetX();
	  delete mark;
	  mark=(TMarker*)c1->WaitPrimitive("TMarker"); 
	  double peak1 = mark->GetX();
	  delete mark;
	  
	  double par[num_par] = {0.};
	  double out[num_par] = {0.}; 
	  
	  double peak2 = peak1 - 50.;
	  double peak1_lo = peak1 - p1,peak1_hi = peak1 + p1;
	  double peak2_lo = peak2 - p1,peak2_hi = peak2 + p1;
	  TF1 *l1 = new TF1("l1", "pol1", bkg_lo, bkg_hi);
	  TF1 *g1 = new TF1("g1", "gaus", peak1_lo,peak1_hi);
	  TF1 *g2 = new TF1("g2", "gaus", peak2_lo,peak2_hi);

	  g1->FixParameter(1,peak1);
	  g2->FixParameter(1,peak2);
	  
	  TF1 *total = new TF1("total", "pol1(0)+gaus(2)+gaus(5)"
			       ,bkg_lo,bkg_hi);
	  myhist->Fit(l1,"R");
	  myhist->Fit(g1,"R+");
	  myhist->Fit(g2,"R+");
	  l1->GetParameters(&par[0]);
	  g1->GetParameters(&par[2]);
	  g2->GetParameters(&par[5]);
	  total->SetParameters(par);
	  myhist->Fit(total,"R");
	  total->GetParameters(out);
	  total->Draw("same");
	  c1->Modified();
	  c1->Update();
	  
	  Peaks[ic] = out[3];
	  cout << Peaks[ic] << endl;
	  
	  mark = (TMarker*)c1->WaitPrimitive("TMarker");
	  delete mark;
	  
	}
    }

  int ref =12;

  for(int ic =0;ic<192;ic++)
    {

      if(Peaks[ic] < 10)
	//ofile << 0 << " " << ic << " " << 1 << " " << 0 << endl;
      else
	{
	  double offset = Peaks[ref] - Peaks[ic];
	  //ofile << 0 << " " << ic << " " << 1 << " " << offset << endl;
	}

    }




  myfile.Close();
  // ofile.close();
  return;
}
