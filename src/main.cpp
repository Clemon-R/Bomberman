/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** main
*/

#include "main.hpp"

static char	demo()
{
	irr::IrrlichtDevice *device =
        irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(640, 480), 16,
            false, false, false, 0);

	if (!device)
		return (1);
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
	irr::core::rect<irr::s32>(10,10,260,22), true);
	irr::scene::IAnimatedMesh* mesh = smgr->getMesh("./test/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return (1);
	}
	irr::scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
	if (node)
	{
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		node->setMD2Animation(irr::scene::EMAT_STAND);
		node->setMaterialTexture( 0, driver->getTexture("./test/sydney.bmp") );
	}
	smgr->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));
	while(device->run())
	{
		driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}
	device->drop();
	return (0);
}

int	main(int argc, char **argv)
{
	std::unique_ptr<game>	project;

	std::cout << "main: init of the project...\n";
	try{
		project.reset(new game());
		if (!project)
			return (84);
		project->init_of_graphic();
		project->run();
	}
	catch (const std::exception &error){
		std::cerr << "main: error happend on the game.\n";
		std::cerr << error.what() << std::endl;
		return (84);
	}
	return (0);
}