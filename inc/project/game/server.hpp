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
	void	run_poll();
private:
	void	init_server();
	void	add_client();

	int	_socket;
	struct sockaddr_in	_address;

	struct pollfd		_fd_table[4];
	int	_fd_table_size;
	int	_fd_table_index;

	int	_poll_return;
};
#endif