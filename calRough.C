{
  TFile file("sort.root");


  ofstream ofile("a.dat");


  ostringstream outstring;
  string name;
  //  for(int itele =0;itele <;itele++)
  //  for(int istrip = 0;istrip<32;istrip++)
  //	  ofile << itele << " " << istrip << " " << 1 << " " << 0 << endl;

  TCanvas *mycan = new TCanvas("mycan","",1000,600);
  for (int itele=0;itele<=1;itele++)
    {
      for (int istrip=0;istrip<48;istrip++)
	{
          outstring.str("");
          outstring<< "S2/S2rings/S2RingR_"<<istrip;
	  name = outstring.str();
          TH1I * hist = (TH1I*)file.Get(name.c_str());
	  hist->GetXaxis()->SetRangeUser(350,900);
          hist->Draw();
	  mycan->Modified();
	  mycan->Update();

	  TMarker * mark;
          double low,high;
          mark = (TMarker*) mycan->WaitPrimitive("TMarker");
          low = mark->GetX();
	  delete mark;
          mark = (TMarker*) mycan->WaitPrimitive("TMarker");
          high = mark->GetX();
	  double slope = (5.148-3.185)/(high-low);
          double intercept = 3.185 - slope*low;
	  ofile << itele << " " << istrip << " " << slope << " " << intercept << endl;
	  cout << itele << "." << istrip << " " << low << " " << high << endl;
	  
	 
	}
    }

  ofile.close();
}
