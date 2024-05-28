// Лабораторная работа № 6
// Вариант 12
//
// Численное интегрирование

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double f(double x) {
    return sin(x * x);
}

int main() {
    // ввод начальных данных
    double a, b;
    a = M_PI / 4;
    b = M_PI / 2;

    // квадратурная формула левых прямоугольников
    cout << "Квадратурная формула левых прямоугольников:" << endl;
    double n = 1;
    double h = b - a;
    double sum = h * f(a);
    cout << "n = " << setw(4) << n << "    h = " << fixed << setprecision(4) << h << "    integral* = " << fixed << setprecision(4) << sum << endl;
    double prev_sum;
    n *= 2;
    h /= 2;
    do {
        prev_sum = sum;
        sum = prev_sum / 2;
        for (int i = 1; i < n; i += 2) {
            sum += f(a + i * h) * h;
        }
        cout << "n = " << resetiosflags(ios::fixed) << setw(4) << n << "    h = " << fixed << setprecision(4) << h << "    integral* = " << fixed << setprecision(4) << sum << endl;
        n *= 2;
        h /= 2;
    } while (abs(sum - prev_sum) >= 0.001 * sum);
    cout << endl;

    // квадратурная формула Симпсона
    cout << "Квадратурная формула Симпсона:" << endl;
    n = 1;
    h = (b - a) / 2;
    double start_sum = (f(a) + f(b)) * h / 2;
    double odd_sum = f(a + h) * 4 * h / 3;
    double even_sum = 0;
    sum = start_sum + odd_sum + even_sum;
    cout << "n = " << resetiosflags(ios::fixed) << setw(4) << n << "    h = " << fixed << setprecision(4) << h << "    integral* = " << fixed << setprecision(4) << sum << endl;
    start_sum /= 2;
    even_sum = even_sum / 2 + odd_sum / 4;
    odd_sum = 0;
    n *= 2;
    h /= 2;
    do {
        prev_sum = sum;
        for (int k = 1; k <= n; k++) {
            odd_sum += f(a + (2 * k - 1) * h);
        }
        odd_sum = odd_sum * 4 * h / 3;
        sum = start_sum + even_sum + odd_sum;
        cout << "n = " << resetiosflags(ios::fixed) << setw(4) << n << "    h = " << fixed << setprecision(4) << h << "    integral* = " << fixed << setprecision(4) << sum << endl;
        start_sum /= 2;
        even_sum = even_sum / 2 + odd_sum / 4;
        odd_sum = 0;
        n *= 2;
        h /= 2;
    } while (abs(sum - prev_sum) >= 0.001 * abs(sum));

    return 0;
}