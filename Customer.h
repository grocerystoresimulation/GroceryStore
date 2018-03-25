#pragma once


#include "Timer.h"

#include <iostream>
using namespace std;


/****************************************************************************************
* Customer class creates a Customer that has a specified time he or she can come to
* check out and a specified time that a cashier can service this customer.
*
*
*
****************************************************************************************/

class Customer
{

public:


	// Default constructor

	Customer()
	{

		arrivalTime = 0;
		serviceTime = 0;

	}

	// Parameterized constructor

	Customer(const Timer & arrivalTime, int serviceTime)
	{

		this->arrivalTime = arrivalTime.timeRemaining();

		// Set the service time
		this->serviceTime = serviceTime;

	}

	// Sets the service time for a customer.

	void setServiceTime(int serviceTime)
	{
		this->serviceTime = serviceTime;
	}


	// Returns the arrival time.

	int getArrivalTime()
	{
		return arrivalTime;
	}

	// Returns a reference of the service time.

	int & getServiceTime()
	{
		return serviceTime;
	}







private:

	int arrivalTime; // Time the customer arrived
	int serviceTime; // Time the customer is serviced


};
