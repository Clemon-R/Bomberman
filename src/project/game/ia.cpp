/*
** EPITECH PROJECT, 2018
** indie studip
** File description:
** ia
*/

#include "project/game/ia.hpp"
#include <algorithm>
#include <cstdlib>

ia::ia(player *parent) : _parent(parent), _last(utils::get_milliseconds()), _target(nullptr)
{
	std::cout << "ia: init...\n";
	if (_parent)
		return;
	std::cout << "ia: initiated\n";
}

ia::~ia()
{
	std::cout << "ia: destructing...\n";
	std::cout << "ia: destructed\n";
}

void	ia::run()
{
	irr::core::position2di	pos = _parent->get_position();
	std::list<irr::core::position2di>	dirs;
	std::list<irr::core::position2di>::iterator	it;

	if (_parent->is_moving())
		_last = utils::get_milliseconds();
	if (utils::get_milliseconds() - _last < 750)
		return;
	_last = utils::get_milliseconds();
	if (!_target)
		_target = get_target();
	get_all_dirs_h(pos, dirs);
	get_all_dirs_v(pos, dirs);
	if (dirs.size() == 0 || !_target)
		return;
	pos = get_cell_near_target(_target, dirs);
	_parent->move_to(pos);
}

player	*ia::get_target()
{
	std::list<std::unique_ptr<player>>::iterator	it = _parent->get_parent()->get_players().begin();

	std::advance(it, std::rand() % _parent->get_parent()->get_players().size());
	if (it != _parent->get_parent()->get_players().end() && it->get() != _parent)
		return (it->get());
	return (nullptr);
}

irr::core::position2di	ia::get_cell_near_target(player *target, std::list<irr::core::position2di> &dirs)
{
	irr::core::position2di	pos  = dirs.front();
	irr::core::position2di	target_pos = target->get_position();
	double			cell_x = abs(target_pos.X - pos.X);
	double			cell_y = abs(target_pos.Y - pos.Y);
	double			old = cell_x + cell_y;

	for (auto &dir : dirs){
		cell_x = abs(target_pos.X - dir.X);
		cell_y = abs(target_pos.Y - dir.Y);
		if (cell_x + cell_y < old){
			pos = dir;
			old = cell_x + cell_y;
		}
	}
	return (pos);
}

std::list<irr::core::position2di>	&ia::get_all_dirs_h(irr::core::position2di &pos, std::list<irr::core::position2di> &dirs)
{
	TYPE_FLOOR	*floor = _parent->get_parent()->get_floor(pos.X, pos.Y);
	TYPE_FLOOR	*left = floor;
	TYPE_FLOOR	*right = floor;
	irr::core::position2di	pos_l;
	irr::core::position2di	pos_r;

	for (int i = 0;floor && (left || right);i++){
		pos_l = irr::core::position2di(pos.X + i, pos.Y);
		pos_r = irr::core::position2di(pos.X - i, pos.Y);
		add_to_dirs(pos_l, &left, dirs);
		add_to_dirs(pos_r, &right, dirs);
	}
}

std::list<irr::core::position2di>	&ia::get_all_dirs_v(irr::core::position2di &pos, std::list<irr::core::position2di> &dirs)
{
	TYPE_FLOOR	*floor = _parent->get_parent()->get_floor(pos.X, pos.Y);
	TYPE_FLOOR	*left = floor;
	TYPE_FLOOR	*right = floor;
	irr::core::position2di	pos_l;
	irr::core::position2di	pos_r;

	for (int i = 0;floor && (left || right);i++){
		pos_l = irr::core::position2di(pos.X, pos.Y + i);
		pos_r = irr::core::position2di(pos.X, pos.Y - i);
		add_to_dirs(pos_l, &left, dirs);
		add_to_dirs(pos_r, &right, dirs);
	}
}

void	ia::add_to_dirs(irr::core::position2di &pos, TYPE_FLOOR **floor, std::list<irr::core::position2di> &dirs)
{
	if (floor && *floor)
		*floor = _parent->get_parent()->get_floor(pos.X, pos.Y);
	if (floor && *floor && std::get<2>(**floor) < GroundType::WALL)
		dirs.push_back(pos);
	else
		*floor = nullptr;
}