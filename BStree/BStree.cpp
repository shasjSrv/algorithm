#include <BStree.h>
#include <iostream>

using namespace std;

template<typename T>
BStree<T>::BStree(vector<T> p,vector<T> q)
{
	m_p = p;
	m_q = q;
	for(int i = 0;i	< m_p.size() + 1; i++){
		m_root.push_back(vector<T>(m_p.size() + 1));
	}
}

/*template<typename T>*/
//~BStree<T>::BStree()
//{
	//m_root.clear();
/*}*/

template<typename T>
void BStree<T>::optimalBST()
{
}

template<typename T>  
void BStree<T>::output()  
{
	if (root->right)
    {
        output_impl(root->right, false, "");
    }
    cout << root->val << endl;
    if (root->left)
    {
        output_impl(root->left, true, "");
    }
}


template<typename T>  
void BStree<T>::output_impl(RBNode<T>* n,bool left,string const & indent)  
{
	if (n->right)
    {
        output_impl(n->right, false, indent + (left ? "|     " : "      "));
    }
	if(n->left == NULL && n->right ==NULL){
		if(left)
			cout<<indent+'|'<<endl;
	}
    cout << indent;
    cout << (left ? '\\' : '/');
    cout << "-----";
	cout << n->val << endl;
	if(n->left == NULL && n->right ==NULL){
		if(!left)
			cout<<indent+'|'<<endl;
	}
    if (n->left)
    {
        output_impl(n->left, true, indent + (left ? "      " : "|     "));
    }
}


template<typename T>
void BStree<T>::cprint()
{

}
