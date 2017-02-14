{
  TObject *obj=gPad->WaitPrimitive("CUTG","CutG");
  CUTG->SetName("bananas");
  bananas->Print();
  int n = bananas->GetN();
  double *x = bananas->GetX();
  double *y = bananas->GetY();
  n = n-1;
  //open file for output of bananas
  ofstream outfile("line.dat",ios::out);
  outfile << n << endl;
  for (int i=0;i<n;i++)outfile << *x++ << " " << *y++ << 
    endl;
  outfile.close();
  delete obj;
}
