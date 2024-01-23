#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double y) {
    return 6 * x * x + 4 * x * y + 3 * y * y;
}

double h(double x, double y) {
    return x + y - 5;
}

double L(double x, double y, double lambda, double mu) {
    return f(x, y) - lambda * h(x, y) + (mu / 2) * h(x, y) * h(x, y);
}

double gradLx(double x, double y, double lambda, double mu) {
    return 12 * x + 4 * y - lambda + mu * (x + y - 5);
}

double gradLy(double x, double y, double lambda, double mu) {
    return 4 * x + 6 * y - lambda + mu * (x + y - 5);
}

double gradLlambda(double x, double y, double lambda, double mu) {
    return h(x, y);
}

double gradLmu(double x, double y, double lambda, double mu) {
    return (h(x, y) * h(x, y)) / 2;
}

void solve(double x, double y, double lambda, double mu, double k) {
    double alpha = 0.01;
    double eps = 0.0001;
    double dx, dy, dlambda, dmu;
    do {
        dx = -alpha * gradLx(x, y, lambda, mu);
        dy = -alpha * gradLy(x, y, lambda, mu);
        dlambda = -alpha * gradLlambda(x, y, lambda, mu);
        dmu = -alpha * gradLmu(x, y, lambda, mu);
        x += dx;
        y += dy;
        lambda += dlambda;
        mu += dmu;
        mu *= k;
        cout<<lambda <<"\t"<<mu <<"\t"<<x <<"\t"<<x <<"\t"<<h(x,y)<<endl;
    } while (sqrt(dx * dx + dy * dy + dlambda * dlambda + dmu * dmu) > eps);
//    cout << "x = " << x << endl;
//    cout << "y = " << y << endl;
//    cout << "lambda = " << lambda << endl;
//    cout << "mu = " << mu << endl;
//}

int main() {
    double x = 0, y = 0, lambda = 0, mu = 1, k = 2;
    solve(x, y, lambda, mu, k);
    return 0;
}

