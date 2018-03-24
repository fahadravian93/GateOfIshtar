/******************************************************************************
 *
 *  Product Name:   Gate Of Ishtar, Segula Technologies
 *
 *     File Name:   CircularBuffer.cpp
 *     Created on:  Mar 24, 2018
 *     Author:      Fahad Umer
 *     Version:     1.0
 *
 *
 *   Description:   CircularBuffer class implementation using array. This file
 *                  contains the function's implementation for circular buffer.
 *
 ******************************************************************************/

#include "CircularBuffer.h"

 /*=============================== INCLUSIONS ================================*/

#include <iostream>
#include <stdexcept>
using std::cout;
using std::endl;


/*========================== PUBLIC MEHOTDS DEFINITIONS ======================*/


/*****************************************************************************
 * Member Function Name: CircularBuffer
 *          Description: Construct the CircularBuffer with user provided capacity.
 *
 *****************************************************************************/
template <class Object>
CircularBuffer<Object>::CircularBuffer( int capacity ) : circularArray( capacity )
{
	makeEmpty( );
}


/*****************************************************************************
 * Member Function Name: ~ CircularBuffer
 *          Description: Destructor the CircularBuffer.
 *
 *****************************************************************************/
template <class Object>
CircularBuffer<Object>::~CircularBuffer( )
{
	/* No dynamically allocated space */
}


/*****************************************************************************
 * Member Function Name:  isEmpty
 *          Description:  Test if the CircularBuffer is logically empty.
 *   		        	  Return true if empty, false otherwise.
 *
 *****************************************************************************/
template <class Object>
bool CircularBuffer<Object>::isEmpty( ) const
{
	return currentSize == 0;
}


/*****************************************************************************
 * Member Function Name:  isFull
 *          Description:  Test if the CircularBuffer is logically full.
 *   		       	      Return true if full, false otherwise.
 *
 *****************************************************************************/
template <class Object>
bool CircularBuffer<Object>::isFull( ) const
{   return currentSize == (int) circularArray.size( );
}


/*****************************************************************************
 * Member Function Name:  getCurrentSize
 *          Description:  return current item counts
 *
 *****************************************************************************/
template <class Object>
int CircularBuffer<Object>::getCurrentSize( ) const
{
	return currentSize ;
}


/*****************************************************************************
 * Member Function Name:  readFromBuffer
 *          Description:  Return and remove the least recently inserted item
 *          			  from the CircularBuffer. Throw Underflow if empty.
 *
 *****************************************************************************/
template <class Object>
Object CircularBuffer<Object>::readFromBuffer( )
{
	bufferMutex.lock();
	if( isEmpty( ) )
	{
		throw std::out_of_range("Circular Buffer Underflow");
	}
	currentSize--;
	Object frontItem = circularArray[ front ];
	front++;
	front %= circularArray.size( );
	bufferMutex.unlock();
	return frontItem;
}


/*****************************************************************************
 * Member Function Name:  writeIntoBuffer
 *          Description:  Insert x into the CircularBuffer.
 *          			  Throw Overflow if CircularBuffer is full.
 *
 *****************************************************************************/
template <class Object>
void CircularBuffer<Object>::writeIntoBuffer( const Object & x )
{
	bufferMutex.lock();
	if( isFull( ) )
	{
		throw std::out_of_range("Circular Buffer Overflow");
	}
	else
	{
		back++;
		back  %= circularArray.size( );
		circularArray[ back ] = x;
		currentSize++;
	}
	bufferMutex.unlock();
}


/*========================== PRIVATE MEHOTDS DEFINITIONS ======================*/


/*****************************************************************************
 * Member Function Name:  makeEmpty
 *          Description:  Make the CircularBuffer logically empty.
 *
 *****************************************************************************/
template <class Object>
void CircularBuffer<Object>::makeEmpty( )
{
	bufferMutex.lock();
	currentSize = 0;
	front = 0;
	back = -1;
	bufferMutex.unlock();
}


