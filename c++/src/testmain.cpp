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
/* time interval in seconds since Epoch */
time_t secondsInterval[arraySize] = {1521000000, 1521200000 , 1521300000 , 1521400000 , 1521500000 , 1521060000 , 1521006000 , 1521837812};


/*====================== MAIN FUNCTION DEFINITION =============================*/

void fillUpBufferWithTestingData ( CircularBuffer<dateTimeType> * date_intervals )
{
	cout <<  "<============== STARTED WRITING DATA INTO BUFFER ===================>" << endl;
	cout << "The Following data has been written into buffer for testing purpose " << endl;

	for (int i =0; i < arraySize ; i++ )
	{
		dateTimeType * now = localtime(&secondsInterval[i]);
		date_intervals->writeIntoBuffer(*now);

		cout << (now->tm_year + 1900) << '-'
				<< (now->tm_mon + 1) << '-'
				<<  now->tm_mday << ' '
				<<  now->tm_hour << ':'
				<<  now->tm_min
				<< "\n";
	}
	cout <<  "<============== STOPPED WRITING DATA INTO BUFFER ===================>" << endl;

}

void printWelcomeNoteAndRules (void )
{
	/* print general info for the user */
	cout <<  "\t\t!!!!Welcome To Gate of Ishtar!!!!" << endl;
	cout <<  "\t\tProduct Name:    Gate Of Ishtar, Segula Technologies" << endl;
	cout <<  "\t\tAuthor      :    Fahad Umer"<<endl;
	cout <<  "\t\tVersion     :    1.0"<<endl;

	/* print available champion options */

	cout << "Select Champion" << endl;
	cout << "Enter\t \"0\" \t to select \"Human\" "<< endl;
	cout << "Enter\t \"1\" \t to select \"Wizard\" "<< endl;
	cout << "Enter\t \"2\" \t to select \"Giant\" "<< endl;
	cout << "Enter\t \"3\" \t to select \"Spirit\" "<< endl;
	cout << "Enter\t \"4\" \t to select \"Vampire\" "<< endl;
	cout << "Enter\t \"Any Other Number\" \t to  \"!!Exit the show\"!! "<< endl;

	/* print any rules if required */

}

int main( )
{
	/* Initialize buffer for testing  purpose */
	/* buffer accept data in standard c++ struct tm type */
	CircularBuffer<dateTimeType> date_intervals;

	fillUpBufferWithTestingData(&date_intervals);
	printWelcomeNoteAndRules();


	/* get the user input */
	int player;
	cin >> player;


	/* validate input */
	if ( player >= CHAMPION_NO_COUNT || player < 0 )
	{
		cout << "Value does not correspond to any player" << endl;
		cout << "Exiting .............." << endl;
		exit(0);
	}

	/* start the show */
	champion_t player_enum = (champion_t) player;
	Champion newPlayer(player_enum);
	championMapType::iterator foundIndex  = newPlayer.getChampionMap().find(player_enum);
	if (foundIndex  != newPlayer.getChampionMap().end() )
	{
		cout << "Champion class constructed. You have selected " << foundIndex->second.second << endl;
		cout << "Your Champion initial health is    = \t" << foundIndex->second.first << endl;
	}
	cout << "Your Champion health at day end is = \t" << newPlayer.calculateChampionHealth(player_enum, &date_intervals) << endl;

	return 0;
}
