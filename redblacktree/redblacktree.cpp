#include "../include/redblacktree.hpp"
#include <iostream>
#include <queue>
#include <vector>


using namespace std;


template<typename T>  
void RBTree<T>::print()  
{  
    RBNode<T> *p;  
    queue<RBNode<T> *> Q;  
    Q.push(root);  
    while(!Q.empty())  
    {  
        p = Q.front();  
        Q.pop();  
        cout<<"节点: "<<p->val<<" ";  
        if(p->left)  
        {  
            cout<<"left:"<<p->left->val<<"->color:"<<p->left->color<<" ";  
            Q.push(p->left);  
        }  
        if(p->right)  
        {  
            cout<<"right:"<<p->right->val<<"->color:"<<p->right->color<<" ";  
            Q.push(p->right);  
        }  
        cout<<endl<<endl;  
    }  
}  
  
/* 
* 
* 搜索v1在红黑树中出现的位置，如果v1在红黑树中则node节点为 
* 值为v1所在红黑树中的节点。 
* 否则node节点为如果将v1插入到红黑树中的父节点 
* 
*/  
template<typename T>  
RBNode<T>* RBTree<T>::Search(const T &v1,RBNode<T> *&node,vector<RBNode<T>*> &v)  
{  
    RBNode<T> *p = root;  
	node = NULL;  
	bool tag = true;
    while(p)  
    {  
        if(p->val == v1)  
        {  
			if(tag){
				node = p;  
				tag = false;
			}
			v.push_back(node);
			p = p->right; 
				//break;  
        }  
        else if(p->val < v1)  
        {  
			node = p;  
            p = p->right;  
        }  
        else  
        {  
			node = p;  
            p = p->left;  
        }  
    }  
	return node;
}  
  
template<typename T>  
bool RBTree<T>::InsertUnique(const T &v1)  
{  
    RBNode<T> *parent = NULL;  
    RBNode<T> *newNode = new RBNode<T>(v1);  
	vector<RBNode<T>*> v;
    Search(v1,parent,v);
	if (!v.empty())
		parent = *v.end();
	if(parent == NULL)  
    {//红黑树为空，当前插入的节点为根节点。插入后将根颜色变为黑  
        root = newNode;  
        root->color = _rb_black_node;  
        return true;  
    }  
    /*if(parent->val == v1)//v1已经存在红黑树中。不再插入  */
        //return false;  
      
    if(v1 < parent->val)  
    {  
        parent->left = newNode;  
    }  
    else  
    {  
        parent->right = newNode;  
    }  
    newNode->parent = parent;  
    InsertReBalance(newNode);  
    return true;  
}  
  
/* 
* 
* 插入节点后进行调整， 
* 使所有节点满足红黑树的性质 
* 
*/  
template<typename T>  
void RBTree<T>::InsertReBalance(RBNode<T> *node)  
{  
    RBNode<T> *parent = node->parent;  
    RBNode<T> *grandParent = NULL;  
    while(parent && parent->color==_rb_red_node)  
    {  
        grandParent = parent->parent;  
        if(parent == grandParent->left)  
        {//父节点为祖父节点的左儿子  
            RBNode<T> *uncle = grandParent->right;  
            if(uncle && uncle->color == _rb_red_node)  
            {//情形1 父节点与叔节点都为红  
                //解决方法父与叔变黑，祖父变黑。祖父变为新的当前节点重新进入算法  
                parent->color = _rb_black_node;  
                uncle->color  = _rb_black_node;  
                grandParent->color = _rb_red_node;  
                node = grandParent;  
                parent = grandParent->parent;  
            }  
            else  
            {  
                if(node == parent->right)  
                {//情形2，叔为黑，当前节点为其父节点的右子节点  
                    //解决方法：以父节点为根进行左旋  
                    //操作后将转换为情形3  
                    node = _rbtree_rotate_left(parent);  
                    parent = node->parent;  
                    grandParent = parent->parent;  
                }  
                //情形3父为红，当前节点为父节点的左子节点  
                //解决方法：父节点变黑，祖父节点变红，以  
                //祖父节点为根节点进行右旋  
                parent->color = _rb_black_node;  
                grandParent->color = _rb_red_node;  
                _rbtree_rotate_right(grandParent);  
            }  
        }  
        else  
        {//父节点为祖父节点的右子节点，情况与上面相同  
            RBNode<T> *uncle = grandParent->left;  
            if(uncle && uncle->color == _rb_red_node)  
            {  
                uncle->color = _rb_black_node;  
                parent->color = _rb_black_node;  
                grandParent->color = _rb_red_node;  
                node = grandParent;  
                parent = node->parent;  
            }  
            else  
            {  
                if(node == parent->left)  
                {  
                    node = _rbtree_rotate_right(parent);  
                    parent = node->parent;  
                    grandParent = parent->parent;  
                }  
                parent->color = _rb_black_node;  
                grandParent->color = _rb_red_node;  
                _rbtree_rotate_left(grandParent);  
            }  
        }  
    }  
    root->color = _rb_black_node;  
}  
  

template<typename T>  
int RBTree<T>::erase(const T & v1)
{
	RBNode<T> *p = NULL;
	RBNode<T> *q = NULL; 
	vector<RBNode<T>*> v;
	v.clear();
	int n = 0;
	if((p = Search(v1,p,v)) != NULL)
	{
		n = v.size();
		while(v.size() > 0){
			q = Rebalance_for_erase(v[v.size()-1]);
			delete q;
			v.pop_back();
		}
	}
	return n;
}

template<typename T> 
RBNode<T>* RBTree<T>::Rebalance_for_erase(RBNode<T> *z)
{
	cout<<z->val<<endl;
	RBNode<T> * y = z;
	RBNode<T> * x = NULL;
	RBNode<T> * x_parent = NULL;
	if(z->left == NULL){
		x = z->right;
	}else{
		if(z->right == NULL)
			x = z->left;
		else{
			y = z->right;
			while(y->left !=NULL)
				y = y->left;
			x = y->right;
		}
	}
	
	if(y != z){
		//y->parent = z->parent;
		z->left->parent = y;
		y->left = z->left;
		if(y != z->right){
			x_parent = y->parent;
			if(x) x->parent = y->parent;
			y->parent->left = x;
			y->right = z->right;
			z->right->parent = y;
		}
		else
			x_parent = y;
		if(z == root)
			root = y;
		else if(z->parent->left == z)
			z->parent->left = y;
		else
			z->parent->right = y;
		y->parent = z->parent;
		std::swap(y->color,z->color);
		y = z;
		if(x)
			cout <<"after:"<<x->val<<endl;
	}else{
		x_parent = y->parent;
		if(x) x->parent = y->parent;
		if ( z == root)
			root = x;
		else if(z->parent->left == z)
			z->parent->left = x;
		else
			z->parent->right = x;
		cout<<"3"<<endl;
		
	}
	//cout<<root->left->val<<endl;
	if(y->color == _rb_black_node){
		while(x != root && (x == NULL || x->color == _rb_black_node)){
			cout<<"come in !"<<endl;
			if(x_parent->left == x){
				RBNode<T> * w = x_parent->right;	
				if(w->color == _rb_red_node){
					x_parent->color = _rb_red_node;
					w->color = _rb_black_node;
					_rbtree_rotate_left(x_parent);
					w = x_parent->right;
				}
				if(w == NULL )
					break;
				if((w->left == NULL || w->left->color == _rb_black_node) &&
					(w->right == NULL || w->right->color == _rb_black_node)){
					w->color = _rb_red_node;
					x = x_parent;
					x_parent = x_parent->parent;
				}else{
					if(w->right == NULL || w->right->color == _rb_black_node){
						if(w->left)  w->left->color = _rb_black_node;
						if(w->right) w->right->color = _rb_red_node;
						_rbtree_rotate_right(w);
						w = x_parent->right;
					}
					w->color = x_parent->color;
					x_parent->color = _rb_black_node;
					if(w->right) w->right->color = _rb_black_node;
					_rbtree_rotate_left(x_parent);
					break;
				}			
			}else{
				RBNode<T> * w = x_parent->left;
				if(w->color == _rb_red_node){
					x_parent->color = _rb_red_node;
					w->color = _rb_black_node;
					_rbtree_rotate_right(x_parent);
					w = x_parent->left;
				}
				if(w ==	NULL)
					break;
				if((w->left == NULL || w->left->color == _rb_black_node) &&
					(w->right == NULL || w->right->color == _rb_black_node)){
					w->color = _rb_red_node;
					x = x_parent;
					x_parent = x_parent->parent;
				}else{
					if(w->left == NULL || w->left->color == _rb_black_node){
						if(w->right)  w->right->color = _rb_black_node;
						if(w->left) w->left->color = _rb_red_node;
						_rbtree_rotate_left(w);
						w = x_parent->left;
					}
					w->color = x_parent->color;
					x_parent->color = _rb_black_node;
					if(w->left) w->left->color = _rb_black_node;
					_rbtree_rotate_right(x_parent);
					break;
				}
			}
		}		
		if(x) x->color = _rb_black_node;
		cout<<"complete"<<endl;
	}

	return y;
}
		
/* 
* 
* 左旋 
* 
*/  
template<typename T>  
RBNode<T> *RBTree<T>::_rbtree_rotate_left(RBNode<T> *x)  
{  
    RBNode<T> *y = x->right;  
    if(y == NULL)  
    {  
        return x;  
    }  
    //x的右节点为y的左节点  
    x->right = y->left;  
    if(y->left)//如果y的左节点存在，其父节点为y  
        y->left->parent = x;  
    if(root == x)  
    {//x为root，旋转后y为新的root根节点  
        root = y;  
    }  
    else  
    {  
        if(x == x->parent->left)  
        {//如果x为其父节点的左子节点。  
            //x的父节点的新左子节点为y  
            x->parent->left = y;  
        }  
        else  
        {  
            x->parent->right = y;  
        }  
        //y的父节点为x的父节点  
        y->parent = x->parent;  
    }  
    //y的左子节点为x  
    y->left = x;  
    //x的父节点为y  
    x->parent = y;  
    return x;  
}  
  
/* 
* 
* 右旋 
* 分析其逻辑与左旋代码类似 
* 
*/  
template<typename T>  
RBNode<T>* RBTree<T>::_rbtree_rotate_right(RBNode<T> *x)  
{  
    RBNode<T> *y = x->left;  
    if(y == NULL)  
    {  
        return x;  
    }  
    x->left = y->right;  
    if(y->right)  
        y->right->parent = x;  
    if(root == x)  
    {  
        root = y;  
    }  
    else  
    {  
        if(x == x->parent->left)  
        {  
            x->parent->left = y;  
        }  
        else  
        {  
            x->parent->right = y;  
        }  
        y->parent = x->parent;  
    }  
    y->right = x;  
    x->parent = y;  
    return x;  
}  
  
/* 
* 
* 销毁整棵红黑树 
* 
*/  
template<typename T>  
void RBTree<T>::Destroy(RBNode<T> *p)  
{  
    if(p->left)  
    {  
        Destroy(p->left);  
    }  
    if(p->right)  
    {  
        Destroy(p->right);  
    }  
    delete p;  
}  

template<typename T>  
void RBTree<T>::output()  
{
	if (root->right)
    {
        output_impl(root->right, false, "");
    }
    cout <<"b:"<<root->val << endl;
    if (root->left)
    {
        output_impl(root->left, true, "");
    }
}


template<typename T>  
void RBTree<T>::output_impl(RBNode<T>* n,bool left,string const & indent)  
{
	if (n->right)
    {
        output_impl(n->right, false, indent + (left ? "|     " : "      "));
    }
    cout << indent;
    cout << (left ? '\\' : '/');
    cout << "-----";
	if(n->color == 0)
		cout <<"b:"<< n->val << endl;
	else
		cout <<"r:"<< n->val << endl;
    if (n->left)
    {
        output_impl(n->left, true, indent + (left ? "      " : "|     "));
    }
}
