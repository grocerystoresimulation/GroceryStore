#pragma once



#include <cassert>

#include <iostream>
using namespace std;



/****************************************************************************************
* Timer class keeps track of time in this Simulation.
* The "minute" time unit is used in this Simulation.
*
*
*
****************************************************************************************/


class Timer
{


public:

	// Default constructor

	Timer()
	{
		minutes = 0;
	}

	// Set minutes to the passed value

	void setMinutes(int minutes)
	{

		assert(minutes >= 0);
		this->minutes = minutes;

	}


	void tick()
	{
		minutes--;
	}




	// Return the number of minutes remaning in the simulation

	int timeRemaining() const
	{
		return minutes;
	}


private:

	int minutes;





};
