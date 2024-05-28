// Лабораторная работа № 5
// Вариант 12
//
// Интерполяция

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

double f_der(double x, int n) {
    if (n == 0) return x * x * x * x * x;
    if (n == 1) return 5 * x * x * x * x;
    if (n == 2) return 5 * 4 * x * x * x;
    if (n == 3) return 5 * 4 * 3 * x * x;
    if (n == 4) return 5 * 4 * 3 * 2 * x;
    if (n == 5) return 5 * 4 * 3 * 2;
    return 0;
}

double error_value(double x_inp, int n, double a, double b, vector<double> x, vector<double> f) {
    for (int j = 0; j <= n; j++) {
        for (int i = 0; i < n; i++) {
            if (abs(x[i] - x_inp) > abs(x[i + 1] - x_inp)) {
                double tmp = x[i];
                x[i] = x[i + 1];
                x[i + 1] = tmp;
                tmp = f[i];
                f[i] = f[i + 1];
                f[i + 1] = tmp;
            }
        }
    }
    double factorial = 1;
    double prod = 1;
    for (int i = 1; i <= n + 1; i++) {
        factorial *= i;
        prod *= abs(x_inp - x[i - 1]);
    }
    double M;
    if (abs(a) > abs (b)) {
        M = abs(f_der(a, n));
    }
    else {
        M = abs(f_der(b, n));
    }
    return M * prod / factorial;
}

int main() {
    // ввод основных данных
    double a, b, h;
    int n;
    cout << "a = ";
    cin >> a;
    cout << "h = ";
    cin >> h;
    cout << "n = ";
    cin >> n;

    // вывод в консоль начальных данных
    vector<double> x, f;
    for (int i = 0; i <= n; i++) {
        x.push_back(a + i * h);
        f.push_back(x[i] * x[i] * x[i] * x[i] * x[i]);
    }
    b = a + n * h;
    cout << endl << "Вектор x:" << endl;
    for (int i = 0; i <= n; i++) {
        cout << setw(8) << fixed << setprecision(4) << x[i];
    }
    cout << endl << "Вектор f:" << endl;
    for (int i = 0; i <= n; i++) {
        cout << setw(8) << fixed << setprecision(4) << f[i];
    }
    cout << endl;

    // нахождение значения интерполяционного многочлена (запись Лагранжа) степени m в точке x_inp
    int m;
    double x_inp;
    cout << endl << "m = ";
    cin >> m;
    if ((m > n) || (m < 0)) {
        cout << "Недопустимое значение m!" << endl;
        return 0;
    }
    cout << "x* = ";
    cin >> x_inp;
    for (int j = 0; j <= n; j++) {
        for (int i = 0; i < n; i++) {
            if (abs(x[i] - x_inp) > abs(x[i + 1] - x_inp)) {
                double tmp = x[i];
                x[i] = x[i + 1];
                x[i + 1] = tmp;
                tmp = f[i];
                f[i] = f[i + 1];
                f[i + 1] = tmp;
            }
        }
    }
    double f_approx_value_x_inp = 0;
    for (int i = 0; i <= m; i++) {
        double product = 1;
        double divised = 1;
        for (int j = 0; j <= m; j ++) {
            if (j != i) {
                product *= (x_inp - x[j]);
                divised *= (x[i] - x[j]);
            }
        }
        product = product * f[i] / divised;
        f_approx_value_x_inp += product;
    }
    cout << "Значение интерполяционного многочлена (запись Лагранжа) степени " << m << " в точке " << fixed << setprecision(4) << x_inp << " равно " << fixed << setprecision(4) << f_approx_value_x_inp << endl;

    // нахождение значения интерполяционного многочлена (запись Лагранжа) в точке x_inp с требуемой точностью
    double eps;
    cout << endl << "Введите значение допустимой погрешности: ";
    cin >> eps;
    cout << endl;
    f_approx_value_x_inp = 0;
    int eps_min_n = -1;
    for (int i = 0; i <= n; i++) {
        double err = error_value(x_inp, i, a, b, x, f);
        cout << "m = " << i << "    погрешность - " << fixed << setprecision(4) << err << endl;
        if (err <= eps) {
            for (int k = 0; k <= i; k++) {
                double product = 1;
                double divised = 1;
                for (int j = 0; j <= i; j ++) {
                    if (j != k) {
                        product *= (x_inp - x[j]);
                        divised *= (x[k] - x[j]);
                    }
                }
                product = product * f[k] / divised;
                f_approx_value_x_inp += product;
            }
            eps_min_n = i;
            cout << "Значение интерполяционного многочлена (запись Лагранжа) степени " << i << " в точке " << fixed << setprecision(4) << x_inp << " равно " << fixed << setprecision(4) << f_approx_value_x_inp << endl;
            break;
        }
        if (i == n) {
            cout << "Заданной точности достичь не удалось" << endl;
        }
    }

    // нахождение значения интерполяционного многочлена (форма Ньютона) степени m в точке x_inp
    cout << endl << "Разделенные разности:" << endl;
    double newton_approx_value = 0;
    for (int i = 0; i <= m; i++) {
        double f_divdif = 0;
        if (i == 0) f_divdif = f[0];
        else {
            for (int j = 0; j <= i; j++) {
                double prod = 1;
                for (int k = 0; k <= i; k++) {
                    if (k != j) prod *= x[j] - x[k];
                }
                f_divdif += f[j] / prod;
            }
        }
        cout << fixed << setprecision(4) << f_divdif << endl;
        double prod = 1;
        for (int j = 0; j < i; j++) {
            prod *= x_inp - x[j];
        }
        newton_approx_value += f_divdif * prod;
    }
    cout << "Значение интерполяционного многочлена (форма Ньютона) степени " << m << " в точке " << fixed << setprecision(4) << x_inp << " равно " << fixed << setprecision(4) << newton_approx_value << endl;

    // нахождение значения интерполяционного многочлена (форма Ньютона) в точке x_inp с требуемой точностью
    cout << endl;
    newton_approx_value = 0;
    for (int i = 0; i <= eps_min_n; i++) {
        double f_divdif = 0;
        if (i == 0) f_divdif = f[0];
        else {
            for (int j = 0; j <= i; j++) {
                double prod = 1;
                for (int k = 0; k <= i; k++) {
                    if (k != j) prod *= x[j] - x[k];
                }
                f_divdif += f[j] / prod;
            }
        }
        double prod = 1;
        for (int j = 0; j < i; j++) {
            prod *= x_inp - x[j];
        }
        newton_approx_value += f_divdif * prod;
    }
    cout << "Значение интерполяционного многочлена (форма Ньютона) степени " << eps_min_n << " в точке " << fixed << setprecision(4) << x_inp << " равно " << fixed << setprecision(4) << newton_approx_value << endl;

    // обратная интерполяция
    double y_inp;
    cout << endl << "y* = ";
    cin >> y_inp;
    for (int j = 0; j <= n; j++) {
        for (int i = 0; i < n; i++) {
            if (abs(f[i] - y_inp) > abs(f[i + 1] - y_inp)) {
                double tmp = x[i];
                x[i] = x[i + 1];
                x[i + 1] = tmp;
                tmp = f[i];
                f[i] = f[i + 1];
                f[i + 1] = tmp;
            }
        }
    }
    double x_approx_value_y_inp = 0;
    for (int i = 0; i <= n; i++) {
        double product = 1;
        double divised = 1;
        for (int j = 0; j <= n; j ++) {
            if (j != i) {
                product *= (y_inp - f[j]);
                divised *= (f[i] - f[j]);
            }
        }
        product = product * x[i] / divised;
        x_approx_value_y_inp += product;
    }
    cout << "Приближённое значение функции f^(-1)(y) в точке " << fixed << setprecision(4) << y_inp << " равно " << fixed << setprecision(4) << x_approx_value_y_inp << endl;

    return 0;
}