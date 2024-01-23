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
    int M, N;
    cout << "Nhap gia tri M: ";
    cin >> M;
    cout << "Nhap gia tri N: ";
    cin >> N;

	cout << "Cac so nguyen to trong khoang tu " <<M <<" den " <<N <<" la: \n";
    int count = 0, sum = 0;
    for (int i = M; i <= N; i++) 
	{
        if (checkPrime(i)) {
            count++;
            sum += i;
            cout << i << " ";
        }
    }
    cout << endl << "So luong cac so nguyen to trong khoang tu " << M << " den " << N << " la: " << count << endl;
    cout << "Tong cac so nguyen to trong khoang tu " << M << " den " << N << " la: " << sum << endl;
    
	cout <<"So nguyen to gan 300 nhat la: ";
	NearestPrime(300);
	
	return 0;
}
