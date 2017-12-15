/*
	Name: Pedram Safaei
	Date: 9/6/2017
	Bugs: ....
	LINKED LIST IMPLEMENTATION
*/

/*
//    This program is just an implementation of linked list, we were given the main file so we didn't have to 
//    work on the interface for the user, the only requirement was implementing the .cpp file for the given .h 
//    file and make it work.
*/

/*
//There are places that I am using if statement in a silly way for example instead of 
		
//		if (IsEmpty())
// I am using 
			
//		if (IsEmpty() == true)
			
//This is just an old habit, if it is not acceptable, I will try to change go with the standard practice.
	
	
	
//There are places that I am going to the beginning in other words I'm setting the cursor equal to head, we also have a function for it (gotoBeginning()) but I
used both the function and the actual implementation in dfferent places just to see how it would affect the functionality (It didn't)

*/


#pragma warning( disable : 4290 ) //this is for visual studio... won't effect the program's functionality

#include "ListLinked.h" //no need to include anything else since the required libraries were included in the .h file

//default constructor
template <typename DataType>
List<DataType>::List(int ignored)
{
	//constructor _ Set members to NULL
	head = NULL;
	cursor = NULL;
}

//copy constructor
template <typename DataType>
List<DataType>::List(const List& other)
{

	//vatiables to help down the road
	ListNode * TempOtherNode;
	ListNode * TempCursorPos;

	//set them to NULL
	TempOtherNode = NULL;
	TempCursorPos = NULL;
	head = NULL;
	cursor = NULL;


	//let the temp know where to go
	TempOtherNode = other.head;

	if (other.isEmpty() == false)
	{
		//TempOtherNode = other.head; Don't really need it here, I could do that outside of my IF statement

		
		//copy as long as the next node is NULL (end of list)
		while (TempOtherNode != NULL)
		{

			insert(TempOtherNode->dataItem); // we'll use the function we already have

			if (TempOtherNode == other.cursor)
			{
				//since we are copying lists, we need to save the cursor (address)
				TempCursorPos = cursor;
			}

			//go to the next
			TempOtherNode = TempOtherNode->next;
			
		
		}

		//what we did earlier in the while->IF statement help this part
		cursor = TempCursorPos;

	}

	else
	{
		//nothing to do so... just hang in there.
	}


}

//assignment operator
template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{
	//Same as the copy constructor but it has a return, I just copied what I had, it should work.

	//vatiables to help down the road
	ListNode * TempOtherNode;
	ListNode * TempCursorPos;

	//set them to NULL
	TempOtherNode = NULL;
	TempCursorPos = NULL;
	head = NULL;
	cursor = NULL;


	//let the temp know where to go
	TempOtherNode = other.head;

	if (other.isEmpty() == false)
	{
		//TempOtherNode = other.head; Don't really need it here, I could do that outside of my IF statement


		//copy as long as the next node is NULL (end of list)
		while (TempOtherNode != NULL)
		{

			insert(TempOtherNode->dataItem); // we'll use the function we already have

			if (TempOtherNode == other.cursor)
			{
				//since we are copying lists, we need to save the cursor (address)
				TempCursorPos = cursor;
			}

			//go to the next
			TempOtherNode = TempOtherNode->next;


		}

		//what we did earlier in the while->IF statement help this part
		cursor = TempCursorPos;

	}

	else
	{
		//nothing to do so... just hang in there.
	}
	
	//since it needs return then return!
	return *this;
}

//deconsrucor
template <typename DataType>
List<DataType>::~List()
{
	//just clear everything (We already have the function so why write a new one?!)
	clear();
}


//insert elemnets
template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
{
	if(isFull() == true)
	{
		throw logic_error ("insert() full list");
	}
	//new node
	ListNode * NewNODE;
	NewNODE = NULL;

	//if our list is not full
	if (isFull() == false)
	{
		NewNODE = new ListNode(newDataItem, NULL);

		//if the list is fresh and empty and you want to inser something then you have to start from the begining
		if (isEmpty() == true)
		{
			//start from the beginning and assign
			head = NewNODE;
			cursor = NewNODE;

		}
		
		else
		{
			//else if the user is just continuing to add
			if (cursor->next != NULL)
			{
				//as long as the next one is not null do assign the next one to our newly added node
				NewNODE->next = cursor->next;
			}

			//linking the node where the cursor is located at to the newly added node
			cursor->next = NewNODE;
			cursor = NewNODE;
		}
		
	}

}

//remove elements
template <typename DataType>
void List<DataType>::remove() throw (logic_error)
{
	//Need that for when the cursor is in between or something
	ListNode* TempCurs;
	TempCurs = cursor;

	if (isEmpty() == false)
	{
		//if we only have one node
		if (cursor == head && cursor->next == NULL)
		{
			head = NULL;
			cursor = NULL;
		}
		
		//is we're at the begining 
		else if (cursor == head)
		{
			//go to next
			gotoNext();

			//the next one is now head
			head = cursor;
		}
	
		else 	//if the cursor is somewhere in between or something
		{
		    // you don't want to just delete something, need to move the cursor and just delete he element
			gotoPrior();

			cursor->next = TempCurs->next;

			if (TempCurs->next != NULL) //if it's not at the end
			{
				gotoNext();
			}
			
			else 
			{
				gotoBeginning();
			}

		}
		
		delete TempCurs; //deallocate

	}
	
	else // if empty mostly
	{
	    throw logic_error ("remove() empty list");
	}

}

//replacing elements
template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{
	//if the list is not empty go ahead and replace the current item (cursor points at it) and replace it, the address would remain the same so we don't need to touch anything else
	if (isEmpty() == false)
		cursor->dataItem = newDataItem;
	else
		throw logic_error ("replace() empty list");
}

//clearing elemts
template <typename DataType>
void List<DataType>::clear()
{
	//we need to start from the begining I could also use gotobeginning() function but I don't really thing there is a difference between the two
	cursor = head;

	while (isEmpty() == false)
	{
		//as long as list is not empty remove, we have a function for it so we will use that
		remove();
	}


}


template <typename DataType>
bool List<DataType>::isEmpty() const
{
	//if head is null return true(it is empty) else return false
	return (head == NULL) ? true : false;
}


template <typename DataType>
bool List<DataType>::isFull() const
{
	//list is always full
	return false;
}


template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
	if(isEmpty() == true)
		throw logic_error ("gotoBeginning() empty list");
	else
		cursor = head;
}


template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
	if (isEmpty() == false)
	{
		while (cursor->next != NULL)
		{
			gotoNext();
		}
	}
	else
		throw logic_error ("gotoEnd() empty list");
}


template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
	//this seems like too many if statements for something simple but this was necessary for the windows compiler for some reason
	if (isEmpty() == true)
		throw logic_error ("gotoNext() empty list");

	else if (cursor->next == NULL)
		return false;

	else
	{
		//if list is not empty and the next curosr is not NULL(end) then you can go ahead and advance
		cursor = cursor->next;
		return true;
	}
}


template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
	ListNode * TempCur;
	TempCur = head;
	
//this seems like too many if statements for something simple but this was necessary for the windows compiler for some reason
	if (isEmpty() == true)
		throw logic_error ("gotoPrior() empty list");
		
		
	else if (cursor == head) //at the beginning
		return false;

	else
	{
		//need to find where the cursor is located
		while (TempCur->next != cursor)
		{
			TempCur = TempCur->next;
		}

		//if found give it the address and return true
		cursor = TempCur;
		return true;
	}

}


template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
	//if list is not empty return the data else return a neg number indicating something is wrong
	return (cursor != NULL) ? cursor->dataItem : throw logic_error ("getCursor() empty list");
}


template <typename DataType>
// Programming exercise 2
void List<DataType>::moveToBeginning() throw (logic_error)
{
	DataType Data;
	//if list is not empty
	if (isEmpty() == false || cursor != head)
	{
		//save whatever is at the cursor to somewhere so you can move it
		Data = cursor->dataItem;

		//remove it
		remove();

		//go to begining
		cursor = head;

		//put it there
		head = new ListNode(Data, cursor);

		gotoBeginning();


	}
	else
		throw logic_error ("moveToBeginning() empty list");
}


template <typename DataType>
// Programming exercise 3
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)
{
	//if nothing's there
	if (isEmpty() == true)
	{
		insert(newDataItem);
	}
	
	else if(isFull() == true)
		throw logic_error ("insertBefore() full list");
		
	//if inserting at the head
	else if (cursor == head)
	{
		head = new ListNode(newDataItem, head);
		gotoBeginning();
	}
	//if all the cases fail then simply go to the previous and insert
	else
	{
		gotoPrior();
		insert(newDataItem);
	}
}

// this was just copied from Show5.cpp
//--------------------------------------------------------------------
// show5.cpp: includes implementation of showStructure
//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
	if (isEmpty())
	{
		cout << "Empty list" << endl;
	}
	else
	{
		for (ListNode* temp = head; temp != 0; temp = temp->next) {
			if (temp == cursor) {
				cout << "[";
			}

			// Assumes that dataItem can be printed via << because
			// is is either primitive or operator<< is overloaded.
			cout << temp->dataItem;

			if (temp == cursor) {
				cout << "]";
			}
			cout << " ";
		}
		cout << endl;
	}
}


template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
	//just initialize with whatever is passed in
	dataItem = nodeData;
	next = nextPtr;
}
