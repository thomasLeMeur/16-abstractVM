/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2017/01/31 14:19:07 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP

#include <iostream>
#include <stdexcept>
#include <sstream>

enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double,
	NbOperandTypes
};

class DivisionBy0Exception	: public std::exception { public : virtual const char * what( void ) const throw() { return "Execution Error : Division by 0"; } };
class OverflowException		: public std::exception { public : virtual const char * what( void ) const throw() { return "Execution Error : OverFlow detected"; } };
class UnderflowException	: public std::exception { public : virtual const char * what( void ) const throw() { return "Execution Error : Underflow detected"; } };

static auto	getValueString = []( auto value ) { std::ostringstream s; s.precision(20); s << value; return s.str(); };

#endif
