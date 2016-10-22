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
	m_or = 0x0004;
	m_zeroAnd = ~m_or;
	for(int i = 0; i < m_initSize; i++ ){
		list<T> * bucket = new(list<T>);
		m_hashList.push_back(bucket);	
	}
}

template<typename T>
DynicHash<T>::~DynicHash()
{
	for(int i = m_hashList.size() - 1; i > 0; i--){
		list<T> * bucket = m_hashList[i]; 
		delete bucket;
		m_hashList.pop_back();
	}
}

template<typename T>
void DynicHash<T>::calculateHash(T val)
{
	for(int i = m_hashList.size() - 1; i > 0 ; i--){
		if((val & i) == val){
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
	int sourceSize = m_hashList.size();
	for(int j = 0; j < sourceSize ; j++){
		if(j != i){
			list<T> * newlist = m_hashList[j];
			m_hashList.push_back(newlist);
		}else{
			list<T> * newlist = new(list<T>);
			if(newlist == NULL){
				cout<<"new error,can't insert:"<<val<<endl;
				return;
			}
			fineTune(val,j + sourceSize,newlist);
		}
	}	

}

template<typename T>
void DynicHash<T>::fineTune(T val,int i,list<T> ** newlist)
{
	typename list<T>::iterator pnlist;
	for(pnlist = (*m_hashList[i]).begin(); pnlist != (*m_hashList[i]).end() ; pnlist++){
		T temp = *pnlist;
		if ((temp & m_zeroAnd) == temp ){
			continue;
		}else{
			(**newlist).push_back(temp);
			(*m_hashList[i]).erase(pnlist);
		}
	}
	if((val & m_zeroAnd) = val){
		if((*m_hashList[i]).size() >= m_size)
		  m_size *= 2;
		(*m_hashList[i]).push_back(val);
	}else{
		if((**newlist).size() >= m_size)
		  m_size *= 2;
		(**newlist).push_back(val);		
	}
	m_or << 1;
	m_zeroAnd = ~m_or;
	if((*m_hashList[i]) == NULL){
		m_hashList.pop_back(*newlist);
	}else{
		m_hashList[i] = *newlist;
	}
}
