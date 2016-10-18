#ifndef    __ARTICULATION_H_
#define	   __ARTICULATION_H_
#include "Graph.h"
#include  <list>
using namespace std;

// A class that represents an undirected graph

class Articulation : public Graph
{
private:
	bool		*visited;
    int			*disc;
    int			*low;
    int			*parent;
    bool		*ap; 
    void APUtil(int v);
public:
	Articulation(int V);   // Constructor
	virtual ~Articulation();   // Disconstructor
    void AP();    // prints articulation points
};
#endif
