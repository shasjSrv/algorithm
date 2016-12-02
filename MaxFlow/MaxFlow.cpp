#include "MaxFlow.h"
#include <vector>
#include <iostream>
#include <queue>

using namespace std;


MaxFlow::MaxFlow(vector<int> R,int P,int M,int F,int N,int B):m_head(vector<int>(m_Max))
															  ,m_dis(vector<int>(m_Max))
															,m_pre(vector<int>(m_Max))
															,m_vis(vector<bool>(m_Max))
{
	int totalDay = R.size();
	S = 0;
	T = 2 * totalDay +1;
	m_e.push_back(Node(0,0,0,0));
	m_e.push_back(Node(0,0,0,0));
	m_R = R;
	for (int i = 1, r; i <= totalDay; i++) {
		/*scanf("%d", &r);*/
		r = m_R[i - 1];
		addedge(S, i, r, 0); 
		addedge(totalDay + i, T, r, 0);
	}
	for (int i = 1; i <= totalDay; i++) {
		addedge(S, totalDay + i, inf, P);
		if (i < totalDay)    addedge(i, i + 1, inf, 0);
		if (i + M <= totalDay) addedge(i, i + M + totalDay, inf, F);
		if (i + N <= totalDay) addedge(i, i + N + totalDay, inf, B);
	}
}

bool MaxFlow::SPFA()
{
	static queue<int> Q;
	for (int i = S; i <= T; i++) 
	  m_dis[i] = inf, m_vis[i] = false;
	Q.push(S); 
	m_dis[S] = 0; 
	m_vis[S] = true;
	while (!Q.empty()) {
		int from = Q.front();
		Q.pop();
		m_vis[from] = false;
		cout << "from:" << from << "\tdis[form]:" << m_dis[from] << endl;
		for (int i = m_head[from]; i; i = m_e[i].next) {
			int to = m_e[i].to;
			//cout << "m_e[" << i << "]:" << m_e[i].cost << endl;
			if (m_e[i].rest && m_dis[to]>m_dis[from] + m_e[i].cost) {				//converse direction ,so m_e[i].cost < 0
				m_dis[to] = m_dis[from] + m_e[i].cost;
				cout << "to:" << to << "\tm_dis:" << m_dis[to] << endl;
				m_pre[to] = i;
				if (m_vis[to] == false) {
					m_vis[to] = true;
					Q.push(to);
				}
			}
		}
	}
	return m_dis[T]<inf;
}


void MaxFlow::update()
{
	int flow = inf;
	for (int i = m_pre[T]; i; i = m_pre[m_e[i ^ 1].to])
		flow = min(flow, m_e[i].rest);
	for (int i = m_pre[T]; i; i = m_pre[m_e[i ^ 1].to]) {
		m_e[i].rest -= flow;
		m_e[i ^ 1].rest += flow;
		cout << "to:" <<m_e[i].to << "\tfrom rest to:" << m_e[i].rest << endl;
	}
	maxflow += flow; 
	mincost += flow*m_dis[T];
	cout << "flow:" << flow << endl;
}

void MaxFlow::MCF()
{
	maxflow = mincost = 0;
	while (SPFA()) {
		cout << "come in!" << endl;
		update();
	}
	//cout << mincost << endl;
}
