{
  TFile file("../bkg.root");


  ofstream ofile("ceasar_bkg.dat");
  TFile file2("ceasar_fits_bkg.root","recreate");


  ostringstream outstring;
  string name;

  int p1= 35, p2=50; //+- fit limits up to 2 peaks. May be different.
  int const num_par = 5; //number of peaks times 2(pol1)+3(gaus).

  int ent = 0;


  //  for (int ic=0;ic<13;ic++)
  for(int ic=0;ic<196;ic++)
    {
   
      outstring.str("");
      if (ic < 10)      outstring << "ceasar/raw/EC00" << ic;
      else if (ic < 100) outstring << "ceasar/raw/EC0" << ic;
      else outstring << "ceasar/raw/EC" << ic;
      name = outstring.str();
      TH1I * hist = (TH1I*)file.Get(name.c_str());
      hist->GetXaxis()->SetRangeUser(400,1800);
      ent = hist->GetEntries();

      cout << ent << endl;
      hist->Draw();
      c1->Modified();
      c1->Update();
      if(ent <50)
	{
	  ofile << ic << " " << -1 << " "  << -1 << endl;
	  cout << ic << " Only has " << ent << " Entries. " << endl;
	  continue;
	}
      else
	{
        
	  TMarker * mark;
	  mark=(TMarker*)c1->WaitPrimitive("TMarker"); //Get the Background limits
	  int bkg_lo = mark->GetX();
	  delete mark;  
	  mark=(TMarker*)c1->WaitPrimitive("TMarker");
	  int bkg_hi = mark->GetX();
	  delete mark;
	  mark=(TMarker*)c1->WaitPrimitive("TMarker"); // Get the 1st peak initial guess
	  peak1 = mark->GetX();
	  delete mark;
    
	  mark=(TMarker*)c1->WaitPrimitive("TMarker"); //Get the Background limits
	  int bkg_lo2 = mark->GetX();
	  delete mark;  
	  mark=(TMarker*)c1->WaitPrimitive("TMarker");
	  int bkg_hi2 = mark->GetX();
	  delete mark;
	  mark=(TMarker*)c1->WaitPrimitive("TMarker"); // Get the 1st peak initial guess
	  peak2 = mark->GetX();
	  delete mark;


	  double par[num_par] = {0.};
          double out[num_par] = {0.}; 
	  double par2[num_par] = {0.};
          double out2[num_par] = {0.}; 
	  
	  int peak1_lo = peak1 - p1, peak1_hi = peak1 + p1; // Peak center and limits
	  int peak2_lo = peak2 - p2, peak2_hi = peak2 + p2; // Peak center and limits
 	
	  TF1 *l1 = new TF1("l1", "pol1", bkg_lo, bkg_hi);
	  TF1 *g1 = new TF1("g1", "gaus", peak1_lo,peak1_hi);
	  TF1 *l2 = new TF1("l2", "pol1", bkg_lo2, bkg_hi2);
	  TF1 *g2 = new TF1("g2", "gaus", peak2_lo,peak2_hi);


	  TF1 *total = new TF1("total", "pol1(0)+gaus(2)", bkg_lo,bkg_hi);
	  TF1 *total2 = new TF1("total2", "pol1(0)+gaus(2)", bkg_lo2,bkg_hi2);

	  hist->Fit(l1,"R");
	  hist->Fit(g1,"R+");
	  hist->Fit(l2,"R+");
	  hist->Fit(g2,"R+");

	  l1->GetParameters(&par[0]);
	  g1->GetParameters(&par[2]);
	  l2->GetParameters(&par2[0]);
	  g2->GetParameters(&par2[2]);

	  total->SetParameters(par);
	  hist->Fit(total,"R");
	  total->GetParameters(out);

	  total2->SetParameters(par2);
	  hist->Fit(total2,"R+");
	  total2->GetParameters(out2);
	  cout << total->GetParameter(3) << " " << out[3] << endl;


	  // double slope = (2.615-1.460)/(out2[3]-out[3]);
	  //double intercept = 1.460 - slope*out[3];
	  // ofile << ic  << " " << slope << " " << intercept << endl;
	  ofile << ic << " " << out[3] << " " << out2[3] << endl;

	  outstring.str("");
	  outstring << "K40_" << ic;
	  name = outstring.str();
	  total->SetName(name.c_str());

 	  outstring.str("");
 	  outstring << "Th228_" << ic;
 	  name = outstring.str();
 	  total2->SetName(name.c_str());
	  file2->cd();
	  total->Write();
	  total2->Write();



        }
      
      
   }
  
  ofile.close();
}
