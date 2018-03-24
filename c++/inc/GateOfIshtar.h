/******************************************************************************
 *
 *  Product Name:   Gate Of Ishtar, Segula Technologies
 *
 *     File Name:   GateOfIshtar.h
 *     Created on:  Mar 24, 2018
 *     Author:      Fahad Umer
 *     Version:     1.0
 *
 *
 *   Description:   This file contains prototype and constants related to
 *                  Gate of Ishtar
 *
 ******************************************************************************/

#ifndef GATEOFISHTAR_H_
#define GATEOFISHTAR_H_

 /*=============================== INCLUSIONS ================================*/

#include <ctime>
#include <string>
#include <map>
#include <tuple>
#include "CircularBuffer.h"

using std::string;
using std::map;
using std::pair;



/*============================ TYPE DEFINITIONS =============================*/

enum champion_t
{
	Human = 0,
	Wizard,
	Giant,
	Spirit,
	Vampire,
	CHAMPION_NO_COUNT
};

typedef pair <const int, string> championPairType;
typedef map<const champion_t, championPairType > championMapType;
typedef tm dateTimeType;


/*=============================== CLASS DECLARATION ============================*/

class Champion {
public:

	/* public member functions */
	explicit Champion(champion_t champion);
	explicit Champion(champion_t champion, int bufferCapacity);
	virtual ~Champion();
	int calculateChampionHealth( champion_t champion , CircularBuffer<dateTimeType> * date_intervals );

	championMapType championMap;

	/* encapsulated data and functions */
private:
	int HP;
	const string  getDayName[8] = {
			"Sunday",
			"Monday",
			"Tuesday",
			"Wednesday",
			"Thursday",
			"Friday",
			"Saturday"
	};

	const int championInitialHP[5] = {100,100,150,100,110};

    /* private methods */
	int  calculateDamageTaken(string day,dateTimeType * date,champion_t champion);
	bool isInvincibleChampion (	champion_t champion) const;
	bool isHollyDay           (	string day) const;
};

#endif /* GATEOFISHTAR_H_ */
