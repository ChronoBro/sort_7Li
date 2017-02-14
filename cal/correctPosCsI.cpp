#include <iostream>
#include <fstream>
#include "TGraph.h"
using namespace std;



void correctPosCsI ()
{

  int no=0;
  ostringstream outstring;
  string name;

  //making this just change Russian calibrations for now
  //never mind previous comment, found mistake in energy calibrations....
  //never mind never mind
  //never mind never mind never mind
  for(no=0;no<32;no++)
    {
      outstring.str("");
      outstring << "/home/lithium7/unpacker/cal/blockCalCsid"<<no;

      name = outstring.str();
      name = name +".cal";
      ofstream ofile0(name.c_str());
      if(!ofile0.is_open()){cout << "ERROR opening " << name << endl;}
      
      outstring.str("");
      outstring << "/home/lithium7/unpacker/cal/posCorrectCal/channels_energy" << no;
      name = outstring.str();
      name = name + ".cal";
      ifstream ifile0(name.c_str());
      if(!ifile0.is_open())cout << "ERROR opening " << name << endl;
      

      int i;
      int j;
      int k;
      int n=4; //number of peaks
      int cycles=8; //number of blocks
      float channel[128];
      float energy[128];
      float use1[4];
      float use2[4];
      TGraph * gr;
      TF1 * fit;
      float slope;
      float intercept;
      float quad;
      
      for (i=0;i<32;i++)
	{
	  
	  ifile0 >> channel[i]>>  energy [i] ;
	  
	}
      //cout << channel[0] << endl;
      //cout << energy[0]<< endl;;
      
      i=0;
      for(j=1;j<=cycles;j++)
	{
	  for(k=0;i<j*n;i++)
	    {
	      use1[k]=channel[i];
	      use2[k]=energy[i];
	      k++;
	      cout << "i = " << i << endl;
	      cout << "k = " << k << endl;
	      cout << "channel = " << channel[i] <<endl;
	      cout << "energy = " << energy[i] << endl;
	    }
	  
	  gr = new TGraph(n,use1,use2);
	  gr->Fit("pol1");
	  fit = gr->GetFunction("pol1");
	  //	  quad = fit->GetParameter(2);
	  slope = fit->GetParameter(1);
	  intercept = fit->GetParameter(0);
	  ofile0 <<   slope << "\t" << intercept << endl;

	}
	  

      ifile0.close();
      ofile0.close();
    }

  for(no=0;no<32;no++)
    {
      outstring.str("");
      outstring << "/home/lithium7/unpacker/cal/blockCalCsiA"<<no;

      name = outstring.str();
      name = name +".cal";
      ofstream ofile0(name.c_str());
      if(!ofile0.is_open()){cout << "ERROR opening " << name << endl;}
      
      outstring.str("");
      outstring << "/home/lithium7/unpacker/cal/posCorrectCal/channels_energy" << no;
      name = outstring.str();
      name = name + "_a.cal";
      ifstream ifile0(name.c_str());
      if(!ifile0.is_open())cout << "ERROR opening " << name << endl;
      

      int i;
      int j;
      int k;
      int n=3; //number of peaks
      int cycles=8; //number of blocks
      float channel[128];
      float energy[128];
      float use1[4];
      float use2[4];
      TGraph * gr;
      TF1 * fit;
      float slope;
      float intercept;
      float quad;
      
      for (i=0;i<32;i++)
	{
	  
	  ifile0 >> channel[i]>>  energy [i] ;
	  
	}
      //cout << channel[0] << endl;
      //cout << energy[0]<< endl;;
      
      i=0;
      for(j=1;j<=cycles;j++)
	{
	  for(k=0;i<j*n;i++)
	    {
	      use1[k]=channel[i];
	      use2[k]=energy[i];
	      k++;
	      cout << "i = " << i << endl;
	      cout << "k = " << k << endl;
	      cout << "channel = " << channel[i] <<endl;
	      cout << "energy = " << energy[i] << endl;
	    }
	  
	  gr = new TGraph(n,use1,use2);
	  gr->Fit("pol1");
	  fit = gr->GetFunction("pol1");
	  //quad = fit->GetParameter(2);
	  slope = fit->GetParameter(1);
	  intercept = fit->GetParameter(0);
	  ofile0  <<  slope << "\t" << intercept << endl;

	}
	  

      ifile0.close();
      ofile0.close();
    }


}

