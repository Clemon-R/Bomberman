/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** enum_list
*/

#ifndef ENUM_LIST_HPP_
	#define ENUM_LIST_HPP_

enum	GroundType
{
	NONE,
	FIRE,
	WALL,
	BRICK,
	TNT
};

enum	CodeEventGui
{
	EXIT = 101,
	PLAY,
	LOAD,
	CHARGE,
	BACK,
	MULTIPLAYER,
	ACTIVATE_MULTI,
	DEACTIVATE_MULTI
};

enum	CodeEventGame
{
	LEAVE = 101,
	CONTINU,
	SAVE,
	BACKGAME,
	SAVEGAME,
	BREAK
};

using	TYPE_FLOOR = std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *>;
#endif /* !ENUM_LIST_HPP_ */
