/**
	@file HashTable.cpp
	
	@brief This is just a simple implementation for HashTables using Binary search Tree for chaining, with that 
	we will also have to write implementation for Binary Search(already did, last project), and use that with 
	this program to implement HashTables.
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 11/07/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 

*/

#include "HashTable.h"

/**
	@brief  default Constructor, sets the defaults size and allocates memory
	
	@param  Size of the tavle
	
	@return None
*/
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>::HashTable(int initTableSize)
{
	
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
	
}

/**
	@brief  copy constructor, used to copy the HashTable
	
	@param  other, which is the original hashtable, so we can copy from this to a new one
	
	@return None
*/

template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>::HashTable(const HashTable& other)
{
	
	copyTable(other);
	
}

/**
	@brief  assignment operator, used to copy the HashTable using the = operator
	
	@param  other, which is the original hashtable, so we can copy from this to a new one
	
	@return None
*/

template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>& HashTable<DataType,KeyType>::operator=(const HashTable& other)
{
	if(this !=&other)
	{
		clear();
		copyTable(other);
	}
	
	return *this;
	
}

/**
	@brief  destructor, clears everything
	
	@param  None
	
	@return None
*/
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>::~HashTable()
{
	
	clear();
	
}

/**
	@brief  insert, inserts data into the hashtable
	
	@param  newdataitem, which is the data we want to insert
	
	@return None
*/
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::insert(const DataType& newDataItem)
{
	
	int index = newDataItem.hash(newDataItem.getKey()) % tableSize;
	dataTable[index].insert(newDataItem);
	
}

/**
	@brief  remove, remove the deleteKey if it is in the table
	
	@param  deleteKey, the key that we want to delete 
	
	@return bool, returns true if we deleted the key successfully and false otherwise
*/
template <typename DataType, typename KeyType>
bool HashTable<DataType,KeyType>::remove(const KeyType& deleteKey)
{
	
	for(int i = 0; i < tableSize; i++)
	{
		if(dataTable[i].remove(deleteKey))
		{
			return true;
		}
	}
	
	return false;
}

/**
	@brief  retrieve, retrieve the data from the hashtable
	
	@param  searchkey, helps to search for the item, thats how we know which item to retrieve
	
	@param  returnItem, that's just to change the dataItem that is connected to the searchKey
	
	@return bool, returns true if we retrieve the data successfully and false otherwise
*/
template <typename DataType, typename KeyType>
bool HashTable<DataType,KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
	for(int i = 0; i < tableSize; i++)
	{
		if(dataTable[i].retrieve(searchKey, returnItem))
		{
			return true;
		}
	}
	
	return false;
}

/**
	@brief  clear, will clear everything out on our HashTable
	
	@param  None
	
	@return None
*/
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::clear()
{
	for(int i = 0; i < tableSize; i++)
	{
		dataTable[i].clear();
	}
}

/**
	@brief  isEmpty, checks to see if the Hashtable is Empty
	
	@param  None
	
	@return bool, returns true if there is no data to be read successfully and is Empty, returns false otherwise
*/
template <typename DataType, typename KeyType>
bool HashTable<DataType,KeyType>::isEmpty() const
{
	return dataTable == NULL;
}

/**
	@brief  showStructure, which is given to us by  the instructor
	
	@param  None
	
	@return None
*/
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::showStructure() const
{
	
	for (int i = 0; i < tableSize; ++i)
	{
		cout << i << ": ";
		dataTable[i].writeKeys();
    }
	
}


/**
	@brief  copyTable, copies the data from source too a new HashTable
	
	@param  Source, where the existing HashTable is
	
	@return None
*/
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::copyTable(const HashTable& source)
{
	tableSize = source.tableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
	
	for(int i = 0; i < tableSize; i++)
	{
		dataTable[i] = source.dataTable[i];
	}
	
}
/**
	@brief  standardDeviation
	
	@param  None
	
	@return double, standardDeviation
*/
template <typename DataType, typename KeyType>
double HashTable<DataType,KeyType>::standardDeviation() const
{
	double a = 0.0;
	return a;
}








































