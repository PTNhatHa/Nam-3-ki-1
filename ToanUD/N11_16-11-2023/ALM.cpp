#include <bits/stdc++.h>

using namespace std;

double f(double x, double y) 
{
    return 6 * pow(x, 2) + 3 * pow(y, 2) + 4 * x * y;
}
double h(double x, double y) 
{
    return x + y - 5;
}

double new_x(double rk, double lamda) 
{
    return (-90*rk*rk + 9*rk*lamda - 6*lamda + 60*rk) / ((14 - 5*rk)*(12 + 2*rk));
}
double new_y(double rk, double lamda)
{
    return (20*rk - 2*lamda)/(14 - 5*rk);
}

void solve()
{
	cout <<"AUGMENTED LAGRANGE MULTIPLIER METHOD\n";
	double x1, x2; 
    double lamda = 0.0, rk = 1.0; 
    double epsilon = 1e-2; 
    cout << setw(10) << "Lamda" << setw(10) << "rk" << setw(15) << "x1" << setw(15) << "x2" << setw(15) << "Value of h" << endl;
    cout << "------------------------------------------------------------------" << endl;
    do{
        x1 = new_x(rk, lamda);
        x2 = new_y(rk, lamda);
        cout << setw(10) << lamda << setw(10) << rk << setw(15) << x1 << setw(15) << x2 << setw(15) << h(x1, x2) << endl;
        lamda += 2*rk*h(x1, x2);
    } while(abs(2*rk*h(x1, x2)) >= epsilon);
    cout << "------------------------------------------------------------------" << endl;
}

int main() 
{
    solve();
    return 0;
}

