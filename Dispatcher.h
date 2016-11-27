//#pragma once

#include <string>
#include "Taxi.h"

using namespace std;

#define NUM_TAXIS 5
#define RED 0
#define GREEN 1
#define BLUE 2
#define YELLOW 3
#define PINK 4

class CGraph;

class CDispatcher
{
public:
	CDispatcher(void);
	~CDispatcher(void);


	//update the movement of the taxis over timestep dt
	void UpdateTaxis(int dt);

	//allocate a taxi to respond to the incoming customer request
	void ProcessCall(string buf);

	//set the map of the city
	void SetMap(string buf);

	//"teleport" the taxis to a given location and set their status to be available
	void SetTaxiLocations(string buf);

private:

	//the city map
	CGraph* m_roadMap;
	//the taxi fleet
	CTaxi m_taxis[NUM_TAXIS];

};
