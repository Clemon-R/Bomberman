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
#include <poll.h>
#include "exception.hpp"

server::server()
{
	std::cout << "server: init..." << std::endl;
	init_server();
	_fd_table_index = 1;
	_fd_table_size = 0;
	std::cout << "server: initiated" << std::endl;
	std::cout << "server: using socket: " << _socket << std::endl;
	std::cout << "server: waiting for connection..." << std::endl;
}

server::~server()
{
	std::cout << "server: destroying..." << std::endl;
	std::endl << "server: destroyed" << std::endl;
}

void	server::add_client()
{
	int	new_socket = 0;

	while (new_socket != -1){
		new_socket == accept(_socket, NULL, NULL);
		if (new_socket == -1){
			std::cout << "server: accept failed" << std::endl;
			break;
		}
		std::cout << "server: incomming connection" << std::endl;
		_fd_table[index].fd = new_socket;
		_fd_table[index].events = POLLIN;
		_fd_table_index += 1;
	}
}

void	server::run_poll()
{
	_poll_return = poll(_fd_table, _fd_table_index, 120000);
	if (_poll_return == -1)
		throw exception("server: poll failed");
	if (_poll_return == 0){
		std::cout << "server: no player joined in time." << std::endl;
	}

	for (int index = 0; index < _fd_table_size; index += 1){
		if (_fd_table[index].revents == 0)
			continue;
		if (_fd_table[index].revents != POLLIN)
			throw exception("server: error on poll.");
		if (_fd_table[index].fd == _socket)
			add_client();
	}
}

void	server::init_server()
{
	int	myTrue = 1;
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
		throw exception("server: couldn't start.");
	memset(_fd_table, 0, sizeof(_fd_table));
	_fd_table[0].fd = _socket;
	_fd_table[0].events = POLLIN;
	memset(&_address, 0, sizeof(struct sockaddr_in));
	_address.sin_family = AF_INET;
	_address.sin_port = htons(0);
	_address.sin_addr.s_addr = INADDR_ANY;
	if (ioctl(_socket, FIONBIO, (char *) &myTrue) == -1){
		close(_socket);
		throw exception("server: ioctl failed");
	}
	if (bind(_socket, (struct sockaddr *)&_address,	sizeof(struct sockaddr_in)) == -1)
		throw exception("server: couldn't bind socket.");
	if (listen(_socket, 3) == -1)
		throw exception("server: couldn't listen on the socket.");
}