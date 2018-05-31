/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** utils
*/

#include "project/utils.hpp"
#include "project/database.hpp"

void	utils::add_button(irr::gui::IGUIEnvironment *env, irr::video::ITexture *img, const irr::core::position2di &pos, irr::s32 action)
{
	if (!img)
		return;
	irr::gui::IGUIButton *btn = env->addButton(utils::get_pos(img, pos), nullptr, action, nullptr, nullptr);
	if (!btn)
		return;
	btn->setImage(img);
	btn->setUseAlphaChannel(true);
	btn->setDrawBorder(0);
}

irr::core::rect<irr::s32>	utils::get_center_img(irr::video::ITexture *img, const irr::core::position2di &size)
{
	irr::core::rect<irr::s32>	result(0, 0, 0, 0);
	std::size_t	scale_x = 1;
	std::size_t	scale_y = 1;

	if (!img)
		return (result);
	scale_x = img->getSize().Width / size.X;
	if (scale_x == 0)
		scale_x = 1;
	scale_y = img->getSize().Height / size.Y;
	if (scale_y == 0)
		scale_y = 1;
	result.UpperLeftCorner = irr::core::position2di(img->getSize().Width - scale_x * size.X, img->getSize().Height - scale_y * size.Y);
	result.LowerRightCorner = irr::core::position2di(img->getSize().Width, img->getSize().Height);
	return (result);
}

irr::core::rect<irr::s32>	utils::get_pos(irr::video::ITexture *elem, const irr::core::position2di &pos)
{
	irr::core::rect<irr::s32>	result(0, 0, 0, 0);

	if (!elem)
		return (result);
	result.UpperLeftCorner = irr::core::position2di(pos.X, pos.Y);
	result.LowerRightCorner = irr::core::position2di(pos.X + elem->getSize().Width, pos.Y + elem->getSize().Height);
	return (result);
}

irr::core::position2di	utils::convert_vector(const irr::core::vector3df &pos, config &config)
{
	irr::core::position2di	result;

	result.X = pos.Z / config.TILE_SIZE;
	result.Y = pos.X / config.TILE_SIZE;
	return (result);
}

irr::core::vector3df	utils::convert_position(const irr::core::position2di &pos, config &config)
{
	irr::core::vector3df	result;

	result.Y = config.TILE_SIZE;
	result.Z = pos.X * config.TILE_SIZE;
	result.X = pos.Y * config.TILE_SIZE;
	return (result);
}