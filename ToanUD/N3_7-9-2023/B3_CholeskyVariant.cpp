#include<math.h>
#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

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
void proMatrix(double a[][10], double b[][10], double c[][10], int n)
{
	int i,j,k;
	for (i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			c[i][j]=0;
			for(k=1;k<=n;k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
}
int compareMatrix(double a[][10], double b[][10], int n){
    for(int i=1; i <= n ;i ++ )
	{
        for(int j=1;j <=n ;j++)
		{
            if(b[i][j] != a[i][j]) return 0;
        }
    }
    return 1;
}
void CholeskyVariant(double a[][10], int n)
{
	double lower[10][10], lowerT[10][10], D[10], y[10][10];
	// phan ra ma tran
    for (int i=1; i<=n; i++)
    {
        lower[i][i] = 1;
    }
    double sum = 0;
    for (int i=1; i<=n; i++)
    {
        sum = 0;
        for (int k=1; k<=i; k++)
            sum += pow(lower[i][k], 2) * D[k];
        D[i] = a[i][i] - sum;
        for (int j=i+1; j<=n; j++)
        {
            sum = 0;
            for (int k=1; k<=i; k++)
                sum += lower[j][k] * lower[i][k] * D[k];
            lower[j][i] = (a[j][i] - sum) / D[i];
        }
    }
    for (int i=1; i<=n; i++)
    {
        y[i][i] = D[i];
    }
    for (int i=1; i<=n; i++) 
	{
        for (int j=1; j<=n; j++)
		{
            lowerT[i][j] = lower[j][i];
            if(i!=j) y[i][j]=0;
        }
    }
    // xuat
    cout << "\nLower Triangular\n";
    output(lower,n,n);
	cout << "\nDiagonal Matrix\n";
	output(y,n,n);
    cout << "\nTranspose\n";
    output(lowerT,n,n);
}
int main()
{
	double a[10][10];
	int h, c;
	cout <<"CHOLESKY VARIANT\n"; //bien the
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
	CholeskyVariant(a,h);
	return 0;
}
