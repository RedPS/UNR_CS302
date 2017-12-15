/**
	@file rushhour.cpp
	
	@brief  There is a commercially available puzzle called "Rush Hour" in which your goal is to unstick a
	complicated traffic jam. The puzzle is played on a 6x6 grid of squares. Vehicles (cars and
	trucks) are scattered over the grid at integer locations, as shown below. Both types of vehicles
	are 1 square wide. Cars are 2 squares long, and trucks are 3 squares long. Vehicles may be
	oriented either horizontally (East-West) or vertically (North-South) relative to the grid.
	Vehicles cannot move through each other, cannot turn, and cannot move off the edge of the grid.
	They can move straight forwards and backwards along their direction of orientation, as long as
	they are not blocked by another vehicle or the edge of the grid. Only one vehicle may move at a
	time, and it may move by only one square at a time.
	The goal of the puzzle is to move vehicles back and forth until a particular horizontally-oriented
	vehicle - your own car - arrives at the rightmost (eastern-most) edge of the grid, where it is
	considered to have escaped the traffic jam.
	The goal of this problem is to write a program that will not only solve any solvable Rush Hour
	puzzle instance, but will give a solution requiring the minimum possible number of (1-square-ata-
	time) moves.The input file [was changed to keyboard by the instructor] will consist of one or more 
	input scenarios. Each scenario begins with a single integer n, giving the number of vehicles 
	in the scenario. There will then be n lines o input, each representing 1 vehicle. Each vehicle consists 
	of a space-separated list of:
	(a) a decimal number, 2 or 3, representing the length of that vehicle in grid squares,
	(b) an uppercase letter H or V, indicating horizontal or vertical orientation for that vehicle,
	(c) a decimal number 0-5 indicating the row number (numbered North to South) of the vehicle
	(or of its northernmost square, if it is oriented vertically) in the initial position.
	(d) a decimal number 0-5 indicating the column number (numbered West to East) of the vehicle
	(or of its westernmost square, if it is oriented horizontally) in the initial position.
	The statement "Scenario k requires x moves." on a line by itself, where k is the number of the
	scenario, starting with 1, and x is the (decimal integer) minimum number of moves required to
	solve the puzzle. This is immediately followed by a sequence of that many moves, one per line,
	that solves the puzzle. Each move consists of
	(a) A decimal number designating the vehicle to be moved, from the vehicles in the input list.
	The first vehicle in the list (your car) is vehicle number 0; subsequent vehicles are numbered
	sequentially from 1.
	The Author of this program has used the below discussion threads from StackOverFlow to get an idea of how 
	The alogorithm works for solving this puzzle recursively. No code was copied from the below website except 
	referecing a pointer, [*&] this was obtained from the first link.
	
	https://stackoverflow.com/questions/5789806/meaning-of-and-in-c
	https://stackoverflow.com/questions/2877724/rush-hour-solving-the-game
	https://stackoverflow.com/questions/5860581/a-search-for-rush-hour-game
	https://stackoverflow.com/questions/34341162/breadth-first-search-cycling-in-rush-hour-solver-when-no-solution-is-available
	
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 10/1/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
	This program was not tested with the input file that is in the PDF instructions, since that input file will take a long time to execute.
	
*/

/*
	Since I am documenting the function definitions, I saw no pints in actually documenting the implementation which is at the end of this 
	File, they are the same thing plus the implementation.

*/



// Header Filess ////////////////////////////////////////////////
//
#include <iostream>

/**
	@brief Since cars and dtrucks had many things to keep track of having a structure like this would  help 
	alot, we could also change that to just a struct, since there are no provate members then there is no point 
	in actually having it as a class, but the author decided to leave it like this, since he started it like this.
	We basically needed varibles to keep track of the vehicle, lenght of it or the dimention of it, direction of it,
	which is either 'H' for Horizontal or 'V' for Vertical. and then the most important thing is to keep track of the
	position both rows and columns of the vehicle.
	
*/
class Transportation
{
	public:
	
	int Which_Vehicle;
	
	int dimention;
	
	char direction;
	
	int Y_pos;
	int X_pos;
		
};

/**
	@brief This function will set up the board [which is 6 by 6] and prepares the board so we can 
	put everyything (all the cars) inside the board with their respective values.
	
	@param int board[6][6] is the board that we have, it is 6 row and d 6 columns, this could probably 
	be cleaner if I didn't harcode the row and column value but tis program is not optimized in general 
	and I saw no points in having global variables.
	
	@param int NumberOfVehicles, we read this number before doing anything and the user needs to enter 
	the number of cars first when the program runs, we will need this number for our loop.
	
	@param Transportation *&Vehicles, initially I had some problems with this code but after searching the 
	internet and seeing this post https://stackoverflow.com/questions/5789806/meaning-of-and-in-c on stackoverflow
	I came up with a good way of passing pointers by reference.
	
	
	@return Nothing, this is a void function.
*/
void Set_board(int board[6][6], int NumberOfVehicles ,Transportation *&Vehicles);

/**
	@brief This function will place all the cars that were read in the previous function (Set_board) on the board,
	so these will fill the board with their values and we will know where they are since we initially set the board up 
	with -1s in all the places, so now where ever we don't have a -1 we have a car.
	
	@param int board[6][6] is the board that we have, it is 6 row and d 6 columns, this could probably 
	be cleaner if I didn't harcode the row and column value but tis program is not optimized in general 
	and I saw no points in having global variables.
	
	@param Transportation *&Vehicles, initially I had some problems with this code but after searching the 
	internet and seeing this post https://stackoverflow.com/questions/5789806/meaning-of-and-in-c on stackoverflow
	I came up with a good way of passing pointers by reference.
	
	@param int Y_pos, this is the row position of each car that gets passed in this function.
	
	@param int X_pos, this is the coluumn position of each car that gets passed in this function.
	
	
	@return Nothing, this is a void function.
*/
void PlaceOnBoard(int board[6][6], Transportation &Vehicles, int Y_pos, int X_pos);

/**
	@brief This function will move the cars from their initial position, this function was actually tricky too 
	write, since we had to know if the cars could move forward or backwards and even then we had dto find if the 
	cars were vertical, or horizontal, so basically we neeeded lots of if statements inside if statements inside
	if statements, basically a headache.
	
	@param int board[6][6] is the board that we have, it is 6 row and d 6 columns, this could probably 
	be cleaner if I didn't harcode the row and column value but tis program is not optimized in general 
	and I saw no points in having global variables.
	
	@param Transportation *&Vehicles, initially I had some problems with this code but after searching the 
	internet and seeing this post https://stackoverflow.com/questions/5789806/meaning-of-and-in-c on stackoverflow
	I came up with a good way of passing pointers by reference.
	
	@param bool direction we had to pass in forwards or backwards.
	
	@return returns true or false, to indicate if the moving of the vehicle was suuccessful or not.
*/
bool Move( int board[6][6], Transportation & Vehicles, bool direction);

/**
	@brief This function is the recursion part which we were supposed to have in our program, basically this function 
	will check if we have solved the puzzle, if not it will continue calling itself and going forrward and backwards using 
	the move function we implemented before to see if it is solved or not.
	
	@param int board[6][6] is the board that we have, it is 6 row and d 6 columns, this could probably 
	be cleaner if I didn't harcode the row and column value but tis program is not optimized in general 
	and I saw no points in having global variables.
	
	@param Transportation *&Vehicles, initially I had some problems with this code but after searching the 
	internet and seeing this post https://stackoverflow.com/questions/5789806/meaning-of-and-in-c on stackoverflow
	I came up with a good way of passing pointers by reference.
	
	@param int NumberOfVehicles, we read this number before doing anything and the user needs to enter 
	the number of cars first when the program runs, we will need this number for our loop.
	
	@param int &moves, we are passing in this one by reference, this is declared 10 in our main sincce 10 is the max
	number of moves that we are allowed to perform.
	
	@param int PerformedMoves, this is for keeping track of how many moves we have done, we pass in 0 initially since 
	we start from 0 and we will check to make sure that it is less than moves which is 10 for this program.
	
	@return it will return the enumber of moves performed which started from 0;
*/
int solve_puzzle(int board[6][6], Transportation *&Vehicles, int NumberOfVehicles, int &moves, int PerformedMoves );

/**
	@brief This function will check to see if the marked car ( 0th car) has reached the end (has escaped).
	
	@param int board[6][6] is the board that we have, it is 6 row and d 6 columns, this could probably 
	be cleaner if I didn't harcode the row and column value but tis program is not optimized in general 
	and I saw no points in having global variables.
	
	@param int DoneMoves, this is for keeping track of how many moves we have done, we pass in 0 initially since 
	we start from 0 and we will check to make sure that it is less than moves which is 10 for this program.
	
	@param int &moves, we are passing in this one by reference, this is declared 10 in our main sincce 10 is the max
	number of moves that we are allowed to perform.
	
	@param Transportation *&Vehicles, initially I had some problems with this code but after searching the 
	internet and seeing this post https://stackoverflow.com/questions/5789806/meaning-of-and-in-c on stackoverflow
	I came up with a good way of passing pointers by reference.
	
	
	@return returns true or false, to indicate eif it actually reached the end or not.
*/
bool CheckEnd(int board[6][6], int DoneMoves, int Moves, Transportation &Vehicles);


// Main Function Implementation ///////////////////////////////////
//
int main()
{
	
	bool solve = true;
	int board[6][6];
	int moves = 10;
	int NumberOfVehicles = -1;
	
	Transportation * Vehicles; // we are going to get the number of cars and create an array of our structure.
	
	int count = 1; //which scenario
	
    while (solve == true) 
	{
		
		std::cin >> NumberOfVehicles;
		
		if( NumberOfVehicles == 0) // if no cars then get out.
		{
		    // the codes below are just to make sure the program exits, I know that this might look retarded 
		    // I could just do retrun 0 or I could just do solve = false and break, or I could even setup my
		    // loop in a way that I wouldn't even need this. or I could just do a while (true) and then break.
			solve = false; 
			return 0;
		}
		else 
		{
			Vehicles = new Transportation[NumberOfVehicles];
			
			Set_board(board, NumberOfVehicles ,Vehicles);
		}
		
		
		moves = 10; // our max moves are 10.
		
		moves = solve_puzzle(board, Vehicles, NumberOfVehicles, moves, 0);
		
		
		std::cout << "Scenario " << count << " requires " << moves << " moves" << std::endl;
		
		delete [] Vehicles; //prevent memory leak by deleting what we created.
		
		count++;
	}
	
	return 0;
	
}
void Set_board(int board[6][6], int NumberOfVehicles ,Transportation *&Vehicles)
{
	
	for(int i = 0; i < 6; i++)
	{
		for(int j=0; j < 6; j++)
		{
			board[i][j] = -1;
		}
	}
	
	for(int a = 0; a < NumberOfVehicles; a++)
	{
		
		Vehicles[a].Which_Vehicle = a;
		
		//get their information
		std::cin >> Vehicles[a].dimention
			     >> Vehicles[a].direction
		    	 >> Vehicles[a].Y_pos
			     >> Vehicles[a].X_pos;
		
		//place it one by one
		PlaceOnBoard(board, Vehicles[a], Vehicles[a].Y_pos, Vehicles[a].X_pos);
		
	}
}

void PlaceOnBoard(int board[6][6], Transportation &Vehicles, int Y_pos, int X_pos)
{
	
	Vehicles.Y_pos = Y_pos;
	Vehicles.X_pos = X_pos;
	
	for(int b = 0; b < Vehicles.dimention; b++)
		{
			board[Y_pos][X_pos] = Vehicles.Which_Vehicle;
			
			if(Vehicles.direction == 'V')
			{
				Y_pos++;
			}
			else if(Vehicles.direction == 'H')
			{
				X_pos++;
			}
		}
}

int solve_puzzle(int board[6][6], Transportation *&Vehicles, int NumberOfVehicles, int &moves, int PerformedMoves )
{
	const bool GoForward = true;
	const bool GoBackward = false;
	
	
	if(CheckEnd(board, PerformedMoves, moves, Vehicles[0]))
	{
		if(PerformedMoves < moves)
			moves = PerformedMoves;
	}
	else
	{
		for(int i = 0; i < NumberOfVehicles; i++)
		{
			if(Move(board, Vehicles[i], GoForward))
			{
				PerformedMoves++;
				
				solve_puzzle(board, Vehicles, NumberOfVehicles, moves, PerformedMoves);
				
				PerformedMoves--;
				
				Move(board, Vehicles[i], GoBackward);
			}
			if(Move(board, Vehicles[i], GoBackward))
			{
				PerformedMoves++;
				
				solve_puzzle(board, Vehicles, NumberOfVehicles, moves, PerformedMoves);
				
				PerformedMoves--;
				
				Move(board, Vehicles[i], GoForward);
			}
		}
	}
	
	return moves;
}

bool CheckEnd(int board[6][6], int DoneMoves, int Moves, Transportation &Vehicles)
{
	
	bool End = false;
	
	if(DoneMoves >= Moves)
	{
		End = true;
	}
	else if (board[Vehicles.Y_pos][5] == 0)
	{
		End = true;
	}
	else
	{
		
	}
	
	return End;
}

bool Move( int board[6][6], Transportation & Vehicles, bool direction)
{
	bool success = false;
	
	const bool GoForward = true;
	
	if(direction == GoForward)
	{
		if(Vehicles.direction == 'V')
		{
			if(Vehicles.Y_pos -1 >= 0)
			{
				if(board[Vehicles.Y_pos -1][Vehicles.X_pos] < 0)
				{
					PlaceOnBoard(board, Vehicles, Vehicles.Y_pos-1, Vehicles.X_pos);
					
					board[Vehicles.Y_pos + Vehicles.dimention][Vehicles.X_pos] = -1;
					
					success = true;
				}
			}
		}
		else
		{
			if((Vehicles.X_pos + Vehicles.dimention) < 6)
			{
				if(board[Vehicles.Y_pos][Vehicles.X_pos + Vehicles.dimention] < 0)
				{
					PlaceOnBoard(board, Vehicles, Vehicles.Y_pos, Vehicles.X_pos+1);
					
					board[Vehicles.Y_pos][Vehicles.X_pos-1] = -1;
					
					success = true;
				}
			}
		}
	}
	
	else
	{
		if( Vehicles.direction == 'V')
		{
			if((Vehicles.Y_pos + Vehicles.dimention) < 6)
			{
				if(board[Vehicles.Y_pos+Vehicles.dimention][Vehicles.X_pos] < 0)
				{
					PlaceOnBoard (board, Vehicles, Vehicles.Y_pos+1, Vehicles.X_pos);
					
					board[Vehicles.Y_pos - 1][Vehicles.X_pos] = -1;
					
					success = true;
				}
			}
		}
		else if ( Vehicles.direction == 'H')
		{
			if((Vehicles.X_pos - 1) >= 0)
			{
				if(board[Vehicles.Y_pos][Vehicles.X_pos - 1] < 0)
				{
					PlaceOnBoard(board, Vehicles, Vehicles.Y_pos,Vehicles.X_pos - 1);
					
					board[Vehicles.Y_pos][Vehicles.X_pos + Vehicles.dimention] = -1;
					
					success = true;
				}
			}
		}
	}
	
	return success;
}
