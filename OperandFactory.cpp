/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "utilities.hpp"

IOperand const * (*OperandFactory::factory[NbOperandTypes])( std::string const & value) = 
{
	OperandFactory::createInt8,
	OperandFactory::createInt16,
	OperandFactory::createInt32,
	OperandFactory::createFloat,
	OperandFactory::createDouble
};

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value )
{
	return (OperandFactory::factory[type])(value);
}

IOperand const * OperandFactory::createInt8( std::string const & value )
{
	return new Operand<int8_t>(value, Int8);
}

IOperand const * OperandFactory::createInt16( std::string const & value )
{
	return new Operand<int16_t>(value, Int16);
}

IOperand const * OperandFactory::createInt32( std::string const & value )
{
	return new Operand<int32_t>(value, Int32);
}

IOperand const * OperandFactory::createFloat( std::string const & value )
{
	return new Operand<float>(value, Float);
}

IOperand const * OperandFactory::createDouble( std::string const & value )
{
	return new Operand<double>(value, Double);
}
