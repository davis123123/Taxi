#include "Dispatcher.h"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

CDispatcher::CDispatcher(void){
	m_taxis[0].m_name = "RED";
	m_taxis[1].m_name = "GREEN";
	m_taxis[2].m_name = "BLUE";
	m_taxis[3].m_name = "YELLOW";
	m_taxis[4].m_name = "PINK";
	
  for (int i = 0; i < NUM_TAXIS; i++)
		m_taxis[i].SetAvailable(true);
}
CDispatcher::~CDispatcher(void){}
//update the movement of the taxis over timestep dt
void CDispatcher::UpdateTaxis(int dt){return;}
//allocate a taxi to respond to the incoming customer request
void CDispatcher::ProcessCall(string buf){
  istringstream in_buf(buf);
  int f_start, f_end;
  char f_command;
  in_buf >> f_command; //get command 'c'
  in_buf >> f_start; // start location
  in_buf >> f_end; //get destination
  CTaxi *cl_taxi;
  int c_taxiWeight = 1000;

  for (int i = 0; i < NUM_TAXIS; i++){
    if(m_taxis[i].IsAvailable() == true){
      int taxi_loc = m_taxis[i].GetLocation();//get location of taxi
      int path_length = m_roadMap->CalcShortestPath(taxi_loc, f_start); //calculate length
      if (path_length < c_taxiWeight){
        cl_taxi = &m_taxis[i];//closest taxi = current taxi
        c_taxiWeight = path_length; //set path length for compare
      }//check shortest path for taxis
    }//if taxi is available
  }

  cl_taxi->SetAvailable(false);//taxi no longer available
  cl_taxi->SetDropoff(f_end);//sets taxi's dropoff location
  m_taxis->SetRoute(m_roadMap, f_start);
  cout << "Dispatching taxi " << m_taxis->m_name << " to location " << f_start << " with destination " << f_end << endl;
m_taxis->PrintRoute(); 
} //INCOMPLETE

//set the map of the city
void CDispatcher::SetMap(string buf){
	istringstream in_buf(buf);
	char b_command;
	in_buf >> b_command;
	int b_size, b_start, b_end, b_weight;
	in_buf >> b_size;
  m_roadMap = new CGraph(b_size);//start new graph
  m_roadMap->Resize(b_size);//readjust size
  while(in_buf >> b_start){ //while extraction is still integer
    in_buf >> b_end;
    in_buf >>b_weight;
    m_roadMap -> AddEdge(b_start, b_end, b_weight);
  } //stops right before next command
}

	//"teleport" the taxis to a given location and set their status to be available
void CDispatcher::SetTaxiLocations(string buf){
  istringstream tBuf(buf);
  //dump command from buffer
  char command, taxi;
  tBuf >> command;
  int location;
  //position all the taxis
  while(!tBuf.eof())
  {
    tBuf>>taxi;
    tBuf>>location;
    int index;
    switch (taxi){
    case 'R':
      index = RED;
      break;
    case 'G':
      index = GREEN;
      break;
    case 'B':
      index = BLUE;
      break;
    case 'Y':
      index = YELLOW;
      break;
    case 'P':
      index = PINK;
      break;
    default:
      assert(false);
    }
    m_taxis[index].SetLocation(location);
  }
}