#include <iostream>
#include <fstream>
#include <string>
using namespace std;




void calCsI()
{


  ofstream  thing("cal/precalCsI-a-Al-16.cal");
  if (thing.is_open())
    {
      ostringstream outstring;
      string name;
      
      int useme;
      int useme1;
      int useme2;
      Double_t mean;
      
      TH1I * use;
      TF1 * fit;
      int i;
      
      for(i=0;i<32;i++)
	{
	  
	  
	  outstring.str("");
	  outstring << "CsI/CsIRaw/ECsI_" << i; //for a for loop
	  name = outstring.str();
	  use = (TH1I*)_file0->Get(name.c_str());
	  useme = use->GetMaximumBin();
	  useme = (use->GetBinWidth(useme))*useme;
	  useme1 = useme-20;
	  useme2 = useme+20;
	  use->Fit("gaus","","",useme1,useme2);
	  fit = use->GetFunction("gaus");
	  mean = fit->GetParameter(1);
	  thing << i << "\t" <<mean << endl;


	}

    }
  else {cout << "Unable to open file" << endl;}
  thing.close();



  return;

}
