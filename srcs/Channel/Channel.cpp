#include "Channel.hpp"
#include "../Server/Instance/ServerInstance.hpp"

Channel::Channel()
{
	std::cout << "Create a channel instance" << std::endl;
	this->setName("");
	this->setTopic("*");
	this->_mode = 0;
	this->_server = ServerInstance::getInstance();
	this->_limit = 0;
	this->_password = "";
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
}

bool	Channel::hasClient(int fd) {
	std::vector<int>::iterator it;

	for (it = this->_clients.begin(); it != this->_clients.end(); it++)
		if (*it == fd)
			return true;

	return false;
}

bool	Channel::hasClient(Client client) {
	return this->hasClient(client.getFd());
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

void	Channel::showClients()
{
	std::cout << "Clients in channel " << this->getName() << ":" << std::endl;
	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		std::cout << "\t" << this->_server->getClient(*it)->getNickname() << std::endl;
	std::cout << std::endl;
}

void Channel::broadcastChanMsg(Client *sender, const std::string& message)
{
	std::vector<int>::iterator  member;
	std::vector<int>            members = this->getClients();
	for (member = members.begin(); member != members.end(); member++)
	{
		if (*member == sender->getFd())
			continue;
		Client * member_client = this->_server->getClient(*member);
		member_client->sendChanMsg(sender, this->getName(), message);
	}
}

void Channel::broadcastMessage(Client *sender, const std::string& message)
{
	std::vector<int>::iterator	member;
	std::vector<int>			members = this->getClients();
	for (member = members.begin(); member != members.end(); member++)
	{
		Client * member_client = this->_server->getClient(*member);
		member_client->sendMessage(sender, message);
	}
}

std::string Channel::getNicknames()
{
	std::ostringstream oss;

	std::vector<int>::iterator  member;
	std::vector<int>            members = this->getClients();
	for (member = members.begin(); member != members.end(); member++)
	{
		Client * member_client = this->_server->getClient(*member);
		if (member != members.begin())
			oss << " ";
		oss << member_client->getNickname();
	}

	return oss.str();
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

void	Channel::addOperator(Client client)
{
	std::cout << "Add operator to channel " << this->getName() << std::endl;
	int fd = client.getFd();
	if (!this->hasOperator(client))
		this->_operators.push_back(fd);
}

void	Channel::delOperator(Client client)
{
	std::cout << "Remove operator from channel " << this->getName() << std::endl;
	int fd = client.getFd();
	std::vector<int>::iterator it = _operators.begin();
	for (; it != _operators.end(); ++it)
	{
		if (*it == fd)
		{
			_operators.erase(it);
			break;
		}
	}
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
	std::cout << "Invite client to channel " << this->getName() << std::endl;
	int fd = client.getFd();
	if (!this->hasInvited(client))
		this->_invited.push_back(fd);
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

std::string	Channel::getTopic()
{
	return this->_topic;
}

void	Channel::setPassword(std::string password)
{
	this->_password = password;
}

bool	Channel::isPassword(std::string password)
{
	return this->_password == password;
}

void	Channel::sendTopic()
{
	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		Client *client = this->_server->getClient(*it);
		client->reply(RPL_TOPIC, this->getName().c_str(), this->getTopic().c_str());
	}
}

void	Channel::setLimit(size_t limit)
{
	this->_limit = limit;
}

size_t		Channel::getLimit()
{
	return this->_limit;
}

bool	Channel::isFull()
{
	return this->_limit != 0 && this->_clients.size() >= this->_limit;
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
