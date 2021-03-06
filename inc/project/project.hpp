/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** game
*/

#ifndef PROJECT_HPP_
	#define PROJECT_HPP_

	#include "irrlicht/irrlicht.h"
	#include "irrklang/irrKlang.h"
	#include "project/config.hpp"
class	gui;
	#include "project/gui/gui.hpp"
	#include "project/interface.hpp"
	#include "saver.hpp"
	#include "exception.hpp"
	#include <iostream>
	#include <memory>

	#define	VERTICAL_SYNC	false

class	project
{
public:
	project();
	~project();

	void	init_of_graphic();
	void	run();
	void	set_interface(interface *window);
	irrklang::ISoundEngine	*get_sound();
private:
	std::unique_ptr<irr::IrrlichtDevice>	_graphic;
	std::unique_ptr<irrklang::ISoundEngine>	_sound;
	std::unique_ptr<config>	_config;
	std::unique_ptr<interface>	_interface;
};
#endif /* !PROJECT_HPP_ */
