/**
	@file Heap.cpp
	
	@brief This is just a simple implementation for heap.h, PA09.
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 11/14/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
		
*/

#include "Heap.h"

/**
	@brief Default constructor
	@param maxNumber which is the size of the heap
	@return NONE
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap < DataType, KeyType, Comparator> ::Heap ( int maxNumber )
{
   size = 0;
   maxSize = maxNumber;
   dataItems = new DataType[ maxSize ];
}
/**
	@brief Copy Constructor
	@param other, which will be the original heap
	@return NONE
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap< DataType, KeyType, Comparator>::Heap ( const Heap& other )
{
   /// I'm just going to call the operator = 
   *this = other;
}
/**
	@brief operator =
	@param other, which will be the original heap
	@return NONE
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType,KeyType,Comparator>& Heap<DataType,KeyType,Comparator>::operator=(const Heap& other)
{
	if(this != &other)
	{
		clear();
		
		size = other.size;
		maxSize = other.maxSize;
		
		dataItems = new DataType[maxSize];
		
		for(int i = 0; i < size; i++)
		{
			dataItems[i] = other.dataItems[i];
		}
		
	}
	
	return *this;
}
/**
	@brief destructor, just calls clear to clear everything
	@param nothing
	@return NONE
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType,KeyType,Comparator>::~Heap()
{
	clear();
}
/**
	@brief Remove, it will remove the data with the highest priority and returns it, logic error if empty
	@param nothing
	@return data that was deleted
*/
template <typename DataType, typename KeyType, typename Comparator>
DataType Heap< DataType, KeyType, Comparator>::remove () throw ( logic_error )
{
	if(isEmpty() == true)
	{
		throw logic_error("Remove(): Heap is Empty, Can't Remove");
	}
	
	DataType temp;
	int current_index = 0;
	DataType DataToReturn;
	int max = current_index;
	
	size--; 
	
	DataToReturn = dataItems[current_index];
	dataItems[current_index] = dataItems[size];
	
	while(current_index < size)
	{
		if(current_index*2 + 2 < size) //two child
		{
			// if left is larger
			if(comparator( dataItems[ current_index*2 + 1 ].getPriority(), dataItems[max].getPriority()))
			{
				max = current_index*2 + 1;
			}
			//right larger 
			if( comparator( dataItems[ (current_index*2) + 2 ].getPriority(), dataItems[max].getPriority()))
			{
				max = current_index*2 + 2;
			}
			//child is greater than parent
			if( max != current_index )
			{
				temp = dataItems[current_index];
				dataItems[ current_index ] = dataItems[max];
				dataItems[max] = temp;
				current_index = max; //update index number
			}
			// parent is largest the largest, then just return
			else 
			{
				return DataToReturn;
			}
			
		}
		
		else if(current_index * 2 + 1 < size) //only one child (since it is a heap then left)
		{
			if( comparator( dataItems[current_index * 2 + 1].getPriority(), dataItems[max].getPriority()))
			{
				max = current_index * 2 + 1;
				
				temp = dataItems[current_index];
				dataItems[current_index] = dataItems[max];
				dataItems[max] = temp;
				
				current_index = max;
			}
			else
				return DataToReturn;
		}
		
		else //check over/over no child  to check 
			return DataToReturn;
	}
	
	return DataToReturn;
}
/**
	@brief clear, clear everything aka call remove until everything's gone
	@param nothing
	@return NONE
*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap < DataType, KeyType, Comparator> :: clear ()
{
   while( isEmpty() == false )
   {
      remove();
   }
}
/**
	@brief isEmpty, just return the size if not 0 then it is not empty
	@param nothing
	@return true/ false if empty then true
*/
template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType,KeyType,Comparator>::isEmpty() const
{
	return size == 0;
}
/**
	@brief isFull, just return the size if not 0 then it is not empty and it's full
	@param nothing
	@return true/ false if full then true
*/
template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType,KeyType,Comparator>::isFull() const
{
	return size == maxSize;
}
/**
	@brief show structure, given to us
	@param nothing
	@return NONE
*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType,KeyType,Comparator>::showStructure() const
{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
	
}
/**
	@brief show structure helper, given to us
	@param index, and level
	@return NONE
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const
{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        /// Output right subtree
        for ( j = 0 ; j < level ; j++ )        /// Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   /// Output dataItems's priority
        if ( 2*index+2 < size )                /// Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        /// Output left subtree
    }
	
}
/**
	@brief writelevel, go through the entire heap, and output
	@param nothing
	@return NONE
*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType,KeyType,Comparator>::writeLevels() const
{
	int currentNode = 0;
	int nextLevel = 1;
	while(currentNode < size)
	{
		if(currentNode < nextLevel)
		{
			cout << dataItems[currentNode].getPriority() << " ";
			currentNode++;
		}
		else
		{
			cout << endl;
			nextLevel = 2*currentNode + 1;
		}
		
	}
	cout << endl;
}
/**
	@brief insert, insert into the node, to the last spot and heapify
	@param newdataitem, the item that you want to insert
	@return NONE
*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType,KeyType,Comparator>::insert(const DataType &newDataItem) throw (logic_error)
{
	DataType temp;
	int current_index = size;
	
	if (isFull () == true)
	{
		throw logic_error("Insert(), heap is full");
	}
	
	dataItems[current_index] = newDataItem;
	size++;
	//compare to parent
	while(comparator( dataItems[current_index].getPriority(), dataItems[(current_index - 1) / 2].getPriority()))
	{
		//swap start
		temp = dataItems[(current_index - 1) / 2];
		dataItems[(current_index - 1) / 2] = dataItems[current_index];
		dataItems[current_index] = temp;
		//swap end
		
		current_index = (current_index - 1) / 2; //update index
	}
	
}

























































