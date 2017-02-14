#include <iostream>
#include <fstream>
using namespace std;

void trendCsI()
{
  int i;
  int j;
  int channel[32];
  float a[32];
  float b[32];
  float c[32];
  float d[32];
  float e[32];
  float f[32];
  float slope;
  float intercept;
  float energy[4];
  energy[0] = 37.57;
  energy[1] = 25.141;
  energy[2] = 12.012;
  energy[3] = 21.624;
  float adcChan[4];

  ofstream ofile0("cal/7LiTAMU-H.cal");
  ofstream ofile1("cal/7LiTAMU-He.cal");


  ifstream file0("cal/precalCsI-a-Al-16.cal");
  ifstream file1("cal/precalCsI-a-Au-20.cal");
  ifstream file2("cal/precalCsI-d-Al-16.cal");
  ifstream file3("cal/precalCsI-d-Al-8.cal");
  ifstream file4("cal/precalCsI-p-Al-16.cal");
  ifstream file5("cal/precalCsI-p-Au-20.cal");
  

  TGraph *p;
  TF1 *fit;

  for (i=0;i<32;i++)
    {

      file0 >> j >> a[i];
      file1 >> j >> b[i];
      file2 >> j >> c[i];
      file3 >> j >> d[i];
      file4 >> j >> e[i];
      file5 >> j >> f[i];
      cout << j << a[i] << endl;

    }

  for (i=0;i<32;i++)
    {
      
      slope=(85.925-48.358)/(b[i]-a[i]);
      intercept = 85.925-slope*b[i];
      
      ofile1 << 0<< "\t" << i<<"\t" << slope<<"\t" << intercept << endl;
    }
  
  for (i=0;i<32;i++)
    {
     
      adcChan[0]= c[i];
      adcChan[1]= d[i];
      adcChan[2] = e[i];
      adcChan[3] = f[i];

      
      p = new TGraph(4,adcChan,energy);
      p->Fit("pol1");
      fit = p->GetFunction("pol1");
      slope = fit->GetParameter(1);
      intercept = fit->GetParameter(0);

      ofile0 << 0<<"\t" << i<<"\t" << slope<< "\t" << intercept<<"\t" << endl;


 
    }








       





      
      



















  return;
}
