/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** game
*/

#include "project/game/game.hpp"
#include "project/utils.hpp"
#include "project/database.hpp"
#include "exception.hpp"

game::game(irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _config(config)
{
	std::cout << "game: init...\n";
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
	if (!_driver || !_env)
		throw exception("Impossible to find the driver");
	std::cout << "game: initiated\n";
}

game::~game()
{
	std::cout << "game: destroying\n";
	std::cout << "game: destroyed\n";
}

void	game::run()
{

}

void	game::spawnAll()
{
	irr::video::ITexture	*img = database::load_img("ground");
	std::size_t	offset = 0;

	if (!img)
		throw exception("Impossible to load the ground");
	offset = (_config->WINDOW_WIDTH - img->getSize().Width * 30) / 2;
	for (int i = 0;i < 900;i += 1){
		_driver->draw2DImage(
			img,
			irr::core::position2di(offset + img->getSize().Width * (i % 30), i / 30 * img->getSize().Height),
			utils::get_center_img(img, irr::core::position2di(img->getSize().Width, img->getSize().Height))
		);
	}
}