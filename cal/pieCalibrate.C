#include <iostream>
#include <fstream>
#include "TGraph.h"
using namespace std;


void pieCalibrate()
{

  ostringstream outstring;
  string name;

  outstring.str("");
  outstring << "/home/lithium7/unpacker/cal/rPies.cal";

  name = outstring.str();
  //name = name +".cal";
  ofstream ofile0(name.c_str());
  if(!ofile0.is_open()){cout << "ERROR opening " << name << endl;return;}
  
  outstring.str("");
  outstring << "/home/lithium7/unpacker/cal/rPies.dat";
  name = outstring.str();
  //name = name + ".cal";
  ifstream ifile0(name.c_str());
  if(!ifile0.is_open()){cout << "ERROR opening " << name << endl; return;}
  
  
  int i;
  int j;
  int k;
  int n=4; //number of peaks
  int cycles=64; //number of blocks
  float channel[256];
  float energy[128];
  float use1[4];
  float use2[4]={3.182,5.139,5.45,5.79498}; //alpha peaks in mixed source
  TGraph * gr;
  TF1 * fit;
  float slope;
  float intercept;
  float quad;
  
  for (i=0;i<n*cycles;i++)
    {
      
      ifile0 >> channel[i];//>>  energy [i] ;
      
    }
  //cout << channel[0] << endl;
  //cout << energy[0]<< endl;;
  

  //how to read channel files
  i=0;
  for(j=1;j<=cycles;j++)
    {
      for(k=0;i<j*n;i++)
	{
	  use1[k]=channel[i];
	  //use2[k]=energy[i];
	  k++;
	  cout << "i = " << i << endl;
	  cout << "k = " << k << endl;
	  cout << "channel = " << channel[i] <<endl;
	  cout << "energy = " << use2[i] << endl;
	}
      
      gr = new TGraph(n,use1,use2);
      gr->Fit("pol1");
      fit = gr->GetFunction("pol1");
      //quad = fit->GetParameter(2);
      slope = fit->GetParameter(1);
      intercept = fit->GetParameter(0);
      ofile0 << 0 << "\t" <<  j-1  << "\t" <<slope << "\t" << intercept <<   endl;
      
    }
  
  
  ifile0.close();
  ofile0.close();
 

}
