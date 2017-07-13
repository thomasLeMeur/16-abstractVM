/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_HPP
# define VM_HPP

#include <iostream>

#include "Logger.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "StackProcess.hpp"

class Vm
{
private :
	Logger			_logger;
	Lexer			_lexer;
	Parser			_parser;
	StackProcess	_stack;

	Vm& operator=( Vm const & other );
	Vm( Vm const & other );

	bool readAndParse( std::istream & stream, std::string const & finalInstr );

public :
	Vm( void );
	~Vm( void );

	void run( std::istream & stream, std::string const & finalInstr );

};

#endif
