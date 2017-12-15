/**
	@file RushHourClasses.cpp
	
	@brief This is the implmentation file for RushHourClasses.h
	
	@author Pedram Safaei
	@author Omar Kamal
	@author Zachary Sonner
	
	@version VERSION 1.0
	
	@date 12/6/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
*/


// Header Files ///////////////////////////////////////////////////
//
#include "RushHourClasses.h"
//

/**
	@brief default constructor, will set the number of cars to 0 since when the eboard gets created it should be empty of cars
	@param NONE
	@return NONE
*/
Board::Board()
{
	numCars = 0;
}

/**
	@brief copy constructor, it will copy a board to another board, in this case it is just calling operator= too do its job
	@param other, which is the original board passed in to be copid
	@return NONE
*/
Board::Board( const Board& other )
{
	*this = other;
}

/**
	@brief opertor=, it will coopy the values of the right hand side of the = sign to the left hand side by clearing it first (if it is not the same class)
	@param other, which is the original board passed in to be copid
	@return *this, which is the object
*/
Board& Board::operator=( const Board& other )
{

   if( this != &other )
   {
      clear();
      numCars = other.numCars;
      for( int i = 0; i < numCars; i++ )
      {
         boardVehicles[i] = other.boardVehicles[i];
      }
   }
   
   return *this;
}

/**
	@brief save the data function, it will save all of the data that the user has enteredd to our class of cars which is part of our board class
	@param totalnum, which is total number of cars
	@return NONE, it is a void  function
*/
void Board::SaveTheData(const int& totalNum)
{
  numCars = totalNum;
  for( int i = 0; i < numCars; ++i)
  {
    cin >> boardVehicles[i].length;
    cin >> boardVehicles[i].orientation;
    cin >> boardVehicles[i].Row;
    cin >> boardVehicles[i].Col;
  }

}

/**
	@brief forward, checks the orientation of the car and if the car is not at the edge and dcan move then it will move
	@param index for car, so we know which car we are trying to move
	@return true if the car can move and false if it can't
*/
bool Board::forward( int IndexForCar )
{
   // horizontal car
   if( boardVehicles[IndexForCar].orientation == 'H' )
   {
      //car  not at right edge of board can move right
      if( boardVehicles[IndexForCar].Col + boardVehicles[IndexForCar].length < 6 && CanItMove(boardVehicles[IndexForCar].Row, boardVehicles[IndexForCar].Col + boardVehicles[IndexForCar].length ))
      {
         // update Col val of car
         boardVehicles[IndexForCar].Col++;
         return true;
      }
   }

   else if( boardVehicles[IndexForCar].orientation == 'V' )
   {
      // car not at bottom edge of board  can move down
      if( boardVehicles[IndexForCar].Row + boardVehicles[IndexForCar].length < 6 && CanItMove(boardVehicles[IndexForCar].Row + boardVehicles[IndexForCar].length, boardVehicles[IndexForCar].Col ))
      {
         // update Row val of car
         boardVehicles[IndexForCar].Row++;
         return true;
      }
   }

   // false if no move !!!!!!!!!!!!
   return false;
}

/**
	@brief backward, checks the orientation of the car and if the car is not at the edge and dcan move then it will move
	@param index for car, so we know which car we are trying to move
	@return true if the car can move and false if it can't
*/
bool Board::backward( int IndexForCar )
{
   // for horizontal car
   if( boardVehicles[IndexForCar].orientation == 'H' )
   {
      //car  not at left edge of board can move left
      if( boardVehicles[IndexForCar].Col > 0 && CanItMove( boardVehicles[IndexForCar].Row, boardVehicles[IndexForCar].Col - 1))
      {
        // update Col val of car
         boardVehicles[IndexForCar].Col--;
         return true;
      }
   }

   // for vertical car
   else if( boardVehicles[IndexForCar].orientation == 'V' )
   {
      // car not at top edge of board  can move up
      if( boardVehicles[IndexForCar].Row > 0 && CanItMove( boardVehicles[IndexForCar].Row - 1, boardVehicles[ IndexForCar ].Col ))
      {
         // update Row val of car
         boardVehicles[IndexForCar].Row--;
         return true;
      }
   }

   // No move !!!!!
   return false;
}

/**
	@brief Is solved will check if the board is solved or not
	@param NONE
	@return boolean value if it is solved and the car (first car) is at the edge then true else false 
*/
bool Board::IsSolved() const
{
   if( numCars > 0 )
   {
	  //Checks if car of index 0 (red car) is at the edge of the board
	  bool check = boardVehicles[0].Col + boardVehicles[0].length == 6;
      return check;
   } //if car is at right edge and board is solved.
   return true;
}

/**
	@brief can it move, we will have to use this functioon in our move forward and backward because we need to know if we can move them before attempting to move the cars.
	@param row and col, which car according to their row and column.
	@return true if the car at that specific row and column can move else false.
*/
bool Board::CanItMove( int Row, int Col ) const
{
   //cars
   for( int i = 0; i < numCars; i++ )
   {
      //length of car
      for( int j = 0; j < boardVehicles[i].length; j++ )
      {
         // if horizontal
         if( boardVehicles[i].orientation == 'H' )
         {
            if( Row == boardVehicles[i].Row && Col == boardVehicles[i].Col + j )
            {
               return false;
            }
         }
         // if  vertical
         else if( boardVehicles[i].orientation == 'V' )
         {
            if( Row == boardVehicles[i].Row + j && Col == boardVehicles[i].Col )
            {
               return false;
            }
         }
      }
   }
   return true;
}

/**
	@brief clear function,sets the number of cars to 0
	@param NONE
	@return NONE
*/
void Board::clear()
{
   numCars = 0;
}

/**
	@brief converting to string function, we will use this to conver our board of vehicles to string and pass it to the map, for more informatioon refer to the main file.
	@param NONE
	@return string version of the vehicle boards ( car data)
*/
string Board::c2string()
{

	stringstream s;
	string sreturn;

	// concatenate stringstream with each car's data
	for( int i = 0; i < numCars; i++ )
	{
		s << boardVehicles[i].length
		  << boardVehicles[i].orientation
		  << boardVehicles[i].Row
		  << boardVehicles[i].Col;
	}

	// convert from string stream to string
	sreturn = s.str();

	// return string (car data)
	return sreturn;
}

/**
	@brief print to board, used for visualizing the board
	@param NONE
	@return NONE
*/
void Board::printBoard()
{
    for(int i = 0; i < 6; ++i)
	{
        for(int j = 0; j < 6; ++j)
		{
            cout << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
