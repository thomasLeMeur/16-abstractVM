/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2017/01/31 14:42:53 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include <string>
#include <limits>
#include <cmath>
#include <sstream>

#include "IOperand.hpp"
#include "OperandFactory.hpp"

class OperandFactory;

template <typename T>
class Operand : public IOperand
{
private :
	eOperandType	_type;
	T				_value;
	std::string		_valueStr;

	Operand<T>( void );
	Operand<T>( Operand<T> const & other );
	Operand<T>& operator=( Operand<T> const & other );

public:
	Operand<T>( std::string const & value, eOperandType const & type ) throw(OverflowException, UnderflowException) : _type(type)
	{
		try
		{
			double val = std::stod(value);

			if (val > std::numeric_limits<T>::max() || ((std::isinf(val) || std::isnan(val)) && (((*reinterpret_cast<long *>(&val) >> 63) & 1) == false)))
				throw OverflowException();
			else if ((type >= Float && val < -std::numeric_limits<T>::max()) || (type < Float && val < std::numeric_limits<T>::min()) || ((std::isinf(val) || std::isnan(val)) && ((*reinterpret_cast<long *>(&val) >> 63) & 1)))
				throw UnderflowException();
			else
				this->_value = static_cast<T>(val);

			std::ostringstream	s;
			if (type == Int8)
				s << static_cast<int>(this->_value);
			else
				s << this->_value;
			this->_valueStr = s.str();

		}
		catch(std::out_of_range &)
		{
			if (value.size() > 0 && value[0] == '-')
				throw UnderflowException();
			else
				throw OverflowException();
		}
		return;
	}

	~Operand<T>( void ) {}


	int					getPrecision( void ) const { return static_cast<int>(this->_type); }
	eOperandType		getType( void ) const { return this->_type; }

	IOperand const *	operator+( IOperand const & rhs ) const throw(OverflowException, UnderflowException)
	{
		auto lambda = []( auto thisVal, auto rhsVal, auto type)
		{
			auto	res = static_cast<decltype(type)>(thisVal) + static_cast<decltype(type)>(rhsVal);

			if (static_cast<decltype(type)>(rhsVal) >= 0 && res < static_cast<decltype(type)>(thisVal))
				throw OverflowException();
			else if (static_cast<decltype(type)>(rhsVal) < 0 && res > static_cast<decltype(type)>(thisVal))
				throw UnderflowException();

			return res;
		};

		std::string		val;
		eOperandType	type = (this->getPrecision() >= rhs.getPrecision()) ? this->getType() : rhs.getType();

		if (dynamic_cast<Operand<int8_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int8_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int8_t>(0)));
		else if (dynamic_cast<Operand<int16_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int16_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int16_t>(0)));
		else if (dynamic_cast<Operand<int32_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int32_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int32_t>(0)));
		else if (dynamic_cast<Operand<float> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<float> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<float>(0)));
		else
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<double> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<double>(0)));

		return OperandFactory::createOperand(type, val);
	}

	IOperand const *	operator-( IOperand const & rhs ) const throw(OverflowException, UnderflowException)
	{
		auto lambda = []( auto thisVal, auto rhsVal, auto type)
		{
			auto	res = static_cast<decltype(type)>(thisVal) - static_cast<decltype(type)>(rhsVal);

			if (static_cast<decltype(type)>(rhsVal) >= 0 && res > static_cast<decltype(type)>(thisVal))
				throw OverflowException();
			else if (static_cast<decltype(type)>(rhsVal) < 0 && res < static_cast<decltype(type)>(thisVal))
				throw UnderflowException();

			return res;
		};

		std::string		val;
		eOperandType	type = (this->getPrecision() >= rhs.getPrecision()) ? this->getType() : rhs.getType();

		if (dynamic_cast<Operand<int8_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int8_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int8_t>(0)));
		else if (dynamic_cast<Operand<int16_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int16_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int16_t>(0)));
		else if (dynamic_cast<Operand<int32_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int32_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int32_t>(0)));
		else if (dynamic_cast<Operand<float> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<float> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<float>(0)));
		else
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<double> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<double>(0)));

		return OperandFactory::createOperand(type, val);
	}

	IOperand const *	operator*( IOperand const & rhs ) const throw(OverflowException, UnderflowException)
	{
		auto lambda = []( auto thisVal, auto rhsVal, auto type)
		{
			if (thisVal != 0 && std::numeric_limits<decltype(type)>::max() / static_cast<decltype(type)>(thisVal) < static_cast<decltype(type)>(rhsVal))
				throw OverflowException();
			else if (thisVal != 0 && ((type >= Float) ? -std::numeric_limits<decltype(type)>::max() : std::numeric_limits<decltype(type)>::min()) / static_cast<decltype(type)>(thisVal) > static_cast<decltype(type)>(rhsVal))
				throw UnderflowException();

			return static_cast<decltype(type)>(thisVal) * static_cast<decltype(type)>(rhsVal);
		};

		std::string		val;
		eOperandType	type = (this->getPrecision() >= rhs.getPrecision()) ? this->getType() : rhs.getType();

		if (dynamic_cast<Operand<int8_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int8_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(this->_type) : static_cast<int8_t>(Int8)));
		else if (dynamic_cast<Operand<int16_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int16_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(this->_type) : static_cast<int16_t>(Int16)));
		else if (dynamic_cast<Operand<int32_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int32_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(this->_type) : static_cast<int32_t>(Int32)));
		else if (dynamic_cast<Operand<float> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<float> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(this->_type) : static_cast<float>(Float)));
		else
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<double> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(this->_type) : static_cast<double>(Double)));

		return OperandFactory::createOperand(type, val);
	}

	IOperand const *	operator/( IOperand const & rhs ) const throw(DivisionBy0Exception, UnderflowException, OverflowException)
	{
		auto lambda = []( auto thisVal, auto rhsVal, auto type)
		{
			if (rhsVal == 0)
				throw DivisionBy0Exception();

			return static_cast<decltype(type)>(thisVal) / static_cast<decltype(type)>(rhsVal);
		};

		std::string		val;
		eOperandType	type = (this->getPrecision() >= rhs.getPrecision()) ? this->getType() : rhs.getType();

		if (dynamic_cast<Operand<int8_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int8_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int8_t>(0)));
		else if (dynamic_cast<Operand<int16_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int16_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int16_t>(0)));
		else if (dynamic_cast<Operand<int32_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int32_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int32_t>(0)));
		else if (dynamic_cast<Operand<float> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<float> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<float>(0)));
		else
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<double> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<double>(0)));

		return OperandFactory::createOperand(type, val);
	}

	IOperand const *	operator%( IOperand const & rhs ) const throw(DivisionBy0Exception, UnderflowException, OverflowException)
	{
		auto lambda = []( auto thisVal, auto rhsVal, auto type)
		{
			if (rhsVal == 0)
				throw DivisionBy0Exception();

			return static_cast<decltype(type)>(fmod(static_cast<decltype(type)>(thisVal), static_cast<decltype(type)>(rhsVal)));
		};

		std::string		val;
		eOperandType	type = (this->getPrecision() >= rhs.getPrecision()) ? this->getType() : rhs.getType();

		if (dynamic_cast<Operand<int8_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int8_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int8_t>(0)));
		else if (dynamic_cast<Operand<int16_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int16_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int16_t>(0)));
		else if (dynamic_cast<Operand<int32_t> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<int32_t> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<int32_t>(0)));
		else if (dynamic_cast<Operand<float> const *>(&rhs))
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<float> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<float>(0)));
		else
			val = getValueString(lambda(this->_value, dynamic_cast<Operand<double> const &>(rhs).getValue(), (type == this->getType()) ? static_cast<T>(0) : static_cast<double>(0)));

		return OperandFactory::createOperand(type, val);
	}


	std::string const &	toString( void ) const { return this->_valueStr; }
	T					getValue( void ) const { return this->_value; }

	static T compare(IOperand const * a, IOperand const * b)
	{
		T val1, val2;

		if (dynamic_cast<Operand<int8_t> const *>(a))
			val1 = dynamic_cast<Operand<int8_t> const *>(a)->getValue();
		else if (dynamic_cast<Operand<int16_t> const *>(a))
			val1 = dynamic_cast<Operand<int16_t> const *>(a)->getValue();
		else if (dynamic_cast<Operand<int32_t> const *>(a))
			val1 = dynamic_cast<Operand<int32_t> const *>(a)->getValue();
		else if (dynamic_cast<Operand<float> const *>(a))
			val1 = dynamic_cast<Operand<float> const *>(a)->getValue();
		else
			val1 = dynamic_cast<Operand<double> const *>(a)->getValue();

		if (dynamic_cast<Operand<int8_t> const *>(b))
			val2 = dynamic_cast<Operand<int8_t> const *>(b)->getValue();
		else if (dynamic_cast<Operand<int16_t> const *>(b))
			val2 = dynamic_cast<Operand<int16_t> const *>(b)->getValue();
		else if (dynamic_cast<Operand<int32_t> const *>(b))
			val2 = dynamic_cast<Operand<int32_t> const *>(b)->getValue();
		else if (dynamic_cast<Operand<float> const *>(b))
			val2 = dynamic_cast<Operand<float> const *>(b)->getValue();
		else
			val2 = dynamic_cast<Operand<double> const *>(b)->getValue();

		return val1 - val2;
	}

};

#endif
