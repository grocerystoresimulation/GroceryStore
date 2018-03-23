#pragma once

#include <cassert>
using namespace std;


class Timer {

public:

	//default constructor
	Timer(int initTime = 0) {

		assert(initTime >= 0);
		minutes = initTime;
	}

	//sets minutes to the passed value
	void set(int minutes) {

		assert(minutes >= 0);
		this->minutes = minutes;
	}

	//'advances' one minute of time
	void tick() {

		minutes--;
	}

	//returns the number of minutes remaining in the simulation
	int timeRemaining() const {

		return minutes;
	}


private:

	int minutes;

};
