#include "BStree.cpp"
#include <iostream>
#include <vector>

using namespace std;


int main()
{
	vector<double>	 p,q;
	p.push_back(0);
	p.push_back(0.15);
	p.push_back(0.1);
	p.push_back(0.05);
	p.push_back(0.1);
	p.push_back(0.2);
	q.push_back(0.05);
	q.push_back(0.1);
	q.push_back(0.05);
	q.push_back(0.05);
	q.push_back(0.05);
	q.push_back(0.1);
	BStree<double> tree(p,q);
}
