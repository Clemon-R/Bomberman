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

game::game(irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _config(config),
_scale_width(0), _scale_height(0), _cell_height(0), _cell_width(0)
{
	std::cout << "game: init...\n";
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
    	_smgr = _graphic->getSceneManager();
	if (!_driver || !_env || !_smgr)
		throw exception("Impossible to find the driver");
	generateFloor();
	irr::scene::IAnimatedMeshSceneNode* anms =
        _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("test/sydney.md2"));
	if (anms)
	{
		irr::scene::ISceneNodeAnimator* anim =
		_smgr->createFlyStraightAnimator(irr::core::vector3df(_scale_height * _cell_height / 2,_cell_height,_scale_height * _cell_height / 2),
		irr::core::vector3df((_scale_height - 2) * _cell_height, _cell_height,_scale_height * _cell_height / 2), 3000, false);
		if (anim){
			anms->addAnimator(anim);
			anim->drop();
		}
		anms->setMaterialFlag(irr::video::EMF_LIGHTING, false);

		anms->setFrameLoop(0, 25);
		anms->setAnimationSpeed(15);
		//anms->setMD2Animation(irr::scene::EMAT_STAND);
		anms->setMD2Animation(irr::scene::EMAT_RUN);

		anms->setScale(irr::core::vector3df(1, 1, 1));
		anms->setRotation(irr::core::vector3df(0,0,0));
		//anms->setPosition(irr::core::vector3df(0, 0, 0));
		anms->setMaterialTexture(0, _driver->getTexture("test/sydney.bmp"));

	}
	/*irr::scene::ICameraSceneNode* fpsCamera = _smgr->addCameraSceneNodeFPS();
    	fpsCamera->setPosition(irr::core::vector3df(-50,100,-150));*/
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

void	game::generateFloor()
{
	irr::video::ITexture	*ground = database::load_img("ground");
	irr::video::ITexture	*wall = database::load_img("wall", ".png");
	std::size_t	offset = 0;

	if (!ground || !wall)
		throw exception("Impossible to load image");
	_scale_width = _config->WINDOW_HEIGHT / ground->getSize().Height;
	_scale_height = _config->WINDOW_HEIGHT / ground->getSize().Height;
	_cell_width = ground->getSize().Width;
	_cell_height = ground->getSize().Height;
	for (int i = 0;i < _scale_width * _scale_height;i += 1){
		if (i % _scale_width == 0 || i / _scale_height == 0
		|| i % _scale_width == _scale_width - 1 || i / _scale_height == _scale_height - 1)
			_floor.push_back(std::make_tuple(GroundType::WALL, wall));
		else
			_floor.push_back(std::make_tuple(GroundType::GROUND, ground));
	}
	drawWall();
	setCamera();
}

void	game::setCamera()
{
	irr::scene::ICameraSceneNode	*cam = _smgr->addCameraSceneNode();
	std::size_t			mid = _scale_height * _cell_height / 2;

	cam->setPosition(irr::core::vector3df(mid, _scale_height * _cell_height * 0.74, mid));
	cam->setTarget(irr::core::vector3df(mid, 0, mid));
}

void	game::drawWall()
{
	std::list<std::tuple<GroundType, irr::video::ITexture *>>::iterator	it = _floor.begin();
	irr::scene::IMeshSceneNode *current = nullptr;

	for (int i = 0;it != _floor.end() && i < _scale_width * _scale_height;i += 1){
		current = _smgr->addCubeSceneNode(_cell_height);
		if (!current)
			continue;
		current->setPosition(irr::core::vector3df(
			i / _scale_height * _cell_height,
			std::get<0>(*it) != GroundType::GROUND ? _cell_height : 0
			, _cell_width * (i % _scale_width)
		));
		current->setMaterialTexture(0, std::get<1>(*it));
		it++;
	}
}

void	game::spawnAll()
{
}