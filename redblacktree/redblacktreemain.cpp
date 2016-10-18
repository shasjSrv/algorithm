#include "redblacktree.cpp"  
#include <iostream> 
#include <fstream>
#include <vector>
using namespace std;  
  
void readDataset(vector<int> &v)
{
	ifstream fi("redBlacktestDataset.txt");
	if(fi == NULL)
		return;
	int n = 0,temp,record;
	bool ok = true;
	while(!fi.eof()){
		if(ok){
			fi >> record;
			ok = false;
		}
		fi >> temp;
		v.push_back(temp);
		if(n == record - 1)
			break;
		n++;
	}
}


int main()  
{  
	vector<int> v;
	readDataset(v);
	RBTree<int> obj;
	for(int i = 0; i < v.size(); i++)
		obj.InsertUnique(v[i]);
	   /* cout<<v[i]<<endl;*/
	//cout<<"v.size():"<<v.size()<<endl;
    /*obj.InsertUnique(30);  */
/*    obj.InsertUnique(40);  */
    //obj.InsertUnique(50);  
    //obj.InsertUnique(20);  
    //obj.InsertUnique(35);  
    //obj.InsertUnique(10);  
    //obj.InsertUnique(11);  
	/*obj.InsertUnique(22);*/
    //obj.print();  
	obj.output();
	obj.erase(17);
	obj.output();
    //obj.print();  
    return 0;  
}  
