/**
	@file Timer.cpp
	
	@brief  This is the implemnetation file for Timer.h We will have to analyze how a routine performs, this is why this lab is 
	called the performance evaluation. According to the book we will have to pay close attention to how the program uses iteration
	and recursion and then express the routine's projected execution time as a function of the number of data item (N) that it
	manipulates as it performs its task. These results would the in the form of O(N) and O(LogN) and dso on.
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 9/26/2017
	
	@bug no known bugs, it was tested multiple times, and it has passed the test cases on the submit website
	
*/

// Header Filess ////////////////////////////////////////////////
//
#include "Timer.h"


/**
	@brief Default contructor, used to set values to a default value as soon as an objecet 
	is created this default contructor will be called.
	@param NONE
	@return Nothing, this is the defult contructor
*/
Timer::Timer()
{
	//setting all the private members to some default value
	beginTime.tv_sec = 0;
	beginTime.tv_usec = 0;

	duration.tv_sec = 0;
	duration.tv_usec = 0;
	
	timerWasStarted = false;
}

/**
	@brief start(), start the timer(set timerWasStarted to true) and throw runtime_error if the time hasn't started yet
	@param NONE
	@exception throws runtime_error if timer can't start
	@return Nothing, since this is a void function 
*/
void Timer::start() throw (runtime_error)
{	
	if(gettimeofday(&beginTime, NULL) == -1)
	{
		throw runtime_error ("start() Timer can't start");
	}
	timerWasStarted = true;
}

/**
	@brief stop(), stops the timer, if the timer hasn't started it will throw an exception
	@param NONE
	@exception throws logic_error is the timer hasn't started
	@return Nothing, since this is a void function 
*/

void Timer::stop() throw(logic_error)
{
	if(timerWasStarted == false)
	{
		throw logic_error ("stop() Timer hasn't started.");
	}
	long T1, T2;
	
	gettimeofday(&duration, NULL);
	
	T1 = beginTime.tv_sec * 1000000 + beginTime.tv_usec;
	T2 = duration.tv_sec  * 1000000 + duration.tv_usec;
	
	duration.tv_sec = T2 - T1;
	
	timerWasStarted = false;
}

/**
	@brief getElapsedTime(), gets the elapsedtime (microsecond to second) and returns it
	@param NONE
	@exception throws logic_error if the timer hasn't started
	@return returns the elapsedTime (duration.tv_sec/1000000.00)
*/
double Timer::getElapsedTime() const throw (logic_error)
{
	if(duration.tv_sec == 0)
	{
		throw logic_error("getElapsedTime() Timer hasn't started.");
	}
	return duration.tv_sec/1000000.00;
}