#include "BigInt.h"

// constructors
BigInt::BigInt()
{
	unsigned char* digit = nullptr;
	len = 0;
	size = 0;
	sign = '+';
}

BigInt::BigInt(const BigInt& copied)
{
	digit = new unsigned char[copied.len];
	len = copied.len;
	size = copied.size;
	sign = copied.sign;
	std::copy(copied.digit, copied.digit + size, digit);
}

BigInt::BigInt(const long long& copied)
{
	size = 0;
	long long number = copied;
	if (number > 0)
		sign = '+';
	else
	{
		sign = '-';
		number *= -1;
	}
	long long num = number;
	while (num != 0)
	{
		size++;
		num /= 10;
	}
	digit = new unsigned char[size];
	len = size;
	for (size_t i=0; i< size; ++i)
	{
		digit[i] = number % 10;
		number /= 10;
	}
}

BigInt::BigInt(BigInt&& moved)
{
	digit = moved.digit;
	len = moved.len;
	size = moved.size;
	sign = moved.sign;
	moved.digit = nullptr;
	moved.len = 0;
	moved.size = 0;
}

BigInt::BigInt(long long&& moved)
{
	size = 0;
	long long number = moved;
	if (number > 0)
		sign = '+';
	else
	{
		sign = '-';
		number *= -1;
	}
	long long num = number;
	while (num != 0)
	{
		size++;
		num /= 10;
	}
	digit = new unsigned char[size];
	len = size;
	for (size_t i = 0; i < size; ++i)
	{
		digit[i] = (number % 10);
		number /= 10;
	}
	moved = 0;
}

//destroctor
BigInt::~BigInt()
{
	if(digit)
		delete[] digit;
}

// =
BigInt& BigInt::operator = (const BigInt& copied)
{
	if (this == &copied)
		return *this;

	unsigned char* tmp_digit = new unsigned char[copied.len];
	len = copied.len;
	if (digit)
		delete[] digit;
	digit = tmp_digit;
	size = copied.size;
	sign = copied.sign;
	std::copy(copied.digit, copied.digit + size, digit);
	return *this;
}

BigInt& BigInt::operator = (const long long& copied)
{
	size = 0;
	long long number = copied;
	if (number > 0)
		sign = '+';
	else
		sign = '-';
	while (number != 0)
	{
		size++;
		number /= 10;
	}
	unsigned char* tmp_digit = new unsigned char[size];
	len = size;
	number = copied;
	for (size_t i = 0; i < size; ++i)
	{
		tmp_digit[i] = number % 10;
		number /= 10;
	}

	if (digit)
		delete[] digit;
	digit = tmp_digit;

	return *this;
}

BigInt& BigInt::operator = (BigInt&& moved)
{
	if (this == &moved)
		return *this;

	if (digit)
		delete[] digit;
	digit = moved.digit;
	len = moved.len;
	size = moved.size;
	sign = moved.sign;
	moved.digit = nullptr;
	moved.len = 0;
	moved.size = 0;
	return *this;
}

BigInt& BigInt::operator = (long long&& moved)
{
	size = 0;
	long long number = moved;
	if (number > 0)
		sign = '+';
	else
		sign = '-';
	while (number != 0)
	{
		size++;
		number /= 10;
	}
	unsigned char* tmp_digit = new unsigned char[size];
	len = size;
	number = moved;
	for (size_t i = 0; i < size; ++i)
	{
		tmp_digit[i] = (number % 10);
		number /= 10;
	}

	if (digit)
		delete[] digit;
	digit = tmp_digit;
	moved = 0;

	return *this;
}

// +
BigInt BigInt::operator + (const BigInt& num) const
{
	if (sign == '+' && num.sign == '-')
	{
		BigInt right = num;
		right.sign = '+';
		return *this - right;
	}
	else if (this->sign == '-' && num.sign == '+')
	{
		BigInt right = num;
		right.sign = '-';
		return *this - right;
	}


	BigInt result;
	unsigned char* large;
	unsigned char* small;
	size_t large_size;
	size_t small_size;
	result.sign = sign; // т.к. оба знака одинаковы, то знак останится тем же
	if (size > num.size)
	{
		result.digit = new unsigned char[size+1];
		result.len = size + 1;
		large = digit;
		large_size = size;
		small = num.digit;
		small_size = num.size;
	}
	else
	{
		result.digit = new unsigned char[num.size+1];
		result.len = num.size + 1;
		large = num.digit;
		large_size = num.size;
		small = digit;
		small_size = size;
	}

	int rest = 0;
	for (size_t i = 0; i<small_size; i++)
	{
		int l = large[i];
		int s = small[i];
		result.digit[i] = (l + s + rest) % 10;
		result.size += 1;
		rest = (l + s + rest) / 10;
	}
	for (size_t i = small_size; i < large_size; i++)
	{
		int l = large[i];
		result.digit[i] = (l + rest) % 10;
		result.size += 1;
		rest = (l + rest) / 10;
	}
	if (rest != 0)
	{
		result.digit[result.len - 1] = (rest) % 10;
		result.size += 1;
	}

	if (result.size == 1 && result.digit[0] == 0)
		result.sign = '+';
	return result;
}

BigInt BigInt::operator + (const long long& number) const
{
	BigInt num = number;
	if (sign == '+' && num.sign == '-')
	{
		BigInt right = num;
		right.sign = '+';
		return *this - right;
	}
	else if (this->sign == '-' && num.sign == '+')
	{
		BigInt right = num;
		right.sign = '-';
		return *this - right;
	}


	BigInt result;
	unsigned char* large;
	unsigned char* small;
	size_t large_size;
	size_t small_size;
	result.sign = sign; // т.к. оба знака одинаковы, то знак останится тем же
	if (size > num.size)
	{
		result.digit = new unsigned char[size + 1];
		result.len = size + 1;
		large = digit;
		large_size = size;
		small = num.digit;
		small_size = num.size;
	}
	else
	{
		result.digit = new unsigned char[num.size + 1];
		result.len = num.size + 1;
		large = num.digit;
		large_size = num.size;
		small = digit;
		small_size = size;
	}

	int rest = 0;
	for (size_t i = 0; i < small_size; i++)
	{
		int l = large[i];
		int s = small[i];
		result.digit[i] = (l + s + rest) % 10;
		result.size += 1;
		rest = (l + s + rest) / 10;
	}
	for (size_t i = small_size; i < large_size; i++)
	{
		int l = large[i];
		result.digit[i] = (l + rest) % 10;
		result.size += 1;
		rest = (l + rest) / 10;
	}
	if (rest != 0)
	{
		result.digit[result.len - 1] = (rest) % 10;
		result.size += 1;
	}

	if (result.size == 1 && result.digit[0] == 0)
		result.sign = '+';
	return result;
}

// -
BigInt BigInt::operator - (const BigInt& num) const
{
	BigInt result;
	unsigned char* large;
	unsigned char* small;
	size_t large_size;
	size_t small_size;
	if (*this >= num)
	{
		if (sign == '+' && num.sign == '-')
		{
			BigInt right = num;
			right.sign = '+';
			return *this + right;
		}
		if (sign == '+')
		{
			result.digit = new unsigned char[size];
			result.len = size;
			large = digit;
			large_size = size;
			small = num.digit;
			small_size = num.size;
		}
		else
		{
			result.digit = new unsigned char[num.size];
			result.len = num.size;
			large = num.digit;
			large_size = num.size;
			small = digit;
			small_size = size;
		}
		result.sign = '+'; // знак большего числа
	}
	else
	{
		if (this->sign == '-' && num.sign == '+')
		{
			BigInt right = num;
			right.sign = '-';
			return *this + right;
		}
		if (sign == '+')
		{
			result.digit = new unsigned char[num.size];
			result.len = num.size;
			large = num.digit;
			large_size = num.size;
			small = digit;
			small_size = size;
		}
		else
		{
			result.digit = new unsigned char[size];
			result.len = size;
			large = digit;
			large_size = size;
			small = num.digit;
			small_size = num.size;
		}
		result.sign = '-'; // знак большего числа
	}

	int avance = 0;
	for (size_t i = 0; i < small_size; i++)
	{
		int l = large[i];
		int s = small[i];
		if (l < s + avance)
		{
			l = l + 10 - s - avance;
			avance = 1;
		}
		else
		{
			l = l - s - avance;
			avance = 0;
		}
		result.digit[i] = l;
		result.size += 1;
	}
	for (size_t i = small_size; i < large_size; i++)
	{
		int l = large[i];
		if (l < avance)
		{
			l = l + 10 - avance;
			avance = 1;
		}
		else
		{
			l = l - avance;
			avance = 0;
		}
		result.digit[i] = l;
		result.size += 1;
	}

	while (result.digit[result.size - 1] == 0 && result.size != 1)
		result.size--;

	if (result.size == 1 && result.digit[0] == 0)
		result.sign = '+';

	return result;
}

BigInt BigInt::operator - (const long long& number) const
{
	BigInt num = number;
	BigInt result;
	unsigned char* large;
	unsigned char* small;
	size_t large_size;
	size_t small_size;
	if (*this >= num)
	{
		if (sign == '+' && num.sign == '-')
		{
			BigInt right = num;
			right.sign = '+';
			return *this + right;
		}
		if (sign == '+')
		{
			result.digit = new unsigned char[size];
			result.len = size;
			large = digit;
			large_size = size;
			small = num.digit;
			small_size = num.size;
		}
		else
		{
			result.digit = new unsigned char[num.size];
			result.len = num.size;
			large = num.digit;
			large_size = num.size;
			small = digit;
			small_size = size;
		}
		result.sign = '+'; // знак большего числа
	}
	else
	{
		if (this->sign == '-' && num.sign == '+')
		{
			BigInt right = num;
			right.sign = '-';
			return *this + right;
		}
		if (sign == '+')
		{
			result.digit = new unsigned char[num.size];
			result.len = num.size;
			large = num.digit;
			large_size = num.size;
			small = digit;
			small_size = size;
		}
		else
		{
			result.digit = new unsigned char[size];
			result.len = size;
			large = digit;
			large_size = size;
			small = num.digit;
			small_size = num.size;
		}
		result.sign = '-'; // знак большего числа
	}

	int avance = 0;
	for (size_t i = 0; i < small_size; i++)
	{
		int l = large[i];
		int s = small[i];
		if (l < s + avance)
		{
			l = l + 10 - s - avance;
			avance = 1;
		}
		else
		{
			l = l - s - avance;
			avance = 0;
		}
		result.digit[i] = l;
		result.size += 1;
	}
	for (size_t i = small_size; i < large_size; i++)
	{
		int l = large[i];
		if (l < avance)
		{
			l = l + 10 - avance;
			avance = 1;
		}
		else
		{
			l = l - avance;
			avance = 0;
		}
		result.digit[i] = l;
		result.size += 1;
	}

	while (result.digit[result.size - 1] == 0 && result.size != 1)
		result.size--;

	if (result.size == 1 && result.digit[0] == 0)
		result.sign = '+';

	return result;
}

BigInt BigInt::operator-() const
{
	BigInt result(*this);
	if (result.size == 1 && result.digit[0] == 0)
		result.sign = '+';
	else
	{
		if (result.sign == '+')
			result.sign = '-';
		else
			result.sign = '+';
	}
	return result;
}

// <<
std::ostream& operator << (std::ostream& out, const BigInt& num)
{
	if (num.sign == '-')
		out << num.sign;
	for (size_t i=0 ; i<num.size;++i)
		out << (char)(num.digit[num.size - 1 - i]+0x30);
	return out;
}

// == != < > <= >=
bool BigInt::operator==(const BigInt& num) const 
{
	if ((sign != num.sign) || (size!=num.size))
		return false;
	for (size_t i = 0; i < size; ++i)
		if(digit[i]!=num.digit[i])
			return false;

	return true;
}

bool BigInt::operator==(const long long& number) const
{
	BigInt num = number;
	if ((sign != num.sign) || (size != num.size))
		return false;
	for (size_t i = 0; i < size; ++i)
		if (digit[i] != num.digit[i])
			return false;

	return true;
}

bool BigInt::operator!=(const BigInt& num) const
{
	return !(*this == num);
}

bool BigInt::operator!=(const long long& number) const
{
	BigInt num = number;
	return !(*this == num);
}

bool BigInt::operator<(const BigInt& num) const
{
	if (sign == num.sign)
	{
		if (sign == '+')
		{
			if (size == num.size)
			{
				for (size_t i = 0; i < size; ++i)
				{
					if (digit[size - 1 - i] < num.digit[size - 1 - i])
						return true;
					if (digit[size - 1 - i] > num.digit[size - 1 - i])
						return false;
				}
				return false;
			}
			else
				return size < num.size;
		}
		else
		{
			if (size == num.size)
			{
				for (size_t i = 0; i < size; ++i)
				{
					if (digit[size - 1 - i] > num.digit[size - 1 - i])
						return true;
					if (digit[size - 1 - i] < num.digit[size - 1 - i])
						return false;
				}
				return false;
			}
			else
				return size > num.size;
		}
	}
	else
		return sign == '-'; // т.к. знаки точно не равны
}

bool BigInt::operator<(const long long& number) const
{
	BigInt num = number;
	if (sign == num.sign)
	{
		if (sign == '+')
		{
			if (size == num.size)
			{
				for (size_t i = 0; i < size; ++i)
				{
					if (digit[size - 1 - i] < num.digit[size - 1 - i])
						return true;
					if (digit[size - 1 - i] > num.digit[size - 1 - i])
						return false;
				}
				return false;
			}
			else
				return size < num.size;
		}
		else
		{
			if (size == num.size)
			{
				for (size_t i = 0; i < size; ++i)
				{
					if (digit[size - 1 - i] > num.digit[size - 1 - i])
						return true;
					if (digit[size - 1 - i] < num.digit[size - 1 - i])
						return false;
				}
				return false;
			}
			else
				return size > num.size;
		}
	}
	else
		return sign == '-'; // т.к. знаки точно не равны
}

bool BigInt::operator>(const BigInt& num) const
{
	return !((*this < num) or (*this == num));
}

bool BigInt::operator>(const long long& number) const
{
	BigInt num = number;
	return !((*this < num) or (*this == num));
}

bool BigInt::operator<=(const BigInt& num) const
{
	return (*this < num) or (*this == num);
}

bool BigInt::operator<=(const long long& number) const
{
	BigInt num = number;
	return (*this < num) or (*this == num);
}

bool BigInt::operator>=(const BigInt& num) const
{
	return !(*this < num);
}

bool BigInt::operator>=(const long long& number) const
{
	BigInt num = number;
	return !(*this < num);
}

