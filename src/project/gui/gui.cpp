/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** gui
*/

#include "project/gui/gui.hpp"
#include "project/database.hpp"
#include "project/utils.hpp"
#include "exception.hpp"

gui::gui(irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic),
_config(config), _driver(nullptr), _env(nullptr), _handler(graphic)
{
	std::cout << "gui: init...\n";
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
	if (!_driver || !_env)
		throw exception("Impossible to find the driver");
	irr::video::ITexture* img = database::load_img("btn_exit", ".png");
	if (!img)
		throw exception("Impossible to load image");
	utils::add_button(_env, img, irr::core::position2di((_config->WINDOW_WIDTH - img->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 + img->getSize().Height / 2), CodeEventGui::EXIT);
	img = database::load_img("btn_play", ".png");
	if (!img)
		throw exception("Impossible to load image");
	utils::add_button(_env, img, irr::core::position2di((_config->WINDOW_WIDTH - img->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 - img->getSize().Height), CodeEventGui::PLAY);
	_graphic->setEventReceiver(&_handler);
	std::cout << "gui: initiated\n";
}

gui::~gui()
{
	std::cout << "gui: destroying...\n";
	std::cout << "gui: destroyed\n";
}

void	gui::run()
{
	irr::video::ITexture* images = database::load_img("bg");
	if (!images)
		return;
	_driver->draw2DImage(
		images,
		irr::core::position2di(0, 0),
		utils::get_center_img(images, irr::core::position2di(_config->WINDOW_WIDTH, _config->WINDOW_HEIGHT))
	);
}