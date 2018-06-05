/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** project
*/

#include "project/project.hpp"
#include "project/database.hpp"

project::project() : _graphic(nullptr), _config(nullptr), _interface(nullptr)
{
	std::cout << "project: init...\n";
	_config.reset(saver::load_config());
	if (_config)
		_config->refresh_config();
	std::cout << "project: initiated\n";
}

project::~project()
{
	std::cout << "project: destructing...\n";
	if (_config)
		saver::save_config(*_config);
	_config.reset(nullptr);
	_interface.reset(nullptr);
	_graphic.reset(nullptr);
	std::cout << "project: destructed\n";
}

void	project::init_of_graphic()
{
	std::cout << "project: init of the graphic...\n";
	_graphic.reset(
		irr::createDevice(
			irr::video::EDT_OPENGL,
			irr::core::dimension2d<irr::u32>(_config->WINDOW_WIDTH, _config->WINDOW_HEIGHT),
			16,
			_config->FULL_SCREEN == "1",
			false,
			VERTICAL_SYNC,
			nullptr
		)
	);
	if (!_graphic)
		throw exception("Impossible to create the graphic");
	_graphic->setWindowCaption(L"The bomberman - by Epitech students");
	_graphic->setResizable(false);
	database::set_config(_graphic.get(), _config.get());
	_interface.reset(new gui(_graphic.get(),_config.get(), this));
	std::cout << "project: graphic initiated\n";
}

void	project::run()
{
	irr::video::IVideoDriver	*driver = nullptr;

	if (!_graphic)
		throw exception("Impossible to run the project, don't have graphic");
	driver = _graphic->getVideoDriver();
	if (!driver)
		throw exception("Impossible to get the video driver");
	std::cout << "project: running...\n";
	while (_graphic->run()){
		driver->beginScene(true, true, irr::video::SColor(255,0,0,0));
		if (_interface)
			_interface->run();
		driver->endScene();
	}
	std::cout << "project: end running\n";
}

void	project::set_interface(interface *window)
{
	_interface.reset(window);
}