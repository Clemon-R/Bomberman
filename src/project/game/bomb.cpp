/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** bomb class definition
*/

#include "project/game/bomb.hpp"
#include "exception.hpp"
#include "project/database.hpp"
#include "project/utils.hpp"

bomb::bomb(irr::core::vector3df bomb_pos)
{
	put_bomb(bomb_pos);
}

bomb::~bomb()
{
	explode_bomb();
}

void	bomb::put_bomb(irr::core::vector3df bomb_pos)
{
	irr::scene::IMeshSceneNode	*current = _smgr->addCubeSceneNode(_config->TILE_SIZE);
	irr::video::ITexture	*bomb = database::load_img("tnt", ".png");

	if (!current)
		return;
	current->setPosition(bomb_pos);
	current->setMaterialTexture(0, bomb);
}

void	bomb::explode_bomb()
{
	std::cout << "Bomb exploded" << std::endl;
}