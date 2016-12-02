#ifndef __MAXFLOW_H_
#define __MAXFLOW_H_

#include <vector>
#include <iostream>

using namespace std;

struct Node{
	int to, next, rest, cost;
	Node(int to1,int next1,int rest1,int cost1){
		to = to1;
		next = next1;
		rest = rest1;
		cost = cost1;
	}
	Node(){};

	Node & operator =(Node no){
		this->to = no.to;
		this->next = no.next;
		this->rest = no.rest;
		this->cost = no.cost;
		return *this;
	}
};


class MaxFlow{
public:
	MaxFlow(vector<int> R,int P,int M,int F,int N,int S);
	MaxFlow(){};
	inline void addedge(int from, int to, int capacity, int cost) {
		Node temp(to,m_head[from],capacity,cost);
		m_e.push_back(temp);
		m_head[from] = m_e.size() - 1;
		temp.to =  from;
		temp.rest = 0;
		temp.next = m_head[to];
		temp.cost = -cost;
		m_e.push_back(temp);
		m_head[to] = m_e.size() - 1;
	}
	bool	SPFA();
	void	update();
	void	MCF();
private:
	const int		inf = 1e9;
	const int		m_Max = 1000;
	vector<int> 	m_head;
	vector<int>		m_R;
	vector<int>		m_dis;
	vector<int>		m_pre;
	vector<bool>	m_vis;
	vector<Node>	m_e;
	int				m_p;
	int				m_m;
	int				m_f;
	int				m_n;
	int				m_s;
	int				m_t;
	int				S;
	int				T;
	int				maxflow;
	int				mincost;
};









#endif
