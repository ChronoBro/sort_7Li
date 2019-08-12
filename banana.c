int banana(){

  //OK now program actually deletes the object and lets me rerun

  //TObject* obj;// = new TObject();
  //obj = (TObject*)gPad->WaitPrimitive("CUTG","CutG");
  //TCutG* obj = (TCutG*)gPad->WaitPrimitive("CUTG","CUTG");
  TCutG* obj = (TCutG*)gPad->WaitPrimitive("CUTG","CutG");
  //CUTG->SetName("bananas");
  obj->SetName("bananas");
  //cout << "WTF" << endl;
  //bananas->Print();
  obj->Print();
  //int n = bananas->GetN();
  int n = obj->GetN();
  //double *x = bananas->GetX();
  double *x = obj->GetX();
  //double *y = bananas->GetY();
  double *y = obj->GetY();
  //open file for output of bananas
  ofstream outfile("banana.dat",ios::out);
  outfile << n << endl;
  for (int i=0;i<n;i++)outfile << *x++ << " " << *y++ << 
    endl;
  outfile.close();
  //bananas->Delete();
  //obj->Delete();
  delete obj;

  return 0;
}
