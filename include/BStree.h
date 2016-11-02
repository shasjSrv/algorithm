#ifndef	__BSTREE_H_
#define __BSTREE_H_
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

template<typename T> 
class BStree
{
public:
	BStree(){}
	BStree(vector<T> p,vector<T> q);
	~BStree(){}
	void			optimalBST();
	void			output();
	void			output_impl(unsigned int indexR,unsigned indexC,bool left,string const & indent);
	void			cprint();
private:
	vector<T>					m_p;
	vector<T>					m_q;
	vector<vector<T> >			m_root;
	vector<vector<T> >			m_w;
	vector<vector<T> >			m_e;
	//RBNode<T> *					root;

};


#endif
