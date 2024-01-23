#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <Eigen/Dense>
using Eigen::MatrixXd;
//#include <Eigen/Dense> 

using namespace Eigen;
using namespace std;
const float max=100;
int h,n;
float sigma[100][100]={0};
float a[100][100],b[100][100],c[100][100],m[100][100],m1[100][100],M[100][100],s[100][100],y[100][100],at[100][100],u[100][100],v[100][100],vt[100][100];
float heso[100],lamda[100];

void nhapmtr(float a[][100], int h, int n)
{	for (int i=0; i<h; i++)
    {
        for (int j=0; j<n; j++)
		{
            cout << "x[" << i << "]["<< j << "]= ";
            cin >> a[i][j];
        }
    }
}

void xuatmtr(float a[][100], int h, int n)
{	int i,j;
	cout << endl;
	for(i=0; i<h; i++)
	{
        for (j=0; j<n; j++)
		{
            cout << setw(8) << setprecision(2) << fixed << a[i][j];
        }
        cout << endl;
	}
}

void mtchuyenvi( float a[][100], int h, int n, float at[][100])
{
  	for(int i=0 ;i<h; i++)
  	{
	    for(int j=0; j<n ;j++){
	      at[j][i] = a[i][j];
	    }
  	}
}

void nhan2mtr(float at[][100], int q, int r, float a[][100], int h, int n,float c[][100]){
	if (r != h)
	{
		cout << "Khong the nhan vi 2 ma tran khong hop le!" << endl;
	}
	else
	{
		for(int i=0;i<q;i++){
			for (int j=0; j<n ;j++){
				c[i][j]=0;
				for(int k=0; k<r ; k++){
			    	c[i][j] += at[i][k]*a[k][j];
				}
			}
		}
	}	
}

void Cal_Eival_Eivec(float s[][100], int h, int n, float lamda[100], float v[][100])
{
    MatrixXf Ae;
    Ae.resize(h, n);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < n; j++)
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
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < n; j++)
        {
        	if (j%2==0)
        	{
            	v[i][j] = - kEigenvector(i, j).real();
			}
			else 
            	v[i][j] = kEigenvector(i, j).real();
        }
    }
    // Sap xep lai eigenValues, eigenVector
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (lamda[i] < lamda[j])
            {
                float temp = lamda[i];
                lamda[i] = lamda[j];
                lamda[j] = temp;
                for (int k = 0; k < n; k++)
                {
                    float temp2 = v[k][i];
                    v[k][i] = v[k][j];
                    v[k][j] = temp2;
                }
            }
        }
    }
    cout << endl << "Tri rieng cua ma tran S: ";
    for (int i=0; i<n; i++)
    {
    	cout << lamda[i] << "  ";
	}
	cout << endl;
}


void findSigmaMatrix(float lamda[100], float sigma[][100], int h, int n)
{
	for (int i=0; i<h; i++)
    {
        sigma[i][i] = sqrt(lamda[i]);
    }
    cout << endl << "Xuat ma tran Sigma: ";
	xuatmtr(sigma,h,n);
}

void findUMatrix(float sigma[][100], float a[][100], float v[][100], float u[][100], int h, int n){
	for(int i=0; i<h; i++)
	{
		float ui[100][100];
		float sigmai = sigma[i][i];
		float vi[100][100];
		for(int j=0; j<n; j++)
		{
			vi[j][0] = v[j][i]; 
		}
		nhan2mtr(a,h,n,vi,n,1,ui); //a*v=u
		for(int j=0; j<h; j++)
		{
			ui[j][0] /= sigmai;
			u[j][i] = ui[j][0];
		}
	}
	cout << endl << "Xuat ma tran U: ";
	xuatmtr(u,h,h);
}

int main()
{
	cout << "Nhap so hang: "; cin >> h;
	cout << "Nhap so cot: "; cin >> n;
	cout << "Nhap he so ma tran: " << endl;
	nhapmtr(a,h,n);
	cout << endl << "Xuat ma tran A: ";
	xuatmtr(a,h,n);
	mtchuyenvi(a,h,n,at);
	nhan2mtr(at,n,h,a,h,n,s);
	cout << endl << "Xuat ma tran S: ";
	xuatmtr(s,n,n);
	Cal_Eival_Eivec(s,n,n,lamda,v);
	findSigmaMatrix(lamda,sigma,h,n);
	
	findUMatrix(sigma,a,v,u,h,n);
	
	mtchuyenvi(v,n,n,vt);
	cout << endl << "Xuat ma tran V^T: ";
	xuatmtr(vt,n,n);
	return 0;
}

