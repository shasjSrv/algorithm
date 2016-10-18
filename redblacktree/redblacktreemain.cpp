#include "redblacktree.cpp"  
#include <iostream>  
using namespace std;  
  
int main()  
{  
    RBTree<int> obj;  
    obj.InsertUnique(30);  
    obj.InsertUnique(40);  
    obj.InsertUnique(50);  
    obj.InsertUnique(20);  
    obj.InsertUnique(35);  
    obj.InsertUnique(10);  
    obj.InsertUnique(11);  
	obj.InsertUnique(22);
    obj.print();  
	obj.erase(30);
    obj.print();  
    return 0;  
}  
