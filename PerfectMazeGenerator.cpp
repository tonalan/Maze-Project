#include <ics46/factory/DynamicFactory.hpp>
#include "PerfectMazeGenerator.hpp"
#include "Maze.hpp"
#include <random>

ICS46_DYNAMIC_FACTORY_REGISTER(
    MazeGenerator, PerfectMazeGenerator, 
    "Perfect Algorithm (Required)");

std::vector<Direction> PossibleMoves; //tracks possible moves
std::random_device device;
std::default_random_engine engine{device()};
PerfectMazeGenerator::PerfectMazeGenerator(){};

void MovementPossible(std::vector<Direction> &PossibleMoves, Maze &maze, std::vector<std::vector<bool>> &cells, int row, int col)
{
    //all checks ensure x and y are in bounds and their adjacent cell is vacant
    if (row >= 0 && row < maze.getHeight() && col > 0 && col < maze.getWidth()) 
    {
        if (cells[row][col - 1] == 0)
        {
            PossibleMoves.push_back(Direction::left);
        }
    }
    if (row < maze.getHeight() && row >= 0 && col >= 0 && col < maze.getWidth() - 1)
    {
        if (cells[row][col + 1] == 0)
        {
            PossibleMoves.push_back(Direction::right);
        }
    }
    if (col >= 0 && col < maze.getWidth() && row > 0 && row < maze.getHeight())
    {
        if (cells[row - 1][col] == 0)
        {
            PossibleMoves.push_back(Direction::up);
        }
    }
    if (col < maze.getWidth() && col >= 0 && row >= 0 && row < maze.getHeight() - 1)
    {
        if (cells[row + 1][col] == 0)
        {
            PossibleMoves.push_back(Direction::down);
        }
    }
}
Direction getRandomDirection(std::vector<Direction> &PossibleMoves)
{   
    int num = PossibleMoves.size();
    std::uniform_int_distribution<int> distribution{0, num - 1};
    return PossibleMoves[distribution(engine)];
}

void RecursiveMazeGenerator(Maze &maze, 
std::vector<std::vector<bool>> &cells,
int row, int col)
{
    cells[row][col] = 1;
    MovementPossible(PossibleMoves, maze, cells, row, col);
    while (PossibleMoves.size() != 0)
    {
        Direction someDirection = getRandomDirection(PossibleMoves);
        maze.removeWall(col, row, someDirection);
        int new_row = row;
        int new_col = col;
        if (someDirection == Direction::left)
        {
            new_col -= 1;
        }
        else if (someDirection == Direction::right)
        {
            new_col += 1;
        }        
        else if (someDirection == Direction::up)
        {
            new_row -= 1;
        }
        else if (someDirection == Direction::down)
        {
            new_row += 1;
        }
    PossibleMoves.clear();
    RecursiveMazeGenerator(maze, cells, new_row, new_col);
    MovementPossible(PossibleMoves, maze, cells, row, col);
    }       
}

void PerfectMazeGenerator::generateMaze(Maze &maze)
{
    int rows = maze.getHeight();
    int cols = maze.getWidth();
    maze.addAllWalls();
    std::vector<std::vector<bool>> cells(rows, std::vector<bool>(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cells[i][j] = 0;    //all cells are unvisited to begin
        }
    }    
    RecursiveMazeGenerator(maze, cells, 0, 0);
};