#ifndef	__BSTREE_H_
#define __BSTREE_H_
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

template<typename T>  
struct RBNode  
{  
    RBNode():left(NULL),right(NULL),val(T()){}  
    RBNode(const T &v1):left(NULL),right(NULL),val(v1){}  
    RBNode  *left;  
    RBNode  *right;  
    T       val;  
	RBNode * operator=(RBNode<T> * p){
		this->left = p->left;
		this->right = p->right;
		this->val = p->val;
		return this;
	}
};

template<typename T> 
class BStree
{
public:
	BStree(){}
	BStree(vector<T> p,vector<T> q);
	~BStree(){}
	void			optimalBST();
	void			output();
	void			output_impl(RBNode<T>* n,bool left,string const & indent);
	void			cprint();
private:
	vector<T>					m_p;
	vector<T>					m_q;
	vector<vector<T> >			m_root;
	vector<vector<T> >			m_w;
	vector<vector<T> >			m_e;
	RBNode<T> *					root;

};


#endif
