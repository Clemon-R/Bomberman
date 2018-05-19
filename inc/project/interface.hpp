/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** interface
*/

#ifndef INTERFACE_HPP_
	#define INTERFACE_HPP_

class	interface
{
public:
	virtual	~interface() =  default;
	virtual void	run() = 0;
};
#endif /* !INTERFACE_HPP_ */
