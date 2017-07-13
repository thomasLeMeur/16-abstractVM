/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackProcess.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StackProcess.hpp"
#include "OperandFactory.hpp"

StackProcess::StackProcess( Logger & log) : _log(log)
{
	this->_typeMap["int8"] = Int8;
	this->_typeMap["int16"] = Int16;
	this->_typeMap["int32"] = Int32;
	this->_typeMap["float"] = Float;
	this->_typeMap["double"] = Double;


	this->_voidConstStr[0] = "dump";
	this->_voidConstStr[1] = "print";
	this->_voidConstStr[2] = "";

	this->_voidConstFuncs[0] = &StackProcess::dump;
	this->_voidConstFuncs[1] = &StackProcess::print;


	this->_voidStr[0] = "add";
	this->_voidStr[1] = "sub";
	this->_voidStr[2] = "mul";
	this->_voidStr[3] = "div";
	this->_voidStr[4] = "mod";
	this->_voidStr[5] = "pop";
	this->_voidStr[6] = "";

	this->_voidFuncs[0] = &StackProcess::add;
	this->_voidFuncs[1] = &StackProcess::sub;
	this->_voidFuncs[2] = &StackProcess::mul;
	this->_voidFuncs[3] = &StackProcess::div;
	this->_voidFuncs[4] = &StackProcess::mod;
	this->_voidFuncs[5] = &StackProcess::pop;


	this->_nonVoidStr[0] = "push";
	this->_nonVoidStr[1] = "assert";
	this->_nonVoidStr[2] = "";

	this->_nonVoidFuncs[0] = &StackProcess::push;
	this->_nonVoidFuncs[1] = &StackProcess::assert;

	return;
}

StackProcess::~StackProcess( void )
{
	while (!this->_stack.empty())
	{
		delete this->_stack.top();
		this->_stack.pop();
	}
	return;
}

void StackProcess::addInstruction( unsigned long idLine, std::vector<std::string> const & tokens )
{
	if (tokens.size() > 0)
		this->_instrs.push_back(std::make_pair(idLine, tokens));
	return;
}

void StackProcess::add( void ) throw(StackProcess::StackTooSmallException, OverflowException, UnderflowException)
{
	if (this->_stack.size() < 2)
		throw StackProcess::StackTooSmallException();

	IOperand const * v1 = this->_stack.top();
	this->_stack.pop();
	IOperand const * v2 = this->_stack.top();
	this->_stack.push(v1);

	IOperand const * tmp = *v2 + *v1;

	this->_stack.pop();
	this->_stack.pop();
	this->_stack.push(tmp);

	delete v1;
	delete v2;

	return;
}

void StackProcess::sub( void ) throw(StackProcess::StackTooSmallException, OverflowException, UnderflowException)
{
	if (this->_stack.size() < 2)
		throw StackProcess::StackTooSmallException();

	IOperand const * v1 = this->_stack.top();
	this->_stack.pop();
	IOperand const * v2 = this->_stack.top();
	this->_stack.push(v1);

	IOperand const * tmp = *v2 - *v1;

	this->_stack.pop();
	this->_stack.pop();
	this->_stack.push(tmp);

	delete v1;
	delete v2;

	return;
}
void StackProcess::mul( void ) throw(StackProcess::StackTooSmallException, OverflowException, UnderflowException)
{
	if (this->_stack.size() < 2)
		throw StackProcess::StackTooSmallException();

	IOperand const * v1 = this->_stack.top();
	this->_stack.pop();
	IOperand const * v2 = this->_stack.top();
	this->_stack.push(v1);

	IOperand const * tmp = *v2 * *v1;

	this->_stack.pop();
	this->_stack.pop();
	this->_stack.push(tmp);

	delete v1;
	delete v2;

	return;
}
void StackProcess::div( void ) throw(StackProcess::StackTooSmallException, DivisionBy0Exception, OverflowException, UnderflowException)
{
	if (this->_stack.size() < 2)
		throw StackProcess::StackTooSmallException();

	IOperand const * v1 = this->_stack.top();
	this->_stack.pop();
	IOperand const * v2 = this->_stack.top();
	this->_stack.push(v1);

	IOperand const * tmp = *v2 / *v1;
	this->_stack.pop();
	this->_stack.pop();
	this->_stack.push(tmp);

	delete v1;
	delete v2;

	return;
}
void StackProcess::mod( void ) throw(StackProcess::StackTooSmallException, DivisionBy0Exception, OverflowException, UnderflowException)
{
	if (this->_stack.size() < 2)
		throw StackProcess::StackTooSmallException();

	IOperand const * v1 = this->_stack.top();
	this->_stack.pop();
	IOperand const * v2 = this->_stack.top();
	this->_stack.push(v1);

	IOperand const * tmp = *v2 % *v1;

	this->_stack.pop();
	this->_stack.pop();
	this->_stack.push(tmp);

	delete v1;
	delete v2;

	return;
}

void StackProcess::pop( void ) throw(StackProcess::PopEmptyStackException)
{
	if (this->_stack.size() < 1)
		throw StackProcess::PopEmptyStackException();

	delete this->_stack.top();
	this->_stack.pop();

	return;
}

void StackProcess::dump( void ) const
{
	std::stack<IOperand const *>	tmp(this->_stack);
	
	if (this->_log.getErrorNb() == 0)
	{
		while(!tmp.empty())
		{
			std::cout << tmp.top()->toString() << std::endl;
			tmp.pop();
		}
	}
	else
		std::cerr << "Execution warning : The 'dump' instruction has not been done because some errors have been found and the stack values can be false" << std::endl;
	return;
}

void StackProcess::print( void ) const throw(StackProcess::PrintException, StackProcess::StackTooSmallException)
{
	if (this->_stack.size() < 1)
		throw StackProcess::StackTooSmallException();
	if (this->_log.getErrorNb() == 0)
	{
		if (this->_stack.top()->getType() != Int8)
			throw StackProcess::PrintException();

		char c = static_cast<char>(std::atoi(this->_stack.top()->toString().c_str()));
		if ((c != 9 && c != 10 && c <= 31) || c >= 127)
			std::cout << "Non printable (ASCII value = " << this->_stack.top()->toString() << ")" << std::endl;
		else
			std::cout << c << std::endl;
	}
	else
		std::cerr << "Execution warning : The 'print' instruction has not been done because some errors have been found and the stack values can be false" << std::endl;

	return;
}

void StackProcess::push( std::string const & type, std::string const & value) throw(OverflowException, UnderflowException)
{
	this->_stack.push(OperandFactory::createOperand(this->_typeMap[type], value));
	return;
}

void StackProcess::assert( std::string const & type, std::string const & value) throw(StackProcess::StackTooSmallException, StackProcess::AssertException, OverflowException, UnderflowException)
{
	if (this->_stack.size() < 1)
		throw StackProcess::StackTooSmallException();
	else
	{
		if (this->_log.getErrorNb() == 0)
		{
			IOperand const *	tmp = OperandFactory::createOperand(this->_typeMap[type], value);

			if (tmp->getType() != this->_stack.top()->getType() || Operand<double>::compare(tmp, this->_stack.top()) != 0)
			{
				delete tmp;
				throw StackProcess::AssertException();
			}
			delete tmp;
		}
		else
			std::cerr << "Execution warning : The 'assert' instruction has not been done because some errors have been found and the stack values can be false" << std::endl;
	}
	return;
}

bool StackProcess::internalFunctionCall(std::string const * array, std::pair<unsigned long, std::vector<std::string> > const & pair, int toCast )
{
	unsigned long	ind = 0;

	while (array[ind] != "")
		if (array[ind] == pair.second[0])
			break;
		else
			ind++;

	if (array[ind] == "")
		return false;

	try
	{
		if (toCast == 0)
			(this->*_voidFuncs[ind])();
		else if (toCast == 1)
			(this->*_voidConstFuncs[ind])();
		else
			(this->*_nonVoidFuncs[ind])(pair.second[1], pair.second[2]);
	}
	catch(DivisionBy0Exception & e)
	{
		this->_log.addEntry(pair.first, std::string(e.what()) + " (the action has not been done)");
	}
	catch(OverflowException & e)
	{
		this->_log.addEntry(pair.first, std::string(e.what()) + " (the action has not been done)");
	}
	catch(UnderflowException & e)
	{
		this->_log.addEntry(pair.first, std::string(e.what()) + " (the action has not been done)");
	}
	catch(StackProcess::StackTooSmallException & e)
	{
		this->_log.addEntry(pair.first, std::string(e.what()) + " (the action has not been done)");
	}
	catch(StackProcess::PopEmptyStackException & e)
	{
		this->_log.addEntry(pair.first, std::string(e.what()) + " (the action has not been done)");
	}

	return true;
}

bool StackProcess::run( void ) throw(StackProcess::MissingExitException)
{
	std::vector<std::pair<unsigned long, std::vector<std::string> > >::iterator	it = this->_instrs.begin();
	std::vector<std::pair<unsigned long, std::vector<std::string> > >::iterator	ite = this->_instrs.end();
	bool																		exit = false;

	for ( ; it != ite && this->_log.getErrorNb() < 20 ; it++)
	{
		if (it->second[0] == "exit")
		{
			exit = true;
			break;
		}
		else
		{
			try
			{
				if (!this->internalFunctionCall(this->_voidStr, *it, 0))
					if (!this->internalFunctionCall(this->_voidConstStr, *it, 1))
						this->internalFunctionCall(this->_nonVoidStr, *it, 2);
			}
			catch(StackProcess::AssertException & e)
			{
				this->_log.addEntry(it->first, std::string(e.what()) + " (end of the execution)");
				break;
			}
			catch(StackProcess::PrintException & e)
			{
				this->_log.addEntry(it->first, std::string(e.what()) + " (end of the execution)");
				break;
			}
			catch(std::exception & e)
			{
				this->_log.addEntry(it->first, "Fatal error : " + std::string(e.what()) + " (unknown exception : end of the execution)");
				break;
			}
		}
	}

	for ( ; it != ite ; it++)
	{
		if (it->second[0] == "exit")
		{
			exit = true;
			break;
		}
	}

	if (!exit)
		throw StackProcess::MissingExitException();

	return (this->_log.getErrorNb() > 0) ? false : true;
}
