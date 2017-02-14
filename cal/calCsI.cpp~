#include <iostream>
#include <fstream>
using namespace std;




void calCsI()
{


  ofstream thing = ("cal/CsI-precal.cal");
  if (thing.is_open())
    {
      ostringstream outstring;
      string name;
      
      int useme;
      int useme1;
      int useme2;
      Double_t mean;
      
      TH1I * use;
      
      for(int i =0;i<32;i++)
	{
	  
	  
	  outstring.str("");
	  outstring << "CsI//CsIRaw/ECsI_" << i; //for a for loop
	  name = outstring.str();
	  use = (TH1I*)_file0->Get(name.c_str());
	  useme = use->GetMaximumBin();
	  useme = (use->GetBinWidth(useme))*useme;
	  useme1 = useme-20;
	  useme2 = useme+20;
	  use->Fit("gaus","","",useme1,useme2);
	  mean = gaus->GetParameter(1);
	  thing << i << " "  << mean << endl;


	}

    }
  else {cout << "Unable to open file" << endl;}
  thing.close()



  return;

}
