#include <iostream>
#include <cstdio>
#include <stack>
#include <list>
#include "../include/Bipartiteness.h"

Bipartite::Bipartite(int V):Graph(V)
{
	isBipartite = true;
	color = new bool [V];
	marked = new bool [V];
	edgeTo = new int [V];
}


Bipartite::~Bipartite()
{
	delete [] color;
	delete [] marked;
	delete [] edgeTo;
}

/*
 * DFS
 */
void Bipartite::dfs(int v)
{
	marked[v] = true;
	list<int>::iterator w;
	for (w = adj[v].begin(); w != adj[v].end(); w++)
	{
		if (!cycle.empty())
		  return;
		if (!marked[*w])
		{
			edgeTo[*w] = v;
			color[*w] = !color[v];
			std::cout<<color[*w]<<std::endl;
			dfs( *w);
		}
		else if (color[*w] == color[v])
		{
			isBipartite = false;
			cycle.push(*w);
			for (int x = v; x != *w; x = edgeTo[x])
			{
				cycle.push(x);
			}
			cycle.push(*w);
		}
	}
}
/* 
 * Returns true if graph is Bipartite
 */
bool Bipartite::isBi()
{
	for (int v = 0; v < V; v++)
	{
		if (!marked[v])
		{
			color[v] = false;
			dfs(v);
		}
	}

	return isBipartite;
}

