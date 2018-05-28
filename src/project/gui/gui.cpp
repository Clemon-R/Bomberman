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

gui::gui(irr::IrrlichtDevice *graphic, config *config, project *project) : _graphic(graphic),
_config(config), _driver(nullptr), _env(nullptr), _handler(std::make_unique<gui_handler>(graphic, *this)), _project(project)
{
	std::cout << "gui: init...\n";
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
	if (!_driver || !_env)
		throw exception("Impossible to find the driver");
	main_menu();
	std::cout << "gui: initiated\n";
}

gui::~gui()
{
	std::cout << "gui: destroying...\n";
	std::cout << "gui: destroyed\n";
}

void	gui::run_gui()
{
	irr::video::ITexture* images = database::load_img("bg");

	if (images)
		_driver->draw2DImage(
			images,
			irr::core::position2di(0, 0),
			utils::get_center_img(images, irr::core::position2di(_config->WINDOW_WIDTH, _config->WINDOW_HEIGHT))
		);
	_env->drawAll();
}

void	gui::run()
{
	irr::video::ITexture* images = database::load_img("bg");

	if (images)
		_driver->draw2DImage(
			images,
			irr::core::position2di(0, 0),
			utils::get_center_img(images, irr::core::position2di(_config->WINDOW_WIDTH, _config->WINDOW_HEIGHT))
		);
	_env->drawAll();
}

void	gui::main_menu()
{
	irr::video::ITexture	*img = database::load_img("btn_exit", ".png");
	irr::video::ITexture	*img1 = database::load_img("btn_play", ".png");

	if (!img || !img1)
		throw exception("Impossible to load image");
	_env->clear();
	utils::add_button(_env, img, irr::core::position2di((_config->WINDOW_WIDTH - img->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 + img->getSize().Height / 2), CodeEventGui::EXIT);
	utils::add_button(_env, img1, irr::core::position2di((_config->WINDOW_WIDTH - img1->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 - img1->getSize().Height), CodeEventGui::PLAY);
	_graphic->setEventReceiver(_handler.get());
}

void	gui::play_game()
{
	_graphic->setEventReceiver(nullptr);
	_project->set_interface(new game(_graphic, _config, _project));
}