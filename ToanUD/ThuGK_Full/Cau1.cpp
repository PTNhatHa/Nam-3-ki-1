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

int UCLN(int a, int b)
{
	while(a!=b)
	{
		if(a>b) a = a-b;
		else b = b-a;
	}
	return a;
}
void NTCN(int n, int nt[1000], int *sl) //nguyen to cung nhau voi n
{
	int s=0;
	for(int i=1; i<n; i++)
	{
		if(UCLN(n,i)==1) 
		{
			s=s+1;
			nt[s] = i;
		}
	}
	*sl=s;
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
void PerpectNumber(int n, int pn[1000], int *sl)
{
	int s=0;
	for(int i=2; i<n; i++)
	{
		if(TongFactors(i) - i == i)
		{
			s=s+1;
			pn[s]=i;
		}
	}
	*sl=s;
}
int main()
{
	int n, m, nt[1000]={0}, sl1, t1=0, pn[1000]={0}, sl2, t2=0;
	cout<< "CAU 1:\n";
	cout<< "N = ";
	cin>>n;
	m=maxFactorPrime(n);
	cout<< "Uoc so nguyen to lon nhat cua "<< n<< " la: "<< m <<endl;
	NTCN(m,nt,&sl1);
	cout<< "So luong so nguyen to cung nhau voi " <<m <<" trong khoang tu 1 den " <<m <<" la: " <<sl1 <<endl;
	cout<< "Cac so nguyen to cung nhau voi "<<m<<" la: \n";
	for(int i=1; i<=sl1; i++)
	{
		cout<< nt[i]<< "\t";
		t1+=nt[i];
	}
	cout<< "\nTong cua chung la: "<<t1;
	
	PerpectNumber(n,pn,&sl2);
	cout<< "\nSo luong so hoan hao giua 1 va "<<n<<" la: "<<sl2<<endl;
	for(int i=1; i<=sl2; i++)
	{
		cout<< pn[i]<< "\t";
		t2+=pn[i];
	}
	cout<< "\nTong cua chung la: "<<t2;
	return 0;
}
