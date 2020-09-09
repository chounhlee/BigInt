/*
* This is based on bigint code I found in some forum a while ago. 
* I cannot find the original source, but original code was done in
* struct. This is an attempt for me to reverse engineer that code 
* to learn, + add some features for myself in case I need to use
* bigint in the future.
*/

#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

//base and base_digit constant
const int base = 1000000000;	//Likely base limit due to int size being 2147483648
const int base_digits = 9;		//base of 10, so digit goes 0-9

class BigInt
{
	public:
		BigInt();
		BigInt(long long v);
		void operator=(long long v);
		void operator=(const BigInt& v);
		int getSign();
		vector<int> getBigInt();
	private:
		vector<int> bigInt;
		int sign;
};

BigInt::BigInt() {
	sign = 1;	
}
BigInt::BigInt(long long v) {
	*this = v;
}

void BigInt::operator=(const BigInt& v) {	//standard assignment here
	sign = v.sign;
	bigInt = v.bigInt;
}
void BigInt::operator=(long long v) {		 
	sign = 1;
	//if parameter v is negative, sign becomes negative change v into positive to put it in the vector
	if (v < 0)
		sign = -1, v = -v;
	//for loop pushes each digit into the vector. 
	for (; v > 0; v = v / base)
		bigInt.push_back(v % base);
}

int BigInt::getSign()
{
	return sign;
}
vector<int> BigInt::getBigInt()
{
	return bigInt;
}

