#include <iostream>
#include <math.h>
using namespace std;
const int max = 10;

void input(double a[][10], int h, int c)
{
	for(int i=1; i<=h; i++)
	{
		for(int j=1; j<=c; j++)
		{
			cout <<"a[" <<i <<"][" <<j <<"] = ";
			cin >>a[i][j];
		}
	}
}
void output(double a[][10], int h, int c)
{
	for(int i=1; i<=h; i++)
	{
		for(int j=1; j<=c; j++)
		{
			cout <<a[i][j] <<"\t";
		}
		cout <<"\n";
	}
}
bool checkMatrixDx(double a[][10], int n)
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			if(a[i][j] != a[j][i]) return false;
		}
	}
	return true;
}
void matranTamgiac(double a[][10], int n)
{
	double m;
	for(int c=1; c<n; c++) //cot
	{
		for(int h=c+1; h<=n; h++) //hang
		{
			m = a[h][c]/a[c][c];
			for(int k=c; k<=n; k++)
			{
				a[h][k] -= m*a[c][k];
			}
		}
	}	
}
double det(double a[][10], int n)
{
	double d=1;
	for(int i=1; i<=n; i++)
	{
		d*=a[i][i];
	}
	return d;
}
bool checkXdDuong(double a[][10], int n)
{
	double d[10][10];
	for(int k=1; k<=n; k++)
	{
		for(int i=1; i<=k; i++)
		{
			for(int j=1; j<=k; j++)
			{
				d[i][j] = a[i][j];
			}
		}
		matranTamgiac(d, k);
		if(det(d,k) <= 0) return 0;
	}
	return 1;
}

void cholesky(double a[][10], int n)
{
	double m[10][10], mT[10][10];
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			m[i][j] = 0;
		}
	}
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=i; j++)
		{
			double sum = 0;
			if(i==j) 
			{
				for(int k=1; k<j; k++)
				{
					sum += pow(m[j][k], 2);
				}
				m[j][j] = sqrt(a[j][j] - sum);
			}
			else
			{
				for(int k=1; k<j; k++)
				{
					sum += m[i][k]*m[j][k];
				}
				m[i][j] = (a[i][j] - sum)/m[j][j];
			}
		}
	}
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			mT[i][j] = m[j][i];
		}
	}
	cout <<"\nLower Triangle:\n";
	output(m,n,n);
	cout <<"\nTranspose:\n";
	output(mT,n,n);
}
int main()
{
	double a[10][10];
	int h, c;
	cout <<"CHOLESKY\n";
	cout <<"Nhap ma tran:\n";
	cout <<"So hang = "; 
	cin >>h;
	cout <<"So cot = ";
	cin >>c;
	if(h!=c) 
	{
		cout <<"Khong phai ma tran vuong!!!";
		return 0;
	}
	input(a,h,c);
	output(a,h,c);
	if(checkMatrixDx(a,h)) cout <<"Matran doi xung";
	else cout <<"ko doi xung";
	if(checkXdDuong(a,h)) cout <<"\nMatran xd duong";
	else cout <<"\nko xd duong";
	cholesky(a,h);
	return 0;
}
