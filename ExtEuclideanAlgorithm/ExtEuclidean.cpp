#include <iostream>

using namespace std;

int ExtEculi(int a, int b ,int & x ,int &y)
{
	if(b == 0){
	  x = 1, y = 0;
	  return 0;
	}else
	{
		int r = ExtEculi(b,a%b,x,y);
		int t = x;
		x = y;
		y = t - a/b * y;
		cout<<"x:"<<x<<"	 y:"<<y<<endl;
		return r;
	}

}

int main()
{
	int x = 0,y = 0;
	int Max = ExtEculi(47,30,x,y);
	cout<<"max:"<<Max<<endl;
}
