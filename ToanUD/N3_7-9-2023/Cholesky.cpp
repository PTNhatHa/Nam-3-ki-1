#include<math.h>
#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;
#define max 1000

int lower[max][max]={0},lowerT[max][max]={0},y[max][max]={0};
int x[max][max],mt[max][max],kq[max][max];
int D[max] = {0};
int m,n;

void input()
{
    cout << "Enter number of rows: " ; cin >> m;
    cout << "Enter number of columns: " ; cin >> n;
    // ktra ma tran vuong
	while (m!=n)
    {
    	cout << "THIS IS NOT A SQUARE MATRIX SO CAN NOT DECOMPOSE! PLEASE RE-ENTER!" << endl;
    	cout << "Enter number of rows: " ; cin >> m;
    	cout << "Enter number of columns: " ; cin >> n;
    }
    cout << "Enter value: " << endl;
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++)
		{
            cout << "x[" << i << "]" << "["<< j << "]" << " = ";
            cin >> x[i][j];
        }
    }
}

void output(int a[][max], int n)
{
	int i,j;
	cout << endl;
	for(i=1;i<=n;i++)
	{
        for (j=1;j<=n;j++)
		{
            cout << setw(5) << a[i][j];
        }
        cout << endl;
	}
}

int compareMatrix(int a[][max], int b[][max], int n){
    for(int i=1; i <= n ;i ++ )
	{
        for(int j=1;j <=n ;j++)
		{
            if(b[i][j] != a[i][j]) return 0;
        }
    }
    return 1;
}

void proMatrix(int a[][max], int b[][max],int c[][max], int n)
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
void CholeskyDecomposition(int a[][max], int n)
{
	// ktra ma tran doi xung
    for (int i=1; i<=n; i++)
	{
        for (int j=1; j<=n; j++)
        {
        	if (i!=j)
        	{
	            if (x[i][j]!=x[j][i]) 
				{
	                cout << endl << "MATRIX IS NOT SYMMETRIC! CAN NOT DECOMPOSE!";
	                exit(0);
	            }
	        }
        }
    }
	// ktra ma tran xac dinh duong
    for (int i=1; i<=n; i++) 
	{
        for (int j=1; j<=i; j++)
		{
            int sum=0;
 
            if (j == i) 
            {
                for (int k=1; k<=j; k++)
                	sum += pow(lower[j][k], 2);
                if (a[j][j]-sum<0) 
				{
                    cout << endl << "THIS IS NOT POSITIVE DEFINITE MATRIX! CAN NOT DECOMPOSE!";
                    exit(0);
                } 
				else
                    lower[j][j] = sqrt(x[j][j] - sum);
            } 
			else 
			{
	        	for (int k=1; k <= j; k++)
	                sum += (lower[i][k] * lower[j][k]);
	            lower[i][j] = (x[i][j] - sum) / lower[j][j];
        	}
        }
    }
    //xuat
    cout << endl << "Lower Triangular" 
         << setw(30) << "Transpose" << endl;
    for (int i=1; i <= n; i++) 
	{
        for (int j=1; j <= n; j++)
		{
            cout << lower[i][j] << "\t";
            lowerT[i][j] = lower[j][i];
        }
        cout << "\t";
         
        for (int j=1; j <= n; j++)
            cout << setw(6) << lower[j][i] << "\t";
        cout << endl;
    }
    proMatrix(lower,lowerT,mt,n);
    if(compareMatrix(x,mt,n)) 
    	cout << endl << "Check result: TRUE";
    else cout << endl << "Check result: FALSE";
 }
 
void VariantDecomposition(int a[][max], int n)
{
	// ktra ma tran doi xung
    for (int i=1; i<=n; i++)
	{
        for (int j=1; j<=n; j++)
        {
        	if (i!=j)
        	{
	            if (x[i][j]!=x[j][i]) 
				{
	                cout << endl << "MATRIX IS NOT SYMMETRIC! CAN NOT DECOMPOSE!";
	                exit(0);
	            }
	        }
        }
    }
	// phan ra ma tran
    for (int i=1; i<=n; i++)
    {
        lower[i][i] = 1;
    }
    int sum = 0;
    for (int i=1; i<=n; i++)
    {
        sum = 0;
        for (int k=1; k<=i; k++)
            sum += pow(lower[i][k], 2) * D[k];
        D[i] = x[i][i] - sum;
        for (int j=i+1; j<=n; j++)
        {
            sum = 0;
            for (int k=1; k<=i; k++)
                sum += lower[j][k] * lower[i][k] * D[k];
            lower[j][i] = (x[j][i] - sum) / D[i];
        }
    }
    for (int i=1; i<=n; i++)
    {
        y[i][i] = D[i];
    }
    // xuat
    cout << endl << "Lower Triangular"
		 << setw(36) << "Diagonal Matrix" 
         << setw(28) << "Transpose" << endl;
    for (int i=1; i<=n; i++) 
	{
        for (int j=1; j<=n; j++)
		{
            cout << lower[i][j] << "\t";
            lowerT[i][j] = lower[j][i];
        }
        cout << "\t";
        for (int j=1; j<=n; j++)
		{
            cout << setw(6) << y[i][j] << "\t";
        }
        cout << "\t";
         
        for (int j=1; j<=n; j++)
            cout << setw(6) << lower[j][i] << "\t";
        cout << endl;
    }
    
    proMatrix(lower,y,mt,n);
    proMatrix(mt,lowerT,kq,n);
    if(compareMatrix(x,kq,n)) 
    	cout << endl << "Check result: TRUE";
    else cout << endl << "Check result: FALSE";
 }
 
int main()
{
	cout <<"CHOLESKY BIEN THE\n";
	input();
	output(x,n);
	CholeskyDecomposition(x,n);
	//VariantDecomposition(x,n);
	
	return 0;
}
