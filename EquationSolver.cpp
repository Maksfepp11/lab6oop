#include "EquationSolver.h"
#include <cmath>
#include <iostream>
#include <functional>

EquationSolver::EquationSolver() {}
EquationSolver::~EquationSolver() {}

// Метод для встановлення інтервалу
void EquationSolver::setInterval(double vol_a, double vol_b) { //void - нічо неповертає
    a = vol_a; // Присвоюємо значення a
    b = vol_b;  // Присвоюємо значення b
}

// / Метод для встановлення точності
void EquationSolver::setTolerance(double vol_eps) {
    eps = vol_eps; // Присвоюємо значення точності
}

// Метод дихотомії з лямбда-виразом для функції
int EquationSolver::bisection(std::function<double(double)> func, double &x) {
    double a_ = a, b_ = b, c; //копія початку кінця та середини іінтервалу
    int iter = 0; //ітерації

    if (func(a_) * func(b_) >= 0) {
        std::cout << "На цьому проміжку немає кореня." << std::endl;
        return -1;
    }

    while ((b_ - a_) > eps) {
        c = (a_ + b_) / 2;

        if (func(a_) * func(c) < 0) {
            b_ = c;
        } else {
            a_ = c;
        }

        iter++;
    }

    x = (a_ + b_) / 2;
    std::cout << "Ітерацій (дихотомія): " << iter << std::endl;
    return 0;
}

// Метод Ньютона з лямбда-виразом для функції і її похідної
int EquationSolver::newton(std::function<double(double)> func, std::function<double(double)> deriv, double &x) {
    double xn = (a + b) / 2;  // Початкова точка (середина інтервалу)
    int maxIter = 1000; //максимальна кількість ітерацій 
    int iter = 0; //лічильник

    if (func(a) * func(b) >= 0) {
        std::cerr << "На цьому проміжку немає кореня. Метод Ньютона не застосовується." << std::endl;
        return -1;
    }

    while (std::abs(func(xn)) > eps && iter < maxIter) { //підставляємо значення в функцію модуля > 
        double df = deriv(xn); // Обчислюємо похідну в точці xn
        if (df == 0) { // Якщо похідна дорівнює нулю
            std::cerr << "Помилка: похідна = 0. Метод Ньютона не застосовується." << std::endl;
            return -1;
        }

        xn = xn - func(xn) / df;
        iter++;
    }

    if (iter == maxIter) {
        std::cerr << "Перевищено максимальну кількість ітерацій." << std::endl;
        return -1;
    }

    x = xn;
    return 0;
}
