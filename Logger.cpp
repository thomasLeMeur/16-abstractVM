/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include <iostream>

Logger::Logger( void )
{
	return;
}

Logger::~Logger( void )
{
	return;
}

void Logger::addEntry( unsigned long idLine, std::string const & entry )
{
	this->_errors.push_back("Line " + std::to_string(idLine) + " : " + entry);
	return;
}

void Logger::printErrors( void ) const
{
	for (unsigned long i = 0 ; i < this->_errors.size() ; i++)
		std::cerr << this->_errors[i] << std::endl;
	if (this->_errors.size() >= 20)
		std::cerr << std::endl << "There are too many errors (clipped to 20)" << std::endl;
	return;
}

unsigned long Logger::getErrorNb( void ) const
{
	return this->_errors.size();
}
