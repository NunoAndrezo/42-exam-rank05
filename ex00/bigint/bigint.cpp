#include "bigint.hpp"

bigint::bigint(): value(0) {}

bigint::bigint(unsigned long long val) : value(val) {}

bigint::bigint(const bigint &other) : value(other.value) {}

bigint::~bigint() {}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
	{
		this->value = other.value;
	}
	return (*this);
}

unsigned long long bigint::getValue() const
{
	return (this->value);
}

bigint bigint::operator+(const bigint &other) const
{
	return (this->value + other.value);
}

bigint &bigint::operator+=(const bigint &other)
{
	this->value += other.value;
	return (*this);
}

bigint &bigint::operator++() // this is the pre-increment operator, it returns the value after incrementing
{
	this->value += 1;
	return (*this);
}

bigint bigint::operator++(int) // this is the post-increment operator, it returns the value before incrementing
{
	bigint temp(*this);
	++(*this); // but how does this increment the "value" variable of this? Answer: because this calls: bigint &bigint::operator++() and that operator increments the "value" variable of this.
	return (temp);
}

//shift with number
bigint bigint::operator<<(unsigned int shift) const // with 21 << 10, we want 210000000000!
{
	unsigned long long multiplier = 1;
	if (shift <= 0)
		return this->value;
	while (shift > 0)
	{
		multiplier = multiplier * 10;
		shift--;
	}
	return (this->value * multiplier);
}

bigint &bigint::operator<<=(unsigned int shift)
{
	unsigned long long	multiplier = 1;
	if (shift <= 0)
		return (*this);
	while (shift > 0)
	{
		multiplier = multiplier * 10;
		shift--;
	}
	this->value *= multiplier;
	return (*this);
}

bigint bigint::operator>>(unsigned int shift) const
{
	unsigned long long divisor = 1;
	if (this->value <= 0)
		return 0;
	while (shift > 0)
	{
		divisor = divisor * 10;
		shift--;
	}
	return (this->value / divisor);
}

bigint &bigint::operator>>=(unsigned int shift)
{
	unsigned long long divisor = 1;
	if (this->value <= 0)
		this->value = 0;
	while (shift > 0)
	{
		divisor = divisor * 10;
		shift--;
	}
	this->value /= divisor;
	return (*this);
}

//shift with object
bigint bigint::operator<<(const bigint &other) const
{
	unsigned long long multiplier = 1;
	unsigned long long shift = other.value;
	if (shift <= 0)
		return this->value;
	while (shift > 0)
	{
		multiplier = multiplier * 10;
		shift--;
	}
	return (this->value * multiplier);
}

bigint &bigint::operator<<=(const bigint &other)
{
	unsigned long long	multiplier = 1;
	unsigned long long shift = other.value;
	if (shift <= 0)
		return (*this);
	while (shift > 0)
	{
		multiplier = multiplier * 10;
		shift--;
	}
	this->value *= multiplier;
	return (*this);
}

bigint bigint::operator>>(const bigint &other) const
{
	unsigned long long divisor = 1;
	unsigned long long shift = other.value;
	if (this->value <= 0)
		return 0;
	while (shift > 0)
	{
		divisor = divisor * 10;
		shift--;
	}
	return (this->value / divisor);
}

bigint &bigint::operator>>=(const bigint &other)
{
	unsigned long long divisor = 1;
	unsigned long long shift = other.value;
	if (this->value <= 0)
		this->value = 0;
	while (shift > 0)
	{
		divisor = divisor * 10;
		shift--;
	}
	this->value /= divisor;
	return (*this);
}

bool bigint::operator<(const bigint &other) const
{
	return (this->value < other.value);
}

bool bigint::operator<=(const bigint &other) const
{
	return (this->value <= other.value);
}

bool bigint::operator>(const bigint &other) const
{
	return (this->value > other.value);
}

bool bigint::operator>=(const bigint &other) const
{
	return (this->value >= other.value);
}

bool bigint::operator==(const bigint &other) const
{
	return (this->value == other.value);
}

bool bigint::operator!=(const bigint &other) const
{
	return (this->value != other.value);
}


std::ostream &operator<<(std::ostream &out, const bigint &other)
{
	out << other.getValue();
	return (out);
}
