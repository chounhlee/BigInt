#include <iostream>
#include <string>
#include <unordered_map> 
#include "BigInt.h"
using namespace std;
int main()
{
	cout << "Hello world!\n";
	string x = "4";
	string y = "8";
	string z = "16";
	string mod = "200";
	BigInt a = x;
	BigInt b = y;
	BigInt c = z;
	BigInt m = mod;
	
	unordered_map<string, BigInt> umap;

	umap["one"] = x;
	umap["two"] = y;
	umap["three"] = z;

	cout << "Example of hashmap" << endl;
	for (auto i : umap)
		cout << i.first << " " << i.second << endl;
	cout << endl;
	cout << "Example of sqrtIsInt function" << endl;
	for (auto i : umap)
	{
		if (i.second.sqrtIsInt())
		{
			cout << i.second << " is a Perfect Square" << endl;
		}
		else
		{
			cout << i.second << " is Not a Perfect Square" << endl;
		}
	}
	cout << endl;
	cout << "Example of sqrt function (non-perfect square is rounded)" << endl;
	for (auto i : umap)
	{
		cout << "sqrt(" << i.second << ") = " << i.second.sqrt() << endl;
	}
	cout << endl;
	cout << "Example of logIsInt function" << endl;
	for (auto i : umap)
	{
		if (i.second.logIsInt(4))
		{
			cout << "Log4(" << i.second << ") result is an integer" << endl;
		}
		else
		{
			cout << "Log4(" << i.second << ") result is not an integer" << endl;
		}
	}
	cout << endl;
	cout << "Example of log function (non integer result is rounded)" << endl;
	for (auto i : umap)
	{
		cout << "Log4(" << i.second << ") = " << i.second.log(4) << endl;
	}
	cout << endl;
	cout << "Example of pow function" << endl;
	for (auto i : umap)
	{
		cout << "Pow(" << i.second << ") = " << i.second.pow(4) << endl;
	}
	cout << endl;
	cout << "Example of pow function with mod parameter" << endl;
	for (auto i : umap)
	{
		cout << "Pow(" << i.second << ") mod 200 = " << i.second.pow(4, m) << endl;
	}
	cout << endl;
	cout << "Example of how big BigInt class can be" << endl;
	a = BigInt("19");
	cout << "The board game 'Go' has " << a.pow(19) << " possible outcome." << endl;

	return 0;
}