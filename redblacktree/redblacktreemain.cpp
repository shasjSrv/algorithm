#include "redblacktree.cpp"  
#include <iostream> 
#include <fstream>
#include <vector>
using namespace std;  
void readDataset(vector<int> &v,int num)
{
	cout<<"num:"<<num<<endl;
	v.clear();
	ifstream fi("redBlacktestDataset.txt");
	if(fi == NULL)
		return;
	int n = 0,temp,record;
	bool ok = true;
	while(!fi.eof()){
		if(num > 0){
			num--;
			fi >> temp;
			continue;
		}
		if(ok){
			fi >> record;
			cout<<"record:"<<record<<endl;
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
	readDataset(v,0);
	RBTree<int> obj;
	time_t start,stop;
    start = time(NULL);
	cout<<"time:"<<start<<endl;
	for(int i = 0; i < v.size(); i++)
		obj.InsertUnique(v[i]); 
    stop = time(NULL);	
	cout<<"time:"<<stop<<endl;
	cout<<"time:"<<stop - start <<endl;
	obj.output();
	obj.erase(17);
	obj.output();
    obj.erase(1);  
	obj.output();
    obj.erase(76);  
	obj.output();
    obj.erase(9);  
	obj.output();
	cout<<"-------------------------------"<<endl;
	int num = v.size() + 1;
	readDataset(v,num);
	RBTree<int> tree;
	for(int i = 0; i < v.size(); i++)
		tree.InsertUnique(v[i]);
	cout<<"v.size()"<<v.size()<<endl;
	tree.output();
	cout<<"-------------------------------"<<endl;
	num += v.size() + 1;
	readDataset(v,num);
	RBTree<int> bigtree;
	start = time(NULL);
	cout<<"time:"<<start<<endl;
	for(int i = 0; i < v.size(); i++)
		bigtree.InsertUnique(v[i]);
    stop = time(NULL);	
	cout<<"time:"<<stop<<endl;
	cout<<"time:"<<stop - start <<endl;
	cout<<"v.size()"<<v.size()<<endl;
	bigtree.output();
    return 0;  
}  

