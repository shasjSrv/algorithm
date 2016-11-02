#include <BStree.h>
#include <iostream>

using namespace std;

template<typename T>
BStree<T>::BStree(vector<T> p,vector<T> q)
{
	m_p = p;
	m_q = q;
	for(int i = 0;i	< m_p.size() + 1; i++){
		m_w.push_back(vector<T>(m_p.size()));
		m_e.push_back(vector<T>(m_p.size()));
		m_root.push_back(vector<T>(m_p.size()));
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
	unsigned int size = m_p.size();
	for(int i = 1; i <= size; i++){
		m_e[i][i - 1] = m_q[i - 1];	
		m_w[i][i - 1] = m_q[i - 1];	
	}
	//cout<<"size:"<< size << endl;
	for(int l = 1; l < size; l++){
		for(int i = 1; i < size - l + 1; i++){
			int j = i + l -1; 
			//cout << "i:" << i << "	j:"<< j << endl;
			m_e[i][j] = 100000;
			m_w[i][j] = m_w[i][j - 1] + m_p[j] + m_q[j];
			for(int r = i ; r <= j; r++){
				T t = m_e[i][r - 1] + m_e[r + 1][j] + m_w[i][j];   
				if(t < m_e[i][j]){
					m_e[i][j] = t;
					m_root[i][j] = r;
				}
			}
		}
	
	}
}

template<typename T>  
void BStree<T>::output()  
{
	unsigned int root = m_root[0].size() - 1;
	unsigned int newIdx = m_root[1][root];
	unsigned int oldRIdx = 1;
	unsigned int oldCIdx = root;
    if (m_root[newIdx + 1][oldCIdx] != 0)
    {
        output_impl(newIdx + 1,oldCIdx, false, "");
    }
    cout << m_root[oldRIdx][oldCIdx] << endl;
	if (m_root[oldRIdx][newIdx - 1] != 0)
    {
        output_impl(oldRIdx,newIdx - 1, true, "");
    }
}

// indexR stand for the number of row in the m_root
// indexC stand for the number of colume in the m_root
template<typename T>  
void BStree<T>::output_impl(unsigned int indexR,unsigned int indexC ,bool left,string const & indent)  
{
	unsigned int newIdx = m_root[indexR][indexC];
	unsigned int oldRIdx = indexR;
	unsigned int oldCIdx = indexC;
	if (m_root[newIdx + 1][indexC] != 0)
	{
		output_impl(newIdx + 1,oldCIdx, false, indent + (left ? "|     " : "      "));
	}
	cout << indent;
	cout << (left ? '\\' : '/');
	cout << "-----";
	cout << m_root[oldRIdx][oldCIdx] << endl;
	if (m_root[indexR][newIdx - 1] != 0)
	{	
		output_impl(oldRIdx,newIdx - 1, true, indent + (left ? "      " : "|     "));
	}
}


template<typename T>
void BStree<T>::cprint()
{
	cout<< "m_root"<<endl;
	for(unsigned int i = 0; i < m_root.size(); i++){
		for(unsigned int j = 0; j < m_root[i].size(); j++){
			cout << m_root[i][j] << "	 ";
		}
		cout<<endl;
	}
	cout<< "---------------------------------"<<endl;
	cout<< "m_w:"<<endl;
	for(unsigned int i = 0; i < m_w.size(); i++){
		for(unsigned int j = 0; j < m_w[i].size(); j++){
			cout << m_w[i][j] << "	 ";
		}
		cout<<endl;
	}
	cout<< "---------------------------------"<<endl;
	cout<< "m_e:"<<endl;
	for(unsigned int i = 0; i < m_root.size(); i++){
		for(unsigned int j = 0; j < m_root[i].size(); j++){
			cout << m_e[i][j] << "	 ";
		}
		cout<<endl;
	}
}
