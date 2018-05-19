/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** saver
*/

#ifndef SAVER_HPP_
	#define SAVER_HPP_

	#define	CONFIG_FILE	"config.conf"

	#include <iostream>
	#include <map>
	#include "project/config.hpp"
	#include "exception.hpp"

class	saver
{
public:
	static void	save_config(config &);
	static config	*load_config();
private:
	static void	load_line_config(const std::string &line, config &config);
	static void	parse_line_config(config &config, const std::string &name, const std::string &value);

	static std::map<std::string, std::string config::*>	_config_params;
};
#endif /* !SAVER_HPP_ */
