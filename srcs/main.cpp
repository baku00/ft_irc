#include <main.hpp>
#include "Server/Server.hpp"

int main(int argc, char **argv) {
	if (argc != 3)
	{
		std::cout << "Usage: ./irc [port] [password]" << std::endl;
		return (1);
	}

	Server *server = ServerInstance::createInstance(std::atoi(argv[1]), argv[2]);
	server->start();

	return 0;
}
