/*
** EPITECH PROJECT, 2018
** indie
** File description:
** server class declaration
*/

#ifndef SERVER_HPP_
	#define SERVER_HPP_

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netinet/ip.h>

class server
{
public:
	server();
	~server();
private:
	void	init_server();
	int	_socket;
	struct sockaddr_in	_address;
};
#endif