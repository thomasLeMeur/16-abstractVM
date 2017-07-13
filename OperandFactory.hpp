/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

#include "utilities.hpp"
#include "IOperand.hpp"

template <typename T> class Operand;

class OperandFactory
{
private :
	OperandFactory( void );
	~OperandFactory( void );
	OperandFactory( OperandFactory const & other );
	OperandFactory& operator=( OperandFactory const & other );

	static IOperand const *	createInt8( std::string const & value );
	static IOperand const *	createInt16( std::string const & value );
	static IOperand const *	createInt32( std::string const & value );
	static IOperand const *	createFloat( std::string const & value );
	static IOperand const *	createDouble( std::string const & value );

public:
	static IOperand const *	createOperand( eOperandType type, std::string const & value );

public :
	static IOperand const * (*factory[NbOperandTypes])(std::string const & value);

};

#endif
