#include "Taxi.h"
#include <iostream>
using namespace std;

	CTaxi::CTaxi(void){return;}
	CTaxi::~CTaxi(void){return;}

	//access functions
	void CTaxi::SetLocation(int v){
		m_location = v;
	}

	int CTaxi::GetLocation(){
		return m_location;
	}

	bool CTaxi::IsAvailable(){
		return m_bAvailable;
	}


	void CTaxi::SetAvailable(bool b){ 
		m_bAvailable = b;
	}

	//sets taxi dropoff to end location
	void CTaxi::SetDropoff(int d){
		m_dropoff == d;
	}

	//causes the taxi to calculate (and store) its route
	void CTaxi::SetRoute(CGraph * graph, int dest){ 
		m_route.clear();
    CGraphNode f_nodes[graph->m_size];
    for (int i = 0; i< graph->m_size; i++){
      f_nodes[i].m_dist = INFINITY;
      f_nodes[i].m_known = false;
      f_nodes[i].m_path = NOT_A_VERTEX;
    }

    int f_curr = m_location;
    f_nodes[f_curr].m_dist = 0;
    vector<EDGE>::iterator f_it;
    while (f_nodes[dest].m_known == false){
      vector<EDGE> f_edges = graph->m_adjList.at(f_curr);
      int f_dist = 0;
      f_it = f_edges.begin();
      while(f_it != f_edges.end()){
        EDGE f_edge = (*f_it);
        CGraphNode f_neighbor = f_nodes[f_edge.endVert];
        if (f_nodes[f_edge.endVert].m_known == false){
          f_dist = f_edge.weight + f_nodes[f_curr].m_dist;
          if (f_dist < f_nodes[f_edge.endVert].m_dist){
            f_nodes[f_edge.endVert].m_dist = f_dist;
            f_nodes[f_edge.endVert].m_path = f_curr;
          }
         }
        }
        f_nodes[f_curr].m_known = true;
        f_curr = NOT_A_VERTEX;
        f_dist = INFINITY;
        for (int i = 0; i < graph->m_size; i++){
          if (f_nodes[i].m_known == false){ 
          	if(f_nodes[i].m_dist < f_dist){
            	f_curr = i;
            	f_dist = f_nodes[i].m_dist;
          	}
          }	
        }
    ++f_it;
    }
    int f_stop = dest;
    for(;f_stop != m_location; f_stop = f_nodes[f_stop].m_path)
      m_route.push_front(f_stop);

    int f_next = m_route.front();
    vector <EDGE> f_edges = graph->m_adjList.at(m_location);
    f_it = f_edges.begin();
    while( f_it != f_edges.end()){
      if ((*f_it).endVert == f_next){
        m_distLeftOnEdge = (*f_it).weight;
      }
    ++f_it;
    }

}

	//update the position of the taxi
	void CTaxi::MoveTimeStep(int dt, CGraph * graph, int taxiIndex){
    int f_curr, f_next;
    for (int i=0; i<dt; i++)
    {
        if (m_bAvailable == false)
        {
            m_distLeftOnEdge--;
            if (m_distLeftOnEdge == 0)
            {
                f_curr = m_route.front();
                m_location = f_curr;
                m_route.pop_front();
                if (m_route.empty())
                {
                    if (m_location == m_dropoff)
                    {
                        m_bAvailable = true;
                        cout << "Taxi " << m_name << " dropping off passenger at " << m_location << "." << endl;
                    }
                    else
                    {
                        SetRoute(graph, m_dropoff);
                        cout << "Taxi " << m_name << " picking passenger up at " << m_location << "." << endl;
                        PrintRoute();
                    }
                }
                else
                {
                    f_next = m_route.front();
                    vector <EDGE> f_edges = graph->m_adjList.at(f_curr);
                    for (vector <EDGE>::iterator f_it = f_edges.begin(); f_it != f_edges.end(); f_it++)
                    {
                        if ((*f_it).endVert == f_next)
                        {
                            m_distLeftOnEdge = (*f_it).weight;
                        }
                    } 
                }
            }
        }
    }
}

void CTaxi::PrintRoute()
{
    cout << "Planned route: ";
    cout << m_location << " ";
    for (list <int>::iterator f_it = m_route.begin(); f_it != m_route.end(); f_it++)
    {
        cout << *f_it << " ";
    }
    cout << endl;
}