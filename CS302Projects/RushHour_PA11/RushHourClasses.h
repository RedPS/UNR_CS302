/**
	@file RushHourClasses.h
	
	@brief There is a commercially available puzzle called "Rush Hour" in which your goal is to unstick a complicated traffic jam.
	The puzzle is played on a 6x6 grid of squares. Vehicles (cars and trucks) are scattered over the grid at integer locations.
	Both types of vehicles are 1 square wide. Cars are 2 squares long, and trucks are 3 squares long.
	Vehicles may be oriented either horizontally (East-West) or vertically (North-South) relative to the grid.
	Vehicles cannot move through each other, cannot turn, and cannot move off the edge of the grid. They can move straight forwards
	and backwards along their direction of orientation, as long as they are not blocked by another vehicle or the edge of the grid.
	Only one vehicle may move at a time, and it may move by only one square at a time.
	The goal of the puzzle is to move vehicles back and forth until a particular horizontally-oriented vehicle - your own car - arrives 
	at the rightmost (eastern-most) edge of the grid, where it is considered to have escaped the traffic jam.
	
	@author Pedram Safaei
	@author Omar Kamal
	@author Zachary Sonner
	
	@version VERSION 1.0
	
	@date 12/6/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
*/

// Precompiler Directives //////////////////////////////////////////
//
#ifndef RUSHHOURCLASSES_H
#define RUSHHOURCLASSES_H
//
// Header Files ///////////////////////////////////////////////////
//
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <sstream>

using namespace std;
//

class Board
{

  public:

  static const int MAX_CARS = 18;
  static const int MAX_ROWS = 6;
  static const int MAX_COLS = MAX_ROWS;

  Board();
  Board( const Board& );
  Board& operator=( const Board& );

  void SaveTheData(const int& totalNum);
  void clear();
  void printBoard();

  bool forward( int IndexForCar);
  bool backward( int IndexForCar);
  bool IsSolved() const;
  bool CanItMove(int row, int col) const;
  string c2string();

  private:

  class Vehicle
  {
     public:
       int length;
       int Row;
       int Col;
       char orientation;
  };

  int numCars;
  Vehicle boardVehicles[MAX_CARS];
  char board[MAX_ROWS][MAX_COLS];

};
// Terminating Precompiler Directives ///////////////////////////////
//
#endif 
//