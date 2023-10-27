#include "ServerInstance.hpp"

Server	*ServerInstance::_server = NULL;

ServerInstance::ServerInstance()
{
	std::cout << "ServerInstance constructor called" << std::endl;
}

ServerInstance::~ServerInstance()
{
	std::cout << "ServerInstance destructor called" << std::endl;
}

ServerInstance::ServerInstance(const ServerInstance &copy)
{
	std::cout << "ServerInstance copy constructor called" << std::endl;
	*this = copy;
}

ServerInstance	&ServerInstance::operator=(const ServerInstance &copy)
{
	std::cout << "ServerInstance assignation operator called" << std::endl;
	if (this != &copy)
	{
		// Do stuff
	}
	return (*this);
}

void	ServerInstance::destroyInstance()
{
	if (ServerInstance::_server != NULL)
	{
		delete ServerInstance::_server;
		ServerInstance::_server = NULL;
	}
}

Server	*ServerInstance::getInstance()
{
	return (ServerInstance::_server);
}

Server	*ServerInstance::createInstance(int port, std::string password)
{
	if (ServerInstance::_server == NULL)
		ServerInstance::_server = new Server(port, password);
	return (ServerInstance::_server);
}

std::iostream &operator<<(std::iostream &stream, ServerInstance &server) {
	(void) server;
	return stream;
}