#include <iostream>
#include <cmath>
using namespace std;

double learningRate = 0.001; // Learning rate
double momentum = 0.5; // He so momentum
int maxIterations = 1000; // So lan lap toi da
double epsilon = 1e-5; // Sai so dung
    
// Gia tri ham so f(x)
double f(double x) 
{
    return log(pow(2*x*x + 1, 2)) + 9*x + 3*exp(x*x) - 5;
}
// Ðao ham bac 1 cua f(x)
double df(double x) 
{
    return (8*x*(2*x*x + 1)) / (pow(2*x*x + 1, 2)) + 9 + 6*x*exp(x*x);
}

// Gradient Descent voi Momentum
double gradientDescentWithMomentum(double initialX) 
{
    double x = initialX;
    double velocity = 0.0;
    for (int i = 0; i < maxIterations; i++) 
	{
        double gradient = df(x);
        velocity = momentum * velocity + (1.0 - momentum) * gradient;
        x -= learningRate * velocity;
        if (abs(gradient) < epsilon) 
		{
            break;
        }
    }
    return x;
}

int main() {
    double x ; // Gia tri ban dau cua x
    cout <<"Nhap gia tri x: " ;
    cin >>x;    
    
    cout <<"\n-----GRADIENT DESCENT WITH MOMENTUM-----\n";
    double result = gradientDescentWithMomentum(x);
    cout <<"Gia tri x toi uu: " <<result <<endl;
    cout <<"Gia tri f(x) toi uu: " <<f(result) <<endl;

    return 0;
}

