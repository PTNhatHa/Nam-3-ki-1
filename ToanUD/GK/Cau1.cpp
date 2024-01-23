#include <iostream>
#include <math.h>
using namespace std;

bool checkPrime(int n)
{
	if(n<2) return false;
	for(int i=2; i<=sqrt(n); i++)
	{
		if(n%i==0) return false;
	}
	return true;
}
int maxFactorPrime(int n)
{
	for (int i=n; i > 1; i--)
	{
		if(n%i==0)
		{
			if(checkPrime(i))
			return i;
		}
	}
}
void primeFactors(int n, int p[1000], int m[1000], int *l)
{
	int i=1;
	m[i]=0;
	if(n%2 == 0) 
	{
		p[i]=2;
		while(n%2 == 0)
		{
			n=n/2;
			m[i]=m[i] + 1;
		}
		i=i+1;
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
				m[i]=m[i] + 1;
			}
			i=i+1;
		}
		
	}
	if(n>2) 
	{
		p[i]=n;
		m[i]=1;
		i=i+1;
	}
	*l = i-1;
}
int TongFactors(int n)
{
	int s=1;
	int p[1000]={0}, m[1000]={0}, l;
	primeFactors(n,p,m,&l);
	for(int i=1; i<=l; i++)
	{
		s*=(pow(p[i],m[i]+1) - 1) / (p[i] - 1);
	}
	return s;
}
void PerpectNumber(int m)
{
	int sl=0, t=0;
	int pn[1000]={0};
	for(int i=2; i<m; i++)
	{
		if(TongFactors(i) - i == i)
		{
			sl=sl+1;
			pn[sl]=i;
			t+=i;
		}
	}
	cout<< "So luong so hoan hao nho hon "<<m<<" la: "<<sl<<endl;
	for(int i=1; i<=sl; i++)
	{
		cout<< pn[i]<< "\t";
	}
	cout<< "\nTong cua chung la: "<<t;
}
void nguyento(int m)
{
	int t=0;
	cout<<"\n\nCac so nguyen to be hon "<<m<<" la:\n";
	for(int i=2; i<m; i++)
	{
		if(checkPrime(i))
		{
			cout<<i<<"\t";
			t=t+i;
		}
	}
	cout<<"\nTong cua chung la: "<<t<<endl;
}
int main()
{
	int n, m;
	cout<< "Cau 1:\n";
	cout<< "N = ";
	cin>>n;
	m=maxFactorPrime(n);
	cout<< "Uoc so nguyen to lon nhat cua "<< n<< " la M = "<< m <<endl;
	PerpectNumber(m);
	nguyento(m);
	return 0;
}
