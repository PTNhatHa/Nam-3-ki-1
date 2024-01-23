#include<iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <Eigen/dense>

using namespace std;

#define MAX 10

void OutputMatrix(double A[][MAX], int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            std::cout << std::setw(7) << std::setprecision(3) << (abs(A[i][j]) < 0.001f ? 0 : A[i][j]);

        std::cout << "\n";
    }
}

void MatrixMultiply(double A[][MAX], double B[][MAX], int a, int p, int b, double C[][MAX])
{
    double temp[MAX][MAX];

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            temp[i][j] = 0;

            for (int m = 0; m < p; m++)
            {
                temp[i][j] += A[i][m] * B[m][j];
            }
        }
    }

    for (int i = 0; i < a; ++i)
        for (int j = 0; j < b; ++j)
            C[i][j] = temp[i][j];
}

void InverseMatrix(double matrix[][MAX], int n, double res[][MAX]) {
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            res[i][j] = 0;
        }
    }

    std::vector<std::vector<double> > augmented(n, std::vector<double>(2 * n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented[i][j] = matrix[i][j];
            augmented[i][j + n] = (i == j) ? 1.0 : 0.0; // Identity matrix
        }
    }

    for (int i = 0; i < n; ++i) {
        double pivot = augmented[i][i];
        if (pivot == 0) {
            return; // Matrix is singular, no unique inverse
        }

        for (int j = 0; j < 2 * n; ++j) {
            augmented[i][j] /= pivot;
        }

        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = augmented[i][j + n];
        }
    }
}


void Eigenvalues(double A[][MAX], int n, int m, double C[])
{
    Eigen::MatrixXd S(n, m);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            S(i, j) = A[i][j];

    Eigen::EigenSolver<Eigen::MatrixXd> solver(S);

    Eigen::VectorXd eivalues = solver.eigenvalues().real();

    for (int i = 0; i < eivalues.size(); ++i)
    {
        std::cout << eivalues(i) << "\n";
        C[i] = eivalues(i);
    }

}

void Eigenvectors(double A[][MAX], int n, int m, double C[][MAX])
{
    Eigen::MatrixXd S(n, m);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            S(i, j) = A[i][j];

    Eigen::EigenSolver<Eigen::MatrixXd> solver(S);

    Eigen::MatrixXd eivectors = solver.eigenvectors().real();

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            C[i][j] = eivectors(i, j);

}

void Sort(double values[MAX], double vectors[MAX][MAX], int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            if (values[i] < values[j])
            {
                double temp = values[i];
                values[i] = values[j];
                values[j] = temp;

                double tempV[MAX];

                for (int k = 0; k < n; ++k)
                {
                    tempV[k] = vectors[k][i];
                    vectors[k][i] = vectors[k][j];
                    vectors[k][j] = tempV[k];
                }
            }
        }
}

void MatrixPower(double M[][MAX], int p, int n, double C[][MAX])
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            if (i == j) C[i][j] = 1;
            else C[i][j] = 0;
        }

    /*for (int i = 0; i < p; ++i)
    {
        MatrixMultiply(C, M, n, C);
    }*/

    while (p)
    {
        if (p % 2)
            MatrixMultiply(C, M, n, n, n, C);
        MatrixMultiply(M, M, n, n, n, M);
        p /= 2;
    }
}
float CalculateProbability(double M[][MAX], int n, int F, int S, int T)
{
    double P[MAX][MAX];
    MatrixPower(M, T + 1, n, P);
    std::cout << "\nTransition Matrix at time " << T << ":\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            std::cout << P[i][j] << " ";
        std::cout << "\n";
    }
    return P[S - 1][F - 1];
}
int main()
{
    int n = 4;

    double G[MAX][MAX] = {
        {0, 0.75, 0.2, 0.05},
        {0.05, 0.2, 0.3, 0.45},
        {0.1, 0.4, 0.3, 0.2},
        {0, 0.15, 0.3, 0.55}
    };

    int rS = 1;

    double S[][MAX] = {
        {0, 1, 0, 0 }
    };

    std::cout << "Original Transition Matrix:\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            std::cout << G[i][j] << " ";
        std::cout << "\n";
    }

    double values[MAX];
    double vectors[MAX][MAX], iP[MAX][MAX], D[MAX][MAX];

    Eigenvalues(G, n, n, values);
    Eigenvectors(G, n, n, vectors);
    Sort(values, vectors, n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
                D[i][i] = values[i];
            else
                D[i][j] = 0;
        }

    InverseMatrix(vectors, n, iP);

    std::cout << "\nP---------\n";
    OutputMatrix(vectors, n, n);

    std::cout << "\nD---------\n";
    OutputMatrix(D, n, n);

    std::cout << "\nInverse P---------\n";
    OutputMatrix(iP, n, n);

    double K[MAX][MAX], temp[MAX][MAX];
    MatrixMultiply(vectors, D, n, n, n, temp);
    MatrixMultiply(temp, iP, n, n, n, K);
    std::cout << "\n";
    OutputMatrix(K, n, n);

    double Dn[MAX][MAX];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (i == j)
                Dn[i][i] = 1;
            else
                Dn[i][j] = 0;
    }

    std::cout << "\nState after n steps:\n";
    for (int i = 1; i <= 3; ++i) {
        for (int k = 0; k < n; ++k) {
            Dn[k][k] *= D[k][k];
        }


        std::cout << "\tState after " << i <<  " steps:\n";

        double Pn[MAX][MAX], temp[MAX][MAX];
        double Sn[MAX][MAX];

        MatrixMultiply(vectors, Dn, n, n, n, temp);
        MatrixMultiply(temp, iP, n, n, n, Pn);
        MatrixMultiply(S, Pn, 1, n, n, Sn);
        
        std::cout << "\t";
        for (int j = 0; j < n; ++j)
            std::cout << Sn[0][j] << " ";
        std::cout << "------- Pro of state" << rS << " is: " << Sn[0][rS - 1] << "\n";

    }

    return 0;
}

