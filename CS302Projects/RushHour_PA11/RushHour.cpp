/**
	@file RushHour.cpp
	
	@brief Driver file for our RushHourClasses files.
	
	@mainpage reads the informatioon from keyboard which will consist of one or more scenarios, Each scenario begins with 
	a single integern which will be the number of cars. There will be n lines of inputs each representing 1 vehicle. Each vehicle consists of a space separated list of 
	(a) a decimal number, 2 or 3, representing the length of that vehicle in grid squares,
	(b) an uppercase letter H or V, indicating horizontal or vertical orientation for that vehicle,
	(c) a decimal number 0-5 indicating the row number (numbered North to South) of the vehicle
	(or of its northernmost square, if it is oriented vertically) in the initial position.
	(d) a decimal number 0-5 indicating the column number (numbered West to East) of the vehicle
	(or of its westernmost square, if it is oriented horizontally) in the initial position.
	The first vehicle in the sequence will always be your horizontally-oriented car which needs to get
	to the right edge of the grid. We may assume our vehicle can always escape.
	The last scenario will be indicated by a scenario with 0 vehicles. This scenario should not beprocessed.
	
	@author Pedram Safaei
	@author Omar Kamal
	@author Zachary Sonner
	
	@version VERSION 1.0
	
	@date 12/6/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
*/

// Program Description/Support /////////////////////////////////////
/**
	@mainpage @brief program requires support from one class file , which consists of a board class which includes a vehicle class.
	the files are:
		RushHourClasses.h		- specification file for our board and vehicle class
		RushHourClasses.cpp 	- implementation for our board and vehicle class
*/

// Header Files ///////////////////////////////////////////////////
//
#include "RushHourClasses.h"
//


int solve(Board currentBoard, const int& numCars);

// Main Function Implementation ///////////////////////////////////
//
int main()
{

	int scenario = 1;
	int numCars = 0;

	Board currentBoard;

	cin >> numCars;

	while(numCars > 0)
	{
		
		currentBoard.SaveTheData(numCars);

		cout << "Scenario " << scenario << " requires " << solve(currentBoard, numCars) << " moves" << endl;

		currentBoard.clear();

		cin >> numCars;

		scenario++;

	}

	return 0;

}
//

/** 
	@brief This function is used to solve thr rush hour board and returns the number of moves it took to solve. It does this by moving
	       a car forward, checking if we have seen he board before and if we havent, adding it to the queue, moving it back again and 
	       repeating this process for backwards.
	@param Board currentBoard, current board that we are working with
	@param const int& numCars, number of cars will be passed in
	@return either number of moves performed or -1 for failing
	@detail @bAlgorithm
	-# First after moving forward, we check if we have seen the board beofre, if we have we dont add it to the queue. 
	   If we havent seen the board before we add it to the queue and move the backwards. This is repeated for backwards.
	-# Queue is from the STL library and is of type Board. Boards are added to the queue is we have not seen them
	   before
	-# The map allwos us to save board configurations as strings so we can refernce it to see if
	   we have seen that board before
*/
int solve(Board currentBoard, const int& numCars)
{

	int numMoves = 0;

	map <string, int> visitedBoards;
	queue <Board> toBeProcessed;

	toBeProcessed.push(currentBoard);
	visitedBoards.insert(pair<string, int>(currentBoard.c2string(), numMoves));

	while(!toBeProcessed.empty())
	{


		//board comes from queue
		currentBoard = toBeProcessed.front();
		toBeProcessed.pop();
		numMoves = visitedBoards.find(currentBoard.c2string())->second;
		
		if(currentBoard.IsSolved())
		{
			return numMoves;
		}
		++numMoves;

		//continue process with popped board
		for(int i = 0; i < numCars; i++)
		{

			if(currentBoard.forward(i))
			{
				//check if board exists
				if(visitedBoards.find(currentBoard.c2string()) == visitedBoards.end())
				{
					//if not add it to the queue
					toBeProcessed.push(currentBoard);
					//convert to string
					//add to map
					visitedBoards.insert(pair<string,int>(currentBoard.c2string(), numMoves));
				}
				//if yes disregard it
				//move backward
				currentBoard.backward(i);
			}
			//if moveBackwards
			if(currentBoard.backward(i))
			{
				//check if board exists
				if(visitedBoards.find(currentBoard.c2string()) == visitedBoards.end())
				{
					//if not add it to the queue
					toBeProcessed.push(currentBoard);
					//convert to string
					//add to map
					visitedBoards.insert(pair<string,int>(currentBoard.c2string(), numMoves));
				}
				//if yes disregard it
				//move forward
				currentBoard.forward(i);
			}
		}
	}

	return -1;
}
