/*
** EPITECH PROJECT, 2018
** indie
** File description:
** server class definition
*/

#include "project/game/server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "exception.hpp"

server::server()
{
	std::cout << "server: init..." << std::endl;
	init_server();
	std::cout << "server: using socket: " << _socket << std::endl;
	std::cout << "server: initiated" << std::endl;
	std::cout << "server: waiting for connection..." << std::endl;
}

server::~server()
{
}

void	server::init_server()
{
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
		throw exception("Couldn't start server.");
	memset(&_address, 0, sizeof(struct sockaddr_in));
	_address.sin_family = AF_INET;
	_address.sin_port = htons(0);
	_address.sin_addr.s_addr = INADDR_ANY;
	if (bind(_socket, (struct sockaddr *)&_address,	sizeof(struct sockaddr_in)) == -1)
		throw exception("Couldn't bind socket.");
	if (listen(_socket, 3) == -1)
		throw exception("Couldn't listen on the socket.");
}