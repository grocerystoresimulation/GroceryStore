#pragma once

#include <cassert>// Provides assert
#include <iostream>
using namespace std;

/***************************************************************************************
* Queue.h
* TEMPLATE CLASS PROVIDED: Queue<Item> (a queue of items)
* 
* The template parameter, Item, is the data type of the items in the queue,
* also defined as Queue<Item>::value_type. 
* It may be any of the C++ built-in types (int, char, etc.), 
* or a class with a default constructor, 
* a copy constructor, and an assignment operator. 
*
****************************************************************************************
* The definition Queue<Item>::size_type is the data type of 
* any variable that keeps track of how many items are in a queue. 
*
* The static const CAPACITY is the maximum capacity of 
* a queue for this first queue implementation.
* 
*
***************************************************************************************/



template <class Item>
class Queue
{

public:

	// TYPEDEFS and MEMBER CONSTANTS

	typedef std::size_t size_type;
	typedef Item value_type;
	static const size_type CAPACITY = 30;

	// CONSTRUCTOR for the queue<Item> template class:

	Queue( );

	// MODIFICATION MEMEBER FUNCTIONS

	void pop( );
	void push( const Item & entry );


	// CONSTANT MEMBER FUNCTIONS

	// Postcondition: The return value is true if the queue is empty.
	bool empty( ) const { return count; }
	Item front( ) const; 


	// Postcondition: The return value is the total number of items in the queue.
	size_type size( ) const { return count; }

private:

	Item data[CAPACITY]; // Circular array

	size_type first; // Index of item at the front of the queue
	size_type last; // Index of item at the rear of the queue
	size_type count; // Total number of items in the queue


					 
	// HELPER MEMBER FUNCTION
	size_type next_index( size_type i ) const
	{
		return ( i + 1 ) % CAPACITY;
	}


};


template <class Item>
const typename queue<Item>::size_type queue<Item>::CAPACITY;

// CONSTRUCTOR for the queue<Item> template class:

// Postcondition: The queue has been initialized as an empty queue.

template <class Item>
Queue<Item>::Queue( )
{

	count = 0;
	first = 0;
	last  = CAPACITY - 1;

}



// MODIFICATION MEMBER FUNCTIONS for the queue<Item> template class:

// Precondition: size( ) > 0.
// Postcondition: The front item of the queue has been removed.

template <class Item>
void Queue<Item>::pop()
// Library facilities used: cassert
{
	assert( !empty( ) );
	first = next_index( first );
	--count;
}

// Precondition: size( ) < CAPACITY.
// Postcondition: A new copy of entry has been inserted at the rear of the queue.

template <class Item>
void Queue<Item>::push( const Item & entry )
// Library facilities used: cassert
{
	assert( size() < CAPACITY );
	last = next_index( last );
	data[last] = entry;
	++count;
}


// CONSTANT MEMBER FUNCTIONS for the queue<Item> template class:

// Precondition: size( ) > 0.
// Postcondition: The return value is the front item of the queue 
// (but the queue is unchanged).

template <class Item>
Item Queue<Item>::front() const
// Library facilities used: cassert
{
	assert( !empty( ) );
	return data[first];
}


