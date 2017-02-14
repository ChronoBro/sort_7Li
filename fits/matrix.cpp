#include "matrix.h"


matrix::matrix(int rows0, int columns0)
{
  rows = rows0;
  columns = columns0;
  C = new float*[rows];
  for(int i=0;i<rows;i++)
    {C[i] = new float[columns];}
  row_vect = new float[rows];
  col_vect = new float[columns];

  M = new float*[rows];
  for(int i=0;i<rows;i++)
    {M[i] = new float[columns];}

  if(rows==columns)
    {
      I =new float*[rows]; //identity matrix of size given, only works if square
      for(int i=0;i<rows;i++)
	I[i] = new float[columns];
      
      for(i=0;i<rows;i++)
	{
	  for(j=0;j<columns;j++)
	    {
	      if(i==j)I[i][j]=1.;
	      else I[i][j]=0.;
	    }
	}
    }

  for(i=0;i<rows;i++)
    {
      for(j=0;j<columns;j++)
	{
	  C[i][j]=0.;
	  M[i][j]=0.;
      	}
    }
  
}

matrix::~matrix()
{
  /*
  for(int i=0;i<rows;i++)
    {
      delete [] C[i];
    }
  delete [] C;
  delete [] row_vect;
  delete [] col_vect;

  for(int i=0;i<rows;i++)
    {
      delete [] I[i];
    }
  delete [] I;
  */
}

float ** matrix::mult(float ** A)
{
  for(i=0;i<rows;i++)
    {
      for(j=0;j<columns;j++)
	{
	  for(k=0;k<rows;k++)
	    {
	      M[i][j]+=C[i][k]*A[k][j];
	    }
	}      
      /*
      //cout << "i = " << i << endl;
      for(j =0; j < columns;j++)
	{row_vect[j] = C[i][j];}//cout << "row_vector_" << j << " = "<< row_vect[j] << endl;}
      //cout << "row_vector_" << j << " = "<< row_vect[j] << endl;

      for(j=0;j< columns;j++)
	{
	  //cout << "j = " <<  j << endl;
	  for(k=0;k<rows;k++)
	    {col_vect[k]=A[k][j];}//cout << "col_vector_" << k << " = "<< col_vect[k] << endl;}

	  //dot row and column vector to get value at C[i][j]
	  use=0;
	  for(l=0;l<columns;l++)
	    {use = col_vect[l]*row_vect[l]+use;}

	  C[i][j]=use;
	}
      */
    }
  return M;
}

float ** matrix::add(float ** A)
{
  for(i=0;i<rows;i++)
    {
      for(j=0;j<columns;j++)
	{
	  C[i][j] = C[i][j]+A[i][j];
	}
    }
  return C;
}

float ** matrix::sub(float **A)
{
  for(i=0;i<rows;i++)
    {
      for(j=0;j<columns;j++)
	{
	  C[i][j]= C[i][j]-A[i][j];
	}
    }
  return C;
}

float * matrix::vect_mult(float * v)
{
  for(i=0;i<rows;i++)
    {
      for(j=0;j<columns;j++)
	{
	  col_vect[i]+= C[i][j]*v[j];
	}
      /*
      for(j =0; j < columns;j++)
	{row_vect[j] = C[i][j];}
      
      for(l=0;l<columns;l++)
	{use = v[l]*row_vect[l]+use;}
      
      col_vect[i]=use;
      */
    }
  return col_vect;
}

float ** matrix::scale(float num)
{
  for(i=0;i<rows;i++)
    {
      for(j=0;j<columns;j++)
	{
	  C[i][j]= C[i][j]*num;
	}
    }
  return C;

}
