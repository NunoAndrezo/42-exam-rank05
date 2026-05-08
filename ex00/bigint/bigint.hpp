/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:03:22 by nuno              #+#    #+#             */
/*   Updated: 2026/01/22 12:32:50 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <climits>
#include <vector>

class bigint
{
	private:
		unsigned long long value;
		// std::string digits; // digits = std::to_string(value); // std::insert
	public:
		bigint();
		bigint(unsigned long long val);
		bigint(const bigint &other);
		~bigint();
		bigint &operator=(const bigint &other);

		unsigned long long getValue() const;

		bigint operator+(const bigint &other) const;
		bigint &operator+=(const bigint &other);

		bigint operator++(int);
		bigint &operator++();

		//shift with number
		bigint operator<<(unsigned int shift) const;
		bigint &operator<<=(unsigned int shift);
		bigint operator>>(unsigned int shift) const;
		bigint &operator>>=(unsigned int shift);
		//shift with object
		bigint operator<<(const bigint &other) const;
		bigint &operator<<=(const bigint &other);
		bigint operator>>(const bigint &other) const;
		bigint &operator>>=(const bigint &other);

		bool operator<(const bigint &other) const;
		bool operator<=(const bigint &other) const;
		bool operator>(const bigint &other) const;
		bool operator>=(const bigint &other) const;
		bool operator==(const bigint &other) const;
		bool operator!=(const bigint &other) const;
};

std::ostream &operator<<(std::ostream &out, const bigint &other);

#endif
