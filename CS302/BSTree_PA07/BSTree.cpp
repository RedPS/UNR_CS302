/**
	@file BSTree.cpp
	
	@brief This is just a simple implementation for expression trees and Binary search, with that 
	we will also have to write implementation for a database reading, which would read a file 
	provided dby the instructional team. 
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 10/26/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
		
*/

#include "BSTree.h"

/**
	@brief Default Constructor, set root of the tree to NULL
*/
template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>::BSTree()
{
   root = NULL;
}
/**
	@brief Copy Constructor, set root to NULL and copy one tree's stuff to the other.
	@param other, which is the otherbinary search tree passed in.
*/
template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>::BSTree( const BSTree<DataType,KeyType>& other )
{
   root = NULL;
   
   copyHelper( root, other.root );
}
/**
	@brief Assignment operator, set root to NULL (if the two trees are enot the same) and copy one tree's stuff to the other.
	@param other, which is the otherbinary search tree passed in.
*/
template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>& BSTree<DataType,KeyType>::operator=( const BSTree<DataType,KeyType>& other )
{

   if( this != &other )
   {
      clear();

      copyHelper( root, other.root );
   }
   
   return *this;
}
/**
	@brief destructor, clears everything.
*/
template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>::~BSTree()
{
   clear();
}
/**
	@brief isert(), it will call inserthelper() to insert stuff in the tree.
	@param we will pass in whatever needs to be inserted.
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::insert( const DataType& newDataItem )
{
   insertHelper( root, newDataItem ); 
}
/**
	@brief remove(), will call removehelper(), to delete an item
	@param we will pass in the key information of the item that needs to be deleted.
*/
template < typename DataType, typename KeyType >
bool BSTree<DataType,KeyType>::remove( const KeyType& deleteKey )
{
   return removeHelper( root, deleteKey );
}
/**
	@brief clear(), calls clearhelper(), it will clear the whole tree.
	@param NONE
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::clear()
{
   if(!isEmpty()) 
	{
		clearHelper(root);
	}
}
/**
	@brief writeKeys(), calls its helper and passes in the root, it will write all the keys of the stuff that are in the tree.
	@param NONE
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::writeKeys() const
{
   writeKeysHelper( root );
   cout << endl;
}
/**
	@brief isEmpty(), checks if the tree is empty.
	@param NONE
*/
template < typename DataType, typename KeyType >
bool BSTree<DataType,KeyType>::isEmpty() const
{
   return root == NULL;  
}
/**
	@brief retrieve(), it will call its helper and the helper will look for an item and dtry to retrieve it.
	@param KeyType& searchKey, the key of the node
	@param DataType& searchDataItem, the data of the enode
*/
template < typename DataType, typename KeyType >
bool BSTree<DataType,KeyType>::retrieve( const KeyType& searchKey, DataType& searchDataItem ) const
{
   return retrieveHelper( root, searchKey, searchDataItem );
}
/**
	@brief showStructure(),this one was just copid from the files that was provided to us.
*/
template <typename DataType, typename KeyType>
void BSTree<DataType,KeyType>::showStructure() const
{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}
/**
	@brief getHeight(), it will have to look to see which side is longer and then return the size.
*/
template <typename DataType, typename KeyType>
int BSTree<DataType,KeyType>::getHeight() const
{
   return getHeightHelper( root );
}
/**
	@brief getcount(), needs to look at both sides and returns the number of nodes.
*/
template < typename DataType, typename KeyType >
int BSTree<DataType,KeyType>::getCount() const
{
   return getCountHelper( root );
}
/**
	@brief thhis is our node, we need to initialize the members.
	@param DataType &nodeDataItem, whatever data we have.
	@param BSTreeNode *leftPtr, is a ptr to our left side.
	@param BSTreeNode *rightPtr, is a ptr to our rright side.
*/
template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>::BSTreeNode::BSTreeNode(const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr)
{
   dataItem = nodeDataItem;
   left = leftPtr;
   right = rightPtr;
}
/**
	@brief showhelper, this was provided to us.
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper( BSTreeNode *p, int level) const
{
   int j;   

   if ( p != 0 )
   {

      showHelper(p->right,level+1);   
          
      for ( j = 0 ; j < level ; j++ )    
          cout << "\t";
      cout << " " << p->dataItem.getKey();   
      if ( ( p->left != 0 ) &&           
           ( p->right != 0 ) )
        cout << "<";
      else if ( p->right != 0 )
         cout << "/";
      else if ( p->left != 0 )
         cout << "\\";
      cout << endl;
      showHelper(p->left,level+1);          
    }
}
/**
	@brief insert helper will help us insert data into the tree.
	@param BSTreeNode* &ptr, a ptr to the place (tree) that we want to insert
	@param const DataType& newDataItem, what we want to insert
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::insertHelper( BSTreeNode* &ptr, const DataType& newDataItem )
{
   if( ptr == NULL ) // if a fresh node
   {
      ptr = new BSTreeNode( newDataItem, NULL, NULL );
      return;
   }
   if( ptr -> dataItem.getKey() > newDataItem.getKey() ) //if key is greater than the data's key
   {  
      insertHelper( ptr -> left, newDataItem );
   }
   else
   {
      insertHelper( ptr -> right, newDataItem );
   }
}
/**
	@brief delete or remove helper, will help us remove stuff from our tree.
	@param BSTreeNode* &ptr, a ptr to the place (tree) that we want to insert
	@param const KeyType& deleteKey, what we want to delete
*/
template <typename DataType, typename KeyType>
bool BSTree<DataType,KeyType>::removeHelper( BSTreeNode* &ptr, const KeyType& deleteKey )
{
	// If a NULL node
	if(ptr == NULL)
	{
		return false;
	}
	// find the node
	if(ptr->dataItem.getKey() == deleteKey)
	{
		// Case 1, 0 children
		if((ptr->left == NULL) && (ptr->right == NULL))
		{
			delete ptr;
			ptr = NULL;
			return true;
		}
		// Case 2, 1 child
		if((ptr->left != NULL) && (ptr->right == NULL))
		{
			BSTreeNode* tmp = ptr;
			ptr = ptr->left;
			delete tmp;
			return true; 
		}
		if((ptr->left == NULL) && (ptr->right != NULL))
		{
			BSTreeNode* tmp = ptr;
			ptr = ptr->right;
			delete tmp;
			return true;
		}
		
		// Case 3: 2 children
		BSTreeNode* tmp = ptr->left;
		while(tmp->right != NULL)
		{
			tmp = tmp->right;
		}
		ptr->dataItem = tmp->dataItem;
		return removeHelper(ptr->left, tmp->dataItem.getKey());
	}
	else // search
	{
		if(ptr->dataItem.getKey() > deleteKey)
		{
			removeHelper(ptr->left, deleteKey);
		}
		else 
		{
			removeHelper(ptr->right, deleteKey);
		}
	}
	
}
/**
	@brief retrievehelper, helps us retreive stuff frrom our binary search trree
	@param BSTreeNode* &ptr, a ptr to the place (tree) that we want to insert
	@param const KeyType& searchKey, what thekey is (the way we find it)
	@param DataType& searchDataItem, what the data is.
*/
template < typename DataType, typename KeyType >
bool BSTree<DataType,KeyType>::retrieveHelper( BSTreeNode* ptr, const KeyType& searchKey, DataType& searchDataItem ) const
{
   if( ptr == NULL )
   {
      return false;
   }

   if( searchKey == ( ptr -> dataItem.getKey() ) )
   {
      searchDataItem = ptr -> dataItem;
      return true;
   }
   
   if( searchKey < ( ptr -> dataItem.getKey() ) )
   {
      retrieveHelper( ptr -> left, searchKey, searchDataItem );
   }
   
   else if( searchKey > ( ptr -> dataItem.getKey() ) )
   {
      retrieveHelper( ptr -> right, searchKey, searchDataItem );
   }
}
/**
	@brief clearhelper, clears the whole tree.
	@param BSTreeNode* &ptr, a ptr to the place (tree) that we want to clear
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::clearHelper( BSTreeNode* &ptr )
{
	if(ptr != NULL)
	{
		clearHelper(ptr -> left);
		clearHelper(ptr -> right);
		
		delete ptr;
		ptr = NULL;
	}
}
/**
	@brief writeKeysHelper, helper function to writekeys to console.
	@param BSTreeNode* &ptr, a ptr to the place (tree) that we want to write
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::writeKeysHelper( BSTreeNode* ptr ) const
{
  if( ptr != NULL )
  {
	//left
     writeKeysHelper( ptr -> left );
     
     cout << ( ptr -> dataItem.getKey() ) << ' ';
	 
    //right
     writeKeysHelper( ptr -> right );
  }
}
/**
	@brief copyhelper, could also just be called copy, as long as the source that 
	we are copying from is not NULL or  empty, we go left copy, right, copy and done.
	@param BSTreeNode* &ptr, a ptr to the place (tree) that we want to copy
	@param BSTreeNode* sourcePtr, a ptr to the source tree
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::copyHelper( BSTreeNode* &ptr, BSTreeNode* sourcePtr )
{
	if(sourcePtr != NULL)
	{
		ptr = new BSTreeNode(sourcePtr -> dataItem, NULL, NULL);
		copyHelper( ptr -> left, sourcePtr -> left );
  		copyHelper( ptr -> right, sourcePtr -> right ); 
	}
}
/**
	@brief getheighthelper, sees which one is and returns that side
	@param BSTreeNode* &ptr, a ptr to the place (tree) that we want to getheihgt
*/
template < typename DataType, typename KeyType >
int BSTree<DataType,KeyType>::getHeightHelper( BSTreeNode* ptr ) const
{
   if( ptr == NULL )
   {
      return 0;
   }
   if( getHeightHelper( ptr -> left ) > getHeightHelper( ptr -> right ) )
   {
      return 1 + getHeightHelper( ptr -> left );
   }
   else
   {
      return 1 + getHeightHelper( ptr -> right );   
   }
}
/**
	@brief getheighthelper, return the number of nodes(both sides)
	@param BSTreeNode* &ptr, a ptr to the place (tree) that we want to getcount
*/
template < typename DataType, typename KeyType >
int BSTree<DataType,KeyType>::getCountHelper( BSTreeNode* ptr ) const
{
   if( ptr == NULL )
   {
      return 0;
   }
   else
   {
      return 1 + getCountHelper( ptr -> right ) + getCountHelper( ptr -> left );
   }
}
