/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

#include <vector>
#include <string>

class Logger
{
private :
	std::vector<std::string>	_errors;

	Logger( Logger const & other );
	Logger& operator=( Logger const & other );

public:
	Logger( void );
	~Logger( void );

	void			addEntry( unsigned long idLine, std::string const & entry );
	void			printErrors( void ) const;
	unsigned long	getErrorNb( void ) const;

};

#endif
