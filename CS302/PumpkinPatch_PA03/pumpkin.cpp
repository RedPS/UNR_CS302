/**
	@file pumpkin.cpp
	
	@brief This program will find patches that include the character 'p', this is the famous pumpkin patch problem from ACM contest.
	The way this program works is that it uses a 2d array to store every character that the user enters, we are assuming that the 
	user will follow the rules, so we are not thrrowing any exceptions for user caused errors. Although the description is letting 
	us know that the dimentions will only be from 0 to 40 for both rows and columns (0 ≤ r ≤ 40 and 0 ≤ c ≤ 40), I went with another
	approach and decided to dynamically allocated memory so this way I wouldn't have eto create a 40 by 40 2d array even if the user
	enters something like 2 by 2, so I'm trying to save memory this way and have enough memory nit more and not less
	
	@author Pedram Safaei
	
	@version 1.0
	
	@date 9/19/2017
	
	@bug no known bugs, was tested with the submit website test cases and tricky private test cases created by the author
	there was a bug with the submit website but that does not count as a bug for this prrogram but it was documented in the 
	code as an IMPORTANT NOTE to whoever is going over the source code.
	
*/


/*
    IMPORTANT NOTE: during testing I encountered this weird problem were I had to remove all of my comments in order for the 
    Submit website to work, if you are encounterring the same problem, REMOVE ALL THE COMMENTS and try again. Just in case I 
    have uploaded a PDF and an HTML documentation for this program which should be fine for using as a documentation.
*/


/*
    Since I am documenting the prototypes I saw no points in documenting the function definitions at the end of this code,
    they do the same thing when a PDF or html is generated.
*/


// Header Files ///////////////////////////////////////////////////
//
#include <iostream>

/**
	@brief This method checks if there are any character 'p's in the 2d array.
	@param patches 2d array, where all the characters are stored.
	@param Position_Row it was declared in main and will start from zero.
	@param Position_col it was declared in main and will start from zero.
	@param row total number of rows that were dynamically allocated.
	@param col total number of columns that were dynamically allocated
	@return true for finding a 'p' and false for not finding one
*/
bool IsItPatch(char **patches, int &Position_Row, int &Position_col, int row, int col);

/**
	@brief This method will find the total number of 'p's, that will help us to get an idea of the length of the sizes.
	@param patches 2d array, where all the characters are stored.
	@param row total number of rows that were dynamically allocated.
	@param col total number of columns that were dynamically allocated.
	@return The total numbers of 'p's found in the 2d array.
*/
int TotalPatchP(char **patches, int row, int col);

/**
	@brief This method will check each patches and try to find the size of them recursively, by checking the upper bound, under, left, and right.
	@param Position_Row it was declared in main and will start from zero.
	@param Position_col it was declared in main and will start from zero.
	@param row total number of rows that were dynamically allocated.
	@param col total number of columns that were dynamically allocated
	@param starting_point, we want it to start from zero.
	@return The total size in one patch
*/
int TotalSizeP(char **patches, int Position_Row, int Position_col, int row, int col, int starting_point);

/**
	@brief This method will sort the sizes, as we are required to do that according to the instructions/
	@param Totalsizearray is a 1D array that storres all the sizes.
	@param Finalsize is the actual size of the array, we need it to know when to stop sorting.
	@return NONE, it is a VOID function.
*/
void sort(int *Totalsizearray, int Finalsize);

/**
	@brief This method will print the final information according to the format that was instructed.
	@param WhichGarden, automatically starts from 1 and gets incremented
	@param Totalsizearray is a 1D array that storres all the sizes.
	@param Finalsize is the actual size of the array, we need it to know when to stop sorting.
	@return NONE, it is a VOID function.
*/
void print(int WhichGarden, int* Totalsizearray, int Finalsize);


// Main Function Implementation ///////////////////////////////////
//
int main()
{
	//variables to store number of cols and rows
	int row;
	int col;

	//automatically start with 1 garden
	int WhichGarden = 1;
	char** pumppatch;



	while (true)
	{
		std::cin >> row >> col; //read the dimentions
		if (col == 0 || row == 0)
		{
			//if 0 just exit
			return 0;
		}
		else
		{
			//allocate memory START
			pumppatch = new char*[row];
			for (int i = 0; i < row; i++)
			{
				pumppatch[i] = new char[col];
			}
			//allocate memory FINISHED
			
			//reading in all the characters START
			for (int a = 0; a< row; a++)
			{
				for (int b = 0; b < col; b++)
				{
					std::cin >> pumppatch[a][b];
				}
			}
			//reading in all the characters FINISHED
			
			
			//Need a 1D array to store the sizes
			//this is allocating more memory which we might not need 
			//we could divide by 2 and it would work with most cases
			//but if we have 800 patches (size 1) then there would be a problem
			int totalsize = TotalPatchP(pumppatch, row, col); 
			int *Totalsizearray = new int[totalsize];
			
			//so we would know where 'p's are later
			int Position_Row = 0;
			int Position_col = 0;


			//saves patch size and puts it in the array we start from 0 since right now there is nothing
			int Finalsize = 0;
			int PatchSize = 0;
			
			
			while (IsItPatch(pumppatch, Position_Row, Position_col, row, col) == true) // as long as there is a patch
			{

				PatchSize = TotalSizeP(pumppatch, Position_Row, Position_col, row, col, 0);
				Totalsizearray[Finalsize] = PatchSize;
				Finalsize++;
			}
			
			//sort the sizes before printing
			sort(Totalsizearray, Finalsize);
			
			//print with the format that was instructed
			print(WhichGarden, Totalsizearray, Finalsize);
			
			//increment and check again
			WhichGarden++;


			//must not forget to deallocate or we would just have a terrible memory leak
			
			//deallocate 2D array START
			for (int i = 0; i < row; i++)
			{
				delete[] pumppatch[i];
			}
			delete[] pumppatch;
			//deallocate 2D array FINISHED
			
			//deallocate 1D array 
			delete[] Totalsizearray;
		}
		
	}

	return 0;
}

void sort(int *Totalsizearray, int Finalsize)
{
	//sort the size
	int temp;
	for (int i = 0; i < Finalsize - 1; i++)
	{
		for (int j = i + 1; j < Finalsize; j++)
		{
			if (Totalsizearray[i] > Totalsizearray[j])
			{
				temp = Totalsizearray[i];
				Totalsizearray[i] = Totalsizearray[j];
				Totalsizearray[j] = temp;
			}
		}
	}
}

void print(int WhichGarden, int* Totalsizearray, int Finalsize)
{
	std::cout << "Garden # " << WhichGarden << ": " << Finalsize << " patches, sizes:";
	for (int i = 0; i < Finalsize; i++)
	{
		std::cout << " " << Totalsizearray[i];
	}
	std::cout << std::endl;
}

int TotalPatchP(char **patches, int row, int col)
{
	int HowmanyP = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (patches[i][j] == 'p')
			{
				HowmanyP++;
			}
		}
	}

	return HowmanyP;
}

bool IsItPatch(char **patches, int &Position_Row, int &Position_col, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (patches[i][j] == 'p')
			{
				Position_Row = i;
				Position_col = j;
				return true;
			}
		}
	}

	return false;
}

int TotalSizeP(char **patches, int Position_Row, int Position_col, int row, int col, int starting_point)
{
	int HowMany = 1;

	patches[Position_Row][Position_col] = 0;

	//search upper_bound
	if ((starting_point != 1) && (Position_Row - 1 >= 0))
	{
		if (patches[Position_Row - 1][Position_col] == 'p')
		{
			HowMany = HowMany + TotalSizeP(patches, Position_Row - 1, Position_col, row, col, 3);
		}
	}
	//search left_bound

	if ((starting_point != 4) && (Position_col - 1 >= 0))
	{
		if (patches[Position_Row][Position_col - 1] == 'p')
		{
			HowMany = HowMany + TotalSizeP(patches, Position_Row, Position_col - 1, row, col, 2);
		}
	}

	//search right_bound

	if ((starting_point != 2) && (Position_col + 1 < col))
	{
		if (patches[Position_Row][Position_col + 1] == 'p')
		{
			HowMany = HowMany + TotalSizeP(patches, Position_Row, Position_col + 1, row, col, 4);
		}
	}

	//search down

	if ((starting_point != 3) && (Position_Row + 1 < row))
	{
		if (patches[Position_Row + 1][Position_col] == 'p')
		{
			HowMany = HowMany + TotalSizeP(patches, Position_Row + 1, Position_col, row, col, 1);
		}
	}

	return HowMany;

}