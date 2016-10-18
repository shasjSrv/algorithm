#ifndef __BIPARTITENESS_H_
#define __BIPARTITENESS_H_

#include <iostream>
#include <cstdio>
#include <stack>
#include <list>
#include "Graph.h"

class Bipartite : public Graph
{
    private:
        bool isBipartite;
        bool *color;
        bool *marked;
        int *edgeTo;
        stack<int> cycle;
    public:
        Bipartite(int V);
		virtual ~Bipartite();
		void dfs(int v);
		bool isBi();
};
#endif
