/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** gui_handler
*/

#ifndef GUI_HANDLER_HPP_
	#define GUI_HANDLER_HPP_

	#include "irrlicht/irrlicht.h"

enum	CodeEventGui
{
	EXIT = 101
};

class	gui_handler : public irr::IEventReceiver
{
public:
	gui_handler(irr::IrrlichtDevice *graphic);
	bool	OnEvent(const irr::SEvent& event) override final;
private:
	irr::IrrlichtDevice	*_graphic;
};
#endif /* !GUI_HANDLER_HPP_ */
