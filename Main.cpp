#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;
int main()
{
	cout << "Hello world!\n";
	string y = "-1524364323427655";
	BigInt x = y;
	cout << x * x << endl;

	return 0;
}