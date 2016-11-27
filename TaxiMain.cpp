
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Dispatcher.h"

using namespace std;

int main(int argc, char* argv[])
{
  ifstream inf("test.dat");
  char command;
  string buffer;

  getline(inf,buffer);//store inf into "buffer" string
  
  CDispatcher dispatcher;
  long time = 0;

  //process all of the events in the file that occur during the simulation
  while(!inf.eof() )
  {
	  stringstream bufStream(buffer);
	  bufStream  >> command;

	  switch (command)
	  {
	  case 't':
		  //time step.  Advance the state of the simulation.
		  
		  int dt;
		  bufStream >> dt;
		  time += dt;
		  cout << "current time: " << time << endl;

		  dispatcher.UpdateTaxis(dt);
		  break;
	  case 'c':
		  dispatcher.ProcessCall(buffer);
		  break;
	  case 'm':
		  dispatcher.SetMap(buffer);
		  break;
	  case 'r':
		  dispatcher.SetTaxiLocations(buffer);
		  break;
	  default:
		  cout << "Unrecognized command: " << command << endl;
	;
	  }
	
	  getline(inf,buffer);
  }

  inf.close();
	return 0;
}

