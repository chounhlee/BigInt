#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;
int main()
{
	cout << "Hello world!\n";
	string x = "16";
	string y = "16";
	string z = "16";
	string mod = "18446744073709551616";
	BigInt a = x;
	BigInt b = y;
	BigInt c = mod;
	cout << a.pow(b) << endl;
	cout << c.sqrtIsInt() << endl;
	cout << c.sqrt() << endl;

	return 0;
}