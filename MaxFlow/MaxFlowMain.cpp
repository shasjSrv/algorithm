#include "MaxFlow.h"


int main()
{
	vector<int> R;
	R.push_back(3);
	R.push_back(2);
	R.push_back(4);
 	MaxFlow plan(R,10,1,6,2,3);
	plan.MCF();
	return 0;
}
