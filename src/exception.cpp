/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** exception
*/

#include "exception.hpp"

exception::exception(const std::string &msg) : _msg(msg)
{
}

const char	*exception::what() const noexcept
{
	return (_msg.c_str());
}