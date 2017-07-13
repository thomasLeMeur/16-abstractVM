/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

#include <vector>
#include <string>

#include "Logger.hpp"

class Lexer
{
private :
	Logger &	_log;
	
	Lexer( void );
	Lexer( Lexer const & other );
	Lexer& operator=( Lexer const & other );

	std::string cleanString( std::string const & line, std::string const & finalInstr ) const;

public:
	Lexer( Logger & log );
	~Lexer( void );

	std::vector<std::string>	lexicalCheck( unsigned long idLine, std::string const & line, std::string const & finalInstr ) const;

};

#endif
