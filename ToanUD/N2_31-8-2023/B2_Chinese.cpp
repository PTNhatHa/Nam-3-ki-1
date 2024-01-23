#include <iostream>
#include <math.h>
using namespace std;

int ModularInverse(int x, int m)
{
	int k=0;
	while((1 + k*m) % x != 0)
	{
		k++;
	}
	return (1 + k*m)/x;
}
int Tich(int p[], int n)
{
	double t=1;
	for(int i=1; i<=n; i++)
	{
		t*=p[i];
	}
	return t;
}
void Show(int a[], int m[], int n)
{
	for(int i=1; i<=n; i++)
	{
		cout <<"\n x = " <<a[i] <<" mod " <<m[i];
	}
}
void chinese(int a[10], int m[10], int n)
{
	int x0[10], x1[10], x = 0;
	int t = Tich(m, n);
	for(int i=1; i<=n; i++)
	{
		x0[i] = t/m[i];
		x1[i] = ModularInverse(x0[i],m[i]);
		x += a[i]*x0[i]*x1[i];
	}
	x = x % t;
	cout <<"\n\n => x = " <<x <<" (mod " <<t <<")";
}
int main()
{
	int max = 10;
	int n, a[max], m[max], x0[max], x1[max], x = 0;
	cout <<"Cau2: CHINESE REMAINDER THEOREM\n";
	cout <<"Nhap n = ";
	cin >>n;
	for(int i=1; i<=n; i++)
	{
		cout <<"Nhap a[" <<i <<"] = ";
		cin >>a[i];
		cout <<"Nhap m[" <<i <<"] = ";
		cin >>m[i];
	}
	Show(a,m,n);
	chinese(a,m,n);
	return 0;
}
