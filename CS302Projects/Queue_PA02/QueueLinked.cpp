
#include "QueueLinked.h"


// Class/Data Structure Member Implementation //////////////////////
//

 /**
 @brief this is the dedefault constructor it will set the values to NULL as soon as the object is created [in this case queue]
 @return NOTHING
       * A default constructor.
       * 
  */
template<typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber)
{
	front = NULL;
	back = NULL;
}


 /**
 @brief this is the copy constructor it will copy one queue into the other
 @return NOTHING
       * A copy constructor.
       * 
  */
template<typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{

	front = NULL;
	back = NULL;
	
	//make a temp pointer, points to the front of the list we have and starts copying and going to the next node this way we don't lose our front.
	QueueNode* tempFront;
	tempFront = other.front;
	
	//if the list is not empty 
	if(other.isEmpty() == false)
	{
		while(tempFront != NULL)
		{
			//use the enqueue to put the data there
			enqueue(tempFront->dataItem);
			
			//go to next
			tempFront = tempFront->next;
		}
	}
}

 /**
 @brief this is the assignment operator it will copy one queue into the othe
 @return the pointer this (*this)
       * Assignment operator
       * 
  */
template<typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
{
	//same as copy, it is just returning *this, so basically the same code
	if(this == &other)
		return *this;
	
	front = NULL;
	back = NULL;
	
	//make a temp pointer, points to the front of the list we have and starts copying and going to the next node this way we don't lose our front.
	QueueNode* tempFront;
	tempFront = other.front;
	
	//if the list is not empty 
	if(other.isEmpty() == false)
	{
		while(tempFront != NULL)
		{
			//use the enqueue to put the data there
			enqueue(tempFront->dataItem);
			
			//go to next
			tempFront = tempFront->next;
		}
	}
	return *this;
	
}

 /**
 @brief destructor, it will clear the queue
 @return NOTHING
       * clear the queue
       * 
  */
template<typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
	//we'll use the efunction we already have to clear
	clear();
}


 /**
 @brief insert elements into the queue function, it will insert one element to the back of the queue
 @return NOTHING(VOID)
       * insert elements into the queue
       * 
  */
template<typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	if(isFull())
	{
		throw logic_error("enqueue() queue full");
	}
	else
	{
		QueueNode* newBack = new QueueNode(newDataItem, NULL);
		
		if(front == NULL && back == NULL) //if there are no elements in the queue
		{
			//make both point to the new element
			front = newBack;
			back = newBack;
		}
		else // else if there are elements (not the first time you are adding) then,
		{
			back->next = newBack; // make the first element point to the new element and
			back = newBack; // make back point to the new element
		}
	}
}
 /**
@brief delete elements from the queue function, it will delete one element from front
@return DataType(The item that was deleted)
       * delete elements from the queue
       * 
  */
template<typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
	if (isEmpty() == true)
	{
		throw logic_error("dequeue() queue empty");
	}
	else  
	{
		if (front == back)//if there is only one element
		{
			
			DataType TempItem = front->dataItem; //get the value ur deleting
			
			QueueNode* temp = front; //make a temp that points to that node
			
			//empty the queue
			front = NULL; 
			back = NULL;
			
			delete temp; //delete that node
			
			return TempItem; //return the deleted value
		}
		else //if the list has more than one  value
		{
			DataType TempItem = front->dataItem;//get the value ur deleting
			
			QueueNode* temp = front; //make a temp that points to that node
			
			front = front->next; //go to the next node
			
			delete temp;
			
			return TempItem;
		}
	}
}

/**
@brief clear, makes the queue empty , it will delete everything
@return NOTHING(VOID)
       * clear, makes the queue empty
       * 
  */
template<typename DataType>
void QueueLinked<DataType>::clear()
{
	while(isEmpty() == false)
	{
		dequeue();
	}
}


/**
@brief checks if the list is empty 
@return Bool(either true or false)
       * checks if the list is empty
       * 
  */
template<typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	return (front == NULL) ? true: false;
}

/**
@brief checks if the list is Full, always returns false for this assignment
@return Bool(either true or false)
       * is full, checks if it is full
       * 
  */
template<typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	//it is never full
	return false;
}

/**
@brief gets the rear element puts it in front
@return NOTHING (VOID)
       * programming exercise 2, putFront
       * 
  */
template<typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
	if(isFull() == true)
	{
		throw logic_error("putFront() queue full");
	}
	else if(isEmpty() == true) //if it is a fresh queue
	{
		enqueue(newDataItem);
	}
	else if(isEmpty() == false) //if there are elements in there before
	{
		QueueNode* NewItem = new QueueNode(newDataItem, front);
		front = NewItem;
	}
}
/**
@brief returns the data that is at the rear(end of line)
@return DataType(value of the last element)
       * programming exercise 2, getRear
       * 
  */
template<typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
	
	if (isEmpty() == true)
	{
		throw logic_error("getRear() queue empty");
	}

	else
	{
		
		DataType TempData = back->dataItem; // save the data so we can return
		
		if (front == back) //if one value inside
		{
			clear();
		}

		else // if there are multiple elements
		{
			QueueNode* tempFront = front; //get front

			while (tempFront->next != back) //as long as the next one in the queue is not the element at the back
			{
				tempFront = tempFront->next; //go to the next one
			}
            //if the next one is the last element 
			delete back; //delete
			back = tempFront; //and set to the one before the last element
			back->next = NULL; // since this is the new BACK then the next one should dbe NULL
		}

		return TempData;
	}
}

/**
@brief returns the size of the queue
@return int (size)
       * programming exercise 3, getLength
       * 
  */
template<typename DataType>
int QueueLinked<DataType>::getLength() const
{
	int size = 0;
	QueueNode* temp;
	temp = front;
	
	while(temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return size;
}
//show structure copid from show7.cpp
template <typename DataType>
void QueueLinked<DataType>:: showStructure () const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
    // Iterates through the queue
	QueueNode* p;

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != NULL ; p = p->next )
	{
	    if( p == front )
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}

//--------------------------------------------------------------------

//The private class inside our QueueLinked class
template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}
