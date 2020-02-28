#include <iostream>
#include "MazeSolver.hpp"

int main() {
    MazeSolver solver("input.txt");
    if(solver.mazeIsReady())
    {
        solver.solveMaze();
        solver.printSolution();
    }
    return 0;
}
