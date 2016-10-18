#include <iostream>
#include <list>
#include "../include/Graph.h"
#include "../include/ArticulationPoints.h"

#define NIL -1
using namespace std;


Articulation::Articulation(int V):Graph(V)
{
	visited = new bool[V];
	disc = new int[V];
	low = new int[V];
	parent = new int[V];
	ap = new bool[V];
}

Articulation::~Articulation()
{
	delete [] visited;
	delete [] disc;
	delete [] low;
	delete [] parent;
	delete [] ap;
}


// A recursive function that find articulation points using DFS traversal
// u --> The vertex to be visited next
// visited[] --> keeps tract of visited vertices
// disc[] --> Stores discovery times of visited vertices
// parent[] --> Stores parent vertices in DFS tree
// ap[] --> Store articulation points
void Articulation::APUtil(int u)
{
	// A static variable is used for simplicity, we can avoid use of static
	// variable by passing a pointer.
	static int time = 0;

	// Count of children in DFS Tree
	int children = 0;

	// Mark the current node as visited
	visited[u] = true;

	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;

	// Go through all vertices aadjacent to this
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;  // v is current adjacent of u

		// If v is not visited yet, then make it a child of u
		// in DFS tree and recur for it
		if (!visited[v])
		{
			children++;
			parent[v] = u;
			APUtil(v);

			// Check if the subtree rooted with v has a connection to
			// one of the ancestors of u
			low[u]  = min(low[u], low[v]);

			// u is an articulation point in following cases

			// (1) u is root of DFS tree and has two or more chilren.
			if (parent[u] == NIL && children > 1){
			  ap[u] = true;
				cout<<"time:"<<time<<"   ";
			}
			// (2) If u is not root and low value of one of its child is more
			// than discovery value of u.
			if (parent[u] != NIL && low[v] >= disc[u]){
				ap[u] = true;
				cout<<"time:"<<time<<"   ";
			}
		}

		// Update low value of u for parent function calls.
		else if (v != parent[u])
		  low[u]  = min(low[u], disc[v]);
	}
}

// The function to do DFS traversal. It uses recursive function APUtil()
void Articulation::AP()
{

	// Initialize parent and visited, and ap(articulation point) arrays
	for (int i = 0; i < V; i++)
	{
		parent[i] = NIL;
		visited[i] = false;
		ap[i] = false;
	}

	// Call the recursive helper function to find articulation points
	// in DFS tree rooted with vertex 'i'
	for (int i = 0; i < V; i++)
	  if (visited[i] == false)
		APUtil(i);

	// Now ap[] contains articulation points, print them
	for (int i = 0; i < V; i++)
	  if (ap[i] == true)
		cout << i << " ";
}


