/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** main
*/

#include "main.hpp"
#include <cstdlib>
#include <ctime>

int	main(int argc, char **argv)
{
	std::unique_ptr<project>	tmp;

	std::cout << "main: init of the project...\n";
	std::srand(std::time(nullptr));
	try{
		tmp.reset(new project());
		if (!tmp)
			return (84);
		tmp->init_of_graphic();
		tmp->run();
	}
	catch (const std::exception &error){
		std::cerr << "main: error happend on the project.\n";
		std::cerr << error.what() << std::endl;
		return (84);
	}
	std::cout << "main: end of the program\n";
	return (0);
}