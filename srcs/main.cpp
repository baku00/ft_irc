#include <main.hpp>
#include "Server/Server.hpp"
#include <tests.hpp>

int get_port(char *port)
{
	int	_port = std::atoi(port);

	if (_port >= 0 && _port <= 65535)
		return _port;
	return -1;
}

int main(int argc, char **argv) {
	if (argc != 3)
	{
		std::cout << "Usage: ./irc [port] [password]" << std::endl;
		return (1);
	}

	const int PORT				= get_port(argv[1]);
	if (PORT == -1)
	{
		std::cout << "Invalid port" << std::endl;
		return 1;
	}
	const std::string PASSWORD	= argv[2];

		Server	*server;
	
	try
	{
		server = ServerInstance::createInstance(PORT, PASSWORD);
		server->start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "Stop server 1" << std::endl;
	ServerInstance::destroyInstance();
	std::cout << "Stop server" << std::endl;

	return 0;
}
