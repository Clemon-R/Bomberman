/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** utils
*/

#ifndef UTILS_HPP_
	#define UTILS_HPP_

	#include "irrlicht/irrlicht.h"

class	utils
{
public:
	static irr::core::rect<irr::s32>	get_pos(irr::video::ITexture *elem, const irr::core::position2di &pos);
	static irr::core::rect<irr::s32>	get_center_img(irr::video::ITexture *img, const irr::core::position2di &size);
};
#endif /* !UTILS_HPP_ */
