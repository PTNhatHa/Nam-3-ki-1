#include <iostream>
#include <math.h>
using namespace std;

void input(float a[][10], int h, int c)
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
void output(float a[][10], int h, int c)
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
void nhan(float a[][10], int r1, int c1, float b[][10], int r2, int c2, float t[][10])
{
	int i,j,k;
	if(c1!=r2)
	{
		cout <<"\nKhong the nhan 2 ma tran!\n";
		return;
	}
	for (i=0;i<r1;i++)
		for (j=0;j<c2;j++)
		{
			t[i][j]=0;
			for (k=0;k<c1;k++)
				t[i][j]+=a[i][k]*b[k][j];
		}
}
void chuyenvi(float a[][10], float aT[][10], int r, int c)
{
	for (int i=0;i<r; i++)
	{
        for (int j=0; j<c; j++)
		{
            aT[j][i]=a[i][j];
        }
    }
}
int main()
{
	float a1[10][10], a2[10][10], a3[10][10];
	int h1, c1, h2, c2;
	cin>>h1;
	cin>>c1;
	input(a1,h1,c1);
	cin>>h2;
	cin>>c2;
	input(a2,h2,c2);
	cout<<"\n";
	output(a1,h1,c1);
	cout<<"\n";
	output(a2,h2,c2);
	cout<<"\na*b\n";
	nhan(a1,h1,c1,a2,h2,c2,a3);
	output(a3,h1,c2);
//	cout <<"MATRIX\n";
//	cout <<"Nhap ma tran:\n";
//	cout <<"So hang = "; 
//	cin >>h;
//	cout <<"So cot = ";
//	cin >>c;
//	input(a,h,c);
//	cout <<"\nMatran da nhap:\n";
//	output(a,h,c);
//	cout <<"\nMatran bien doi thanh tam giac:\n";
//	matranTamgiac(a, h);
//	output(a,h,c);
//	cout <<"\nDet(a) = " <<det(a,h);
	return 0;
}
