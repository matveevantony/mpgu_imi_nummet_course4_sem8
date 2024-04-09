// Лабораторная работа № 1
// Вариант 12
//
// Численное решение уравнения методом итераций (вариант 2)

#include <iostream>
#include <iomanip>
using namespace std;

double f(double x) {
    return x * x * x * x + 2.4 * x * x * x - 6.81 * x * x - 15.98 * x - 7.6;
}

double f_1(double x) {
    return 4 * x * x * x + 2.4 * 3 * x * x - 6.81 * 2 * x - 15.98;
}

double f_2(double x) {
    return 4 * 3 * x * x + 2.4 * 3 * 2 * x - 6.81 * 2;
}

double f_3(double x) {
    return 4 * 3 * 2 * x + 2.4 * 3 * 2;
}

double root_iter(double a, double b, double eps) {
    double root = 0;
    cout << "-----" << endl;
    cout << "Отрезок [" << fixed << setprecision(4) << a << ";" << b << "]" << endl;
    cout << "f'''(" << fixed << setprecision(4) << a << ") * f'''(" << b << ") > 0 ";
    if (f_3(a) * f_3(b) > 0) {
        cout << "+" << endl;
        cout << "f''(" << fixed << setprecision(4) << a << ") * f''(" << b << ") > 0 ";
        if (f_2(a) * f_2(b) > 0) {
            cout << "+" << endl;
            cout << "f'(" << fixed << setprecision(4) << a << ") * f'(" << b << ") > 0 ";
            if (f_1(a) * f_1(b) > 0) {
                cout << "+" << endl;
                cout << "Метод итераций к отрезку [" << fixed << setprecision(4) << a << ";" << b << "] применим" << endl;
                double m1;
                double M1;
                if (f_1(a) > 0) {
                    if (f_1(a) < f_1(b)) {
                        m1 = f_1(a);
                        M1 = f_1(b);
                    }
                    else {
                        M1 = f_1(a);
                        m1 = f_1(b);
                    }
                }
                else {
                    if (f_1(a) < f_1(b)) {
                        M1 = -f_1(a);
                        m1 = -f_1(b);
                    }
                    else {
                        m1 = -f_1(a);
                        M1 = -f_1(b);
                    }
                }
                double x;
                double x_prev;
                x = (a + b) / 2;
                int k = 0;
                do {
                    k++;
                    x_prev = x;
                    if (f_1(a) > 0) {
                        x = x - ((2 * f(x)) / (M1 + m1));
                    }
                    else {
                        x = x + ((2 * f(x)) / (M1 + m1));
                    }
                } while (((M1 - m1) / (2 * m1)) * abs(x - x_prev) > eps);
                root = x;
                cout << "Корень: " << fixed << setprecision(4) << x << ". Количество шагов: " << k << "." << endl;
            } 
            else {
                cout << "-" << endl;
                cout << "Метод итераций к отрезку [" << fixed << setprecision(4) << a << ";" << b << "] не применим" << endl;
            }
        }
        else {
            cout << "-" << endl;
            cout << "Метод итераций к отрезку [" << fixed << setprecision(4) << a << ";" << b << "] не применим" << endl;
        }
    }
    else {
        cout << "-" << endl;
        cout << "Метод итераций к отрезку [" << fixed << setprecision(4) << a << ";" << b << "] не применим" << endl;
    }
    cout << "-----" << endl;
    return root;
}

int main() {
    double B = 17;
    double h = 0.125;
    double eps = 0.0001;
    for (double a = -B; a < B; a += h) {
        double b = a + h;
        if (f(a) * f(b) < 0) {
            root_iter(a, b, eps);
        }
    }
    cout << endl;
    return 0;
}