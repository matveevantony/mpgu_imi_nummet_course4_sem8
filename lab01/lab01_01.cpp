// Лабораторная работа № 1
// Вариант 12
//
// Нахождение отрезков, которым принадлежат корни уравнения f(x) = 0

#include <iostream>
using namespace std;

double f(double x) {
    return x * x * x * x + 2.4 * x * x * x - 6.81 * x * x - 15.98 * x - 7.6;
}

int main() {
    double B = 17;
    double h = 1;
    for (double a = -B; a < B; a += h) {
        double b = a + h;
        if (f(a) * f(b) < 0) {
            cout << "[" << a << "; " << b << "]  "; 
        }
    }
    cout << endl;
    return 0;
}