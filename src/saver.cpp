/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** saver
*/

#include "saver.hpp"
#include <fstream>
#include <stdio.h>

std::map<std::string, std::string config::*>	saver::_config_params = {
	{"SCALE", &config::SCALE},
	{"FULL_SCREEN", &config::FULL_SCREEN}
};

void	saver::save_config(config &config)
{
	std::ofstream	file;

	std::cout << "saver: starting save config...\n";
	std::cout << "saver: removing old config if exist...\n";
	remove(CONFIG_FILE);
	file.open(CONFIG_FILE);
	if (!file.is_open())
		throw exception("Impossible to write the config");
	for (const auto &elem : _config_params)
		file << elem.first << "=" << config.*(elem.second) << std::endl;
	file.close();
	std::cout << "saver: config saved\n";
}

void	saver::load_line_config(const std::string &line, config &config)
{
	std::size_t	pos = std::string::npos;

	pos = line.find_first_of('=');
	if (pos == std::string::npos)
		return;
	parse_line_config(config, line.substr(0, pos), line.substr(pos + 1));
}

void	saver::parse_line_config(config &config, const std::string &name, const std::string &value)
{
	for (const auto &elem : _config_params){
		if (elem.first == name){
			config.*(elem.second) = value;
			break;
		}
	}
}

config	*saver::load_config()
{
	std::ifstream	file;
	config	*file_config = new config();
	std::string	line;

	if (!file_config)
		throw exception("Impossible to alloc some memory");
	std::cout << "saver: starting to load config...\n";
	file.open(CONFIG_FILE);
	if (!file.is_open())
		return (file_config);
	while (getline(file, line))
		saver::load_line_config(line, *file_config);
	file.close();
	return (file_config);
}