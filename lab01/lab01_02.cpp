// Лабораторная работа № 1
// Вариант 12
//
// Численное решение уравнения методом половинного деления

#include <iostream>
#include <iomanip>
using namespace std;

double f(double x) {
    return x * x * x * x + 2.4 * x * x * x - 6.81 * x * x - 15.98 * x - 7.6;
}

double root_halfdiv(double a, double b, double eps) {
    double m;
    while (b - a >= eps) {
        m = (a + b) / 2;
        if (f(a) * f(m) < 0) {
            b = m;
        }
        else {
            a = m;
        }
    }
    return m;
}

int main() {
    double B = 17;
    double h = 1;
    double eps = 0.0001;
    for (double a = -B; a < B; a += h) {
        double b = a + h;
        if (f(a) * f(b) < 0) {
            cout << fixed << setprecision(4) << root_halfdiv(a, b, eps) << " ";
        }
    }
    cout << endl;
    return 0;
}