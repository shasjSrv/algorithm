#include "dynamicHash.cpp"


using namespace std;


int main()
{
	DynicHash<int> example;
	example.calculateHash(4);
	example.calculateHash(12);
	example.calculateHash(32);
	example.calculateHash(16);
	example.calculateHash(1);
	example.calculateHash(5);
	example.calculateHash(21);
	example.calculateHash(10);
	example.calculateHash(15);
	example.calculateHash(7);
	//example.output();
	example.calculateHash(20);
	example.output();
	example.deleteVal(32);
	//example.output();
	example.deleteVal(16);
	example.output();
	example.calculateHash(32);
	example.calculateHash(16);
	example.output();
	example.calculateHash(9);
	example.calculateHash(13);
	example.output();
	example.calculateHash(0);
	example.calculateHash(8);
	example.calculateHash(36);
	example.calculateHash(28);
	example.output();
	example.deleteVal(12);
	example.deleteVal(28);
	example.output();
	example.calculateHash(12);
	example.calculateHash(28);
	example.output();
	

}
