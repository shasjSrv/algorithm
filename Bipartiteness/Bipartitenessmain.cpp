#include <iostream>
#include <cstdio>
#include <stack>
#include <list>
#include "Bipartiteness.h"


int main()
{
    Bipartite g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(0, 3);
    g1.addEdge(1, 0);
    g1.addEdge(1, 2);
    g1.addEdge(2, 1);
    g1.addEdge(2, 3);
    g1.addEdge(3, 2);
    g1.addEdge(3, 0);
    if (g1.isBi())
        cout<<"The graph is Bipartite"<<endl;
    else
        cout<<"The graph is not Bipartite"<<endl;
}
