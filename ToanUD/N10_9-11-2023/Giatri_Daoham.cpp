#include <iostream>
#include <cmath>
using namespace std;
// Ham so f(x)
double f(double x) {
    return (exp(2 * x) + x - 10) * (exp(2 * x) + x - 10) + 2 * (x + 1) * (x + 1);
}
// Ðao ham cua ham so f(x)
double df(double x) {
    return  ( exp(2 * x) + x - 10) * (4.0 * exp(2 * x) + 2) + 4.0 * (x + 1);
}
// dao ham bac hai cua f(x) 
double dff(double x) {
    	return 2*pow((2*exp(2*x)+1),2) + 8*exp(2*x)*(exp(2*x)+x-10)+4; 
}

int main() {
    double initialX ; // Gia tri ban dau cua x
    double learningRate = 0.001; // Learning rate
    double momentum = 0.1; // He so momentum
    int maxIterations = 1000; // So lan lap toi da
    double epsilon = 1e-5; // Sai so dung
    cout << "Moi ban nhap vao gia tri x ban dau : " ;
    cin >> initialX;    
    cout << "Gia tri cua f(x) tai x =" << initialX << " là " << f(initialX) << endl;
    cout << "Gia tri cua f'(x) tai x =" << initialX << " là " << df(initialX) << endl;
    cout << "Gia tri cua f''(x) tai x =" << initialX << " là " << dff(initialX) << endl;
    return 0;
}

