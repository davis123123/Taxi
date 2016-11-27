#include "Graph.h"
#include <list>
#include <vector>

using namespace std;
 
	CGraphNode::CGraphNode(void){}
	CGraphNode::~CGraphNode(void){}

	CGraph::CGraph(int initSize){
		m_size = initSize;
	}

	CGraph::~CGraph(void){}

	//adds an edge to the graph going from start to end and having weight "weight"
	void CGraph::AddEdge(int start, int end, int weight){
		edge iAdd;
		iAdd.endVert = end;
		iAdd.weight = weight;
		(m_adjList.at(start)).push_back(iAdd);
		}
		
	//return the length of a specified edge through the parameter length. 
	//returns false if there is no such edge, otherwise true
	bool CGraph::GetEdgeLength(int start, int end, int * length){return true;}

	//calculates the weight of the shortest path between start and end
	int CGraph::CalcShortestPath(int start, int end){
		CGraphNode f_nodes[m_size]; //array of nodes withsize m_size

		for (int i = 0; i < m_size; i++){
			f_nodes[i].m_dist = INFINITY;
			f_nodes[i].m_known = false;
			f_nodes[i].m_path = NOT_A_VERTEX;
		}//sets all the elements

		int f_curr = start;
		f_nodes[f_curr].m_dist = 0;
		vector<EDGE>::iterator f_this; //pointer
		while(f_nodes[end].m_known == false){
			vector<EDGE> f_edge = m_adjList.at(f_curr); //set to start
			int f_dist = 0;
			f_this = f_edge.begin();//point f_this to beginning of f_edge
			
			while(f_this != f_edge.end()){
				EDGE m_edge = (*f_this);
				CGraphNode f_neighbor = f_nodes[m_edge.endVert];
				if(f_nodes[m_edge.endVert].m_known == false){
					f_dist = m_edge.weight;
					f_dist += f_nodes[f_curr].m_dist;
					if (f_dist < f_nodes[m_edge.endVert].m_dist)
					{
						f_nodes[m_edge.endVert].m_dist = f_dist;
						f_nodes[m_edge.endVert].m_path = f_curr;
					}
				}
				++f_this; //continue advancing f_this until it reaches end
			}//find smallest unknown vertex

			f_nodes[f_curr].m_known = true;
			f_curr = NOT_A_VERTEX;
			f_dist = INFINITY;

			for(int i = 0; i < m_size; i++){
				if(f_nodes[i].m_known == false){
				  if(f_nodes[i].m_dist < f_dist){
					  f_curr = i;
				 	  f_dist = f_nodes[i].m_dist;
					  }
				}
			}//Dijkstras Algorithm
		}
		return f_nodes[end].m_dist;
	}

void CGraph::Resize(int b_size){
		m_adjList.clear(); //clear old list
  	vector <edge> f_list;
	  m_adjList.resize(b_size, f_list); //resizes the list 
}