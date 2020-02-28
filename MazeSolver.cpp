//
//  MazeSolver.cpp
//  project
//
//  Created by Tawhid Mahmud on 11/6/18.
//  Copyright © 2018 Tawhid Mahmud. All rights reserved.
//

#include "MazeSolver.hpp"


//constructor
//pre: input file is in correct format with first two values being integers
//      followed by valid maze characters in {'_', '*','$'}
//post: if inuput file cannot be read outputs "Cannot read from input_file_name"
//      otherwise sets maze_rows_ and maze_columns from first two values in input file
//      and allocates two 2-dimesional array of size maze_rows_ and maze_columns
//      both maze_ and solution_ are initialized with characters read from input
MazeSolver::MazeSolver(std::string input_file)
{
    
    int row =0, col =0;
    std::ifstream stream;
    stream.open(input_file);
    if(!stream)
    {
        std::cout << "Cannot read from input_file_name" <<  std::endl;
    }
    stream >> row >> col;
    //std::cout << row << col;
    
    
    initializeMaze(row, col);
    fillMaze(stream);
    
    
    maze_ready = true;
    initializeSolution();
    stream.close();
    
}

// destructor
//post: deletes maze_ and solution_
MazeSolver::~MazeSolver()
{
    for(int i =0; i < maze_rows_; i++)
    {
        delete []maze_[i];
    }
    
    delete []maze_;
    
    for(int i =0; i < maze_rows_; i++)
    {
        delete []solution_[i];
    }
    
    delete []solution_;
}



//return: true if maze has been initialized, false otherwise
bool MazeSolver::mazeIsReady() {
    return maze_ready;
}

//pre: maze_ has been initialized with valid character values in {'_', '*','$'}
//post: solution_ has been marked with '>' signs along the path to the exit
//      prints "Found the exit!!!" if exit is found
//      or "This maze has no solution." if no exit could be found
//return: true if exit is found, false otherwise

bool MazeSolver::solveMaze()
{
    Position current;
    current.row = 0;
    current.column = 0;
    while(!backtrack_stack_.empty())
    {
        
        if(maze_[current.row][current.column] == '$')
        {
            std::cout << "Found Exit!!!" << std::endl;
            return true;
        }
        else if (extendPath(current))
        {
            solution_[current.row][current.column] = '>';
            current = backtrack_stack_.top();
            
        }
        else
        {
            maze_[current.row][current.column]= 'X';
            solution_[current.row][current.column] ='@';
            backtrack_stack_.pop();
            if(!backtrack_stack_.empty())
            {
                current = backtrack_stack_.top();
                
            }
            else{
                std::cout << "This maze has no solution." << std::endl;
                return false;
            }
            
        }
    }
    return false;
}


//post: prints the solution to the standard output stream
//      with single space character between each maze character
void MazeSolver::printSolution()
{
    std::cout << "Solution" << std::endl;
    
    for(int i= 0; i<maze_rows_; i++)
    {
        for(int j= 0; j<maze_columns_; j++)
        {
            std::cout << solution_[i][j] << " ";
            
            
        }
        std::cout << std::endl;
    }
}


//  ------------------------------------------------------------------------------



//PRIVATE MEMBER FUNCTIONS (helper functions)


//pre: rows and columns are positive integers
//post: allocates maze_ with rows and columns
//called by constructor
void MazeSolver::initializeMaze(int rows, int columns)
{
    maze_rows_ = rows;
    maze_columns_ = columns;
    
    maze_ = new char*[rows];
    for(int i =0; i<rows; i++)
    {
        maze_[i] = new char[columns];
    }
    
    
}


//pre: maze_ has been allocated with the correct number of rows and columns read from input file
//post: fills in maze_ with characters read from input file
//called by constructor

void MazeSolver::fillMaze(std::ifstream& input_stream)
{
    std::cout << "Maze " << std::endl;
    char new_char;
    
    for(int i= 0; i<maze_rows_; i++)
    {
        for(int j= 0; j<maze_columns_; j++)
        {
            input_stream >> new_char;
            maze_[i][j]=new_char;
            std::cout << maze_[i][j] << " ";
            
            
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl << std::endl;
}



//pre: maze_ has been initialized with valid character values in {'_', '*','$'}
//     start position is always [0][0]
//post: initializes solution_ with a copy of maze_
//      initializes backtrack_stack_  with all viable paths from position [0][0]
//      and mark current position as visited ( > ) on solution_
//called by constructor
void MazeSolver::initializeSolution()
{
    Position start;
    start.row =0;
    start.column =0;
    copyMazetoSolution();
    
    if(mazeIsReady())
    {
        backtrack_stack_.push(start);
        solution_[start.row][start.column] = '>';
    }
    
}

//pre: maze_ has been properly initialized
//post: allocates solution_ to the correct number of rows and columns
//      and copies the contents of maze_ into solution_
//called by initializeSolution()
void  MazeSolver::copyMazetoSolution()
{
    
    for(int i =0; i<maze_rows_; i++)
    {
        if (mazeIsReady())
        {
            solution_ = new char*[maze_rows_];
            for(int i =0; i<maze_rows_; i++)
            {
                solution_[i] = new char[maze_columns_];
            }
        }
        for(int i =0; i<maze_rows_; i++)
        {
            for(int j =0; j<maze_columns_; j++)
            {
                solution_[i][j] = maze_[i][j];
            }
        }
    }
}

//pre: current_position is a valid position on the maze_
//post: adds all positions extensible from current_position to backtrack_stack_
//return: true if path was extended, false otherwise
//called by solveMaze()

bool MazeSolver::extendPath(Position current_position){
    Position new_position;
    
    bool extended = false;
    
    if(isExtensible(current_position, SOUTH) && current_position.row < maze_rows_ && current_position.column < maze_columns_) {
        new_position = getNewPosition(current_position, SOUTH);
        backtrack_stack_.push(new_position);       // pushes the location South of current into stack
        extended = true;
    }
    
    if(isExtensible(current_position, EAST) && current_position.row < maze_rows_ && current_position.column < maze_columns_) {
        new_position = getNewPosition(current_position, EAST);
        backtrack_stack_.push(new_position);    // pushes the location East of current into stack
        extended = true;
        
    }
    
    return extended;
}

 
 //pre: old_position is a Position initialized with row and column to valid positions in maze_ and it is extensible in direction dir
 //return: a new Position on the maze moving in direction dir from old_position
 //called by extendPath()
 
Position MazeSolver::getNewPosition(Position old_position, direction dir) {
    Position new_position;
    
    if(isExtensible(old_position, dir) && dir == SOUTH)// && old_position.row < maze_rows_ && old_position.column < maze_columns_)
    {
        new_position.row = old_position.row +1;
        new_position.column = old_position.column;
    }
    else if(isExtensible(old_position, dir) && dir == EAST)// && old_position.row < maze_rows_ && old_position.column < maze_columns_)
    {
        new_position.row = old_position.row;
        new_position.column = old_position.column+1;
    }
    
    return new_position;
}
 
 //checks if the path can be extended in maze_ from position current_position in direction dir
 //return: true if path can be extended given current_position and dir, false otherwise
 //called by extendPath
    bool MazeSolver::isExtensible(Position current_position, direction dir) {
        if( dir == SOUTH && current_position.row +1 < maze_rows_ && current_position.column < maze_columns_ && (maze_[current_position.row +1][current_position.column] == '_' || maze_[current_position.row +1][current_position.column] == '$'))
        {
            return true;
        }
        else if(dir == EAST && current_position.column +1 < maze_columns_ && current_position.row < maze_rows_ && (maze_[current_position.row][current_position.column+1] == '_' || maze_[current_position.row][current_position.column+1] == '$'))
        {
            return true;
        }
        
        return false;
    }
