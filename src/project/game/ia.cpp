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

	if (utils::get_milliseconds() - _last < 500)
		return;
	if (!_target || !_target->is_alive()){
		_target = get_target();
		if (_target && _target->is_alive())
			_old_pos_target = _target->get_position();
	}
	if (!_target)
		return;
	if (_path.size() == 0 || check_if_target_new_pos(_target)){
		_path = get_dirs_by_target(_target, pos, true);
		if (_path.size() == 0)
			_path = get_dirs_by_target(_target, pos, false);
		_old_pos_target = _target->get_position();
	}
	if (!_parent->is_moving() && _path.size() > 0){
		std::cout << "ia: moving to pos X - " << _path.back().X << ", pos Y - " << _path.back().Y << std::endl;
		_parent->move_to(_path.back());
		_path.pop_back();
	}
	if (_target && check_if_near_target(_target))
		_parent->drop_bomb();
	if (_path.size() == 0 && check_if_near_bomb())
		_path = get_dirs_fear(pos);
	_last = utils::get_milliseconds();
}

std::list<irr::core::position2di>	ia::get_dirs_fear(irr::core::position2di &fear)
{
	std::list<irr::core::position2di>	result;
	irr::core::position2di	pos = fear;
	irr::s32	*axe = nullptr;
	TYPE_FLOOR	*tmp = nullptr;
	TYPE_FLOOR	*current = _parent->get_parent()->get_floor(fear.X, fear.Y);

	if (!current)
		return (result);
	axe = std::rand() % 2 ? &pos.X : &pos.Y;
	*axe += std::rand() % 2 ? 1 : -1;
	for (int i = 0;i < 6;i++){
		tmp = _parent->get_parent()->get_floor(pos.X, pos.Y);
		if (tmp && std::get<2>(*tmp) < GroundType::WALL)
			result.push_back(pos);
		axe = std::rand() % 2 ? &pos.X : &pos.Y;
		*axe += std::rand() % 2 ? 1 : -1;
	}
	return (result);
}

bool	ia::check_if_near_bomb()
{
	std::list<bomb *>	bombs = _parent->get_parent()->get_bombs();
	irr::core::position2di	bomb_pos;
	irr::core::position2di	pos;

	pos = _parent->get_position();
	for (auto &bomb : bombs){
		bomb_pos = bomb->get_position();
		if (abs(bomb_pos.X - pos.X) + abs(bomb_pos.Y - pos.Y) <= 1)
			return (true);
	}
	return (false);
}

bool	ia::check_if_near_target(player *target)
{
	irr::core::position2di	pos;
	irr::core::position2di	target_pos;

	if (!target)
		return (false);
	pos = _parent->get_position();
	target_pos = target->get_position();
	if (abs(pos.X - target_pos.X) + abs(pos.Y - target_pos.Y) <= 1)
		return (true);
	return (false);
}

bool	mycomparison(const irr::core::position2di &first, const irr::core::position2di &second)
{
	return (true); 
}

void	ia::get_pos_by_dir(std::pair<irr::s32 *, irr::s32 *> *dirs,
		irr::core::position2di &pos,
		irr::core::position2di &target_pos,
		bool dir)
{
	if (dir){
		dirs[0] = std::pair<irr::s32 *, irr::s32 *>(&pos.X, &pos.Y);
		dirs[1] = std::pair<irr::s32 *, irr::s32 *>(&target_pos.X, &target_pos.Y);
	} else {
		dirs[0] = std::pair<irr::s32 *, irr::s32 *>(&pos.Y, &pos.X);
		dirs[1] = std::pair<irr::s32 *, irr::s32 *>(&target_pos.Y, &target_pos.X);
	}
}

int	ia::get_direction(std::pair<irr::s32 *, irr::s32 *> *dirs, irr::core::position2di &pos)
{
	int	direction = direction = *dirs[1].first - *dirs[0].first;
	TYPE_FLOOR	*current = nullptr;

	if (direction == 0){
		*dirs[0].first += 1;
		current = _parent->get_parent()->get_floor(pos.X, pos.Y);
		if (current && std::get<2>(*current) < GroundType::WALL)
			direction = 1;
		*dirs[0].first -= 2;
		current = _parent->get_parent()->get_floor(pos.X, pos.Y);
		if (direction == 0 && current && std::get<2>(*current) < GroundType::WALL)
			direction = -1;
		*dirs[0].first += 1;		
	}
	if (direction == 0)
		return (0);
	return (direction > 0 ? 1 : -1);
}

TYPE_FLOOR	*ia::search_best_pos(std::pair<irr::s32 *, irr::s32 *> *dirs, irr::core::position2di &pos, int direction, int other_direction)
{
	TYPE_FLOOR	*current = nullptr;
	TYPE_FLOOR	*side = nullptr;
	TYPE_FLOOR	*choosen = nullptr;
	std::size_t	tmp;
	std::size_t	distance = 0;

	std::cout << "ia: axe " << (&pos.X == dirs[0].first ? "X" : "Y") << std::endl;
	std::cout << "ia: direction - " << direction << std::endl;
	*dirs[0].first += direction;
	current = _parent->get_parent()->get_floor(pos.X, pos.Y);
	for (;current;){
		std::cout << "ia: checking pos X - " << pos.X << ", pos Y - " << pos.Y << std::endl;
		tmp = abs(*dirs[0].first - *dirs[1].first) + abs(*dirs[0].second - *dirs[1].second);
		if (tmp == 0 || std::get<2>(*current) >= GroundType::WALL)
			break;
		side = nullptr;
		if (other_direction != 0){
			*dirs[0].second += other_direction;
			side = _parent->get_parent()->get_floor(pos.X, pos.Y);
			*dirs[0].second -= other_direction;
		}
		if ((distance == 0 || tmp < distance) && tmp > 0 && (!side || std::get<2>(*side) < GroundType::WALL)){
			distance = tmp;
			choosen = current;
		}
		*dirs[0].first += direction;
		current = _parent->get_parent()->get_floor(pos.X, pos.Y);
	}
	return (choosen);
}

std::list<irr::core::position2di>	ia::get_dirs_by_target(player *target, irr::core::position2di pos, bool dir)
{
	std::list<irr::core::position2di>	result;
	TYPE_FLOOR				*choosen = nullptr;
	irr::core::position2di			target_pos;
	std::pair<irr::s32 *, irr::s32 *>	dirs[2];
	int	direction = 0;
	int	other_direction = 0;

	if (!target)
		return (result);
	std::cout << "ia: find new path...\n";
	target_pos = target->get_position();
	std::cout << "ia: finding the axe...\n";
	get_pos_by_dir(dirs, pos, target_pos, dir);
	if (!dirs[0].first || !dirs[0].second || !dirs[1].first || !dirs[1].second)
		return (result);
	std::cout << "ia: finding the direction...\n";
	direction = get_direction(dirs, pos);
	if (*dirs[1].second != *dirs[0].second)
		other_direction *= *dirs[1].second > *dirs[0].second ? 1 : -1;
	std::cout << "ia: finding the best next pos...\n";
	if (direction != 0)
		choosen = search_best_pos(dirs, pos, direction, other_direction);
	if (choosen){
		std::cout << "ia: choosen pos X - " << std::get<0>(*choosen) << ", pos Y - " << std::get<1>(*choosen) << std::endl;
		result.push_back(irr::core::position2di(std::get<0>(*choosen), std::get<1>(*choosen)));
		if (abs(std::get<0>(*choosen) - target_pos.X) + abs(std::get<1>(*choosen) - target_pos.Y) > 1)
			result.merge(get_dirs_by_target(target, result.back(), !dir), &mycomparison);
	}
	return (result);
}

bool	ia::check_if_target_new_pos(player *target)
{
	irr::core::position2di	pos = target->get_position();

	std::cout << "ia: checking...\n";
	if (pos != _old_pos_target)
		return (true);
	return (false);
}

player	*ia::get_target()
{
	std::list<std::unique_ptr<player>>::iterator	it = _parent->get_parent()->get_players().begin();

	std::cout << "ia: getting new target...\n";
	std::advance(it, std::rand() % _parent->get_parent()->get_players().size());
	if (it != _parent->get_parent()->get_players().end() && it->get() != _parent && (*it)->is_alive())
		return (it->get());
	std::cout << "ia: no target found\n";
	return (nullptr);
}