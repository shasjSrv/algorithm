#ifndef __RED_BLACKTREE_H_
#define __RED_BLACKTREE_H_
#include <iostream>  
#include <queue> 
#include <string>
using namespace std;  
static int _rb_black_node = 0;  
static int _rb_red_node   = 1;  
template<typename T>  
struct RBNode  
{  
    RBNode():left(NULL),right(NULL),parent(NULL),val(T()),color(_rb_red_node){}  
    RBNode(const T &v1):left(NULL),right(NULL),parent(NULL),val(v1),color(_rb_red_node){}  
    RBNode  *left;  
    RBNode  *right;  
    RBNode  *parent;  
    int     color;  
    T       val;  
	RBNode * operator=(RBNode<T> * p){
		this->color = p->color;
		this->left = p->left;
		this->right = p->right;
		this->parent = p->parent;
		this->val = p->val;
		return this;
	}
};  
  
template<typename T>  
class RBTree  
{  
public:  
    RBTree():root(NULL){}  
    ~RBTree()  
    {  
        if(root)  
        {  
            Destroy(root);  
        }  
    }  
    void			print();  
    RBNode<T>*		Search(const T &v1,RBNode<T> *&node,vector<RBNode<T>*> &v);  
    bool			InsertUnique(const T &v1);  
	int				erase(const T & v1);
	RBNode<T>*		Rebalance_for_erase(RBNode<T> *z);
    void			DeleteValue(const T &v1);  
    void			Destroy(RBNode<T> *p);  
    void			InsertReBalance(RBNode<T> *node);  
    RBNode<T>*		_rbtree_rotate_left(RBNode<T> *node);  
    RBNode<T>*		_rbtree_rotate_right(RBNode<T> *node);  
	void			output();
	void			output_impl(RBNode<T>* n,bool left,string const & indent);
private:  
    RBNode<T> *root;  
};  
    
#endif
