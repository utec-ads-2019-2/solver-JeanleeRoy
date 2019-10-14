#include <iostream>
#include "solver.h"

int main(int argc, char const *argv[]) {
    string expresion;
    cout << "Expresion : \n\t";
    cin >> expresion;
    Solver solver(expresion);
    solver.printn();
    solver.printree();
    return 0;
}
