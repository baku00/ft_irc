#include <main.hpp>
#include "Server/Server.hpp"
#include <tests.hpp>

int main(int argc, char **argv) {

	if (argc == 2 && argv[1] == std::string("--test"))
	{
		test_mode();
		return 0;
	}

	const bool DEV_MODE = true;
	if (argc != 3 && !DEV_MODE)
	{
		std::cout << "Usage: ./irc [port] [password]" << std::endl;
		return (1);
	}

	const int PORT				= DEV_MODE ? 6667 : std::atoi(argv[1]);
	const std::string PASSWORD	= DEV_MODE ? "password" : argv[2];

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

	server->stop("", 0);

	return 0;
}
