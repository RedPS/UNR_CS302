/**
	@file databse.cpp
	
	@brief This is just a simple implementation for expression trees and Binary search, with that 
	we will also have to write implementation for a database reading, which would read a file 
	provided dby the instructional team. For this file we will have to write the databse stuff, to 
	read info.
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 10/26/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 
	
	
*/

//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "BSTree.cpp"
#include <cstdlib>

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 37;   //   I have changed this value so it would drun properly on the website. Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};


int main ()
{
    ifstream acctFile("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID = 0;                         // User input account ID
    long recNum = 0;                          // Record number
	
    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.
	
	string TEMP;
	
	acctFile >> entry.acctID;
	for(entry.recNum = 0; !acctFile.eof(); entry.recNum++)
	{
		index.insert(entry);
		acctFile >> TEMP 
				 >> TEMP 
				 >> TEMP;
		acctFile >> entry.acctID;
	}
	
    // Output 
	cout << endl;
	cout << "Account IDs :" << endl;
	index.writeKeys();
	cout << endl;

    // Clear the status flags for the database file.
    acctFile.clear();

    // Read an account ID ( keyboard )
	cout << "Enter account ID : ";
	while(cin >> searchID)
	{
		if(index.retrieve(searchID, entry))
		{
			cout << entry.recNum << " : ";
			acctFile.seekg(bytesPerRecord*entry.recNum, ios::beg);
			acctFile >> acctRec.acctID;
			acctFile >> acctRec.firstName;
			acctFile >> acctRec.lastName;
			acctFile >> acctRec.balance;
			cout << acctRec.acctID << " " << acctRec.firstName << " " << acctRec.lastName << " " << acctRec.balance << endl;
		}
		else
		{
			cout << "No record with that account ID" << endl;
		}
		cout << "Enter account ID (EOF to quit): ";
	}
	return 0;
}