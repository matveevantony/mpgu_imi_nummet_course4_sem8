// Лабораторная работа № 3
// Вариант 12
//
// Численное решение систем нелинейных уравнений (метод Ньютона)

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double f1(double x, double y) {
    return exp(x + y) - x * x + y - 2.8;
}

double f2(double x, double y) {
    return (x + 0.5) * (x + 0.5) + y * y - 2;
}

double df1dx(double x, double y) {
    return exp(x + y) - 2 * x;
}

double df1dy(double x, double y) {
    return exp(x + y) + 1;
}

double df2dx(double x, double y) {
    return 2 * x + 1;
}

double df2dy(double x, double y) {
    return 2 * y;
}

int main() {
    // точность приближения
    double eps = 0.001;

    // счётчик итераций
    int count = 0;

    // нахождение нулевого приближения
    double x = 0;
    double y = 0;
    double minsumabs = abs(f1(0,0)) + abs(f2(0,0));
    double step = 0.1;
    do {
        for (double a = 0; a <= 1.5; a += step) {
            for (double b = 0; b <= 2; b += step) {
                double value = abs(f1(a,b)) + abs(f2(a,b));
                if (value < minsumabs) {
                    minsumabs = value;
                    x = a;
                    y = b;
                }
            }
        }
        step /= 2;
    } while (minsumabs >= 1);
    cout << "шаг " << setw(2) << count << ": " << fixed << setprecision(3) << x << " " << fixed << setprecision(3) << y << endl;

    // итерационный процесс
    double x_prev, y_prev;
    double a11, a12, a21, a22;
    double delta;
    do {
        count++;
        x_prev = x;
        y_prev = y;
        delta = df1dx(x,y) * df2dy(x,y) - df1dy(x,y) * df2dx(x,y);
        a11 = - df2dy(x,y) / delta;
        a12 = df1dy(x,y) / delta;
        a21 = df2dx(x,y) / delta;
        a22 = - df1dx(x,y) / delta;
        x = x_prev + a11 * f1(x_prev, y_prev) + a12 * f2(x_prev, y_prev);
        y = y_prev + a21 * f1(x_prev, y_prev) + a22 * f2(x_prev, y_prev);
        cout << "шаг " << setw(2) << count << ": " << fixed << setprecision(3) << x << " " << fixed << setprecision(3) << y << endl;
    } while (max(abs(x - x_prev), abs(y - y_prev)) > eps);
    return 0;
}