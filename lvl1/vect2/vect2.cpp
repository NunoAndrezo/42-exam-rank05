#include "vect2.hpp"

vect2::vect2()
{
	this->x = 0;
	this->y = 0;
}

vect2::vect2(int n1, int n2) : x(n1), y(n2) {}

vect2::vect2(const vect2 &other)
{
	*this = other;
}

vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	return (*this);
}

vect2::~vect2(){}

int vect2::operator[](int index) const
{
	if (index == 0)
		return (this->x);
	return (this->y);
}

int &vect2::operator[](int index)
{
	if (index == 0)
		return (this->x);
	return (this->y);
}

vect2 vect2::operator-() const
{
	vect2 temp = *this;
	temp[0] = -temp[0]; // or temp[0] = this->x * -1
	temp[1] = -temp[1]; //    temp[1] = this->y * -1 
	return temp;
}

vect2 vect2::operator++(int) // v1++
{
	vect2 temp = *this;

	++(*this);
	return (temp);
}

vect2 &vect2::operator++()
{
	this->x += 1;
	this->y += 1;
	return (*this);
}

vect2 vect2::operator--(int)
{
	vect2 temp(*this);
	(*this)--;
	return temp;
}

vect2 &vect2::operator--()
{
	this->x--;
	this->y--;
	return (*this);
}