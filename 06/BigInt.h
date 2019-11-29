#include <iostream>
#include <string>

class BigInt
{
	unsigned char* digit;
	char sign;
	size_t size;
	size_t len; // max length digit
public:
	//constructors
	BigInt();
	BigInt(const BigInt& copied);
	BigInt(const long long& copied);
	BigInt(BigInt&& moved);
	BigInt(long long&& moved);
	// destructor
	~BigInt();
	// =
	BigInt& operator = (const BigInt& copied);
	BigInt& operator = (const long long& copied);
	BigInt& operator = (BigInt&& moved);
	BigInt& operator = (long long&& moved);
	// +
	BigInt operator+(const BigInt& num) const;
	BigInt operator+(const long long& num) const;
	// -
	BigInt operator-(const BigInt& num) const;
	BigInt operator-(const long long& num) const;
	BigInt operator-() const;
	// <<
	friend std::ostream& operator<<(std::ostream& out, const BigInt& num);
	// == != < > <= >=
	bool operator==(const BigInt& num) const;
	bool operator==(const long long& num) const;
	bool operator!=(const BigInt& num) const;
	bool operator!=(const long long& num) const;
	bool operator<(const BigInt& num) const;
	bool operator<(const long long& num) const;
	bool operator>(const BigInt& num) const;
	bool operator>(const long long& num) const;
	bool operator<=(const BigInt& num) const;
	bool operator<=(const long long& num) const;
	bool operator>=(const BigInt& num) const;
	bool operator>=(const long long& num) const;

private:

};