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
void saochep (float a[][10], float b[][10], int n)
{
    for (int i=0;i<n; i++){
        for (int j=0; j<n; j++){
            b[i][j]=a[i][j];
        }
    }
}
void matranTamgiac(float a[][10], int n)
{
	double m;
	for(int c=0; c<n-1; c++) //cot
	{
		for(int h=c+1; h<n; h++) //hang
		{
			m = a[h][c]/a[c][c];
			for(int k=c; k<n; k++)
			{
				a[h][k] -= m*a[c][k];
			}
		}
	}	
}
double det(float a[][10], int n)
{
	double d=1;
	float b[10][10];
	saochep(a,b,n);
	matranTamgiac(b,n);
	for(int i=0; i<n; i++)
	{
		d*=b[i][i];
	}
	return d;
}
void nhan(float a[][10], float b[][10], float c[][10], int n)
{
	int i,j,k;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
		{
			c[i][j]=0;
			for (k=0;k<n;k++)
				c[i][j]+=a[i][k]*b[k][j];
		}
}
void cutMatrix(float a[][10], float t[][10], int r, int c, int n)
{
	int p,q;
	p=0;
	for(int i=0; i<n; i++)
	{
		if(i!=r)
		{
			q=0;
			for(int j=0; j<n; j++)
			{
				if(j!=c)
				{
					t[p][q]=a[i][j];
					q++;
				}
			}
			p++;
		}
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
void nghichdao(float a[][10], float a1[][10], int n)
{
	float t[10][10], at[10][10];
	float d = det(a,n);
	if(d==0)
	{
		cout <<"\nMatran khong kha nghich\n";
		return;
	}
	if (n == 1) 
	{
        a1[0][0] = 1;
        return;
    }
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cutMatrix(a,t,i,j,n);
			at[i][j] = ((i + j) % 2 == 0) ? 1 : -1;
			at[i][j] *= det(t,n-1)/d;
		}
	}
	chuyenvi(at,a1,n,n);
}
int main()
{
	float a1[10][10], a2[10][10];
	int n;
	cin>>n;
	input(a1,n,n);
	cout<<"\n";
	output(a1,n,n);
	cout<<"\ndet="<<det(a1,n);
	cout <<"\na^-1\n";
	nghichdao(a1,a2,n);
	output(a2,n,n);
	return 0;
}
