#include <iostream>
#include "EquationSolver.h"
#include <cmath>
#include <functional>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(65001); 
    EquationSolver solver; //створюється об'єкт класу який містить методи для розв'язання рівнянь.
    solver.setInterval(0, 0.8);  
    solver.setTolerance(1e-6);

    // Лямбда-вираз для функції f(x), який використовується в ньютоні і дихотомії
    auto func = [](double x) { //auto - визначає тип змінної, func - змінна для функції. [](double x - лямбда вираз, []-змінні з зовні 
       double t = tan(x); // обчислю тангенс від x і зберігаємо його в змінну t.
        return t - (pow(t, sqrt(3)) + 1) / (3 + 0.2 * pow(t, sqrt(5)));
    }; 

    // Лямбда-вираз для похідної f'(x)
    auto deriv = [](double x) { //auto - визначає тип змінної, deriv - похідна. [](double x - лямбда вираз, []-змінні з зовні 
        double t = tan(x); // обчислю тангенс від x і зберігаємо його в змінну t.
        double sec2 = 1 / (cos(x) * cos(x)); // sec^2(x)

        double u = pow(t, sqrt(3)) + 1; //чисельник 
        double v = 3 + 0.2 * pow(t, sqrt(5));//знаменник

        double u_prime = sqrt(3) * pow(t, sqrt(3) - 1) * sec2; //похідна чисельника
        double v_prime = 0.2 * sqrt(5) * pow(t, sqrt(5) - 1) * sec2;//похідна знаменника

        return sec2 - (u_prime * v - u * v_prime) / (v * v); //похідна
    };

    double root_bisect, root_newton; //змінні, у яких будуть збережені корені, знайдені методом дихотомії та методом Ньютона.

    // Використання методу дихотомії
    if (solver.bisection(func, root_bisect) == 0)
        cout << "Метод дихотомії: x = " << root_bisect << endl;

    // Використання методу Ньютона
    if (solver.newton(func, deriv, root_newton) == 0)
        cout << "Метод Ньютона: x = " << root_newton << endl;

    return 0;
}
