/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** exception
*/

#ifndef EXCEPTION_HPP_
	#define EXCEPTION_HPP_

	#include <exception>
	#include <iostream>

class	exception : public std::exception
{
public:
	exception(const std::string &);

	const char	*what() const noexcept override;
private:
	std::string	_msg;
};
#endif /* !EXCEPTION_HPP_ */
