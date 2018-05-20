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

gui::gui(irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _state(GuiState::MAIN),
_config(config), _driver(nullptr), _env(nullptr), _handler(std::make_unique<gui_handler>(graphic, *this))
{
	std::cout << "gui: init...\n";
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
	if (!_driver || !_env)
		throw exception("Impossible to find the driver");
	main_menu();
	_graphic->setEventReceiver(_handler.get());
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

void	gui::run_game()
{

	_env->drawAll();
}

void	gui::run()
{
	if (_state == GuiState::MAIN)
		run_gui();
	else
		run_game();
}

void	gui::main_menu()
{
	_env->clear();
	irr::video::ITexture* img = database::load_img("btn_exit", ".png");
	if (!img)
		throw exception("Impossible to load image");
	utils::add_button(_env, img, irr::core::position2di((_config->WINDOW_WIDTH - img->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 + img->getSize().Height / 2), CodeEventGui::EXIT);
	img = database::load_img("btn_play", ".png");
	if (!img)
		throw exception("Impossible to load image");
	utils::add_button(_env, img, irr::core::position2di((_config->WINDOW_WIDTH - img->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 - img->getSize().Height), CodeEventGui::PLAY);
}

void	gui::break_menu()
{
	_env->clear();
	irr::video::ITexture* img = database::load_img("btn_exit", ".png");
	if (!img)
		throw exception("Impossible to load image");
	utils::add_button(_env, img, irr::core::position2di((_config->WINDOW_WIDTH - img->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 + img->getSize().Height / 2), CodeEventGui::BACK);
	img = database::load_img("btn_play", ".png");
	if (!img)
		throw exception("Impossible to load image");
	utils::add_button(_env, img, irr::core::position2di((_config->WINDOW_WIDTH - img->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 - img->getSize().Height), CodeEventGui::PLAY);

}

void	gui::game_menu()
{
	_env->clear();
	irr::video::ITexture* img = database::load_img("btn_break", ".png");
	if (!img)
		throw exception("Impossible to load image");
	utils::add_button(_env, img, irr::core::position2di(0, 0), CodeEventGui::PAUSE);
}

void	gui::set_state(GuiState state)
{
	_state = state;
	switch (state){
		case GuiState::BREAK:
		break_menu();
		break;
		case GuiState::MAIN:
		main_menu();
		break;
		case GuiState::GAME:
		game_menu();
		break;
	}
}