/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vm.hpp"

Vm::Vm( void ) : _logger(), _lexer(_logger), _parser(_logger), _stack(_logger)
{
	return;
}

Vm::~Vm( void )
{
	return;
}

void Vm::run( std::istream & stream, std::string const & finalInstr )
{
	try
	{
		if (!this->readAndParse(stream, finalInstr) || !this->_stack.run())
			this->_logger.printErrors();
	}
	catch(StackProcess::MissingExitException & e)
	{
		this->_logger.printErrors();
		std::cerr << "Fatal Error : The 'exit' final instruction is missing" << std::endl;
	}
	return;
}

bool Vm::readAndParse( std::istream & stream, std::string const & finalInstr )
{
	unsigned long				idLine = 1;
	std::string					line;
	std::vector<std::string>	tokens;

	while (std::getline(stream, line) && this->_logger.getErrorNb() < 20)
	{
		tokens = this->_lexer.lexicalCheck(idLine, line, finalInstr);
		if (finalInstr == ";;" && tokens.size() == 1 && tokens[0] == ";;")
			break;

		tokens = this->_parser.parseLine(idLine, tokens);
		this->_stack.addInstruction(idLine, tokens);
		idLine++;
	}
	return (this->_logger.getErrorNb() > 0) ? false : true;
}

