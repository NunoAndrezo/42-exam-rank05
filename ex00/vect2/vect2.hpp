#pragma once

#include <iostream>
#include <vector>

class vect2
{
	private:
		int x;
		int y;
	public:
		vect2();
		vect2(int n1, int n2);
		vect2(const vect2 &other);
		~vect2();
		vect2 &operator=(const vect2 &other);
		
		int getX() const {return (this->x);};
		int	getY() const {return (this->y);};

		int operator[](int index) const;
		int &operator[](int index);


		vect2 operator-() const;
		vect2 operator++(int);
		vect2 operator--(int);
		vect2 &operator++();
		vect2 &operator--();

		vect2 operator+(const vect2 &other) const;
		vect2 operator-(const vect2 &other) const;
		vect2 operator*(int n) const;

		vect2 &operator+=(const vect2 &other);
		vect2 &operator-=(const vect2 &other);
		vect2 &operator*=(int n);

		bool operator==(const vect2& obj) const;
		bool operator!=(const vect2& obj) const;

};

vect2 operator*(int n, const vect2 &other);

std::ostream &operator<<(std::ostream &out, const vect2 &src);