#pragma once

#include <iostream>

using namespace std;


template <class QueueElement>
class dynamic_queue {

public:

	//default constructor
	dynamic_queue(int capacity = 10) {

		itail = 0;
		ihead = 0;
		initial_capacity = 10;
		array_capacity = capacity;
		array_size = 0;
		myArray = new QueueElement[initial_capacity];
	}
	//copy constructor
	dynamic_queue(const dynamic_queue &copyQueue) {

		array_capacity = copyQueue.array_capacity;
		array_size = copyQueue.array_size;

		myArray = new QueueElement[array_capacity];

		for (int i = 0; i < array_capacity; i++) {

			myArray[i] = copyQueue.myArray[i];
		}

		ihead = copyQueue.ihead;
		itail = copyQueue.itail;
	}
	//default destructor
	~dynamic_queue() {

		for (int i = 0; i < array_capacity; i++) {

			delete &myArray[i];
		}

		delete[] myArray;
	}
	//returns a reference to the head element of the queue
	QueueElement& getHead() {

		if (array_size != 0) {

			return myArray[ihead % array_capacity];
		}
		else {

			throw new exception("Queue is Empty");
		}
	}
	//returns a reference to the tail element
	QueueElement& getTail() {

		if (array_size != 0) {

			return myArray[itail % array_capacity];
		}
		else {

			throw new exception("Queue is Empty");
		}
	}
	//method to return the size of the dynamic array
	int getSize() const {

		return array_size;
	}
	//returns a boolean staing whether the dynamic array is empty or not
	bool isEmpty() const {

		if (array_size == 0) {

			return true;
		}
		else {

			return false;
		}
	}
	//checks if queue is full
	bool isFull() {

		if (getSize() == array_capacity) return true;
		else return false;
	}
	/*-----------------------------------------------------------------------
	isFull

	Precondition: none
	Postcondition: returns a boolean value true if the queue is full, false otherwise
	-----------------------------------------------------------------------*/

	//creates a new array with double the capacity of the current array and copy each element into the new array
	void increaseSize() {

		QueueElement * newArray;
		newArray = new QueueElement[getCapacity() * 2];

		//copy each element of the old array
		int temp = ihead;
		for (int i = 0; i < getSize(); i++) {

			newArray[i] = myArray[temp];
			temp = (temp + 1) % array_capacity;
		}

		//program works with the delete commented out as well as only inutting arrival rate < #registers
		//delete[] myArray;

		//point myArray variable to the newly created array
		myArray = newArray;

		delete[] newArray;

		array_capacity *= 2;
		ihead = 0;
		itail = array_size - 1;
	}
	/*-----------------------------------------------------------------------
	increase size

	Precondition: queue is full
	Postcondition: doubles the capacity of the current array as a new array and copies all of its elements to a new array
	-----------------------------------------------------------------------*/

	//creates a new array with half the capacity of the current array and copy each element into the new array
	void decreaseSize() {

		initial_capacity = 10;
		//cannot reduce the capacity of the array to below the intial capacity
		if ((array_capacity / 2) < initial_capacity) {

			return;
		}

		QueueElement * newArray;
		newArray = new QueueElement[array_capacity / 2];

		//copy each element of the old array

		int temp = ihead;
		for (int i = 0; i < getSize(); i++) {

			cout << "size of current array: " << getSize() << endl;
			cout << "i" << i << endl;

			newArray[i] = myArray[temp];
			temp = (temp + 1) % array_capacity;
		}

		//program works with the delete commented out as well as only inutting arrival rate < #registers
		//delete[] myArray;

		//point myArray variable to the newly created array
		myArray = newArray;

		delete[] newArray;

		array_capacity /= 2;
		ihead = 0;
		itail = array_size - 1;
	}
	/*-----------------------------------------------------------------------
	decreaseSize

	Precondition: array is equal or less than 1/4 full
	Postcondition: copies all of the array elements into a new array of 1/2 the capacity
	-----------------------------------------------------------------------*/


	//returns the capacity of the dynamic array as an int
	int getCapacity() {

		return array_capacity;
	}
	/*-----------------------------------------------------------------------
	getCapacity

	Precondition: none
	Postcondition: returns an int of the array's capacity
	-----------------------------------------------------------------------*/

	//displays each 'active' element of the array (i.e. ignores elements that are actually in the array, but are not in the queue)
	void display(ostream &out) const {

		cout << endl << "The current contents of the list are: " << endl << endl;

		if (array_size == 0) {

			cout << "Queue is empty" << endl;
			return;
		}

		for (int i = 0; i < getSize(); i++) {

			cout << myArray[(i + ihead) % array_capacity] << endl;
		}
	}
	/*-----------------------------------------------------------------------
	display

	Precondition: the stream to print to
	Postcondition: displays all the elements of the queue
	-----------------------------------------------------------------------*/

	//increments the head tracker to 'remove' the oldest queue element
	void dequeue() {

		if (isEmpty()) {

			throw new exception("Queue is empty");
		}


		ihead = (ihead + 1) % array_capacity;

		array_size--;

		//make sure the size of the array can never be less than 0
		if (array_size <= 0) array_size = 0;

		if (getSize() <= (.25 * array_capacity)) {

			decreaseSize();
		}
	}
	/*-----------------------------------------------------------------------
	Default Constructor

	Precondition: none
	Postcondition: increments the head tracker, essentially 'removing' the head element
	-----------------------------------------------------------------------*/

	//adds a new element at the tail of the queue
	void enqueue(const QueueElement &value) {

		if (isFull() != true) {

			if (isEmpty() == true) {

				myArray[itail] = value;
			}
			else {

				itail = (itail + 1) % array_capacity;
				myArray[itail] = value;
			}

			array_size++;
		}
		else {

			increaseSize();
			enqueue(value);
		}
	}
	/*-----------------------------------------------------------------------
	enqueue

	Precondition: the element to be added to the array
	Postcondition: A element of any type is added to the tail of the array
	-----------------------------------------------------------------------*/

	//switches all the member variables of a to b and vice versa
	bool swap(dynamic_queue &a, dynamic_queue &b) {

		if (a.myArray != b.myArray) {

			dynamic_queue<QueueElement> temp;

			temp = a;
			a = b;
			b = temp;

			return true;
		}
		else {

			return false;
		}
	}
	/*-----------------------------------------------------------------------
	swap

	Precondition: a dynamic_queue
	Postcondition: A swaps all the variables of the passed in queue with the local queue
	-----------------------------------------------------------------------*/

	//Empties the queue and resizes it to the intial capacity
	void clear() {

		delete[] myArray;

		QueueElement * newArray;
		newArray = new QueueElement[initial_capacity];

		myArray = newArray;
		array_size = 0;
		itail = 0;
		ihead = 0;
	}
	/*-----------------------------------------------------------------------
	clear

	Precondition: none
	Postcondition: resets all the elements of the queue and intializes it back to its intial capacity
	-----------------------------------------------------------------------*/

	//assigns the right queue's contents to the left queue
	const dynamic_queue& operator=(const dynamic_queue &RHS) {

		if (this->myArray == RHS.myArray) return *this;

		array_capacity = RHS.array_capacity;
		array_size = RHS.array_size;

		myArray = new QueueElement[array_capacity];

		for (int i = 0; i < array_capacity; i++) {

			myArray[i] = RHS.myArray[i];
		}

		ihead = RHS.ihead;
		itail = RHS.itail;

		return *this;
	}
	/*-----------------------------------------------------------------------
	operator =

	Precondition: a dynamic_queue
	Postcondition: the LHS queue now has all the variables and queue elements of the HRS queue
	-----------------------------------------------------------------------*/

	//friend ostream& operator<< <> (ostream&, const dynamic_queue<dynamic_queue>&) {}

private:
	/***** Data Members *****/
	int ihead;
	int itail;
	int initial_capacity; // initial capacity of array
	int array_capacity; // current capacity of the array
	int array_size; // current size of queue stored in array
	QueueElement *myArray; // pointer to dynamically allocated array
};
