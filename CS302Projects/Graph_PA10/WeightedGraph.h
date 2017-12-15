/**
	@file WeightedGraph.h
	
	@brief This is just a simple .h or specification file for  WeightedGraph, PA010. This file was not written by the student, it was just modified 
	to fit the requirements.
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 11/14/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
		
*/

#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include <stdexcept>
#include <iostream>
#include <climits>    
#include <string>   

using namespace std;

class WeightedGraph
{
  public:
    static const int 
	MAX_GRAPH_SIZE = 10,         
	INFINITE_EDGE_WT = INT_MAX;  

    class Vertex
    {
      public:
	    void setLabel( const string& newLabel ) { label=newLabel; }
	    string getLabel( ) const { return label; }
      	void setColor(char newColor) { color = newColor; }
      	char getColor() const { return color; }

      private:
	    string label;  
      	char color;
    };

 
    WeightedGraph ( int maxNumber = MAX_GRAPH_SIZE );
    WeightedGraph ( const WeightedGraph& other );
    WeightedGraph& operator= ( const WeightedGraph& other );
    ~WeightedGraph ();



    //void functions
    void insertVertex ( const Vertex& newVertex ) throw ( logic_error ); // Insert vertex
    void insertEdge ( const string& v1, const string& v2, int wt ) throw ( logic_error );  // Insert edge
    void removeVertex ( const string& v ) throw ( logic_error );  // Remove vertex
    void removeEdge ( const string& v1, const string& v2 ) throw ( logic_error );// Remove edge
    void showStructure () const;
    void showShortestPaths () const;
    void clear();
    
    //bool functions
    bool retrieveVertex ( const string& v, Vertex& vData ) const; // retrieve vertex
    bool getEdgeWeight ( const string& v1, const string& v2, int& wt ) const throw ( logic_error ); // retrieve edge
    bool hasProperColoring() const;
    bool areAllEven () const;
    // Graph status operations
    bool isEmpty () const;                            //  empty
    bool isFull () const;                             //  full

  
 
 
    

  private:


    int getIndex ( const string& v ) const;    // Converts vertex label to an
                                               //   adjacency matrix index
    int getEdge ( int row, int col ) const;    // Get edge weight using
                                               //   adjacency matrix indices
    void setEdge ( int row, int col, int wt);  // Set edge weight using
                                               //   adjacency matrix indices
    int getPath ( int row, int col ) const;
    
    void setPath ( int row, int col, int wt) const;
    
    // Data members
    int maxSize,          // Maximum number of vertices in the graph
        size;             // Actual number of vertices in the graph
    Vertex *vertexList;   // Vertex list
    int *adjMatrix;       // Adjacency matrix
    int *pathMatrix;      // path matrix

};

#endif		// #ifndef WEIGHTEDGRAPH_H
