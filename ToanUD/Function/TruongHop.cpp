#include <iostream>
#include <math.h>
#include <iomanip>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

MatrixXd inputMatrix(int row, int col)
{
    MatrixXd A(row, col);
    for (int i = 0; i < A.rows(); i++)
      for (int j = 0; j < A.cols(); j++)
      {
		cout << "x[" << i << "]["<< j << "]= ";
		cin >> A(i, j);
	  }
    return A;
}

void printMatrix(MatrixXd matrix)
{
    for (int i = 0; i < matrix.rows(); i++)
    {
        for (int j = 0; j < matrix.cols(); j++)
        {
            cout << setw(11) << setprecision(5) << fixed << matrix(i, j) ;
        }
        cout << endl;
    }
}

void printMatrixRow(MatrixXd matrix, int row)
{
    for (int j = 0; j < matrix.cols(); j++)
    {
        cout << setw(11) << setprecision(5) << fixed << matrix(row, j) ;
    }
    cout << endl;
}

MatrixXd mutiplyMatrix(MatrixXd a, MatrixXd b)
{
    if (a.cols() != b.rows())
      return MatrixXd();
    else
    {
      MatrixXd temp(a.rows(), b.cols());
      for (int i = 0; i < a.rows(); i++)
      {
        for (int j = 0; j < b.cols(); j++)
        {
          double sum = 0;
          for (int k = 0; k < a.cols(); k++)
            sum += a(i, k) * b(k, j);
          temp(i, j) = sum;
        }
      }
      return temp;
    }
}
int main()
{
    int size;
    cout << "Size: "; cin >> size;
    MatrixXd P = inputMatrix(size, size);
    cout << "Display matrix P:" << endl;
    printMatrix(P);
    
    int n, st, end;
    MatrixXd Pn;
    Pn = P;
    cout << "Enter n steps: "; cin >> n;
    cout << "Probability after " << n << " steps: "<< endl;
	for (int i = 1; i <= n; i++) 
	{
        if(i == n) 
		{
        	printMatrix(Pn);
        	break;
        }
        Pn = mutiplyMatrix(Pn, P);
    }
    cout << endl << "Enter state to start: "; cin >> st;
    cout << "Enter state to end: "; cin >> end;
    cout << "Max probability in state " << end << ", after " << n << " steps, start from state " << st << " is: " << Pn(st-1, end-1);
    return 0;
}

