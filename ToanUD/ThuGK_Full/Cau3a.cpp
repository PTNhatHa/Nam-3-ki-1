#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
using namespace std;
#define MAX 10

/*
	Dieu kien cua ma tran A: 
		+ A vuong
		+ A doi xung
*/
typedef float m2c[MAX][MAX];
void inputMatrix(int &m,int &n,m2c data)
{
	do{
		cout<<"rows: ";
		cin>>m;
		cout<<"colums: ";
		cin>>n;
		if(m==n) break;
		else printf("khong phai ma tran vuong\n");
	} while(m!=n);
	cout<<"Nhap ma tran M:\n";
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j<= n; j++)
		{
			cout<<"a[" <<i<<"][" <<j<<"] = ";
			cin>>data[i][j];
		}
	}
}

void outputMatrix(int n,m2c data)
{
	for(int i = 1; i<=n; i++)
	{
		for(int j = 1; j<=n; j++)
		{
			cout << fixed << setprecision(2) <<data[i][j]<<"\t";
		}
		cout<<endl;
	}
}

bool checkSymmetry(int n,m2c data) //kiem tra doi xung
{
    for (int i = 1; i <= n; i++)
	 {
        for (int j = i + 1; j <= n; j++)
		 {
            if (data[i][j] != data[j][i]) 
			{
                return false;
            }
        }
    }
    return true;
}

void multiplyMatrix(m2c a, m2c b, m2c c, int n) 
{
    for (int i = 1; i <= n; i++)
	 {
        for (int j = 1; j <= n; j++) 
		{
            c[i][j] = 0;
            for (int k = 1; k <= n; k++) 
			{
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
void transposeMatrix(m2c a, m2c b, int n) 
{
    for (int i = 1; i <= n; i++) 
	{
        for (int j = 1; j <= n; j++)
		{
            b[i][j] = a[j][i];
        }
    }
}

bool compareMatrix(m2c a, m2c b, int n)
{
	for (int i = 1; i <= n; i++) 
	{
        for (int j = 1; j <= n; j++)
		{
            if(a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}
// Varient of the classical cholesky Decomposition L*D*L^T
void choleskyDecompositionVarient(int n,m2c data)
{
	if(checkSymmetry(n,data)==false)
	{
		cout<<"\nMa tran khong doi xung\n";
		return;	
	}
	m2c L,D,L_T;
	//Tinh ma tran L va D
	 for (int i = 1; i <= n; i++)
	  {
        for (int j = 1; j <= i; j++)
		 {
            double sum = 0;
            if (j == i) 
			{
                for (int k = 1; k < j; k++) 
				{
                    sum += L[j][k] * L[j][k] * D[k][k];
                }
                D[j][j] = data[j][j] - sum;
                L[j][j] = 1;
            } 
			else 
			{
                for (int k = 1; k < j; k++) 
				{
                    sum += L[i][k] * L[j][k] * D[k][k];
                }
                L[i][j] = (data[i][j] - sum) / D[j][j];
            }
        }
    }

    for (int i = 1; i <= n; i++)
	{
        for (int j = 1; j <= n; j++) 
		{
            if(i!=j) D[i][j] = 0;
        }
    }
	// Tinh ma tran L^T
    transposeMatrix(L,L_T,n);
	
	cout<<"\nVarient of Cholesky Decomposition: M = L.D.L^T\n";
	cout<<"Matrix L:\n";
	outputMatrix(n,L);
	cout<<"Matrix D:\n";
	outputMatrix(n,D);
	cout<<"Matrix L_T:\n";
	outputMatrix(n,L_T);
	
	m2c T,M;
	cout<<"\nCheck varient of cholesky decomposition: L*D*L^T = A:\n";
	multiplyMatrix(L,D,T,n);
	multiplyMatrix(T,L_T,M,n);
	outputMatrix(n,M);
	cout<<endl<<compareMatrix(data,M,n);
}

int main(){
	int n,m;
	m2c data,lower;
	inputMatrix(m,n,data);
	cout<<"\nMa tran vua nhap:\n";
	outputMatrix(n,data);
	cout<<"--------------------------\n";
	choleskyDecompositionVarient(n,data);
}
