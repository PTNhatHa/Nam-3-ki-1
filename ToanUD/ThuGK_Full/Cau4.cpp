#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <Eigen/Dense>
using Eigen::MatrixXd;
using namespace Eigen;
using namespace std;

void input(float a[][10], int r, int c)
{
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
		{
			cout <<"a[" <<i <<"][" <<j <<"] = ";
			cin >>a[i][j];
		}
	}
}
void output(float a[][10], int r, int c)
{
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
		{
			cout << setw(8) << setprecision(2) << fixed <<a[i][j];
		}
		cout <<"\n";
	}
}
void saochep(float a[][10], float b[][10], int r, int c)
{
    for (int i=0;i<r; i++)
	{
        for (int j=0; j<c; j++)
		{
            b[i][j]=a[i][j];
        }
    }
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
    // Sap xep lai eigenValues, eigenVector
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
void findSigmaMatrix(float lamda[10], float sigma[][10], int r, int c)
{
	for (int i=0; i<r; i++)
    {
    	for(int j=0; j<c; j++)
        {
        	if(i==j) sigma[i][j] = sqrt(lamda[i]);
        	else sigma[i][j] = 0;
		}
    }
}
void findUMatrix(float sigma[][10], float a[][10], float v[][10], float u[][10], int r, int c){
	for(int i=0; i<r; i++)
	{
		float ui[10][10];
		float sigmai = sigma[i][i];
		float vi[10][10];
		for(int j=0; j<c; j++)
		{
			vi[j][0] = v[j][i]; 
		}
		nhan(a,r,c,vi,c,1,ui);
		for(int j=0; j<r; j++)
		{
			ui[j][0] /= sigmai;
			u[j][i] = ui[j][0];
		}
	}
}
int main()
{
	float a[10][10], aT[10][10], s[10][10], lamda[10], v[10][10], sigma[10][10], vT[10][10], u[10][10], M1[10][10], M2[10][10];
	int r, c;
	cout <<"Cau4: SINGULAR VALUE DECOMPOSITION\n";
	cout <<"\nNhap kich thuoc matran a: \n";
	cout <<"Nhap so hang: ";
	cin >>r;
	cout <<"Nhap so cot: ";
	cin >>c;
	cout <<"\nNhap matran A: \n";
	input(a,r,c);
	cout <<"\nMatran A:\n";
	output(a,r,c);
	
	chuyenvi(a,aT,r,c);
	nhan(aT,c,r,a,r,c,s);
	Cal_Eival_Eivec(s,c,c,lamda,v);
	cout <<"\nTri rieng cua ma tran S: ";
    for (int i=0; i<c; i++)
    {
    	cout <<lamda[i] <<"  ";
	}
	cout <<endl;
	cout <<"Ma tran S:\n";
	output(s,c,c);
	
	findSigmaMatrix(lamda,sigma,r,c);
	chuyenvi(v,vT,c,c);
	findUMatrix(sigma,a,v,u,r,c);
	
	cout <<"\nMa tran U:\n";
	output(u,r,r);
	cout <<"\nMa tran Sigma:\n";
	output(sigma,r,c);
	cout <<"\nMa tran V^T:\n";
	output(vT,c,c);
	
	nhan(u,r,r,sigma,r,c,M1);
	nhan(M1,r,c,vT,c,c,M2);
	cout<<"\nCheck: A = U.Sigma.V^T\n";
	output(M2,r,c);
	return 0;
}
