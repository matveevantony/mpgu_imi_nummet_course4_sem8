// Лабораторная работа № 2
// Вариант 12
//
// Численное решение систем линейных уравнений (метод Зейделя)

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double A_var12[3][3] = {{0.38, -0.33, 0.12}, {-0.56, 0.42, 0.06}, {0.10, 0.25, -0.31}};
    double b_var12[3] = {0.215, -0.198, 2.623};
    int n;
    double eps;
    cout << endl << "Решение системы из n линейных уравнений с n переменными" << endl << "(метод Зейделя)" << endl << "-------------------------------------------------------" << endl;
    cout << "n = ";
    cin >> n;
    cout << "e = ";
    cin >> eps;
    double A[n][n];
    double b[n];
    bool flag = true;
    if (n == 3) {
        string ans;
        cout << "Использовать матрицу A и столбец b по умолчанию (12 вариант)? (y/n) ";
        cin >> ans;
        if (ans == "y") {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    A[i][j] = A_var12[i][j];
                }
                b[i] = b_var12[i];
            }
            flag = false;
        }
    }
    if (flag) {
        cout << "Введите построчно матрицу A:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> A[i][j];
            }
        }
        cout << "Введите в строку столбец b: ";
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
    }
    cout << endl << "Матрица A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(8) << fixed << setprecision(4) << A[i][j];
        }
        cout << endl;
    }
    cout << endl << "Столбец b:" << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(8) << fixed << setprecision(4) << b[i] << endl;
    }

    cout << endl << "Проверка применимости метода Зейделя:" << endl;
    int method = -1;
    double alpha = -1;
    double beta = -1;
    double gamma = -1;
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += abs(A[i][j]);
        }
        if (sum > alpha) {
            alpha = sum;
        }
    }
    if (alpha < 1) {
        cout << "alpha < 1   =>   будем использовать чебышевскую метрику" << endl;
        method = 0;
    }
    else {
        cout << "alpha >= 1   =>   не можем использовать чебышевскую метрику" << endl;
    }
    if (method == -1) {
        for (int j = 0; j < n; j++) {
            double sum = 0;
            for (int i = 0; i < n; i++) {
                sum += abs(A[i][j]);
            }
            if (sum > beta) {
                beta = sum;
            }
        }
        if (beta < 1) {
            cout << "beta < 1   =>   будем использовать l1 метрику" << endl;
            method = 1;
        }
        else {
            cout << "beta >= 1   =>   не можем использовать l1 метрику" << endl;
        }
    }
    if (method == -1) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum += A[i][j] * A[i][j];
            }
        }
        gamma = sqrt(sum);
        if (gamma < 1) {
            cout << "gamma < 1   =>   будем использовать евклидову метрику" << endl;
            method = 2;
        }
        else {
            cout << "gamma >= 1   =>   не можем использовать евклидову метрику" << endl;
        }
    }
    if (method == -1) {
        return 0;
    }

    int count = 0;
    double x[n];
    // double x[n] = {1.6, -1.7, 1.8};
    double x_prev[n];
    cout << endl << "Приближения к решению:" << endl;
    for (int i = 0; i < n; i++) {
        x[i] = b[i];
    }
    cout << "x" << count << ":";
    for (int i = 0; i < n; i++) {
        cout << setw(8) << fixed << setprecision(4) << x[i];
    }
    cout << endl;
    while (true) {
        count++;
        for (int i = 0; i < n; i++) {
            x_prev[i] = x[i];
        }
        for (int i = 0; i < n; i++) {
            double newvalue = 0;
            for (int j = 0; j < n; j++) {
                newvalue += A[i][j] * x[j];
            }
            newvalue += b[i];
            x[i] = newvalue;
        }
        cout << "x" << count << ":";
        for (int i = 0; i < n; i++) {
            cout << setw(8) << fixed << setprecision(4) << x[i];
        }
        cout << endl;
        if (method == 0) {
            double maxdif = -1;
            for (int i = 0; i < n; i++) {
                if (abs(x[i] - x_prev[i]) > maxdif) {
                    maxdif = abs(x[i] - x_prev[i]);
                }
            }
            if ((alpha / (1 - alpha) * maxdif) < eps) {
                break;
            }
        }
        if (method == 1) {
            double sumdif = 0;
            for (int i = 0; i < n; i++) {
                sumdif += abs(x[i] - x_prev[i]);
            }
            if ((beta / (1 - beta) * sumdif) < eps) {
                break;
            }
        }
        if (method == 2) {
            double sumsq = 0;
            for (int i = 0; i < n; i++) {
                sumsq += (x[i] - x_prev[i]) * (x[i] - x_prev[i]);
            }
            double dif = sqrt(sumsq);
            if ((gamma / (1 - gamma) * dif) < eps) {
                break;
            }
        }
    }
    cout << endl;

    cout << "Ответ:";
    for (int i = 0; i < n; i++) {
        cout << setw(8) << fixed << setprecision(4) << x[i];
    }
    cout << endl << endl;
}