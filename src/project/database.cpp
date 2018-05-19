/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** database
*/

#include "project/database.hpp"

irr::IrrlichtDevice	*database::_graphic = nullptr;
config			*database::_config = nullptr;
std::map<std::string, irr::video::ITexture *>	database::_list_imgs;

irr::video::ITexture	*database::load_img(const std::string &name, const std::string ext)
{
	irr::video::ITexture	*img = nullptr;
	irr::video::IVideoDriver	*driver = nullptr;
	std::string		path(PATH_IMG);
	std::map<std::string, irr::video::ITexture *>::iterator	it;

	if (!_graphic || !(driver = _graphic->getVideoDriver()))
		return (img);
	path.append("/").append(name);
	path.append("_").append(std::to_string(_config->GAME_SCALE));
	path.append(ext);
	if ((it = _list_imgs.find(path)) != _list_imgs.end())
		return (it->second);
	img = driver->getTexture(path.c_str());
	if (img)
		_list_imgs.insert(std::make_pair(path, img));
	return (img);
}

void	database::set_config(irr::IrrlichtDevice *graphic, config *config)
{
	_graphic = graphic;
	_config = config;
}