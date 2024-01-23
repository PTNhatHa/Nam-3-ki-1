#include <iostream>
#include <math.h>
using namespace std;

void primeFactors(int n, int p[5000], int m[5000], int *l)
{
	int i=1;
	p[0]=1;
	m[0]=1;
	m[i]=0;
	if(n%2 == 0) 
	{
		p[i]=2;
		while(n%2 == 0)
		{
			n=n/2;
			m[i]++;
		}
		i++;
	}

	for(int j=3; j<=sqrt(n); j+=2)
	{
		if(n%j == 0) 
		{
			p[i]=j;
			m[i]=0;
			while(n%j == 0)
			{
				n=n/j;
				m[i]++;
			}
			i++;
		}
	}
	if(n>2) 
	{
		p[i]=n;
		m[i]++;
		i++;
	}
	*l = i;
}
int Tong(int p[5000], int m[5000], int l, int n)
{
	int s=1;
	for(int i=1; i<l; i++)
	{
		s*=(pow(p[i],m[i]+1) - 1) / (p[i] - 1);
	}
	return s;
}
int main()
{
	int n, p[5000], m[5000], l;
	cout <<"CAU 1\n";
	cout <<"Nhap n: ";
	cin >>n;
	
	primeFactors(n,p,m,&l);
	cout <<"\na) PHAN TICH THUA SO NGUYEN TO\n";
	cout <<n <<" = ";
	for(int k=1; k<l; k=k+1)
	{
		cout <<p[k] <<"^" <<m[k] <<" ";
	}
	
	cout <<"\n\nb) TINH TONG CAC UOC SO\n";
	cout <<"Tong cac uoc so cua " <<n <<" la: " <<Tong(p,m,l,n);
	return 0;
}
