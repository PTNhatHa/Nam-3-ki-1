#include<math.h>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;
#define max 100

void input(int a[max][max], int h, int c)
{
	for(int i=0; i<h; i++)
	{
		for(int j=0; j<c; j++)
		{
			cout <<"a[" <<i <<"][" <<j <<"] = ";
			cin >>a[i][j];
		}
	}
}
void inputRandom(int a[max][max], int h, int c)
{
	
	srand(time(NULL)); 
	for(int i=0; i<h; i++)
	{
		for(int j=0; j<c; j++)
		{
			a[i][j] = rand() % 11;
		}
	}
}
void output(int a[max][max], int h, int c)
{
	for(int i=0; i<h; i++)
	{
		for(int j=0; j<c; j++)
		{
			cout <<a[i][j] <<"\t";
		}
		cout <<"\n";
	}
}
void dis2point(int a[max][max], int d[max][max], int n) //n^2
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			d[i][j] = sqrt(pow(a[i][0] - a[j][0], 2) + pow(a[i][1] - a[j][1], 2));
		}
	}
}
void swap(int *a, int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
void sortX(int a[max][max], int n)
{
	int min;
	for(int i=0; i<n-1; i++)
	{
		min=i;
		for(int j=i+1; j<n; j++)
		{
			if(a[j][0] < a[min][0]) min=j;
		}
		swap(&a[i][0], &a[min][0]);
		swap(&a[i][1], &a[min][1]);
	}
}
void copyMatrix(int a[max][max], int b[max][max])
{
	for(int i=0; i<h; i++)
	{
		for(int j=0; j<c; j++)
		{
			b[i][j] = a[i][j];
		}
	}
}
double closestPair(int a[max][max], int n)
{
	copyMatrix(a,b);
	sortX(b,n);
	
}
int main()
{
	int n, a[max][max], d[max][max];
	cout <<"So diem muon nhap: "; 
	cin>>n;
	cout <<"Nhap toa do cac diem:\n";
	inputRandom(a,n,2);
	cout <<"Cac diem vua nhap la:\n";
	output(a,n,2);
//	cout <<"Khoang cach giua cac diem:\n";
//	dis2point(a,d,n);
//	output(d,n,n);

//	cout <<"Sau khi sap xep theo X:\n";
//	sortX(a,n);
//	output(a,n,2);

	return 0;
}
