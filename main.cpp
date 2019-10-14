#include <iostream>
#include "solver.h"

int main(int argc, char const *argv[]) {
    string expresion;
    cin >> expresion;
    Solver solver(expresion);
    solver.printn();
    return 0;
}
