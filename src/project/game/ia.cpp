/*
** EPITECH PROJECT, 2018
** indie studip
** File description:
** ia
*/

#include "project/game/ia.hpp"
#include <algorithm>
#include <cstdlib>

ia::ia(player *parent) : _parent(parent), _last(utils::get_milliseconds())
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
	auto	floor = _parent->get_parent()->get_floor(pos.X, pos.Y);
	std::list<irr::core::position2di>	dirs;
	std::list<irr::core::position2di>::iterator	it;

	if (utils::get_milliseconds() - _last < 750)
		return;
	_last = utils::get_milliseconds();
	for (int i = 0;i < 4;i += 1){
		pos.X += i % 2 - 2 * (i == 3);
		pos.Y += (i + 1) % 2 - 2 * (i == 2);
		floor = _parent->get_parent()->get_floor(pos.X, pos.Y);
		if (floor && std::get<2>(*floor) == GroundType::NONE)
			dirs.push_back(irr::core::position2di(pos.X, pos.Y));
		pos.X -= i % 2 - 2 * (i == 3);
		pos.Y -= (i + 1) % 2 - 2 * (i == 2);
	}
	if (dirs.size() == 0)
		return;
	it = dirs.begin();
	std::advance(it, std::rand() % dirs.size());
	if (!_parent->is_moving())
		_parent->move_to(*it);
}