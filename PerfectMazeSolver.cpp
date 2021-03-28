#include <ics46/factory/DynamicFactory.hpp>
#include "PerfectMazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include <random>

ICS46_DYNAMIC_FACTORY_REGISTER(
    MazeSolver, PerfectMazeSolver, 
    "Perfect Solver (Required)");

PerfectMazeSolver::PerfectMazeSolver(){};
std::vector<Direction> PossibleMoves2; //tracks possible moves
std::random_device device2;
std::default_random_engine engine2{device2()};

void MovementPossible(const Maze& maze, std::vector<Direction> &PossibleMoves2, MazeSolution &mazeSolution, std::vector<std::vector<bool>> &cells, int row, int col)
{
    //all checks ensure x and y are in bounds and their adjacent cell is vacant
    if (row >= 0 && row < mazeSolution.getHeight() && col > 0 && col < mazeSolution.getWidth()) 
    {
        if (cells[row][col - 1] == 0 && !maze.wallExists(col, row, Direction::left))
        {
            PossibleMoves2.push_back(Direction::left);
        }
    }
    if (row < mazeSolution.getHeight() && row >= 0 && col >= 0 && col < mazeSolution.getWidth() - 1)
    {
        if (cells[row][col + 1] == 0 && !maze.wallExists(col, row, Direction::right))
        {
            PossibleMoves2.push_back(Direction::right);
        }
    }
    if (col >= 0 && col < mazeSolution.getWidth() && row > 0 && row < mazeSolution.getHeight())
    {
        if (cells[row - 1][col] == 0 && !maze.wallExists(col, row, Direction::up))
        {
            PossibleMoves2.push_back(Direction::up);

        }
    }
    if (col < mazeSolution.getWidth() && col >= 0 && row >= 0 && row < mazeSolution.getHeight() - 1)
    {
        if (cells[row + 1][col] == 0 && !maze.wallExists(col, row, Direction::down))
        {
            PossibleMoves2.push_back(Direction::down);
        }
    }
}
Direction getRandomDirection2(std::vector<Direction> &PossibleMoves)
{   
    int num = PossibleMoves2.size();
    std::uniform_int_distribution<int> distribution{0, num - 1};
    return PossibleMoves2[distribution(engine2)];
}

bool RecursiveMazeSolver(const Maze& maze, 
MazeSolution& mazeSolution, std::vector<std::vector<bool>> &cells,
int row, int col, int final_x, int final_y)
{
    if (col == final_x && row == final_y)
    {
        return 1;
    }
    cells[row][col] = 1;
    MovementPossible(maze, PossibleMoves2, mazeSolution, cells, row, col);
    while (PossibleMoves2.size() != 0)
    {
        Direction someDirection = getRandomDirection2(PossibleMoves2);  
        int new_row = row;
        int new_col = col;  
        mazeSolution.extend(someDirection);     
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
    PossibleMoves2.clear();
    if (RecursiveMazeSolver(maze, mazeSolution, cells, new_row, new_col, final_x, final_y))
    {
        return 1;
    }
    mazeSolution.backUp();
    MovementPossible(maze, PossibleMoves2, mazeSolution, cells, row, col);
    }
    return 0;
}

void PerfectMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    int rows = maze.getHeight();
    int cols = maze.getWidth();
    std::pair<int, int> finalCell = mazeSolution.getEndingCell();
    int final_x = finalCell.first;
    int final_y = finalCell.second;
    std::vector<std::vector<bool>> cells(rows, std::vector<bool>(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cells[i][j] = 0;    //all cells are unvisited to begin
        }
    }   
    RecursiveMazeSolver(maze, mazeSolution, cells, 0, 0, 
    final_x, final_y);     
};
