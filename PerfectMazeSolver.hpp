#ifndef PERFECTMAZESOLVER_HPP
#define PERFECTMAZESOLVER_HPP
#include "MazeSolver.hpp"

class PerfectMazeSolver : public MazeSolver
{
public:
    PerfectMazeSolver();
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
};

#endif