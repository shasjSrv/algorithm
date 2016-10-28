#ifndef __DYNAMICHASH_H_
#define __DYNAMICHASH_H_
#include <list>
#include <vector>

using namespace std;

template<typename T>
class DynicHash
{
public:
	DynicHash();
	~DynicHash();
	void	calculateHash(T val);
	void	expendHashTable(T val,int i);		//i is oneth bucket which should to be divided
	void	fineTune(T val,int i,int j,list<T> * newlist);
	bool	findVal(T val,int &i,int &j);		//i and j is the pos of val in the hashtable
	bool	deleteVal(T val);					//delete the val in the hashtable
	void	output();
private:
	vector<list<T> *> 	m_hashList;
	int					m_size;			//default set is 4
	vector<int>			m_or;			//for new bucket we use it to distinguish new bit which belones to 1
	int					m_zeroAnd;		//for new bucket we use it to distinguish new bit which belones to 0
	const int			m_initSize;
	/*int					m_serchAnd;		//to & with val for hash serch;*/
	/*vector<int>			m_serchOr;      //to left shift find the appropriate value for m_serchAnd*/
};

#endif
