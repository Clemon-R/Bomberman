/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** database
*/

#ifndef DATABASE_HPP_
	#define DATABASE_HPP_

	#include <iostream>
	#include <map>
	#include "irrlicht/irrlicht.h"
	#include "project/config.hpp"

class	database
{
public:
	static void			set_config(irr::IrrlichtDevice *_graphic, config *config);
	static irr::video::ITexture	*load_img(const std::string &name, const std::string ext = ".jpg");
private:
	static irr::IrrlichtDevice	*_graphic;
	static config			*_config;
	static std::map<std::string, irr::video::ITexture *>	_list_imgs;
};
#endif /* !DATABASE_HPP_ */
