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
	std::list<irr::core::position2di>	get_dirs_by_target(player *target, irr::core::position2di pos, bool dir);
	TYPE_FLOOR	*search_best_pos(std::pair<irr::s32 *, irr::s32 *> *dirs, irr::core::position2di &pos, int direction, int other_direction);
	void	get_pos_by_dir(std::pair<irr::s32 *, irr::s32 *> *first,  irr::core::position2di &pos,  irr::core::position2di &target_pos, bool dir);
	int	get_direction(std::pair<irr::s32 *, irr::s32 *> *dirs, irr::core::position2di &pos);
	std::list<irr::core::position2di>	get_dirs_fear(irr::core::position2di fear);

	bool	check_if_target_new_pos(player *target);
	bool	check_if_near_target(player *target);
	bool	check_if_near_bomb();
	player	*get_target();

	player	*_parent;
	player	*_target;
	bomb	*_fear;
	bool	_lock;
	std::size_t	_last;
	irr::core::position2di	_old_pos_target;
	std::list<irr::core::position2di>	_path;
};
#endif /* !IA_HPP_ */
