/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include <regex>
#include <stdexcept>

#include "Logger.hpp"

class Parser
{
public :
	class BadInstructionException			: public std::exception { public : virtual const char * what( void ) const throw() { return "Parser Error : Unknown non-parametric instruction"; } };
	class BadParametricInstructionException	: public std::exception { public : virtual const char * what( void ) const throw() { return "Parser Error : Unknown parametric instruction"; } };
	class BadOperandTypeException			: public std::exception { public : virtual const char * what( void ) const throw() { return "Parser Error : Unknown operand type"; } };
	class BadIntGrammarException			: public std::exception { public : virtual const char * what( void ) const throw() { return "Parser Error : Integer types expects a value under the form [-]?[0-9]+"; } };
	class BadFloatGrammarException			: public std::exception { public : virtual const char * what( void ) const throw() { return "Parser Error : Floating types expects a value under the form [-]?[0-9]+.[0-9]+"; } };

private :
	Logger &	_log;
	std::regex	_intRegex;
	std::regex	_floatRegex;
	std::string	_intTypes[4];
	std::string	_floatTypes[3];
	std::string	_oneTokenInstr[10];
	std::string	_threeTokensInstr[3];

	Parser( void );
	Parser( Parser const & other );
	Parser& operator=( Parser const & other );

	void	checkInstruction( std::vector<std::string> const & tokens ) const throw(Parser::BadInstructionException);
	void	checkParametricInstruction( std::vector<std::string> const & tokens ) const throw(Parser::BadParametricInstructionException);
	void	checkOperandType( std::vector<std::string> const & toekns ) const throw(Parser::BadOperandTypeException, Parser::BadIntGrammarException, Parser::BadFloatGrammarException);

public:
	Parser( Logger & log );
	~Parser( void );

	std::vector<std::string>	parseLine( unsigned long idLine, std::vector<std::string> const & tokens ) const;

};

#endif
