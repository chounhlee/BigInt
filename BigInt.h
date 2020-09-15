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

// Beginning of Static Helper functions
typedef vector<long long> vll; // vector long long

//Converts number into different base.
static vector<int> convert_base(const vector<int>& a, int old_digits, int new_digits) {
	vll p((long long)__max(old_digits, new_digits) + 1); // size of p = larger of the two base
	p[0] = 1; // first digit
	for (long long i = 1; i < (long long)p.size(); i++)
	{
		p[i] = p[i - 1] * 10; //each element is vector is multiple of 10, represents base.
	}
	vector<int> res;
	long long cur = 0;
	int cur_digits = 0;
	for (int i = 0; i < (int)a.size(); i++) {
		cur += a[i] * p[cur_digits]; //takes first few digits into the count, p[cur_digit] covers current nth digit
		cur_digits += old_digits; //adding base digit of original number (or remainer) 
		while (cur_digits >= new_digits) { //keeps loop while cur_digit is greater than new_digit
			res.push_back(int(cur % p[new_digits])); //add new digit to vector res, with new base (remainder first as they are smaller number)
			cur /= p[new_digits]; //divide by new base 
			cur_digits -= new_digits; //subtract new digit from cur_digit to keep track
		}
	}
	res.push_back((int)cur); //add to vector
	while (!res.empty() && !res.back()) //loop stops when last element is not zero or vector is empty
	{
		res.pop_back();
	}
	return res;
}

// Karatsuba multiplcation algorithm, for efficient multiplication
static vll karatsubaMultiply(const vll& a, const vll& b) {
	long long n = a.size();
	vll res(n + n);
	if (n <= 32) {
		for (long long i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				res[i + j] += a[i] * b[j];
		return res;
	}

	int k = n >> 1;
	vll a1(a.begin(), a.begin() + k);
	vll a2(a.begin() + k, a.end());
	vll b1(b.begin(), b.begin() + k);
	vll b2(b.begin() + k, b.end());

	vll a1b1 = karatsubaMultiply(a1, b1);
	vll a2b2 = karatsubaMultiply(a2, b2);

	for (int i = 0; i < k; i++)
		a2[i] += a1[i];
	for (int i = 0; i < k; i++)
		b2[i] += b1[i];

	vll r = karatsubaMultiply(a2, b2);
	for (int i = 0; i < (int)a1b1.size(); i++)
		r[i] -= a1b1[i];
	for (int i = 0; i < (int)a2b2.size(); i++)
		r[i] -= a2b2[i];

	for (long long i = 0; i < (int)r.size(); i++)
		res[i + k] += r[i];
	for (int i = 0; i < (int)a1b1.size(); i++)
		res[i] += a1b1[i];
	for (int i = 0; i < (int)a2b2.size(); i++)
		res[i + n] += a2b2[i];
	return res;
}
// End of Static Helper functions

class BigInt
{
	public:
		//start of Constructors 
		BigInt(); 
		BigInt(long long v);
		BigInt(const string& s);
		//end of Constructors
		//***********************************************************************
		//Start of  Helper member functions
		void trim();
		bool isZero() const;
		void read(const string& s);
		long long longValue() const;
		friend pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1);
		//End of Helper meber functions
		//***********************************************************************
		//Start of mathmatical functions
		BigInt abs() const;
		//End of mathmatical functions
		//***********************************************************************
		//Start of Overloaded Operators 
		void operator=(const BigInt& v);
		void operator=(long long v);
		BigInt operator+(const BigInt& v) const;
		BigInt operator-(const BigInt& v) const;
		BigInt operator-() const;
		void operator*=(int v);
		BigInt operator*(int v) const;
		void operator/=(int v);
		BigInt operator/(int v) const;
		int operator%(int v) const;
		BigInt operator/(const BigInt& v) const;
		BigInt operator%(const BigInt& v) const;
		friend istream& operator>>(istream& stream, BigInt& v);
		friend ostream& operator<<(ostream& stream, const BigInt& v);
		BigInt operator*(const BigInt& v) const;
		void operator+=(const BigInt& v);
		void operator-=(const BigInt& v);
		void operator*=(const BigInt& v);
		void operator/=(const BigInt& v);
		bool operator<(const BigInt& v) const;
		bool operator>(const BigInt& v) const;
		bool operator<=(const BigInt& v) const;
		bool operator>=(const BigInt& v) const;
		bool operator==(const BigInt& v) const;
		bool operator!=(const BigInt& v) const;
		//End of overloaded operators
	private:
		vector<int> bigInt;
		int sign;
};

// Start of Constructors Definitions
BigInt::BigInt() {
	sign = 1;	
}
BigInt::BigInt(long long v) {
	*this = v;
}
BigInt::BigInt(const string& s) {
	read(s);
}
// End of Constructors Definitions

// Beginning of Helper member function
void BigInt::trim() {
	while (!bigInt.empty() && !bigInt.back())
		bigInt.pop_back();
	if (bigInt.empty())
		sign = 1;
}

bool BigInt::isZero() const {
	return bigInt.empty() || (bigInt.size() == 1 && !bigInt[0]);
}

void BigInt::read(const string& s) {
	sign = 1;
	bigInt.clear();
	int pos = 0;
	while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
		if (s[pos] == '-')
			sign = -sign;
		++pos;
	}
	for (int i = s.size() - 1; i >= pos; i -= base_digits) {
		int x = 0;
		for (int j = __max(pos, i - base_digits + 1); j <= i; j++)
			x = x * 10 + s[j] - '0';
		bigInt.push_back(x);
	}
	trim();
}

long long BigInt::longValue() const {
	long long res = 0;
	for (int i = bigInt.size() - 1; i >= 0; i--)
		res = res * base + bigInt[i];
	return res * sign;
}

pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1) {
	int norm = base / (b1.bigInt.back() + 1);
	BigInt a = a1.abs() * norm;
	BigInt b = b1.abs() * norm;
	BigInt q, r;
	q.bigInt.resize(a.bigInt.size());

	for (int i = a.bigInt.size() - 1; i >= 0; i--) {
		r *= base;
		r += a.bigInt[i];
		int s1 = r.bigInt.size() <= b.bigInt.size() ? 0 : r.bigInt[b.bigInt.size()];
		int s2 = r.bigInt.size() <= b.bigInt.size() - 1 ? 0 : r.bigInt[b.bigInt.size() - 1];
		int d = ((long long)base * s1 + s2) / b.bigInt.back();
		r -= b * d;
		while (r < 0)
			r += b, --d;
		q.bigInt[i] = d;
	}

	q.sign = a1.sign * b1.sign;
	r.sign = a1.sign;
	q.trim();
	r.trim();
	return make_pair(q, r / norm);
}

// End of Helper member function

BigInt BigInt::abs() const {
	BigInt res = *this;
	res.sign *= res.sign;
	return res;
}

// Start of the overloaded operators

BigInt BigInt::operator-() const {
	BigInt res = *this;
	res.sign = -sign;
	return res;
}

BigInt BigInt::operator-(const BigInt& v) const {
	if (sign == v.sign) {
		if (abs() >= v.abs()) {
			BigInt res = *this;
			for (int i = 0, carry = 0; i < (int)v.bigInt.size() || carry; ++i) {
				res.bigInt[i] -= carry + (i < (int)v.bigInt.size() ? v.bigInt[i] : 0);
				carry = res.bigInt[i] < 0;
				if (carry)
					res.bigInt[i] += base;
			}
			res.trim();
			return res;
		}
		return -(v - *this);
	}
	return *this + (-v);
}
BigInt BigInt::operator+(const BigInt& v) const {
	if (sign == v.sign) {
		BigInt res = v;

		for (int i = 0, carry = 0; i < (int)__max(bigInt.size(), v.bigInt.size()) || carry; ++i) {
			if (i == (int)res.bigInt.size())
				res.bigInt.push_back(0);
			res.bigInt[i] += carry + (i < (int)bigInt.size() ? bigInt[i] : 0);
			carry = res.bigInt[i] >= base;
			if (carry)
				res.bigInt[i] -= base;
		}
		return res;
	}
	return *this - (-v);
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
	//for loop pushes each base into the vector. 
	for (; v > 0; v = v / base) 
		bigInt.push_back(v % base);
}


void BigInt::operator*=(int v) {
	if (v < 0)
		sign = -sign, v = -v;
	for (int i = 0, carry = 0; i < (int)bigInt.size() || carry; ++i) {
		if (i == (int)bigInt.size())
			bigInt.push_back(0);
		long long cur = bigInt[i] * (long long)v + carry;
		carry = (int)(cur / base);
		bigInt[i] = (int)(cur % base);
		//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
	}
	trim();
}

BigInt BigInt::operator*(int v) const {
	BigInt res = *this;
	res *= v;
	return res;
}

void BigInt::operator/=(int v) {
	if (v < 0)
		sign = -sign, v = -v;
	for (int i = (int)bigInt.size() - 1, rem = 0; i >= 0; --i) {
		long long cur = bigInt[i] + rem * (long long)base;
		bigInt[i] = (int)(cur / v);
		rem = (int)(cur % v);
	}
	trim();
}


BigInt BigInt::operator/(int v) const {
	BigInt res = *this;
	res /= v;
	return res;
}

int BigInt::operator%(int v) const {
	if (v < 0)
		v = -v;
	int m = 0;
	for (int i = bigInt.size() - 1; i >= 0; --i)
		m = (bigInt[i] + m * (long long)base) % v;
	return m * sign;
}

BigInt BigInt::operator*(const BigInt& v) const {
	vector<int> a6 = convert_base(this->bigInt, base_digits, 6); //Converts to base 6
	vector<int> b6 = convert_base(v.bigInt, base_digits, 6);	// Converts to base 6
	vll a(a6.begin(), a6.end()); // create vector 
	vll b(b6.begin(), b6.end()); // create vector
	//*****************************************************************************
	//makes 2 vectors equal size
	while (a.size() < b.size())
		a.push_back(0);
	while (b.size() < a.size())
		b.push_back(0);
	while (a.size() & (a.size() - 1)) // increase the vector size until a.size is power of 2
		a.push_back(0), b.push_back(0);
	//*****************************************************************************
	vll c = karatsubaMultiply(a, b);
	BigInt res;
	res.sign = sign * v.sign;
	for (int i = 0, carry = 0; i < (int)c.size(); i++) {
		long long cur = c[i] + carry;
		res.bigInt.push_back((int)(cur % 1000000));
		carry = (int)(cur / 1000000);
	}
	res.bigInt = convert_base(res.bigInt, 6, base_digits);
	res.trim();
	return res;
}

void BigInt::operator+=(const BigInt& v) {
	*this = *this + v;
}
void BigInt::operator-=(const BigInt& v) {
	*this = *this - v;
}
void BigInt::operator*=(const BigInt& v) {
	*this = *this * v;
}

void BigInt::operator/=(const BigInt& v) {
	*this = *this / v;
}

BigInt BigInt::operator/(const BigInt& v) const {
	return divmod(*this, v).first;
}

BigInt BigInt::operator%(const BigInt& v) const {
	return divmod(*this, v).second;
}

istream& operator>>(istream& stream, BigInt& v) {
	string s;
	stream >> s;
	v.read(s);
	return stream;
}

ostream& operator<<(ostream& stream, const BigInt& v) {
	if (v.sign == -1)
		stream << '-';
	stream << (v.bigInt.empty() ? 0 : v.bigInt.back());
	for (int i = (int)v.bigInt.size() - 2; i >= 0; --i)
		stream << setw(base_digits) << setfill('0') << v.bigInt[i];
	return stream;
}

bool BigInt::operator<(const BigInt& v) const {
	if (sign != v.sign)
		return sign < v.sign;
	if (bigInt.size() != v.bigInt.size())
		return bigInt.size() * sign < v.bigInt.size()* v.sign;
	for (int i = bigInt.size() - 1; i >= 0; i--)
		if (bigInt[i] != v.bigInt[i])
			return bigInt[i] * sign < v.bigInt[i] * sign;
	return false;
}

bool BigInt::operator>(const BigInt& v) const {
	return v < *this;
}
bool BigInt::operator<=(const BigInt& v) const {
	return !(v < *this);
}
bool BigInt::operator>=(const BigInt& v) const {
	return !(*this < v);
}
bool BigInt::operator==(const BigInt& v) const {
	return !(*this < v) && !(v < *this);
}
bool BigInt::operator!=(const BigInt& v) const {
	return *this < v || v < *this;
}

// end of the overloaded operators

// Beginning of hash code (my code)
class BigIntHash {
public:
	size_t operator()(const BigInt& v) const {
		string s = "";
		stringstream ss;
		ss << v;
		ss >> s;
		return hash<string>()(s);
	}
};
// End of hash code 