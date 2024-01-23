#include <iostream>
#include <math.h>
using namespace std;
int p[100], m[100], l;

void primeFactors(int n)
{
	int i=1;
	p[0]=1;
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
	l = i;
}
int gcd1(int a, int b)
{
	if(b==0) return a;
	else return gcd1(b, a%b);
}

int gcd2(int a, int b)
{
	while(a!=b)
	{
		if(a>b) a = a-b;
		else b = b-a;
	}
	return a;
}

int NumberOfCoprime(int n)
{
	int pn=1;
	primeFactors(n);
	for(int i=1; i<l; i++)
	{
		pn*=pow(p[i], m[i]-1)*(p[i]-1);
	}
	return pn;
}
void CoprimeN(int n)
{
	cout <<"\nThe number coprime to n: ";
	for(int i=1; i<n; i++)
	{
		if(gcd1(n,i)==1) cout <<i <<" ";
	}
}
bool checkPrime(int n)
{
	if(NumberOfCoprime(n) == n-1) return 1;
	return 0;
}
int main()
{
	int a, b, n;
	cout <<"\nBT1: GREATEST COMMON DIVISOR\n";
	cout <<"Nhap a = ";
	cin >>a;
	cout <<"Nhap b = ";
	cin >>b;
	cout <<"gcd1(" <<a <<" ," <<b <<") = ";
	if(a>b) cout <<gcd1(a,b);
	else cout <<gcd1(b,a);
	cout <<"\ngcd2(" <<a <<" ," <<b <<") = " <<gcd2(a,b);
	
	cout <<"\nBT2: EULER'S TOTIENT FUNCTION(1)\n";
	cout <<"Nhap n = ";
	cin >>n;
	cout <<"The number of coprime numbers to " <<n <<" between 1 and " <<n <<" is " <<NumberOfCoprime(n);
	CoprimeN(n);
	
	cout <<"\nBT3: EULER'S TOTIENT FUNCTION(2)\n";
	cout <<"Nhap n = ";
	cin >>n;
	if(checkPrime(n)) cout <<n <<" is Prime\n";	
	else cout <<n <<" is not Prime\n";

	return 0;
}
