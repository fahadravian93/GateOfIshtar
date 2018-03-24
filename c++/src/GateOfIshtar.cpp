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
 *   Description:   This file contains function implementation related  to
 *                  Gate of Ishtar
 *
 ******************************************************************************/


/*=============================== INCLUSIONS ================================*/

#include "GateOfIshtar.h"
#include "CircularBuffer.cpp"

/*====================== PRIVATE FUNCTION DEFINITIONS ======================*/

/*****************************************************************************
 * Function Name: Champion
 *   Description: Parameterized constructor for Champion class object
 *                function initialize health of selected champion.
 *
 *****************************************************************************/
Champion::Champion(champion_t champion)
{
	championMap.insert( pair <champion_t, championPairType> ( Human,  championPairType (100, "Human"  )));
	championMap.insert( pair <champion_t, championPairType> ( Wizard, championPairType (100, "Wizard" )));
	championMap.insert( pair <champion_t, championPairType> ( Giant,  championPairType (150, "Giant"  )));
	championMap.insert( pair <champion_t, championPairType> ( Spirit, championPairType (100, "Spirit" )));
	championMap.insert( pair <champion_t, championPairType> ( Vampire,championPairType (110, "Vampire")));


	 championMapType::iterator foundIndex  = championMap.find(champion) ;

	if (foundIndex  != championMap.end() )
	{
		HP = foundIndex->second.first ;
	}
	else
		throw std::out_of_range("Invalid Champion Id"); /* may be caused due to internal wrong implementation */
}


/*****************************************************************************
 * Function Name: Champion
 *   Description: Default destructor for Champion class object
 *
 *****************************************************************************/
Champion::~Champion()
{
}


/*****************************************************************************
 * Function Name: isHollyDay
 *   Description: Test if the day is either Tuesday or Thursday, in either
 *                case damage shall be zero as Tuesdays and Thursdays are
 *                holly days in ancient babylon, so neither gods nor demons
 *                roam around the Gate. Our champions are safe from harm on
 *                the holly days.
 *
 *****************************************************************************/
bool Champion::isHollyDay( string day ) const
{
	return ( "Tuesday" == day || "Thursday" == day );
}


/*****************************************************************************
 * Function Name: isInvincibleChampion
 *   Description: Test if the day is either invincible or not. Magical
 *                champions (e.g. Wizards, Spirits) are able to deceive
 *                the guards and pass through the gate without losing any HP.
 *
 *****************************************************************************/
bool Champion::isInvincibleChampion (	champion_t champion) const
{
	return ( Wizard == champion || Spirit == champion );
}


/*****************************************************************************
 * Function Name: calculateDamageTaken
 *   Description: Calculate the The amount of health (HP) a champion may lose
 *                between 7 and 25 HP depending on the time of the day as the
 *                different god and demon forces are appearing during the day.
 *
 *****************************************************************************/
int Champion::calculateDamageTaken(string day,dateTimeType* date,champion_t champion)
{
	/* checking if the day is Tuesday or Thursday or the champion is invincible , in either case damage shall be none */
	if (isHollyDay (day) || isInvincibleChampion(champion))
	{
		return 0 ;
	}
	else /* calculate damage */
	{
		/* "Janna" demon of Wind spawned */
		if 		(  ( date->tm_hour == 6  )
				&& ( date->tm_min  >= 0  )
				&& ( date->tm_min  <= 29 )    )
		{
			return 7;
		}
		/* "Tiamat" goddess of Oceans spawned */
		else if (   ( date->tm_hour == 6  )
				&&  ( date->tm_min  >= 30 )
				&&  ( date->tm_min  <= 59 )    )
		{
			return 18;
		}
		/* "Mithra" goddess of sun spawned */
		else if  (  ( date->tm_hour == 7  )
				&&  ( date->tm_min  >= 0  )
				&&  ( date->tm_min  <= 59 )    )
		{
			return 25;
		}
		/* "Warwick" God of war spawned */
		else if  (  ( date->tm_hour == 8  )
				&&  ( date->tm_min  >= 0  )
				&&  ( date->tm_min  <= 29 )    )
		{
			return 18;
		}
		/* "Kalista" demon of agony spawned */
		else if  (  ( date->tm_hour >= 8  )
				&&  ( date->tm_hour <= 14 )
				&&  ( date->tm_min  >= 30 )
				&&  ( date->tm_min  <= 59 )    )
		{
			return 7;
		}
		/* "Ahri" goddess of wisdom spawned */
		else if  (  ( date->tm_hour == 15 )
				&&  ( date->tm_min  >= 0  )
				&&  ( date->tm_min  <= 29  )    )
		{
			return 13;
		}
		/* "Brand" god of fire spawned */
		else if  ( ( date->tm_hour == 15  && date->tm_min >= 0  )
				|| ( date->tm_hour == 16  && date->tm_min <= 59 )    )
		{
			return 25;
		}
		/* "Rumble" god of lightning spawned */
		else if  ( ( date->tm_hour == 17  )
				&& ( date->tm_min  >= 0   )
				&& ( date->tm_min  <= 59  )    )
		{
			return 18;
		}
		/* "Skarner" the scorpion demon spawned */
		else if  ( ( date->tm_hour >= 18 )
				&& ( date->tm_hour <= 19 )
				&& ( date->tm_min  >= 0  )
				&& ( date->tm_min  <= 59 )    )
		{
			return 7;
		}
		/* "Luna" The goddess of the moon spawned */
		else if  ( ( date->tm_hour == 20  )
				&& ( date->tm_min  <= 59   )    )
		{
			return 13;
		}
		else
		{
			return 0;
		}
	}

	return 0;
}

/*====================== PUBLIC FUNCTION DEFINITIONS ======================*/


/********************************************************************************
 * Function Name: calculateChampionHealth
 *   Description: Calculate amount of health remained for a champion
 *                at the end of day.
 *
 * @param       : champion       - type of the champion (e.g. 'Wizard', 'human')
 * @param       : date_intervals - circular buffer of date time intervals having
 *                                    standard c++ "struct tm" type.
 *
 ********************************************************************************/
int Champion::calculateChampionHealth (champion_t champion , CircularBuffer<dateTimeType> * date_intervals)
{
	int total_damage = 0 ;
	dateTimeType previousdateInterval ;
	dateTimeType nextdateInterval;

	if ( date_intervals->getCurrentSize() <=1 ) {
		/* Do nothing on purpose as health should be updated after every hour and we don't have sufficient information
		 * to compute interval. Either buffer is empty or have one item */
	}
	else
	{
		/* Safe to read data from buffer even if the buffer is shared between multiple threads because buffer_mutex will
		 * handle race conditions. */
		previousdateInterval = date_intervals->readFromBuffer();
		double interval = 0 ;

		/* Iterate till the buffer is not empty */
		while ( ! date_intervals->isEmpty() )
		{
			int next_damage = calculateDamageTaken(getDayName[previousdateInterval.tm_wday], &previousdateInterval , champion);

			if (! date_intervals->isEmpty()) {
				/* Safe to read data from buffer even if the buffer is shared between multiple threads because buffer_mutex will
				 * handle race conditions. */
				nextdateInterval = date_intervals->readFromBuffer();
				interval = difftime ( mktime (&nextdateInterval), mktime (&previousdateInterval) ) ;
			}

			/* Champion should only lose HP once every hour */
			if (  interval >= 3600  )
			{
				total_damage += next_damage;
				interval = 0 ;
			}
			else
			{
				/* Accumulate total time difference for those date time intervals whose damage has been calculated but not compensated.
				 * It can happen time difference between two consecutive intervals is less than an hour but is greater than an hour
				 * between front and back of circular buffer e.g
				 *
				 * ["2018-3-24 3:00" , "2018-3-24 3:30" , "2018-3-24 4:00" , "2018-3-24 4:30" ]
				 *     ^                                                             ^
				 *     |                                                             |
				 *   front 															back
				 *
				 * In above example, time difference between two consecutive intervals is never greater than an hour but is greater
				 * than an hour between front and back so damage must be updated when accumulated interval reaches an hour or more.
				 *
				 *  */
				interval += interval;
			}

			/* Don't miss next interval damage as the item was removed from buffer upon read operation */
			previousdateInterval = nextdateInterval ;
		}

	}

	/* update new health, minimum value of health is 0 at which champion will die*/
	HP =  ( total_damage > HP ) ? ( 0 ) : ( HP - total_damage ) ;

	return HP ;
}
