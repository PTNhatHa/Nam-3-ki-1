#include <iostream>
#include <math.h>
using namespace std;

int modpow(int x, int n, int m)
{
	if(n == 0) return 1%m;
	long long u = modpow(x, n/2, m);
	u = (u*u)%m;
	if(n%2 == 1) u = (u*x)%m;
	return u;
}
void check(int x, int y, int m, int n)
{
	cout <<"(x+y) % m == (x % m + y % m) % m): ";
	if((x+y) % m == (x % m + y % m) % m) cout <<"True\n"; else cout <<"False\n";
	cout <<"(x-y) % m == (x % m - y % m) % m): ";
	if((x-y) % m == (x % m - y % m) % m) cout <<"True\n"; else cout <<"False\n";
	cout <<"(x*y) % m == (x % m * y % m) % m): ";
	if((x*y) % m == (x % m * y % m) % m) cout <<"True\n"; else cout <<"False\n";
	cout <<"x^n % m == (x % m)^n % m): ";
	if(modpow(x, n, m) == modpow((x % m), n, m)) cout <<"True\n"; else cout <<"False\n";
}
int ModularInverse(int x, int m)
{
	int k=0;
	while((1 + k*m) % x != 0)
	{
		k++;
	}
	return (1 + k*m)/x;
}
int main()
{
	int x, y, m, n;
	cout <<"BT4: MODULAR ARITHMETIC\n";
	cout <<"Nhap x = ";
	cin >>x;
	cout <<"Nhap y = ";
	cin >>y;
	cout <<"Nhap m = ";
	cin >>m;
	cout <<"Nhap n = ";
	cin >>n;
	check(x,y,m,n);
	
	cout <<"BT5: MODULAR INVERSE\n";
	cout <<"Nhap x = ";
	cin >>x;
	cout <<"Nhap m = ";
	cin >>m;
	cout <<"The inverse of x modulo m is x^(-1) = " <<ModularInverse(x,m);
	return 0;
}
