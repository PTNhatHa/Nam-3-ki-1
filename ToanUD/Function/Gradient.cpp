#include <iostream>
#include <cmath>
using namespace std;

double learningRate = 0.01; // Learning rate
double momentum = 0.1; // He so momentum
int maxIterations = 10000; // So lan lap toi da
double epsilon = 1e-5; // Sai so dung
    
// Gia tri ham so f(x)
double f(double x) 
{
    return 2*exp(pow(x,5) - pow(x,3)) - 5*pow(x,3) - x + log(x+45) + 20;
}
// Ðao ham bac 1 cua f(x)
double df(double x) 
{
    return 2*(5*pow(x,4) - 3*pow(x,2))*exp(pow(x,5) - pow(x,3)) - 15*pow(x,2) - 1 + 1/(x+45);
}
// Ðao ham bac 2 cua f(x)
double dff(double x) 
{
    return (40*pow(x,3) - 12*x)*exp(pow(x,5) - pow(x,3)) + 2*pow((5*pow(x,4) - 3*pow(x,2)), 2)*exp(pow(x,5) - pow(x,3)) - 30*x - 1 - 1/pow((x+45),2);
}

// Gradient descent
double gradientDescent(double initialX)
{
    double x = initialX;
    double v = 0.0;
    for (int i = 0; i < maxIterations; i++)
    {
        double gradient = df(x);
        v = gradient;
        x -= learningRate * v;
        if (abs(gradient) < epsilon)
        {
            break;
        }
    }
    return x;
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
// Newton's Method
double newtonMethod(double initialX) 
{
    double x = initialX;
    for (int i = 0; i < maxIterations; i++) 
	{
        double gradient = df(x);
        double hessian = dff(x);
        x -= gradient / hessian;
        if (abs(gradient) < epsilon) 
		{
            break;
        }
    }
    return x;
}
int main() {
    double x ; // Gia tri ban dau cua x
    cout <<"f1(x) = (e^(2x) + x - 10)^2 + 2*(x + 1)^2";
    cout <<"\n----------BT1----------\n";
    cout <<"Nhap gia tri x: " ;
    cin >>x;    
//    cout <<"f(x)= " <<f(x) <<endl;
//    cout <<"f'(x)= " <<df(x) <<endl;
//    cout <<"f''(x)= " <<dff(x) <<endl;
    
//    cout <<"\n----------BT2----------\n";
//    cout <<"-----GRADIENT DESCENT-----\n";
//    double rs1 = gradientDescent(x);
//    cout <<"Gia tri x toi uu: " <<rs1 <<endl;
//    cout <<"Gia tri f(x) toi uu: " <<f(rs1) <<endl;
    
    cout <<"\n-----GRADIENT DESCENT WITH MOMENTUM-----\n";
    double result = gradientDescentWithMomentum(x);
    cout <<"Gia tri x toi uu: " <<result <<endl;
    cout <<"Gia tri f(x) toi uu: " <<f(result) <<endl;

//	cout <<"\n-----NEWTON'S METHOD-----\n";
//    double newtonResult = newtonMethod(x);
//    cout <<"Gia tri x toi uu: " <<newtonResult <<endl;
//    cout <<"Gia tri f(x) toi uu: " <<f(newtonResult) <<endl;

    return 0;
}

