/**
	@file ExpressionTree.cpp
	
	@brief This is just a simple implementation for expression trees lab from the lab book.
		   The below explaination is from the lab book: 
		   
		   Although you ordinarily write arithmetic expressions in linear form, you treat them as
		   hierarchical entities when you evaluate them. When evaluating the following
		   arithmetic expression, for example,
	       (1+3)*(6-4)
		   you first add 1 and 3, then you subtract 4 from 6. Finally, you multiply these
		   intermediate results together to produce the value of the expression. In performing
		   these calculations, you have implicitly formed a hierarchy in which the multiply
		   operator is built on a foundation consisting of the addition and subtraction operators.
	       You can represent this hierarchy explicitly using the following binary tree. Trees such
	       as this one are referred to as expression trees.
	
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 10/11/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
	
	
*/

#include "ExpressionTree.h"



/**
	@brief This is the default contructor, it will set the default value when the tree is created, 
	as soon as the tree gets created the default value should be NULL;
	
*/
template <typename DataType>
ExprTree<DataType>::ExprTree ()
{
	root = NULL;
}

/**
	@brief This is the copy contructor, we are supposed to write a coopy function so I am just setting root to its default value and 
	calling the copy function that we were supposed to write, this way I am not writing useless codes.
*/
template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
	root = NULL;
	copy(root, source.root);
}

/**
	@brief this is the assignment operator, I am doing the same thing I did for copy constructor, but this time I have to 
	check to see if the tree is equal to the tree we already have, and if it is make surre NOT TO clear it and cause memory problems.
*/
template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)
{
	if(this == &source)
	{
		return *this;
	}
	
	clear();
	copy(root, source.root);
	return *this;
}

/**
	@brief this is the destructor, it will just call our clear function, this will allow us not to copy and paste code over and over.
*/
template <typename DataType>
ExprTree<DataType>::~ExprTree ()
{
	clear();
}

/**
	@brief the build function that was in the .h file, we are just calling our own build function here.
*/
template <typename DataType>  
void ExprTree<DataType>::build ()
{
	buildHelper(root);
}

/**
	@brief the expression function that was in the .h file, we are just calling our own expression function here but before it we need
	to make sure that the tree is not empty.
*/
template <typename DataType>
void ExprTree<DataType>::expression () const
{
	if(root !=NULL)
	{
		expressionHelper(root);
	}
}

/**
	@brief the evaluate function that was in the .h file, we are just calling our own evaluate function here but before it we need
	to make sure that the tree is not empty and if it is we are throwing a logic error, and we need to save the value somwhere and return it.
*/
template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
		
		if(root == NULL)
		{
			throw logic_error("evaluate(), Empty!");
		}
		
		DataType Temp;
		Temp = evaluateHelper(root);
		
		return Temp;
}
/**
	@brief clear function, this function will call the clear Helper function as long as our tree is not empty.
*/
template <typename DataType>
void ExprTree<DataType>::clear ()
{
	if(root != NULL)
	{
		clearHelper(root);
	}
}	

/**
	@brief commute function, it will call the commute helper function as long the tree is not empty.
*/
template <typename DataType>
void ExprTree<DataType>::commute()
{
	if(root != NULL)
	{
		commuteHelper(root);
	}
}	

/**
	@brief isEquivalent, it will check to see if both roots are NULL so it will return true or false based on that, and if their data is the same, 
	it will call the Helper function and return true or false.
*/
template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
	
   if(root == NULL || source.root == NULL)  
	{
		return root == source.root;
	}
	if(root->dataItem == source.root->dataItem) 
	{
		return isEquivalentHelper(root, source.root);
	}
	return false;
	
}
/**
	@brief ShowStructure, this function is taken from the show8.cpp file from the student kit, the isEmpty has been changed to 
	if root == NULL which is basically the same thing.
*/
template <typename DataType>   
void ExprTree<DataType>::showStructure () const
{
	if(root == NULL)
	{
		cout << "Empty tree" << endl;
	}
	else
	{
		cout << endl;
		showHelper(root,1);
		cout << endl;
	}
}
/**
	@brief this is just to set the members of our nodes to whatever gets passed in.
*/
template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode ( char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr )
{
	dataItem = elem;
	left = leftPtr;
	right = rightPtr;
}


	
//helper function 
/**
	@brief first helper function, this will read whatever the user enters, until they give up and enter a new thing (new line) or they
	just exit.
	@param it gets the address of a pointer, so we can add/ create new nodes.
	@return It is a void function, so NOthing.
*/
template <typename DataType>
void ExprTree<DataType>::buildHelper( ExprTreeNode* &TreePtr )
{
	char input;
	
 
	cin >> input;
   
  
	if( input != '\n' )
    {

		TreePtr = new ExprTreeNode( input, NULL, NULL ); 


		if( !isdigit( input) )
		{
			buildHelper( TreePtr -> left );
			buildHelper( TreePtr -> right );
		}
		
   }
}
/**
	@brief clear helper, helps us clear the tree from left to right.
	@param it gets the address of a pointer, so we can add/ create new nodes.
	@return It is a void function, so NOthing.
*/
template <typename DataType>
void ExprTree<DataType>::clearHelper( ExprTreeNode* &TreePtr)
{
	if(TreePtr->left != NULL)
	{
		clearHelper(TreePtr->left);
	}
	else if(TreePtr->right != NULL)
	{
		clearHelper(TreePtr->right);
	}
	
	delete TreePtr;
	TreePtr = NULL;
}
/**
	@brief expression helper, helps us with calculations, this is an inorder traversal, which helps us with placing the paranthesis.
	@param it gets the address of a pointer, so we can add/ create new nodes.
	@return It is a void function, so NOthing.
*/
template <typename DataType>
void ExprTree<DataType>::expressionHelper( ExprTreeNode* TreePtr ) const
{
	if(isdigit(TreePtr->dataItem))
	{
		cout << TreePtr->dataItem;
	}
	else
	{
		cout << "(";
		expressionHelper(TreePtr->left);
		cout << TreePtr->dataItem;
		expressionHelper(TreePtr->right);
		cout << ")";
	}
}
/**
	@brief copy, function will help us copy things, is is techincally a helper function but we don't have a copy so I just named 
	it copy instead of copyHelper. and it will look at the node passed in and copies as long as it is not NULL.
	@param it gets the address of a pointer, so we can add/ create new nodes.
	@param a pointer to the other tree, or as the header file provides it , SOURCE.
	@return It is a void function, so NOthing.
*/
template <typename DataType>
void ExprTree<DataType>::copy( ExprTreeNode* &TreePtr, ExprTreeNode* sourcePtr )
{
	if(sourcePtr != NULL)
	{
		TreePtr = new ExprTreeNode(sourcePtr->dataItem, NULL, NULL);
		copy(TreePtr->left, sourcePtr->left);
		copy(TreePtr->right, sourcePtr->right);
	}
	else
		TreePtr = NULL;
}
/**
	@brief copy, this show helper function was provided by the show8.cpp
	@param a pointer to the other tree, or as the header file provides it , SOURCE.
	@param which level, top, btn, middle.
	@return It is a void function, so NOthing.
*/
template <typename DataType>
void ExprTree<DataType>::showHelper( ExprTreeNode* TreePtr, int level ) const
{
	int j;
	
	if(TreePtr != 0)
	{
		 showHelper(TreePtr->right,level+1);        
        for ( j = 0 ; j < level ; j++ )   
            cout << "\t";
        cout << " " << TreePtr->dataItem;        
        if ( ( TreePtr->left != 0 ) &&         
             ( TreePtr->right != 0 ) )
           cout << "<";
        else if ( TreePtr->right != 0 )
           cout << "/";
        else if ( TreePtr->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(TreePtr->left,level+1);        
	}
}
/**
	@brief evaluateheelper helps us with evaluating function by having multiple if statements, or just using a switch
	and idetifying the operator and adding, subtracting, dividing or multiplying left and right.
	@param a pointer to the other tree, or as the header file provides it , SOURCE.
	@return Datatype which would be specified on the run time so it can be anything that the user chooses.
*/
template <typename DataType>
DataType ExprTree<DataType>::evaluateHelper( ExprTreeNode* TreePtr ) const
{
	DataType Temp;
	
	if(isdigit(TreePtr ->dataItem))
	{
		return atoi(&(TreePtr -> dataItem));
	}
	
	switch(TreePtr->dataItem)
	{
		case '+':
		Temp =(evaluateHelper(TreePtr->left) + evaluateHelper(TreePtr->right));
		break;
		
		case '-':
		Temp = (evaluateHelper(TreePtr->left) - evaluateHelper(TreePtr->right));
		break;
		
		case '*':
		Temp = (evaluateHelper(TreePtr->left) * evaluateHelper(TreePtr->right));
		break;
		
		case '/':
		Temp = (evaluateHelper(TreePtr->left) / evaluateHelper(TreePtr->right));
		break;
	}
	return Temp;
}

  
//programming exercise 2
/**
	@brief this is commutehelper, for programming excersie number 2, which would basically commute the operands for every
	arithmetic operator in the expression tree.
	@param a pointer to the other tree, or as the header file provides it , SOURCE.
	@return VOID, so nothing.
*/
template <typename DataType>
void ExprTree<DataType>::commuteHelper( ExprTreeNode* TreePtr)
{
	if(TreePtr != NULL)
	{
		ExprTreeNode* Temp = TreePtr->left;
		
		TreePtr->left = TreePtr->right;
		TreePtr->right = Temp;
		
		commuteHelper(TreePtr->left);
		commuteHelper(TreePtr->right);
		
	}
}
	
//programming exercise 3
/**
	@brief this is isequivalenthelper function which would basically check two trees passed in and check if the expression
	are equivvalent or not.
	@param a pointer to the expression tree so we know what to comapare with.
	@param a pointer to the source tree so we know what to comapare with.
	@return bool, so either true or false, which would show equivalancy.
*/
template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper( ExprTreeNode* TreePtr, ExprTreeNode* sourcePtr ) const
{
	

	bool Temp = false;


	if( ( TreePtr == NULL ) || ( sourcePtr == NULL ) )
	{
   
		if( ( TreePtr == NULL ) && ( sourcePtr == NULL ) )
		{
   
			Temp = true;
		}
		
	}
 
	else if( TreePtr->dataItem == sourcePtr->dataItem )
	{
  
		Temp = ( isEquivalentHelper( TreePtr->left, sourcePtr->left ) && isEquivalentHelper( TreePtr->right, sourcePtr->right) );

		if( !Temp )
		{
			if( (TreePtr->dataItem == '+') || (TreePtr->dataItem == '*') )
			{
				Temp = ( isEquivalentHelper( TreePtr->right, sourcePtr->left ) && isEquivalentHelper( TreePtr->left, sourcePtr->right) );
			}
		}
		
	}
 

	return Temp;
   
}
	
	
   
   