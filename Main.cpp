#include <iostream>
#include "BigInt.h"
using namespace std;
int main()
{
	cout << "Hello world!\n";
	long long y = 1000;
	BigInt x(y);
	cout << x.getBigInt()[0] << endl;
	return 0;
}