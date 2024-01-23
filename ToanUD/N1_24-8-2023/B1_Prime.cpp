#include <iostream>
#include <math.h>
using namespace std;

//p=so nguyen to
//m=so mu tuong ung
//l=so luong pt cua p/m
void primeFactors(int n, int p[100], int m[100], int *l)
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

int numberOfFactors(int m[], int l)
{
	int s = 1;
	for(int i=1; i<=l; i++)
	{
		s*=(m[i] + 1);
	}
	return s;
}
int TongFactors(int p[], int m[], int l, int n)
{
	int s=1;
	for(int i=1; i<=l; i++)
	{
		s*=(pow(p[i],m[i]+1) - 1) / (p[i] - 1);
	}
	return s;
}
void Factor(int n)
{
	for(int i = 1; i <= n; i++)
	{
		if(n%i==0)
		{
			cout <<i <<" ";
		}
	}
}
double TichFactors(int n, int sl)
{
	double t = pow(n,6);
	return t;
}

bool PerpectNumber(int n, int sum)
{
	if(sum == n)
	{
		return 1;
	}
	return 0;
}

int DensityOfPrimes(int n)
{
	return n/(log(n));
}

bool checkPrime(int n)
{
	if(n<2) return false;
	for(int i=2; i<=sqrt(n); i++)
	{
		if(n%i==0) return false;
	}
	return true;
}
void NearestPrime(int n)
{
	int before, after;
	before=n-1;
	after=n+1;
	while(!checkPrime(before) && !checkPrime(after))
	{
		before--;
		after++;
	}
	if(checkPrime(before) && checkPrime(after)) cout <<before <<", " <<after;
	else
	{
		if(checkPrime(before)) cout <<before;
		else cout <<after;
	}	
}
int main()
{
	int n;
	int p[100], m[100], l;
	cout <<"Nhap n: ";
	cin >>n;
	
	primeFactors(n,p,m,&l);
	cout <<"\nBT1: PHAN TICH THUA SO NGUYEN TO\n";
	cout <<n <<" = ";
	for(int k=1; k<=l; k=k+1)
	{
		cout <<p[k] <<"^" <<m[k] <<" ";
	}
	
	cout <<"\n\nBT2: TINH SO UOC VA LIET KE\n";
	cout <<"So " <<n <<" co " <<numberOfFactors(m,l) <<" uoc so: ";
	Factor(n);
	
	cout <<"\n\nBT3: TINH TONG CAC UOC SO\n";
	cout <<"Tong cac uoc so cua " <<n <<" la: " <<TongFactors(p,m,l,n);
	
	cout <<"\n\nBT4: TINH TICH CAC UOC SO\n";
	cout <<"Tich cac uoc so cua " <<n <<" la: " <<TichFactors(n,numberOfFactors(m,l));
	
	cout <<"\n\nBT5: PERFECT NUMBER\n";
	if(PerpectNumber(n,TongFactors(p,m,l,n)))
	{
		cout <<"So " <<n <<" la so hoan hao! ";
	}
	else
	{
		cout <<"So " <<n <<" khong phai so hoan hao! ";
	}
	
	cout <<"\n\nBT6: DENSITY OF PRIMES\n";
	cout <<"Mat do cac so nguyen to trong khoang tu 1 den " <<n <<" la: " <<DensityOfPrimes(n);
	
	cout <<"\n\nBT7: NEAREST PRIME\n";
	cout <<"So nguyen to gan " <<n <<" nhat la: ";
	NearestPrime(n);
	
	return 0;
}
