void getCsICal()
{
  
  ifstream Lfile("CsIdats/CsI_55N.dat");
  ifstream Hfile("CsIdats/CsI_75N.dat");
  ifstream Proton("CsI_Proton_New.cal");
  if(!Lfile || !Hfile || !Proton)
    {
      cout << "Couldn't find the data" << endl;
      return;
    }
  
  float posL[56] = {0.};
  float posH[56] = {0.};
  float Pslope[56] = {0.};
  float Pinter[56] = {0.};
  //float energy[2] = {52.0077,71.4806}; //Protons
  //float energy[2] = {257.54,357.01}; //Lithium-6
  float energy[2] = {540.245,845.7856}; //Nitrogen-14
  //  float energy[2] = {537.694,570.197}; //Oxygen-16
  //ofstream ofile("CsI_Proton_New.cal");
  //ofstream ofile("CsI_Lithium6.cal");
  ofstream ofile("CsI_Nitrogen_New.cal");
  //ofstream ofile("CsI_Oxygen_New.cal");

  int idum = 0;
  int idum2 = 0;
  float fdum =0.;
  float fdum2 =0.;

  for(;;)
    {
      if(Proton.eof())break;
      Proton >> idum >> idum2 >> fdum >> fdum2;
      Pslope[idum2] = fdum;
      Pinter[idum2] = fdum2;

    }
  Proton.close();
  for(;;)
    {
      if(Lfile.eof())break;
      Lfile >>idum >> fdum;
      posL[idum] = fdum;
    }
  for(int j =0;j<56;j++)
    {
      if(Hfile.eof())break;
      Hfile >>idum >> fdum;
      posH[idum] = fdum;
    }
  
  float slope = 0;
  float inter = 0;
  int N = 0;
  float aveS = 0;
  float aveI = 0;
  for(int ii = 0; ii<56;ii++)
    {
      //  cout << ii << " " << posL[ii] << " " << posH[ii] << endl;
      if(posH[ii] ==-1 || posL[ii]==-1)
	{
	  slope =1;
	  inter = 0;
	}
      else
	{
	  fdum = posL[ii]*Pslope[idum]+Pinter[idum];
	  fdum2 = posH[ii]*Pslope[idum]+Pinter[idum];
	  slope = (energy[1]-energy[0])/(fdum2-fdum);
	  inter = energy[0] - slope*fdum;
	  //slope = (energy[1] - energy[0])/(posH[ii]-posL[ii]); //proton
	  //inter = energy[0] - posL[ii]*slope; //proton
	  N++;
	  aveS += slope;
	  aveI += inter;
	}
      // cout << slope << " " << inter << endl;
      ofile << 0 << " "  << ii << " " << slope;
      ofile << " " << inter << endl;
      
    }
  
  cout << aveS/(float*)N << " " << aveI/(float*)N << endl;
  Lfile.close();
  Hfile.close();
  ofile.close();
  return;
}
