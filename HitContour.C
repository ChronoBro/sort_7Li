void HitContour()
{

 TCanvas * mycan1 = new TCanvas("mycan1","mycan1",900,600);
 TFile * data = new TFile("sort.root");

 TH2F * hitmap = (TH2F*)data->Get("/corr/Li7/HitMap")->Clone("6");
 // cout << "here" << endl;

 for(int i=1;i<=250;i++)
   {
     //h1 = hitmap->GetXaxis()->GetBinCenter(i);
     //cout << "here2" << endl;
     for(int j=1;j<=250;j++)
       {
	 //h2 = hitmap->GetYaxis()->GetBinCenter(j);
	 //cout << "here1" << endl;
	 float check = hitmap->GetBinContent(i,j);
	 //if(check>90 && check < 110)hitmap->SetBinContent(i,j,10000);
	 //cout << "f2(" << i << "," << j << ") = " << f2->Eval(h1,h2,0,0) << endl;
	 //if(check>48 && check < 52)hitmap->SetBinContent(i,j,10000);
	 //if(check>8 && check < 12)hitmap->SetBinContent(i,j,10000);
       }
   }
 
 //hitmap->GetZaxis()->SetNdivisions(200);
 gStyle->SetOptStat(0);
 mycan1->SetLogz();
 hitmap->Draw("colz");

 return;
}
