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
	std::cout << "Destroying ServerInstance" << std::endl;
	if (ServerInstance::_server != NULL)
	{
		std::cout << "Destroy Instance" << std::endl;
		delete ServerInstance::_server;
		ServerInstance::_server = NULL;
	}
	std::cout << "ServerInstance destroyed" << std::endl;
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
