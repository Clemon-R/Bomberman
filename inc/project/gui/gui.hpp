/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** gui
*/

#ifndef GUI_HPP_
	#define GUI_HPP_

	#include "irrlicht/irrlicht.h"
	#include "project/interface.hpp"
	#include "project/config.hpp"
	#include "project/gui/gui_handler.hpp"
	#include <iostream>

class	gui : public interface
{
public:
	gui(irr::IrrlichtDevice *graphic, config *config);
	~gui();

	void	run() override;
private:
	irr::IrrlichtDevice	*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	gui_handler			_handler;

	config			*_config;
};
#endif /* !GUI_HPP_ */
