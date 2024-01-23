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

int main() {
    int n;
    cout << "Nhap gia tri n: ";
    cin >> n;
	cout <<"So nguyen to gan "<<n<<" nhat la: ";
	NearestPrime(n);
	return 0;
}
