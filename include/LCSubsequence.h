#ifndef	__BSTREE_H_
#define __BSTREE_H_
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;



class LCSubsequence
{
public:
	LCSubsequence(){}
	LCSubsequence(string p,string q);
	~LCSubsequence(){}
	void			Lcs_Length();
	void			output();
private:
	vector<char>							m_mainstr;
	vector<char>							m_substr;
	vector<vector<unsigned int> >			m_c;
	vector<vector<unsigned int> >			m_b;				//1 left up, 2 up ,3 left
	
};


#endif
