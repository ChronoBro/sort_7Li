
Double_t erf( Double_t x)
{
  Double_t t = 1./(1. +.47047*x);
  Double_t sum = 0.3480242*t  -.0958798*pow(t,2) + .7478556*pow(t,3);
  sum *= exp(-pow(x,2));
  //cout << x << " " << 1-sum << endl;
  return 1 - sum;
}


Double_t erfc(Double_t x)
{
  if (x < 2.) return 1-erf(x);
  return exp(-pow(x,2))/x/sqrt(3.14159); 
}

Double_t responce(Double_t x, Double_t sigma, Double_t k)
{
  if (x > 100.*sigma) return 0.;

  Double_t fact = TMath::Erfc((k*x+pow(sigma,2))/(sqrt(2.)*k*sigma));
  fact *= exp((2.*k*x+pow(x,2))/(2.*pow(k,2)))*sigma*sqrt(3.14159/2.);
  return fact;
}

Double_t responces(Double_t x, Double_t sigma, Double_t k)
{
  // cout << " x= " << x << " sigma= " << sigma << " k= " << k << endl;
  // cout << exp(x/k) *TMath::Erfc(x/sqrt(2.)/sigma + sigma/sqrt(2.)/k) << endl; 
  return exp(x/k) *TMath::Erfc(x/sqrt(2.)/sigma + sigma/sqrt(2.)/k); 
}

Double_t Gaussian(Double_t x, Double_t sigma)
{
  if (x > 10.*sigma) return 0.;
  return 1/1.722/sigma*exp(-pow(x/sigma,2)/2.);
}


Double_t fitPeaks( Double_t *x, Double_t *par)
{
  int Npeaks = 11;
  Double_t y = x[0]*par[1]+par[0];
  Double_t sum = 0.;
  for (int i=0;i<Npeaks;i++)
    {
       sum += par[2]*par[5+Npeaks+i]*responces(y-par[5+i],par[3],par[4]); 
      // sum += par[2]*par[5+Npeaks+i]*Gaussian(y-par[5+i],par[3]); 
   }

  return sum;
}


void fit(int itele, int ifstrip, double maxPeak, double * x)
{
  ifstream File("FrontE_si.Cf249");
  if (File.is_open() != 1) cout << "file not opened" << endl; 
  int const Npeaks = 11;
  double energy[Npeaks];
  double intensity[Npeaks]= {0.03,0.2,3.7,0.26,84.4,1.,2.8,4.,0.24,1.11,2.17};
  char line[80];
  File.getline(line,80);
  cout << "line= " << line << endl;

  if (itele > 3 || itele < 0) return;
  if (ifstrip > 31 || ifstrip < 0) return; 
  int Itele,Ifstrip;
  for (;;)
      {

	File >> Itele >> Ifstrip;
        for (int ipeak=0;ipeak<Npeaks;ipeak++) File >> energy[ipeak];
	// cout << Itele << " " << Ifstrip << endl;
        if (Itele == itele && Ifstrip == ifstrip) break;
      }

  File.close();
  File.clear();
  for (int ipeak=0;ipeak<5;ipeak++) cout << energy[ipeak] << " " ;
  cout << endl;
  for (int ipeak=5;ipeak<Npeaks;ipeak++) cout << energy[ipeak] << " " ;
  cout << endl;



  TF1 *func = new TF1("fitPeaks",fitPeaks,maxPeak-26,maxPeak+60,5+2*Npeaks);

  func->SetParameter(0, 0);
  double scale  = .0088;
  func->SetParameter(1,scale);
  func->SetParameter(2,300.);
  func->SetParameter(3,.0245);
  func->FixParameter(4,.0245);
  for (int i=0;i<Npeaks;i++)
    {
      func->FixParameter(5+i,energy[i]);
      func->FixParameter(5+Npeaks+i,intensity[i]);
    }


  double offset =  energy[4]- maxPeak*scale;
  cout << "offset= " << offset << endl;
  func->FixParameter(0,offset);



  char name[10];
  sprintf(name,"B%d_%d",itele,ifstrip);
  TH1S *hist = (TH1S*)f.Get(name); 



  //func->Draw("same");
  hist->Fit(func,"R");

  double par[30];
  func->GetParameters(par);

  cout << par[0] << " " << par[1] << " " << par[3]*2.35*1000. << endl;

  x[0] = par[0];
  x[1] = par[1];
  x[2] = par[3];
  x[3] = maxPeak;
  x[4] = par[3]*2.35*1000.;

}

void all()
{
ifstream FileFront("sourceFront.dat");
 ofstream FitFront("FitFront.dat");
int itele,istrip,ipeak;
double channel, energy;
 double x[5];
 int iteleOld = -1;

 TCanvas *canvas[4];
 char name[5];
for (;;)
  {
    FileFront >> itele >> istrip >> ipeak;
    if (FileFront.eof()) break;
    if (itele != iteleOld)
      {
	cout << " " << itele << endl;
	sprintf(name,"tel%d",itele);
	canvas[itele] = new TCanvas(name,name);
	canvas[itele]->Divide(4,8);
      }
    iteleOld = itele;
    canvas[itele]->cd(istrip+1);
    FileFront >> channel >> energy;
    cout << itele << " " <<istrip << " " << channel << endl;

     sprintf(name,"F%d_%d",itele,istrip);
    TH1S *hist =(TH1S*)f.Get(name);
    //hist->SetRange(channel-100.,channel+100.);
    hist->Draw();
    fit(itele,istrip,channel,x);
    
      FitFront<< itele<< " " << istrip << " " 
      << x[0] << " " << x[1] << " " << x[2] << " " << x[2] <<
      " " << channel << " " << x[2] << endl;
    
    
  }
}
