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
	void	expendHashTable(T val,int i);		//i is which bucket should to be divided
	void	fineTune(T val,int i,list<T> ** newlist);
private:
	vector<list<T> *> 	m_hashList;
	int					m_size;			//default set is 4
	int					m_or;			//for new bucket we use it to distinguish new bit which belones to 1
	int					m_zeroAnd;		//for new bucket we use it to distinguish new bit which belones to 0
	const int			m_initSize;
};

#endif
