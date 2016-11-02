#include "LCSubsequence.h"
#include <iostream>
#include <string>

using namespace std;



int main()
{
	string mainstr = "ABCBDAB";
	string substr = "BDCABA";
	LCSubsequence lcs(mainstr,substr);
	lcs.Lcs_Length();
	lcs.output();
}
