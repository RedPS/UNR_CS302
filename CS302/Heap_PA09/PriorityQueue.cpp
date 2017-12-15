/**
	@file PriorityQueue.cpp
	
	@brief This is just a simple implementation for Heap, PA09. This file in particular belongs to the PriorityQueue.
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 11/14/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
		
*/
#include "PriorityQueue.h"

/**
	@brief default constructor 
	@param maxNumber, which is the max number of data
	@return None
*/
template <typename DataType, typename KeyType, typename Comparator >
PriorityQueue < DataType, KeyType, Comparator > :: PriorityQueue (int maxNumber) : Heap < DataType, KeyType, Comparator > :: Heap(maxNumber) 
{
	
}

/**
	@brief enqueue, used for inserting stuff
	@param a new data item, so we know what to insert_iterator
	@return NONE
*/
template < typename DataType, typename KeyType, typename Comparator >
void PriorityQueue< DataType, KeyType, Comparator > :: enqueue (const DataType& newDataItem)
{
	Heap < DataType, KeyType, Comparator > :: insert (newDataItem);
}

/**
	@brief dequeue, used for removing stuff 
	@param none
	@return either the data that was removed or logic_error(which will be handled in remove())
*/
template < typename DataType, typename KeyType, typename Comparator >
DataType PriorityQueue < DataType, KeyType, Comparator > :: dequeue ()
{
   return Heap< DataType, KeyType, Comparator>::remove();
}