/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackProcess.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKPROCESS_HPP
# define STACKPROCESS_HPP

#include <vector>
#include <string>
#include <utility>
#include <stack>
#include <map>
#include <typeindex>

#include "Logger.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"

class StackProcess
{
public:
	class MissingExitException		: public std::exception { public : virtual const char * what( void ) const throw() { return "Execution Error : 'exit' instruction is missing"; } };
	class PopEmptyStackException	: public std::exception { public : virtual const char * what( void ) const throw() { return "Execution Error : 'pop' instruction is called when the stack is empty"; } };
	class StackTooSmallException	: public std::exception { public : virtual const char * what( void ) const throw() { return "Execution Error : The stack doesn't have enough elements to call the instruction"; } };
	class AssertException	: public std::exception { public : virtual const char * what( void ) const throw() { return "Execution Error : The 'assert' instruction is false"; } };
	class PrintException	: public std::exception { public : virtual const char * what( void ) const throw() { return "Execution Error : The 'print' instruction is false"; } };

private :
	Logger &															_log;
	std::vector<std::pair<unsigned long, std::vector<std::string> > >	_instrs;
	std::stack<IOperand const *>										_stack;
	std::map<std::string, eOperandType>									_typeMap;

	std::string															_voidStr[7];
	std::string															_nonVoidStr[3];
	std::string															_voidConstStr[3];
	void (StackProcess::*_voidFuncs[6])( void );
	void (StackProcess::*_voidConstFuncs[2])( void ) const;
	void (StackProcess::*_nonVoidFuncs[2])( std::string const & type, std::string const & value );


	StackProcess( void );
	StackProcess( StackProcess const & other );
	StackProcess& operator=( StackProcess const & other );

	bool internalFunctionCall(std::string const * array, std::pair<unsigned long, std::vector<std::string> > const & pair, int toCast );
	
	void add( void ) throw(StackProcess::StackTooSmallException, OverflowException, UnderflowException);
	void sub( void ) throw(StackProcess::StackTooSmallException, OverflowException, UnderflowException);
	void mul( void ) throw(StackProcess::StackTooSmallException, OverflowException, UnderflowException);
	void div( void ) throw(StackProcess::StackTooSmallException, DivisionBy0Exception, OverflowException, UnderflowException);
	void mod( void ) throw(StackProcess::StackTooSmallException, DivisionBy0Exception, OverflowException, UnderflowException);

	void pop( void ) throw(StackProcess::PopEmptyStackException);
	void dump( void ) const;
	void print( void ) const throw(StackProcess::PrintException, StackProcess::StackTooSmallException);
	void push( std::string const & type, std::string const & value) throw(OverflowException, UnderflowException);
	void assert( std::string const & type, std::string const & value) throw(StackProcess::StackTooSmallException, StackProcess::AssertException, OverflowException, UnderflowException);

public:
	StackProcess( Logger & log );
	~StackProcess( void );

	void	addInstruction( unsigned long idLine, std::vector<std::string> const & tokens );
	bool	run( void ) throw(StackProcess::MissingExitException);

};

#endif
