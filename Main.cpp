#include <iostream>
#include <string>
#include <unordered_map> 
#include "BigInt.h"
using namespace std;
int main()
{
	cout << "Hello world!\n";
	string x = "12345678987654321";
	string y = "-1524364323427655";
	string z = "10101010101010101010101010101010101010101";
	BigInt a = x;
	BigInt b = y;
	BigInt c = z;
	
	unordered_map<string, BigInt> umap;

	umap["one"] = x;
	umap["two"] = y;
	umap["three"] = z;

	for (auto i : umap)
		cout << i.first << " " << i.second << endl;

	cout << umap["one"] << endl;
	cout << umap["two"] << endl;
	cout << umap["three"] << endl;

	return 0;
}