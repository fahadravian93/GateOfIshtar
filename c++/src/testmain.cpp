/******************************************************************************
 *
 *  Product Name:   Gate Of Ishtar, Segula Technologies
 *
 *     File Name:   testmain.cpp
 *     Created on:  Mar 24, 2018
 *     Author:      Fahad Umer
 *     Version:     1.0
 *
 *
 *   Description:   This file contains main function for testing Gate of Ishtar
 *
 ******************************************************************************/


/*=============================== INCLUSIONS ================================*/

#include <iostream>
#include <ctime>
#include "CircularBuffer.cpp"
#include "GateOfIshtar.h"
using namespace std;


/*====================== INTERNAL DEFINITION =================================*/
const int arraySize = 8;
time_t secondsInterval[arraySize] = {1521000000, 1521200000 , 1521300000 , 1521400000 , 1521500000 , 1521060000 , 1521006000 , 1521837812};


/*====================== MAIN FUNCTION DEFINITION =============================*/
int main( )
{
	/*** Initialize buffer for testing  purpose ***/
	CircularBuffer<dateTimeType> date_intervals;

	cout <<  "<============== STARTED WRITING DATA INTO BUFFER ===================>" << endl;
	cout << "The Following data has been written into buffer for testing purpose " << endl;

	for (int i =0; i < arraySize ; i++ )
	{
		dateTimeType * now = localtime(&secondsInterval[i]);
		date_intervals.writeIntoBuffer(*now);

		cout << (now->tm_year + 1900) << '-'
		         << (now->tm_mon + 1) << '-'
		         <<  now->tm_mday << ' '
				 <<  now->tm_hour << ':'
				 <<  now->tm_min
		         << "\n";
	}
	cout <<  "<============== STOPPED WRITING DATA INTO BUFFER ===================>" << endl;

	/* print general info for the user */
	cout <<  "\t\t!!!!Welcome To Gate of Ishtar!!!!" << endl;
	cout <<  "\t\tProduct Name:    Gate Of Ishtar, Segula Technologies" << endl;
	cout <<  "\t\tAuthor      :    Fahad Umer"<<endl;
	cout <<  "\t\tVersion     :    1.0"<<endl;

//	/* print available champion options */
//	for (int i =0; i < CHAMPION_NO_COUNT ; i++ )
//	{
//		dateTimeType * now = localtime(&secondsInterval[i]);
//		date_intervals.writeIntoBuffer(*now);
//
//		cout << (now->tm_year + 1900) << '-'
//		         << (now->tm_mon + 1) << '-'
//		         <<  now->tm_mday << ' '
//				 <<  now->tm_hour << ':'
//				 <<  now->tm_min
//		         << "\n";
//	}

	champion_t name = Giant;
	Champion newPlayer(name);
	cout << newPlayer.calculateChampionHealth(name, &date_intervals) << endl;

	return 0;
}
