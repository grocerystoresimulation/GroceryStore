#pragma once
#include <iostream>

#include "Timer.h"

using namespace std;

class Customer {

public:

	//default constructor
	Customer() {

		timeOfArrival = serviceTime = 0;
	}
	//specificconstructor
	Customer(const Timer &T, int serviceTime) {

		//record the customer's time of arrival
		timeOfArrival = T.timeRemaining();

		//set the service time
		this->serviceTime = serviceTime;
	}
	//copy constructor
	Customer(const Customer &copyCust) {

		timeOfArrival = copyCust.timeOfArrival;
		serviceTime = copyCust.serviceTime;

	}
	//returns the arrival time
	int getArrivalTime() {

		return timeOfArrival;
	}
	//returns a reference to the serviceTime
	int& getServiceTime() {

		return serviceTime;
	}
	//sets the service time
	void setServiceTime(int time) {

		serviceTime = time;
	}
	//decreases the serviceTime by 1
	void decrementServicetime() {

		//return serviceTime - 1;
		serviceTime--;
	}
	//displays the object's variables
	void display(ostream &out) {

		out << "Arrival Time:   " << timeOfArrival << endl;
		out << "Service Time:   " << serviceTime << endl;
	}
	//sets this object to the RHS one
	const Customer& operator=(const Customer &RHS) {

		if (this == &RHS) return *this;

		this->timeOfArrival = RHS.timeOfArrival;
		this->serviceTime = RHS.serviceTime;

		return *this;
	}

private:
	//member variables
	int timeOfArrival;
	int serviceTime;


};
