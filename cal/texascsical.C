void texascsical()
{

  ifstream in("texascsi.txt");
  if(!in.is_open())
    {
      cout << "No data!" << endl;
      return;
    }

  float peak[2][32][3] = {0.};  //channel


  int icsi = -1;

  float slope[2][32]  ={0.};
  float inter[2][32] = {0.};

  float energyt[3] = {29.3,15.4,8.4}; //MeV
  float energya[3] = {70.1,37.6,21.3}; //MeV

  char bogus[200];
  in.getline(bogus,200);

  for(;;)
    {
      in >> icsi >> peak[0][icsi][0] >> peak[0][icsi][1] >> peak[0][icsi][2];
      in >> peak[1][icsi][0] >> peak[1][icsi][1] >> peak[1][icsi][2];

      if(in.eof())
	break;


      //      cout << peak1[0][icsi] << " " << peak1[1][icsi] << endl;
    }

  TCanvas *mycan = (TCanvas*)gROOT->FindObject("mycan");
  if(!mycan)
    {
      mycan = new TCanvas("mycan","",1000,800);
      mycan->Divide(8,4);
    }
  TCanvas *mycan1 = (TCanvas*)gROOT->FindObject("mycan1");
  if(!mycan1)
    {
      mycan1 = new TCanvas("mycan1","",1000,800);
      mycan1->Divide(8,4);
    }


  ofstream outt("triton.cal");
  for(int i = 0;i<32;i++)
    {
      mycan->cd(i+1);
      TGraph *mygraph = new TGraph(3,peak[0][i],energyt);
      mygraph->Draw("AP");
      mygraph->SetMarkerStyle(20);

      TF1 *fit = new TF1("fit","pol1",0,1200);

      mygraph->Fit(fit,"rQ");
      cout << fit->GetParameter(0) << " " << fit->GetParameter(1) << endl;
      outt << 0 << " " << i << " " << fit->GetParameter(1) << " ";
      outt << fit->GetParameter(0) << endl; 

    }

  ofstream outa("alpha.cal");
  for(int i = 0;i<32;i++)
    {
      mycan1->cd(i+1);
      TGraph *mygraph1 = new TGraph(3,peak[1][i],energya);
      mygraph1->Draw("PA");
      mygraph1->SetMarkerStyle(21);

      TF1 *fit = new TF1("fit","pol1",0,2000);

      mygraph1->Fit(fit,"rQ");
      cout << fit->GetParameter(0) << " " << fit->GetParameter(1) << endl;
      outa << 0 << " " << i << " " << fit->GetParameter(1) << " ";
      outa << fit->GetParameter(0) << endl; 


    }
	


  return;

}
