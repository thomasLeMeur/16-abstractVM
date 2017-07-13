/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/XX/XX XX:XX:XX by student           #+#    #+#             */
/*   Updated: 2016/XX/XX XX:XX:XX by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

#include "Vm.hpp"

int	main( int ac, char **av )
{
	if (ac == 1)
	{
		Vm	vm;

		vm.run(std::cin, ";;");
	}
	else
	{
		for (int i = 1 ; i < ac ; i++)
		{
			Vm				vm;
			std::ifstream	file(av[i]);

			if (file.fail())
				std::cerr << "avm : " << av[i] << " : Can't open the file" << std::endl;
			else
			{
				
				vm.run(file, "");
			}
			file.close();
		}
	}
	return (0);
}
