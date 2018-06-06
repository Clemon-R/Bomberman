/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** ia
*/

#ifndef IA_HPP_
	#define IA_HPP_

class	player;
	#include "project/game/player.hpp"
	#include "project/utils.hpp"
	#include <iostream>
	#include <list>

class	ia
{
public:
	ia(player *parent);
	~ia();

	void	run();
private:
	std::list<irr::core::position2di>	&get_all_dirs_h(irr::core::position2di &pos, std::list<irr::core::position2di> &dirs);
	std::list<irr::core::position2di>	&get_all_dirs_v(irr::core::position2di &pos, std::list<irr::core::position2di> &dirs);

	void	add_to_dirs(irr::core::position2di &pos, TYPE_FLOOR **floor, std::list<irr::core::position2di> &dirs);
	irr::core::position2di	get_cell_near_target(player *target, std::list<irr::core::position2di> &dirs);
	player	*get_target();

	player	*_parent;
	player	*_target;
	std::size_t	_last;
};
#endif /* !IA_HPP_ */
