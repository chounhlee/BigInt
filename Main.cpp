#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;
int main()
{
	cout << "Hello world!\n";
	string y = "2";
	string x = "8";
	string z = "5070602400912917605986812821504";
	string mod = "13413519481471788";
	BigInt a = z;
	BigInt b = y;
	BigInt c = x;
	cout << a.pow(b) << endl;
	cout << a.log(b) << endl;
	cout << a.logIsInt(b) << endl;
	cout << a.logIsInt(c) << endl;
	return 0;
}