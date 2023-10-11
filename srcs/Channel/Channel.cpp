#include "Channel.hpp"
#include "../Server/Instance/ServerInstance.hpp"

Channel::Channel()
{
	std::cout << "Create a channel instance" << std::endl;
	this->setName("");

}

Channel::Channel(const Channel &copy) {
	*this = copy;
}

Channel::~Channel()
{}

void	Channel::setName(std::string name) {
	this->_name = name;
}

std::string	Channel::getName() {
	return this->_name;
}

void	Channel::addClient(int fd) {
	std::cout << "Add new Client to channel" << std::endl;
	if (!this->hasClient(fd))
		this->_clients.push_back(fd);
	for (std::vector<Message *>::iterator it = this->_messages.begin(); it != this->_messages.end(); it++)
		Client::sendMessage(fd, ServerInstance::getInstance()->getClient((*it)->getSender())->getFullname() + " PRIVMSG " + this->getName() + " :" + (*it)->getContent());
	
}

std::vector<int>	Channel::getClients() {
	return this->_clients;
}

bool	Channel::hasClient(int fd) {
	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (*it == fd)
			return true;
	}
	return false;
}

void	Channel::showClients()
{
	std::cout << "Clients in channel " << this->getName() << ":" << std::endl;
	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		std::cout << "\t" << ServerInstance::getInstance()->getClient(*it)->getNickname() << std::endl;
	std::cout << std::endl;
}

void	Channel::sendMessage(Client *sender, std::string message)
{
	if (message.find("\r\n") == std::string::npos)
		message += "\r\n";

	if (sender == NULL)
		return ;

	this->_messages.push_back(new Message(sender->getFd(), message));

	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (*it != sender->getFd())
			Client::sendMessage(*it, sender->getFullname() + " PRIVMSG " + this->getName() + " :" + message);
	}
}

Channel &Channel::operator=(const Channel &copy) {
	if (this != &copy) {
		this->_name			= copy._name;
		this->_clients			= copy._clients;
	}
	return *this;
}

std::iostream &operator<<(std::iostream &stream, Channel &client) {
	(void) client;
	return stream;
}
