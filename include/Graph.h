#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <list>



using namespace std;

// A class that represents an abstract graph
class Graph
{
protected:
    int			V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
public:
    Graph(int V);   // Constructor
	virtual ~Graph();   // Disconstructor
    void addEdge(int v, int w);   // function to add an edge to graph
};


#endif
