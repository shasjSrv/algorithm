#include <list>
#include <vector>
#include <dynamicHash.h>
#include <iostream>

using namespace std;

template<typename T>
DynicHash<T>::DynicHash():
	m_size(4),
	m_initSize(4)
{
	for(int i = 0; i < m_initSize; i++ ){
		list<T> * bucket = new(list<T>);
		m_hashList.push_back(bucket);	
		m_or.push_back(0x0004);
	}
	m_zeroAnd = ~m_or[0];
}

template<typename T>
DynicHash<T>::~DynicHash()
{
	for(int i = m_hashList.size() - 1; i >= 0; i--){
		bool ok = true;
		list<T> * bucket = m_hashList[i]; 
		for(int j = 0; j < m_hashList.size() - 1; j++){
			if(bucket == m_hashList[j]){
				ok = false;
				break;
			}
		}
		if(ok){
			delete bucket;
		}
		m_hashList.pop_back();
	}
}

template<typename T>
void DynicHash<T>::calculateHash(T val)
{
	int sourceSize = m_hashList.size();
	for(int i = m_hashList.size() - 1; i >= 0 ; i--){
		if((val % sourceSize) == i){
			if((*m_hashList[i]).size() < m_size)
				(*m_hashList[i]).push_back(val);
			else
				expendHashTable(val,i);
				break;
		}	
	}
}

template<typename T>
void DynicHash<T>::expendHashTable(T val,int i)
{
	unsigned int sourceSize = m_hashList.size();
	unsigned int half = sourceSize / 2;
	for(int j = 0; j < sourceSize ; j++){
		if(j == i){
			list<T> * newlist = new(list<T>);
			if(newlist == NULL){
				cout<<"new error,can't insert:"<<val<<endl;
				return;
			}
			unsigned int k = i,g = i;
			if(k > half - 1){
				k -= half;
			}
			if(g <= half - 1){
				g += half;
			}
			if(i / half % 2 == 1){				//look forawrd to find first bucket if it is odd
				if(m_hashList[k] == m_hashList[i]){
					/*if (i < half - 1)*/
					//if(m_hashList[i] == m_hashList[i + half])
					//else
					/*if(m_hashList[i] == m_hashList[i - half])*/
					j = k;
				}
			}else{
				if(m_hashList[g] == m_hashList[i]){
					j = g;
				}
			}
			if(j == i)
			   j += sourceSize;
			fineTune(val,i,j,newlist);
			return;
		}
	}	

}

template<typename T>
void DynicHash<T>::fineTune(T val,int i,int j,list<T> * newlist)
{
	int source_i = i;
	list<T> * p = m_hashList[i];
	typename list<T>::iterator pnlist = (*m_hashList[i]).begin();
	typename list<T>::iterator plist;
	m_zeroAnd = ~m_or[i];
	cout<<"insert m_or:"<<m_or[i]<<endl;
	for(pnlist = (*m_hashList[i]).begin(); pnlist != (*m_hashList[i]).end() ;){
		T temp = *pnlist;
		cout<<temp<<endl;
		cout<<(temp&m_zeroAnd)<<endl;
		cout<< ((temp % m_or[i]) & m_zeroAnd) << endl;
		if ((temp&m_zeroAnd) == temp ){
			pnlist++;
		}else{
			(*newlist).push_back(temp);
			plist = pnlist;
			plist++;
			(*m_hashList[i]).erase(pnlist);
			pnlist = plist;
		}
	}
	
	if((val & m_zeroAnd) == val){
		if((*m_hashList[i]).size() >= m_size)
		  m_size *= 2;
		(*m_hashList[i]).push_back(val);
	}else{
		if((*newlist).size() >= m_size)
		  m_size *= 2;
		(*newlist).push_back(val);		
	}

	p = m_hashList[j];
	cout<<p<<endl;
	cout<<"before push back"<<endl;
	if(p == NULL){
		cout<<"push back"<<endl;
		int sourceSize = m_hashList.size();
		for(int k = 0; k < sourceSize; k++){
			if(k != i){
				list<T> * oldlist = m_hashList[k];
				m_hashList.push_back(oldlist);
				m_or.push_back(m_or[k]);
			}else{
				m_hashList.push_back(newlist);
				m_or[i] = m_or[i] << 1;
				m_or.push_back(m_or[i]);
				m_or[m_hashList.size()-1] = m_or[i];
				cout<<"m_hashList.size():"<<m_hashList.size()<<endl;
			}
		}
	}else{
		cout<<"j:"<<j<<endl;
		if(j > i)
			m_hashList[j] = newlist;
		else
			m_hashList[i] = newlist;
		m_or[source_i] = m_or[source_i] << 1;
		m_or[j] = m_or[j] << 1;
	}
}



template<typename T>
bool  DynicHash<T>::findVal(T val,int &i,int &j)
{
	i = (val % m_hashList.size())/* & m_serchAnd*/;	
	if(i >= m_hashList.size() || i == -1){
		return false;
	}
	typename list<T>::iterator plist;
	j = 0;
	for(plist = (*m_hashList[i]).begin(); plist != (*m_hashList[i]).end() ;plist++){
		if(*plist == val){
			cout<<"vector:"<<i<<"	list jth:"<<j<<endl;
			return true;
		}
		j++;
	}
	return false;
}


template<typename T>
bool  DynicHash<T>::deleteVal(T val)
{
	int i=-1,j=0;
	bool ok = true;
	if(findVal(val,i,j)){
		list<T> * resource = m_hashList[i];
		list<T> * destination;
		(*m_hashList[i]).remove(val);
		if((*m_hashList[i]).size() == 0){
			int temp = i % m_initSize;
			unsigned int sourceSize = m_hashList.size();
			unsigned int half = m_hashList.size()/2;
			//short halfFlag = 0;			//0 
			/*for(int k = temp + m_hashList.size() - m_initSize;k >= 0; k-=4){*/
				//if(m_hashList[k] != m_hashList[i]){
					//if(k != i){
						//destination = m_hashList[k];
						//ok = true;
						//if(i < half){
							//if(destination == m_hashList[i + half]){
								//m_or[i] = m_or[i] >> 1;
								//cout<<"m_or:"<<m_or[i]<<endl;
							//}
						//}else{
							//if(destination == m_hashList[i - half]){
								//m_or[i] = m_or[i] >> 1;
								//cout<<"m_or:"<<m_or[i]<<endl;
							//}
						//}
					//}
				//}else{
					//continue;
				//}
			/*}*/
			unsigned int k = i,g = i;
			if(k > half - 1){
				k -= half;
			}
			if(g <= half - 1){
				g += half;
			}
			if(i / half  % 2 == 1){
				if(m_hashList[i] == m_hashList[k]){
					ok = false;
					/*if (i < half - 1)*/
					//m_hashList[i] = m_hashList[i + half];
					//else
					/*m_hashList[i] = m_hashList[i - half];*/
				}else{
					m_hashList[i] = m_hashList[k];
					m_or[k] = m_or[i] = m_or[i] >> 1;
				}
			}else{
				if(m_hashList[i] == m_hashList[g]){
					ok = false;
					/*if (i < half - 1)*/
					//m_hashList[i] = m_hashList[i + half];
					//else
					/*m_hashList[i] = m_hashList[i - half];	*/				
				}else{
					m_hashList[i] = m_hashList[g];
					m_or[g] = m_or[i] = m_or[i] >> 1;
				}
			}

			if(ok){
				delete resource;
			}
		}
		return true;	
	}else{
		cout<<"These is no val equal to "<<val<<" in hash table!"<<endl;
		return false;
	}
}

template<typename T>
void DynicHash<T>::output()
{
	cout<<"hashsize:"<<m_hashList.size()<<endl;
	int size = m_hashList.size();
	typename list<T>::iterator pnlist;
	for(int i = 0 ; i < size ; i++){
		cout<<i<<": ";
		for(pnlist = (*m_hashList[i]).begin(); pnlist != (*m_hashList[i]).end(); pnlist++){
			cout<<*pnlist<<"	";
		}
		cout<<endl;
	}
	
}
