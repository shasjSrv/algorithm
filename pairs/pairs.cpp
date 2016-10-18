#include <iostream>
#include <Vec.h>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int MinPairs(vector<vec3> v)
{
	int min = 999999;
	vector<vec3>::iterator i,j;
	for(i = v.begin();i != v.end();i++ )
	{
		for (j = i + 1; j != v.end(); j++)
			if (std::abs((*i).dot(*j)) < min)
				min = std::abs((*i).dot(*j));	
	}
	return min;
}



int main()
{
	vec3 A;
	vector<vec3> v;
	ifstream fi("data");
	if(fi == NULL)
		return 0;
	while(!fi.eof()){
		fi >> A.X[0] >> A.X[1] >> A.X[2];
		v.push_back(A);	
	}
	cout<<MinPairs(v)<<endl;

	return 0;
}
