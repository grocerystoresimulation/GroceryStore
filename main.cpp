#pragma once
#include "Timer.h"
#include "Customer.h"
#include "Simulation.h"

#include <iostream>

using namespace std;

void runSim() {

	//run the simulation
	Simulation sim;
	sim.run();

	cin.ignore();
	cin.ignore();
	cin.ignore();

	exit(0);
}

void runQueueTest() {

	//test dynamic queue class
	dynamic_queue<int> queue1;
	queue1.enqueue(1);
	queue1.enqueue(2);
	queue1.enqueue(3);
	queue1.enqueue(4);
	queue1.enqueue(5);
	queue1.enqueue(6);
	queue1.enqueue(7);

	queue1.dequeue();
	queue1.dequeue();
	queue1.dequeue();

	queue1.enqueue(8);
	queue1.enqueue(9);
	queue1.enqueue(10);

	cout << "queue should have the elements: 4 5 6 7 8 9 10" << endl;
	queue1.display(cout);

	queue1.dequeue();
	queue1.dequeue();
	queue1.dequeue();
	queue1.dequeue();
	queue1.dequeue();
	queue1.dequeue();
	queue1.dequeue();

	cout << "\nqueue should now be empty " << endl;
	queue1.display(cout);

	queue1.clear();

	cout << "\nadding some more elements" << endl;
	queue1.enqueue(1);
	queue1.enqueue(2);
	queue1.enqueue(3);

	cout << "\nqueue should have the elements: 1 2 3" << endl;
	queue1.display(cout);

	cout << "head and tail: " << queue1.getHead() << " " << queue1.getTail() << endl;
	cin.ignore();
	cin.ignore();
	cin.ignore();
	exit(0);
}

int main() {

	int input = 0;
	cout << "Would you like to test the dynamic queue or run the grocery store simulation? (1 for queue, 2 for simulation)" << endl;
	cin >> input;

	if (input == 1) {

		runQueueTest();
	}
	if (input == 2) {

		runSim();
	}

	return 0;
}
