#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <Eigen/Dense>
using Eigen::MatrixXd;
using namespace Eigen;
using namespace std;
void input(float a[][10], int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout <<"a[" <<i <<"][" <<j <<"] = ";
			cin >>a[i][j];
		}
	}
}
void output(float a[][10], int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout << setw(8) << setprecision(2) << fixed <<a[i][j];
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

//Tim tri rieng _ Vector rieng
void Cal_Eival_Eivec(float s[][10], int r, int c, float lamda[10], float v[][10])
{
    MatrixXf Ae;
    Ae.resize(r, c);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            Ae(i, j) = s[i][j];
        }
    }
    EigenSolver<MatrixXf> k(Ae);
    VectorXcf kEigenvalue = k.eigenvalues();
    for (int i = 0; i < kEigenvalue.size(); i++)
    {
        lamda[i] = kEigenvalue(i).real();
    }
    MatrixXcf kEigenvector = k.eigenvectors();
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
        	if (j%2==0)
        	{
            	v[i][j] = - kEigenvector(i, j).real();
			}
			else 
            	v[i][j] = kEigenvector(i, j).real();
        }
    }
//    output(v,r);
    // Sap xep lai eigenValues, eigenVector theo thu tu tang dan
    for (int i = 0; i < c - 1; i++)
    {
        for (int j = i + 1; j < c; j++)
        {
            if (lamda[i] < lamda[j])
            {
                float temp = lamda[i];
                lamda[i] = lamda[j];
                lamda[j] = temp;
                for (int k = 0; k < c; k++)
                {
                    float temp2 = v[k][i];
                    v[k][i] = v[k][j];
                    v[k][j] = temp2;
                }
            }
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
void MatrixMultiply(float A[][10], float B[][10], int a, int p, int b, float C[][10])
{
    double temp[10][10];

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            temp[i][j] = 0;

            for (int m = 0; m < p; m++)
            {
                temp[i][j] += A[i][m] * B[m][j];
            }
        }
    }

    for (int i = 0; i < a; ++i)
        for (int j = 0; j < b; ++j)
            C[i][j] = temp[i][j];
}
void markov(float a[][10], int n)
{
	float p[10], x[4], P[10][10]={0}, D[10][10]={0}, P1[10][10]={0}, lamda[10], M1[10][10], A[10][10];
	int i, j;
	Cal_Eival_Eivec(a,n,n,lamda,P);
	cout <<"\nTri rieng cua ma tran A: ";
    for (int i=0; i<n; i++)
    {
    	D[i][i] = lamda[i];
    	cout <<lamda[i] <<"  ";
	}
	nghichdao(P,P1,n);
	cout <<"\nMatran P:\n";
	output(P,n);
	cout <<"\nMatran duong cheo chinh D:\n";
	output(D,n);
	cout <<"\nMatran nghich dao P^(-1):\n";
	output(P1,n);
	cout<<"\nCheck: PDP^-1 (= A)\n";
	nhan(P,D,M1,n);
	nhan(M1,P1,A,n);
	output(A,n);
	
	float Dn[10][10];
	float S[][10] = 
	{
        {0, 1, 0, 0 }
    };
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) 
		{
            if (i == j)
                Dn[i][i] = 1;
            else
                Dn[i][j] = 0;
    	}

    cout << "\nTrang thai sau n buoc:\n";
    for (int i = 1; i <= 3; ++i) 
	{
        for (int k = 0; k < n; ++k) 
		{
            Dn[k][k] *= D[k][k];
        }
        cout << "\tTrang thai sau " << i <<  " buoc:\n";

        float Pn[10][10], temp[10][10];
        float Sn[10][10];

        MatrixMultiply(P, Dn, n, n, n, temp);
        MatrixMultiply(temp, P1, n, n, n, Pn);
        MatrixMultiply(S, Pn, 1, n, n, Sn);
        
        cout << "\t";
        int rS = 1;
        for (int j = 0; j < n; ++j)
            std::cout << Sn[0][j] << " ";
        cout << "------- Xac suat cua trang thai " << rS << " la: " << Sn[0][rS - 1] << "\n";
    }
}
int main()
{
	int n, i, j;
	float a[10][10];
	cout <<"MARKOV:\n";
	cout <<"Nhap so phan tu ma tran vuong: ";
	cin >>n;
	input(a,n);
	cout <<"\nMa tran A:\n";
//	output(a,n);
	markov(a,n);
	return 0;
}
