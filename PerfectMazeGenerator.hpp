#ifndef PERFECTMAZEGENERATOR_HPP
#define PERFECTMAZEGENERATOR_HPP
#include "MazeGenerator.hpp"

class PerfectMazeGenerator : public MazeGenerator
{
public:
    PerfectMazeGenerator();
    void generateMaze(Maze& maze) override;
};

#endif