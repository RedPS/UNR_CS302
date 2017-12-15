//--------------------------------------------------------------------
//
//  Laboratory 7, Programming Exercise 1                   storesim.cs
//
//  Program implementation shell.
//
//--------------------------------------------------------------------

// Simulates the flow of customers through a line in a store.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "config.h"

// Use which ever implementation is currently configured.

#   include "QueueLinked.cpp"


using namespace std;

int main ()
{

    QueueLinked<int> custQ;      // Line (queue) of customers containing the
			 //   time that each customer arrived and
                                 //   joined the line
    int simLength,               // Length of simulation (minutes)
        minute = 0,  //I set that equal to zero since minute needs to be initialized                // Current minute
        timeArrived,             // Time dequeued customer arrived
        waitTime,                // How long dequeued customer waited
        totalServed = 0,         // Total customers served
        totalWait   = 0,         // Total waiting time
        maxWait     = 0,         // Longest wait
        numArrivals = 0;         // Number of new arrivals

    // Seed the random number generator. Equally instructive to run the
    // simulation with the generator seeded and not seeded.
    srand(7);

    cout << endl << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    // Put your code here to run this simulation. Use "rand()" to get
    // a pseudorandom number that you can use to calculate probabilities.
	
 	while(minute < simLength)
	{
	    
		++minute;
		
		if(custQ.isEmpty()== false)
		{
		    
			timeArrived = custQ.dequeue();
			waitTime = minute - timeArrived;
			
			
			if(waitTime > maxWait)
			{
				maxWait = waitTime;
			}
			
			totalWait += waitTime;
			++totalServed;
		
		}
		switch(rand() % 4)
		{
		    
			case 1:
			
				++numArrivals;
				custQ.enqueue(minute);
				break;
			
			case 2:
			
				numArrivals = 2;
				
				for(int i = 0; i < numArrivals; i++)
				{
					custQ.enqueue(minute);
				}
				
				break;
			
			
			default: 
				numArrivals = 0;
				
			
			
		}
		
	}




    // Print out simulation results
    cout << endl;
    cout << "Customers served : " << totalServed << endl;
    cout << "Average wait     : " << setprecision(2)
         << double(totalWait)/totalServed << endl;
    cout << "Longest wait     : " << maxWait << endl;

    return 0;
}
