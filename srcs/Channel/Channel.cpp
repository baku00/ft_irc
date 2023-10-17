#include "Channel.hpp"
#include "../Server/Instance/ServerInstance.hpp"

Channel::Channel()
{
	std::cout << "Create a channel instance" << std::endl;
	this->setName("");
	this->_mode = 0;
	this->_server = ServerInstance::getInstance();
}

Channel::Channel(const Channel &copy)	{ *this = copy; }
Channel::~Channel()						{}

bool	Channel::hasMode(t_mode mode)
{
	t_mode mask = ~mode | _mode;
	return (mask == BASE_MASK);
}

void				Channel::addMode(t_mode mode)		{						_mode |= mode;		}
void				Channel::delMode(t_mode mode)		{	if (hasMode(mode))	_mode ^= mode;		}
void				Channel::setName(std::string name)	{						this->_name = name;	}
std::string			Channel::getName()					{	return				this->_name;		}
std::vector<int>	Channel::getClients()				{	return				this->_clients;		}

void	Channel::addClient(int fd) {
	if (!this->hasClient(fd))
		this->_clients.push_back(fd);

	for (std::vector<Message *>::iterator it = this->_messages.begin(); it != this->_messages.end(); it++)
		Client::sendMessage(fd, (*it)->getFullname() + " PRIVMSG " + this->getName() + " :" + (*it)->getContent());
}

bool	Channel::hasClient(int fd) {
	std::vector<int>::iterator it;

	for (it = this->_clients.begin(); it != this->_clients.end(); it++)
		if (*it == fd)
			return true;

	return false;
}

bool	Channel::removeClient(int fd)
{
	std::vector<int>::iterator it;
	
	for (it = this->_clients.begin(); it != this->_clients.end(); it++)
		if (*it == fd)
			break ;

	bool isInChannel = it != this->_clients.end();

	if (isInChannel)
		this->_clients.erase(it);

	return isInChannel;
}

void	Channel::removeClient(std::map<std::string, Channel *> *channels, int fd)
{
	std::map<std::string, Channel *>::iterator it;

	for (it = channels->begin(); it != channels->end(); it++)
		it->second->removeClient(fd);
}

void	Channel::showClients()
{
	std::cout << "Clients in channel " << this->getName() << ":" << std::endl;
	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		std::cout << "\t" << this->_server->getClient(*it)->getNickname() << std::endl;
	std::cout << std::endl;
}

void	Channel::sendMessage(Client *sender, std::string message)
{
	if (message.find("\r\n") == std::string::npos)
		message += "\r\n";

	if (sender == NULL)
		return ;

	this->_messages.push_back(new Message(sender->getFd(), sender->getFullname(), message));

	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (*it != sender->getFd())
			Client::sendMessage(*it, sender->getFullname() + " PRIVMSG " + this->getName() + " :" + message);
	}
}

Channel *Channel::create(std::string name)
{
	Channel *channel = new Channel();
	channel->setName(name);
	ServerInstance::getInstance()->addChannel(channel);
	return channel;
}

bool	Channel::hasOperator(Client client)
{
	std::vector<int>::iterator it = _operators.begin();
	for (; it != _operators.end(); ++it)
	{
		if (*it == client.getFd())
			return true;
	}
	return false;
}

bool	Channel::hasInvited(Client client)
{
	std::vector<int>::iterator it = _invited.begin();
	for (; it != _invited.end(); ++it)
	{
		if (*it == client.getFd())
			return true;
	}
	return false;
}

void	Channel::invite(Client client)
{
	std::cout << "Invite client to channel #" << this->getName() << std::endl;
	int fd = client.getFd();
	if (!this->hasInvited(client))
		this->_invited.push_back(fd);
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
