#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include "Server/Server.hpp"

int main(int argc, char **argv) {
	if (argc != 3)
	{
		std::cout << "Usage: ./irc [port] [password]" << std::endl;
		return (1);
	}

	Server server(std::atoi(argv[1]), argv[2]);
	server.start();

	return 0;
}
