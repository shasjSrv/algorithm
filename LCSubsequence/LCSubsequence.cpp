#include <LCSubsequence.h>
#include <iostream>

using namespace std;

LCSubsequence::LCSubsequence(string p,string q)
{
	const char * mainstr = p.c_str();
	const char * suvstr = q.c_str();
	m_mainstr.push_back('\0');
	m_substr.push_back('\0');
	for(unsigned int i = 0; i < p.length(); i++){
		m_mainstr.push_back(p[i]);		
	}	
	for(unsigned int i = 0; i < q.length(); i++){
		m_substr.push_back(q[i]);
	}
	for(unsigned int i = 0 ; i < p.length() + 1;i++){
		m_c.push_back(vector<unsigned int>(q.length() + 1));
		m_b.push_back(vector<unsigned int>(q.length() + 1));
	}
}


void LCSubsequence::Lcs_Length()
{
	unsigned int i = 0;
	unsigned int j = 0;
	for(i = 0; i < m_mainstr.size(); i++){
		m_c[i][0] = 0;
	}
	for(i = 0; i < m_substr.size(); i++){
		m_c[0][i] = 0;
	}
	for(i = 1; i < m_mainstr.size(); i++){
		for(j = 1; j< m_substr.size(); j++){
			cout<< "m_mainstr:" << m_mainstr[i] << "  m_substr:" << m_substr[j] <<"   " << i << "     " << j << " ";
			cout << "      before:" << m_c[i][j] << "    after:";
			if(m_mainstr[i] == m_substr[j]){
				m_c[i][j] = m_c[i - 1][j - 1] + 1;
				m_b[i][j] = 1;
			}else if( m_c[i - 1][j] >= m_c[i][j - 1] ){
				m_c[i][j] = m_c[i - 1][j];
				m_b[i][j] = 2;
			}else{
				m_c[i][j] = m_c[i][j - 1];
				m_b[i][j] = 3;
			}
			cout << m_c[i][j] << endl;
			
		}
	}
}


void LCSubsequence::output()
{
	for(int i = 0; i < m_c.size(); i++){
		for(int j = 0; j < m_c[i].size(); j++){
			cout << " " << m_c[i][j];
		}
		cout<< endl;
	}
	
	vector<char> str;
	for(unsigned int i = m_c.size() - 1,j = m_c[i].size() - 1;;){
		cout<< "i:" << i << "j:" << j;
		if(i == 0 || j == 0)
		  break;
		if(m_b[i][j] == 3){
			j--;
			cout<< "left" <<endl;
		}else if(m_b[i][j] == 2){
			i--;
			cout<< "up"<< endl;
		}else{
			cout<< m_substr[j] << endl;
			str.push_back(m_substr[j]);
			i--;
			j--;
		}
	
	}
	cout << endl;
	int size = str.size();
	for(int i = size -1; i >= 0; i--){
		cout << str[i] << "  ";
	}
	cout << endl;

}
