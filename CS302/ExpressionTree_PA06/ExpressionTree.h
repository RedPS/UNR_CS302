//--------------------------------------------------------------------
//
//  Laboratory 8                                     ExpressionTree.h
//
//  Class declarations for the linked implementation of the
//  Expression Tree ADT -- including the recursive helpers for the
//  public member functions
//
//  Instructor copy with the recursive helper function declarations.
//  The student version does not have those, but has a place to write
//  the declarations in the private section.
//
//--------------------------------------------------------------------

#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <stdexcept>
#include <iostream>
#include <stdlib.h> 

using namespace std;

template <typename DataType>
class ExprTree {
  public:

    // Constructor
    ExprTree ();
    ExprTree(const ExprTree& source);

    ExprTree& operator=(const ExprTree& source);

    // Destructor
    ~ExprTree ();

    // Expression tree manipulation operations
    void build ();
    void expression () const;
    DataType evaluate() const throw (logic_error);
    void clear ();              // Clear tree
    void commute();  // Exercise 2
    bool isEquivalent(const ExprTree& source) const; // Exercise 3

    // Output the tree structure -- used in testing/debugging
    void showStructure () const;

  private:

    class ExprTreeNode {
      public:
        // Constructor
        ExprTreeNode ( char elem,
                       ExprTreeNode *leftPtr, ExprTreeNode *rightPtr );

        // Data members
        char dataItem;          // Expression tree data item
        ExprTreeNode *left,     // Pointer to the left child
                     *right;    // Pointer to the right child
    };
	
	//helper function 
	
    void buildHelper( ExprTreeNode* &TreePtr );
	void clearHelper( ExprTreeNode* &TreePtr );
	void expressionHelper( ExprTreeNode* TreePtr ) const;
    void copy( ExprTreeNode* &TreePtr, ExprTreeNode* sourcePtr );
    void showHelper( ExprTreeNode* TreePtr, int level ) const;
	DataType evaluateHelper( ExprTreeNode* TreePtr ) const;

   
	//programming exercise 2
	void commuteHelper( ExprTreeNode* TreePtr );
	
	//programming exercise 3
	bool isEquivalentHelper( ExprTreeNode* TreePtr, ExprTreeNode* sourcePtr ) const;
	
	
   
    


    // Data member
    ExprTreeNode *root;   // Pointer to the root node
};

#endif		// #ifndef EXPRESSIONTREE_H
