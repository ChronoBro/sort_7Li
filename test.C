void test()
{


  int iRpie =-1;
  int rold[64] ={0};
  int rnew[64] = {0};
  for(int chipNum = 1;chipNum<3;chipNum++)
    {
      for(int chanNum = 0;chanNum<32;chanNum++)
	{
	  int i = chanNum + 32*(chipNum-1);
	  if(chipNum ==1)
	    {
	      if(chanNum <16)
		{
		  iRpie = 15-chanNum;
		}
	      else
		{
		  iRpie = 47-chanNum;
		}
	    }
	  if(chipNum ==2)
	    {
	      iRpie = 63 - chanNum;
	    }
	  rnew[i] = iRpie;
	  // cout << chipNum << " " << chanNum << " " << iRpie << endl;
	}
    }

  for(int chipNum = 1;chipNum<3;chipNum++)
    {
      for(int chanNum = 0;chanNum<32;chanNum++)
	{
	  int i = chanNum + 32*(chipNum-1);
  
	  if(chipNum ==1)
	    {
	      iRpie = 31 - chanNum;
	    }
	  if(chipNum ==2)
	    {
	      if(chanNum < 16)
		{
		  iRpie = 15 - chanNum + 32;
		}
	      else 
		{
		  iRpie = 31 - chanNum + 48;
		}
	    }
	  rold[i] = iRpie;
	  // cout << chipNum << " " << chanNum << " " << iRpie << endl;

	}
    }

  for(int i =0;i<64;i++)
    {
      // cout << i << " " << rold[i] << " " << rnew[i] << endl;
    }

  ifstream in("cal/rPies.cal.save");
  if(!in.is_open())
    {
      cout <<"No data" << endl;
      return;
    }

  int itele = -1;
  int ichan = -1;
  float slope[64] = {0.};
  float inter[64] = {0.};
  for(int i=0;i<64;i++)
    {
      in >> itele >> ichan >> slope[i] >> inter[i];
      // cout << slope[i] << " " << inter[i] << endl;
    }


  float slopenew[64] = {0.};
  float internew[64] = {0.};
  for(int i =0;i<64;i++)
    {
      int aa = rnew[i];
      int bb = rold[i];
      slopenew[aa] = slope[bb];
      internew[aa] = inter[bb];

      cout << aa << " " << bb << endl;
      cout << slopenew[aa] << " " << internew[aa] << endl;

    }

  ofstream out("rPies.cal");

  for(int i = 0;i<64;i++)
    {
      out << 0 << " " << i << " " << slopenew[i] << " " << internew[i] << endl;
    }

  out.close();


  return;
}
