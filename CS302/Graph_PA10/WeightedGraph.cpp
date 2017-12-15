/**
	@file WeightedGraph.cpp
	
	@brief This is just a simple implementation for  WeightedGraph.h, PA010. 
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 11/14/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
		
*/
#include "WeightedGraph.h"

using namespace std;

/**
 @brief default constructor, it will initialize and allocate memory for all our components
 @param maxNumber will be used to initialize maxSize so we know how much we should allocate
 @return NONE
*/
WeightedGraph::WeightedGraph( int maxNumber )
{
   //initi size [we have two, size and maxsize]
   size = 0;
   maxSize = maxNumber;
   
   //alloc memeory for matrices [adj and path] and vertexx
   adjMatrix = new int[ maxSize * maxSize ];
   pathMatrix = new int[ maxSize * maxSize ];
   vertexList = new Vertex[maxSize];
   
   //initialize it 
   Vertex temp;
   for( int i = 0; i < maxSize; i++ )
   {
      vertexList[ i ] = temp;
      for( int j = 0; j < maxSize; j++ )
      {
         setEdge( i, j, INFINITE_EDGE_WT );
      }
   }
}

/**
 @brief copy constructor
 @param Other, is the original graph that we want to copy its contenet
 @return NONE
*/
WeightedGraph::WeightedGraph( const WeightedGraph& other )
{
   // just use the = operator, why bother
   *this = other;
}

/**
 @brief operator= 
 @param Other, is the original graph that we want to copy its contenet
 @return *this
*/
WeightedGraph& WeightedGraph::operator=( const WeightedGraph& other )
{
   if( this != &other )
   {
      // clear 
      delete [] adjMatrix;
      delete [] pathMatrix;
      delete [] vertexList;
      
      //take care of sizes
      size = other.size;
      maxSize = other.maxSize;
      
      
      //take care of alloc memory
      adjMatrix = new int[ maxSize * maxSize ];
      pathMatrix = new int[ maxSize * maxSize ];
      vertexList = new Vertex[maxSize];
      
      for( int i = 0; i < size; i++ ) // copy from original
      {
         vertexList[ i ] = other.vertexList[ i ];
         for( int j = 0; j < size; j++ )
         {
            setEdge( i, j, other.getEdge( i, j ) );
            setPath( i, j, other.getPath( i, j ) );
         }
      }
   }
   return *this;
}

/**
 @brief destructor, will just get rid of what we allocated
 @param NONE
 @return NONE
*/
WeightedGraph::~WeightedGraph()
{
   delete [] adjMatrix;
   delete [] pathMatrix;
   delete [] vertexList;
}

/**
 @brief insertvertex
 @param newvertex, of object vertex so we know what to insert
 @return NONE
*/
void WeightedGraph::insertVertex (const Vertex& newVertex) throw ( logic_error )
{
   //if full
   if( isFull() )
   {
      throw logic_error( "Insert() full can't inset" );
      return;
   }
   
   // if exists a vertex that match
   for( int i = 0; i < size; i++ )
   {
      if( newVertex.getLabel() == vertexList[ i ].getLabel() )
      {
         vertexList[ i ] = newVertex;
         vertexList[ size ].setColor( newVertex.getColor() );
         return;
      }
   }
   
   // insert [new] vertex, take care of size
   vertexList[size] = newVertex;
   vertexList[size].setColor(newVertex.getColor());
   size++;
}

/**
 @brief insert edge
 @param v1 
 @param v2
 @param wt
 @return NONE
*/
void WeightedGraph::insertEdge ( const string& v1, const string& v2, int wt ) throw ( logic_error )
{
   // save indexes
   int v1index = getIndex(v1);
   int v2index = getIndex(v2);
   
   if( v1index == -1 || v2index == -1 )
   {
      throw logic_error( "insertedge(), not in graph" );
      return;
   }
   setEdge(v1index, v2index, wt);
}

/**
 @brief clear, just set size = 0 
 @param none
 @return none
*/
void WeightedGraph::clear()
{
    size = 0;
}

/**
 @brief retrieve vertex, get the vertex if there return true
 @param v
 @param Data
 @return true/false based on if it gets found or not
*/
bool WeightedGraph::retrieveVertex (const string& v, Vertex& vData) const
{
   if(isEmpty()== true)
   {
      return false;
   }
   
   // go through vertices
   for( int count = 0; count < size; count++ )
   {
      if( v == vertexList[count].getLabel())
      {
         vData = vertexList[count];
         return true;
      }
   }
   return false;
}

/**
 @brief getweight for edge
 @param v1
 @param v2
 @param wt, by reference 
 @return bool, depending on if wt== to INFINITEEDGE
*/
bool WeightedGraph::getEdgeWeight ( const string& v1, const string& v2, int& wt ) const throw ( logic_error )
{
   int v1index = getIndex(v1);
   int v2index = getIndex(v2);
   
   if( v1index == -1 || v2index == -1 )
   {
      throw logic_error( "getEdgeWeight(), not in graph" );
   }
   
   wt = getEdge( v1index, v2index);
   
   return wt != INFINITE_EDGE_WT;
}

/**
 @brief remove vertecx go through and remoce  the needed vertex
 @param v
 @return NONE
*/
void WeightedGraph::removeVertex ( const string& v ) throw ( logic_error )
{
   for( int i = 0; i < size; i++ )
   {
      if( v == vertexList[ i ].getLabel())
      {
         for( int col = i; col < size; col++ )
         {
            for( int row = 0; row < size; row++ )
            {
               adjMatrix[ row * maxSize + col ] = adjMatrix[ row * maxSize + col + 1 ];
            }
         } 
         
         for( int col = 0; col < size; col++ )
         {
            for( int row = i; row < size; row++ )
            {
               adjMatrix[row * maxSize + col] = adjMatrix[(row + 1) * maxSize + col];
            }
         } 
         
         for( int col = i; col < size; col++ )
         {
            vertexList[col] = vertexList[col + 1];
         }
         
         size--;
         return;
      }
      
   }
   //else if nothing found
   throw logic_error( "removevertex(), no vertex in graph" );
}

/**
 @brief remove edge
 @param v1
 @param v2
 @return NONE
*/
void WeightedGraph::removeEdge(const string& v1, const string& v2) throw ( logic_error )
{
   int v1index = getIndex(v1);
   int v2index = getIndex(v2);
   
   if( v1index == -1 || v2index == -1 )
   {
      throw logic_error( "removeedge(), edge enot found" );
   }
   
   setEdge( v1index, v2index, INFINITE_EDGE_WT );
}
/**
 @brief ISEMPTY
 @param NONE
 @return true/false depending on if it is empty or not
*/
bool WeightedGraph::isEmpty () const
{
   return size == 0;
}

/**
 @brief isFull
 @param NONE
 @return true/false, if current size if == to maxsize then true otherwise false
*/
bool WeightedGraph::isFull() const
{
   return size == maxSize;
}

/**
 @brief showstructure, was given to us
 @param none
 @return NONE
*/
void WeightedGraph::showStructure () const
{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Vertex list : " << endl;
       for ( int row = 0 ; row < size ; row++ )
           cout << row << '\t' << vertexList[row].getLabel() << '\t' << vertexList[row].getColor() << endl;

       cout << endl << "Edge matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
}

/**
 @brief showshortestpath, part of it was given to us
 @param NONE
 @return NONE
*/
void WeightedGraph::showShortestPaths() const
{
   //set the path
   for( int i = 0; i < size; i++ )
   {
      for( int j = 0; j < size; j++ )
      {
         setPath( i, j, getEdge( i, j ));
      }
      
      setPath( i, i, 0 );
   }
   
   //loop through and set the path
   for( int i = 0; i < size; i++ )
   {
       
      for( int j = 0; j < size; j++ )
      {
          
         for( int c = 0; c < size; c++ )
         {
             
            if( (getPath( j, i ) != INFINITE_EDGE_WT) && (getPath( i, c ) != (INFINITE_EDGE_WT)))
            {
                
               if( (getPath( j, i ) + getPath( i, c ) < getPath( j, c )) || (getPath( j, c ) == INFINITE_EDGE_WT))
               {
                   
                  setPath( j, c, ( getPath( j, i ) + getPath( i, c )));
                  
               }
               
            }
            
         }
         
      }
      
   }
   
   //this was just given to us, the same as show structure
   cout << endl << "Path matrix : " << endl << '\t' ;
   
   for( int i = 0; i < size; i++ )
   {
      cout << i << '\t';
   }
   cout << endl;
   
   for( int i = 0; i < size; i++ )
   {
      cout << i << '\t';
      
      for( int j = 0; j < size; j++ )
      {
          
        int wt = getPath( i, j );
        
        if ( wt == INFINITE_EDGE_WT )
            cout << "- \t";
        else
            cout << wt << '\t';
         
      }
      
      cout << endl;
   }
}

/**
 @brief haspropercoloring
 @param none
 @return none
*/
bool WeightedGraph::hasProperColoring() const
{
   //loop through
   for( int i = 0; i < size; i++ )
   {
      for( int j = 0; j < size; j++ )
      {

         if( getEdge( i, j ) != INFINITE_EDGE_WT )
         {
            if( (vertexList[i].getColor() == vertexList[ j ].getColor()) && (i != j )) // don't really have to do i!=j since we eknow its INFINITE EDGE
            {
               return false;
            }
         }
      }
   }
   
   return true;
}

/**
 @brief all are even
 @param none
 @return none
*/
bool WeightedGraph::areAllEven() const
{
   int count = 0; //keep track
   
   //loop through
   for( int i = 0; i < size; i++ )
   {
      for( int j = 0; j < size; j++ )
      {
         if( getEdge( i, j ) != INFINITE_EDGE_WT )
         {
            count++;
         }
      }
      //if not even trurn false
      if( count % 2 != 0 )
      {
         return false;
      }
      //set back to zero
      count = 0;
   }
   
   return true;
}

/**
 @brief getindex
 @param v, which index?
 @return position of it otherwise -1 for not
*/
int WeightedGraph::getIndex(const string& v) const
{
   for( int i = 0; i < size; i++ )
   {
      if( vertexList[i].getLabel() == v )
      {
         return i;
      }
   }
   return -1;
}

/**
 @brief getedge, simple getter for edge
 @param row which row?
 @param col which col?
 @return the eedge
*/
int WeightedGraph::getEdge( int row, int col ) const
{
   return adjMatrix[row * maxSize + col];
}

/**
 @brief set the edge, simple setter
 @param row which row?
 @param col which col?
 @return NONE
*/
void WeightedGraph::setEdge (int row, int col, int wt)
{
   adjMatrix[row * maxSize + col] = wt;
   adjMatrix[col * maxSize + row] = wt;
}

/**
 @brief getpath, return the path
 @param row which row?
 @param col which col?
 @return integer, which path
*/
int WeightedGraph::getPath(int row, int col) const
{
   return pathMatrix[(row * maxSize) + col];
}

/**
 @brief setPath
 @param row which row?
 @param col which col?
 @return NONE
*/
void WeightedGraph::setPath (int row, int col, int wt) const
{
   pathMatrix[(row * maxSize) + col] = wt;
   pathMatrix[(col * maxSize) + row] = wt;
}



