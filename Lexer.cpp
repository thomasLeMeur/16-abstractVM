/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer( Logger & log ) : _log(log)
{
	return;
}

Lexer::~Lexer( void )
{
	return;
}

std::vector<std::string> Lexer::lexicalCheck( unsigned long idLine, std::string const & line, std::string const & finalInstr ) const
{
	unsigned long				pos;
	std::string					error;
	std::vector<std::string>	tokens;
	std::string					s = this->cleanString(line, finalInstr);

	//If the string is empty, return an empty token vector
	if (s != "")
	{
		//Find the position of the end of the first token
		pos = s.find(' ');

		//If the end is reached, there is just one token
		if (pos == std::string::npos)
			tokens.push_back(s);
		else
		{
			//Extract the first token and put it into the token vector
			tokens.push_back(s.substr(0, pos));
			s = s.substr(pos + 1);

			//Find the end of the type of the operand
			pos = s.find('(');

			//If the end is reached, there is a lexical error
			if (pos == std::string::npos)
			{
				this->_log.addEntry(idLine, "Lexer Error : After a parametric instruction, the operand type expects a value between parenthesis : '(' is missing");
				tokens.clear();
			}
			else
			{
				//Extract the second token and put it into the token vector
				tokens.push_back(s.substr(0, pos));
				s = s.substr(pos + 1);

				//Find the end of the value of the operand
				pos = s.find(')');

				//If the end is reached, there is a lexical error
				if (pos == std::string::npos)
				{
					this->_log.addEntry(idLine, "Lexer Error : After a parametric instruction, the operand type expects a value between parenthesis : ')' is missing");
					tokens.clear();
				}
				else
				{
					//Extract the third token and put it into the token vector
					tokens.push_back(s.substr(0, pos));
					s = s.substr(pos + 1);

					if (s != "")
					{
						this->_log.addEntry(idLine, "Lexer Error : After a parametric instruction, nothing is expected after the value : '" + s + "' found");
						tokens.clear();
					}
				}
			}
		}
	}
	return tokens;
}

std::string Lexer::cleanString( std::string const & line, std::string const & finalInstr ) const
{
	std::string		s = "";
	unsigned long	ind = 0;
	unsigned long	len = line.size();

	//Pass the first spaces and tabulations
	while (ind < len && (line[ind] == ' ' || line[ind] == '\t'))
		ind++;

	//Save the first token
	while (ind < len && (line[ind] != ' ' && line[ind] != '\t'))
		s += line[ind++];

	//Pass the next spaces and tabulations
	while (ind < len && (line[ind] == ' ' || line[ind] == '\t'))
		ind++;

	//Add a space separator and concatenate all the non empty characters
	if (ind < len)
	{
		s += " ";
		while (ind < len)
		{
			if (line[ind] != ' ' && line[ind] != '\t')
				s += line[ind];
			ind++;
		}
	}

	//Check if the line is not the stdin end command
	if (finalInstr != ";;" || s != ";;")
	{
		//Find the first ';' (comment character) and delete the comment part of the line
		unsigned long pos = s.find(';');
		if (pos < std::string::npos)
			s = s.substr(0, pos);
	}

	if (s.size() > 0 && s[s.size() - 1] == ' ')
		s = s.substr(0, s.size() - 1);

	return s;
}
