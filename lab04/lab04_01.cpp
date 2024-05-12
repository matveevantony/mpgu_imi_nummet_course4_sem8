// Лабораторная работа № 4
// Вариант 12
//
// Дискретный вариант среднеквадратических приближений

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <vector>
#include <set>
using namespace std;

int main() {
    // исходные данные
    vector<double> x = {-1, 0, 1 , 2};
    vector<double> f = {13.9, 1.1, -10.1, -18.9};

    // ввод точек сетки и значений функции в точках сетки
    cout << "Использовать векторы x и f по умолчанию (вариант 12)? (Y/N): ";
    char ans;
    cin >> ans;
    while (ans != 'Y' && ans != 'N') {
        cout << "Введите Y (да) или N (нет): ";
        cin >> ans;
    }
    if (ans == 'N') {
        x.clear();
        f.clear();
        cin.ignore();
        cout << "Введите вектор x - точки сетки: ";
        string inpt;
        getline(cin, inpt);
        istringstream isx(inpt);
        double inpt_double;
        while (isx >> inpt_double) {
            x.push_back(inpt_double);
        }
        cout << "Введите вектор f - значения функции в точках сетки: ";
        getline(cin, inpt);
        istringstream isf(inpt);
        double inpf_double;
        while (isf >> inpf_double) {
            f.push_back(inpf_double);
        }
    }

    // вывод в консоль вектора x
    cout << "x = (";
    for (int i = 0; i < x.size() - 1; i++) {
        cout << x[i] << ", ";
    }
    cout << x[x.size() - 1] << ")" << endl;

    // вывод в консоль вектора f
    cout << "f = (";
    for (int i = 0; i < f.size() - 1; i++) {
        cout << f[i] << ", ";
    }
    cout << f[f.size() - 1] << ")" << endl;

    // проверка введённых данных
    if (x.size() != f.size()) {
        cout << "Размерности векторов x и f не совпадают!" << endl;
        return 0;
    }
    if (x.size() < 3) {
        cout << "Размерность векторов меньше 3!" << endl;
        return 0;
    }
    set<double> x_set;
    for(auto iter = x.begin(); iter != x.end(); iter++) {
        x_set.insert(*iter);
    }
    if (x.size() != x_set.size()) {
        cout << "Точки сетки не должны повторяться!" << endl;
        return 0;
    }

    // вычисление коэффициентов системы
    double prod11 = 0;
    double prod1x = 0;
    double prod1x2 = 0;
    double prod1f = 0;
    double prodxx = 0;
    double prodxx2 = 0;
    double prodxf = 0;
    double prodx2x2 = 0;
    double prodx2f = 0;
    double prodff = 0;
    for (int i = 0; i < x.size(); i++) {
        prod11 += 1;
        prod1x += x[i];
        prod1x2 += x[i] * x[i];
        prod1f += f[i];
        prodxx += x[i] * x[i];
        prodxx2 += x[i] * x[i] * x[i];
        prodxf += x[i] * f[i];
        prodx2x2 += x[i] * x[i] * x[i] * x[i];
        prodx2f += x[i] * x[i] * f[i];
        prodff += f[i] * f[i];
    }

    cout << endl << "Приближения:" << endl;

    // приближение многочленом степени n = 0
    double a0 = prod1f / prod11;
    cout << "n = 0:    g(x) = " << a0 << endl;

    // приближение многочленом степени n = 1
    double delta = prod11 * prodxx - prod1x * prod1x;
    double delta1 = prod1f * prodxx - prod1x * prodxf;
    double delta2 = prod11 * prodxf - prod1f * prod1x;
    double b0 = delta1 / delta;
    double b1 = delta2 / delta;
    cout << "n = 1:    g(x) = " << b0 << (b1 >= 0 ? " + " : " - ") << abs(b1) << " * x" << endl;

    // приближение многочленом степени n = 2
    double delta_3 = prod11 * prodxx * prodx2x2 + prod1x * prodxx2 * prod1x2 + prod1x2 * prod1x * prodxx2 - prod1x2 * prodxx * prod1x2 - prodxx2 * prodxx2 * prod11 - prodx2x2 * prod1x * prod1x;
    double delta_31 = prod1f * prodxx * prodx2x2 + prodxf * prodxx2 * prod1x2 + prodx2f * prod1x * prodxx2 - prod1x2 * prodxx * prodx2f - prodxx2 * prodxx2 * prod1f - prodx2x2 * prod1x * prodxf;
    double delta_32 = prod11 * prodxf * prodx2x2 + prod1x * prodx2f * prod1x2 + prod1x2 * prod1f * prodxx2 - prod1x2 * prodxf * prod1x2 - prodxx2 * prodx2f * prod11 - prodx2x2 * prod1f * prod1x;
    double delta_33 = prod11 * prodxx * prodx2f + prod1x * prodxx2 * prod1f + prod1x2 * prod1x * prodxf - prod1f * prodxx * prod1x2 - prodxf * prodxx2 * prod11 - prodx2f * prod1x * prod1x;
    double c0 = delta_31 / delta_3;
    double c1 = delta_32 / delta_3;
    double c2 = delta_33 / delta_3;
    cout << "n = 2:    g(x) = " << c0 << (c1 >= 0 ? " + " : " - ") << abs(c1) << " * x" << (c2 >= 0 ? " + " : " - ") << abs(c2) << " * x^2" << endl;

    // вычисление норм разностей между табличной функцией и приближениями
    cout << "Нормы разности между функцией, заданной таблицей, и приближением:" << endl;
    double r0 = sqrt(prodff - prod1f * a0);
    cout << "n = 0:    ||f - g(x)|| = " << r0 << endl;
    double r1 = sqrt(prodff - prod1f * b0 - prodxf * b1);
    cout << "n = 1:    ||f - g(x)|| = " << r1 << endl;
    double r2 = sqrt(prodff - prod1f * c0 - prodxf * c1 - prodx2f * c2);
    cout << "n = 2:    ||f - g(x)|| = " << r2 << endl;

    return 0;
}