#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<iostream>
#include<iomanip>
using namespace std;
float M[10][10];
void input(float a[][10], int n)
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			cout <<"a[" <<i <<"][" <<j <<"] = ";
			cin >>a[i][j];
		}
	}
}
void output(float a[][10], int n)
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			cout << setw(8) << setprecision(4) << fixed <<a[i][j];
		}
		cout <<"\n";
	}
}
void saochep (float a[][10], float b[][10], int n)
{
    for (int i=1;i<=n; i++)
	{
        for (int j=1; j<=n; j++)
		{
            b[i][j]=a[i][j];
        }
    }
}
void nhan(float a[][10], float b[][10], float c[][10], int n)
{
	int i,j,k;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
		{
			c[i][j]=0;
			for (k=1;k<=n;k++)
				c[i][j]+=a[i][k]*b[k][j];
		}
}
void Markov(float P[][10], int n)
{
	int day;
	float T[10][10], K[10][10];
	cout<<"Nhap so ngay: ";
	cin>>day;
	saochep(P,T,n);
	for(int i=1; i<day; i++)
	{
		nhan(P,T,K,n);
		saochep(K,T,n);
	}
	cout<<"\nKq:\n";
	output(K,n);
}
int main()
{
	int n;
	float P[10][10];
	cout <<"---------- MARKOV CHAIN ----------\n";
	cout <<"Nhap so phan tu ma tran vuong: ";
	cin >>n;
	input(P,n);
	output(P,n);
	Markov(P,n);
	return 0;
}
