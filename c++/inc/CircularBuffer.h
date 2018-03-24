/******************************************************************************
 *
 *  Product Name:   Gate Of Ishtar, Segula Technologies
 *
 *     File Name:   CircularBuffer.h
 *     Created on:  Mar 24, 2018
 *     Author:      Fahad Umer
 *     Version:     1.0
 *
 *
 *   Description:   CircularBuffer class implementation using array. Circular buffer is thread safe. This file
 *                  contains the function prototypes for circular buffer.
 *
 ******************************************************************************/

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_


 /*=============================== INCLUSIONS ================================*/

#include <vector>
#include <mutex>
using std::mutex;
using std::vector;


/*=============================== CLASS DECLARATION ============================*/
template <class Object>
class CircularBuffer
{
public:

	/*constructor and destructors */
	explicit CircularBuffer( int capacity = DefaultBufferSize );
	virtual ~CircularBuffer();

	/*getters and setters */
	bool isEmpty( ) const;
	int  getCurrentSize( ) const;
	bool isFull( ) const;
	void writeIntoBuffer( const Object & x );
	Object readFromBuffer( );

	/*encapsulated data */
private:
	static const int DefaultBufferSize = 20;
	vector<Object> circularArray;
	int            currentSize;
	int            front;
	int            back;
	mutex          bufferMutex; /* used to avoid race conditions in multiple thread application */

	void makeEmpty( );

};


#endif /* CIRCULARBUFFER_H_ */
