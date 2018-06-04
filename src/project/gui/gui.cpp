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
	_graphic->setEventReceiver(_handler.get());
	main_menu();
	std::cout << "gui: initiated\n";
}

gui::~gui()
{
	std::cout << "gui: destroying...\n";
	_handler.reset(nullptr);
	std::cout << "gui: destroyed\n";
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
	irr::video::ITexture	*img2 = database::load_img("btn_load", ".png");
	irr::video::ITexture	*img3 = database::load_img("btn_multiplayer", ".png");
	std::size_t		x = 0;
	std::size_t		y = 0;

	if (!img || !img1 || !img2 || !img3)
		throw exception("Impossible to load image");
	std::cout << "gui: main menu\n";
	x = (_config->WINDOW_WIDTH - img->getSize().Width) / 2;
	y = _config->WINDOW_HEIGHT / 2;
	_env->clear();
	utils::add_button(_env, img1, irr::core::position2di(x, y - img1->getSize().Height), CodeEventGui::PLAY);
	utils::add_button(_env, img3, irr::core::position2di(x, y + img3->getSize().Height / 2), CodeEventGui::MULTIPLAYER);
	utils::add_button(_env, img2, irr::core::position2di(x, y + img2->getSize().Height * 2), CodeEventGui::LOAD);
	utils::add_button(_env, img, irr::core::position2di(x, y + img->getSize().Height * 3.5), CodeEventGui::EXIT);
}

void	gui::load_menu()
{
	irr::video::ITexture	*img = database::load_img("btn_load", ".png");
	irr::video::ITexture	*img1 = database::load_img("btn_back", ".png");
	std::size_t		x = 0;
	std::size_t		y = 0;

	if (!img || !img1)
		throw exception("Impossible to load image");
	std::cout << "gui: load menu\n";
	x = (_config->WINDOW_WIDTH - img1->getSize().Width) / 2;
	y = _config->WINDOW_HEIGHT / 2;
	_env->clear();
	_text = _env->addEditBox(L"", irr::core::recti(x, y - img1->getSize().Height, x + img->getSize().Width, y));
	utils::add_button(_env, img, irr::core::position2di(x, y + img->getSize().Height / 2), CodeEventGui::CHARGE);
	utils::add_button(_env, img1, irr::core::position2di(x, y + img1->getSize().Height * 2), CodeEventGui::BACK);
}

void	gui::multiplayer_menu()
{
	irr::video::ITexture	*img1 = database::load_img("btn_back", ".png");
	std::size_t	x = 0;

	if (!img1)
		throw exception("Impossible to load image");
	std::cout << "gui: multiplayer menu\n";
	x = (_config->WINDOW_WIDTH - img1->getSize().Width) / 2;
	_env->clear();
	utils::add_button(_env, img1, irr::core::position2di(x, _config->WINDOW_HEIGHT / 2), CodeEventGui::BACK);
}

void	gui::play_game()
{
	std::cout << "gui: starting game...\n";
	_graphic->setEventReceiver(nullptr);
	_project->set_interface(new game(_graphic, _config, _project));
}

void	gui::load_game(const std::string &filename)
{
	game	*current = nullptr;

	std::cout << "gui: loading a game...\n";
	_graphic->setEventReceiver(nullptr);
	current = new game(_graphic, _config, _project, false);
	if (!current)
		return;
	current->load_game(filename);
	_project->set_interface(current);
}

const std::string	gui::get_text()
{
	std::string	result;

	for (int i = 0;_text && _text->getText() && _text->getText()[i];i++){
		result += _text->getText()[i];
	}
	return (result);
}