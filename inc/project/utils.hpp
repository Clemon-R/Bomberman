/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** utils
*/

#ifndef UTILS_HPP_
	#define UTILS_HPP_

	#include "irrlicht/irrlicht.h"
	#include <iostream>

class	utils
{
public:
	static void	add_button(irr::gui::IGUIEnvironment *env, irr::video::ITexture *img, const irr::core::position2di &pos, irr::s32 action);
	static irr::core::rect<irr::s32>	get_pos(irr::video::ITexture *elem, const irr::core::position2di &pos);
	static irr::core::rect<irr::s32>	get_center_img(irr::video::ITexture *img, const irr::core::position2di &size);
};
#endif /* !UTILS_HPP_ */
