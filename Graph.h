//#pragma once
#include <list>
#include <vector>


using namespace std;

#define INFINITY 99999
#define NOT_A_VERTEX -1

class CGraphNode
{
public:
	CGraphNode(void);
	~CGraphNode(void);

	long m_dist;
	bool m_known;
	int m_path;

};


typedef struct edge
{
	int endVert;
	int weight;
} EDGE;

class CGraph
{
public:
	CGraph(int initSize);

	~CGraph(void);

	//adds an edge to the graph going from start to end and having weight "weight"
	void AddEdge(int start, int end, int weight);

	//return the length of a specified edge through the parameter length. 
	//returns false if there is no such edge, otherwise true
	bool GetEdgeLength(int start, int end, int * length);

	//calculates the weight of the shortest path between start and end
	int CalcShortestPath(int start, int end);

	void Resize(int size);

	int m_size;

	vector <vector <EDGE> > m_adjList;

private:
	//helper function for above.  Find the smallest unknown vertex
	int SmallestUnkonwnVertex();
	
	int m_lastDijkCall;
	//number of nodes in the graph
public:
	CGraphNode * m_verts;
};
