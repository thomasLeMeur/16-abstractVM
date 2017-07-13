/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser( Logger & log ) : _log(log), _intRegex("-?[0-9]+"), _floatRegex("-?[0-9]+\\.[0-9]+")
{
	this->_intTypes[0] = "int8";
	this->_intTypes[1] = "int16";
	this->_intTypes[2] = "int32";
	this->_intTypes[3] = "";

	this->_floatTypes[0] = "float";
	this->_floatTypes[1] = "double";
	this->_floatTypes[2] = "";

	this->_oneTokenInstr[0] = "pop";
	this->_oneTokenInstr[1] = "dump";
	this->_oneTokenInstr[2] = "add";
	this->_oneTokenInstr[3] = "sub";
	this->_oneTokenInstr[4] = "mul";
	this->_oneTokenInstr[5] = "div";
	this->_oneTokenInstr[6] = "mod";
	this->_oneTokenInstr[7] = "print";
	this->_oneTokenInstr[8] = "exit";
	this->_oneTokenInstr[9] = "";

	this->_threeTokensInstr[0] = "push";
	this->_threeTokensInstr[1] = "assert";
	this->_threeTokensInstr[2] = "";

	return;
}

Parser::~Parser( void )
{
	return;
}

void Parser::checkInstruction( std::vector<std::string> const & tokens ) const throw(Parser::BadInstructionException)
{
	unsigned long	ind = 0;

	if (tokens.size() == 1)
	{
		while (this->_oneTokenInstr[ind] != "")
			if (tokens[0] == this->_oneTokenInstr[ind++])
				return;
		throw Parser::BadInstructionException();
	}
	return;
}

void Parser::checkParametricInstruction( std::vector<std::string> const & tokens ) const throw(Parser::BadParametricInstructionException)
{
	unsigned long	ind = 0;

	if (tokens.size() == 3)
	{
		while (this->_threeTokensInstr[ind] != "")
			if (tokens[0] == this->_threeTokensInstr[ind++])
				return;
		throw Parser::BadParametricInstructionException();
	}
	return;
}

void Parser::checkOperandType( std::vector<std::string> const & tokens ) const throw(Parser::BadOperandTypeException, Parser::BadIntGrammarException, Parser::BadFloatGrammarException)
{
	unsigned long	ind;

	if (tokens.size() == 3)
	{
		ind = 0;
		while (this->_intTypes[ind] != "")
			if (tokens[1] == this->_intTypes[ind++])
			{
				if (std::regex_match(tokens[2], this->_intRegex))
					return;
				else
					throw Parser::BadIntGrammarException();
			}

		ind = 0;
		while (this->_floatTypes[ind] != "")
			if (tokens[1] == this->_floatTypes[ind++])
			{
				if (std::regex_match(tokens[2], this->_floatRegex))
					return;
				else
					throw Parser::BadFloatGrammarException();
			}
		
		throw Parser::BadOperandTypeException();
	}
	return;
}

std::vector<std::string> Parser::parseLine( unsigned long idLine, std::vector<std::string> const & tokens ) const
{
	try
	{
		this->checkInstruction(tokens);
		this->checkParametricInstruction(tokens);
		this->checkOperandType(tokens);
		return std::vector<std::string>(tokens);
	}
	catch(Parser::BadIntGrammarException & e)
	{
		this->_log.addEntry(idLine, std::string(e.what()) + " : '" + tokens[2] + "' found");
	}
	catch(Parser::BadFloatGrammarException & e)
	{
		this->_log.addEntry(idLine, std::string(e.what()) + " : '" + tokens[2] + "' found");
	}
	catch(Parser::BadOperandTypeException & e)
	{
		this->_log.addEntry(idLine, std::string(e.what()) + " '" + tokens[1] + "'");
	}
	catch(std::exception & e)
	{
		this->_log.addEntry(idLine, std::string(e.what()) + " '" + tokens[0] + "'");
	}
	return std::vector<std::string>();
}
