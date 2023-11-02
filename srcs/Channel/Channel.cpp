#include "Channel.hpp"
#include "../Server/Instance/ServerInstance.hpp"

Channel::Channel()
{
	std::cout << "Create a channel instance" << std::endl;
	this->setName("");
	this->setTopic("*");
	this->setPassword("");
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

void	Channel::	addClient(int fd) {
	if (!this->hasClient(fd))
	{
		this->_clients.push_back(fd);
		this->sendTopicToClient(fd);
	}
}

void	Channel::sendTopicToClient(int fd)
{
	Client *client = this->_server->getClient(fd);
	client->reply(RPL_TOPIC, this->getName().c_str(), this->getTopic().c_str());
}

bool	Channel::hasClient(int fd) {
	std::vector<int>::iterator it;

	for (it = this->_clients.begin(); it != this->_clients.end(); it++)
		if (*it == fd)
			return true;

	return false;
}

bool	Channel::hasClient(Client & client) {
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
		if (member_client)
			member_client->sendChanMsg(sender, this->getName(), message);
	}
}

void Channel::broadcastMessage(Client *sender, const std::string& message)
{
	std::vector<int>::iterator  member;
	std::vector<int>            members = this->getClients();
	for (member = members.begin(); member != members.end(); member++)
	{
		Client * member_client = this->_server->getClient(*member);
		if (member_client)
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
		if (member_client == NULL)
			continue;
		if (member != members.begin())
			oss << " ";
		if (this->hasOperator(*member))
			oss << "@";
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

void	Channel::addOperator(int fd)
{
	Client *client = ServerInstance::getInstance()->getClient(fd);
	if (!client)
		return;
	if (!this->hasOperator(*client))
	{
		this->_operators.push_back(fd);
		client->reply(RPL_ADDOPERATOR, client->getNickname().c_str(), this->getName().c_str());
	}
}

void	Channel::removeOperator(int fd)
{
	std::vector<int>::iterator it = _operators.begin();
	for (; it != _operators.end(); ++it)
	{
		if (*it == fd)
		{
			_operators.erase(it);
			return;
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

void	Channel::removeInvited(Client client)
{
	std::vector<int>::iterator it = _invited.begin();
	for (; it != _invited.end(); ++it)
	{
		if (*it == client.getFd())
		{
			_invited.erase(it);
			return;
		}
	}
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

std::string	Channel::getTopic()
{
	return this->_topic;
}

void	Channel::sendTopic()
{
	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		Client *client = this->_server->getClient(*it);
		if (client)
			client->reply(RPL_TOPIC, this->getName().c_str(), this->getTopic().c_str());
	}
}

void	Channel::setPassword(std::string password)
{
	this->_password = password;
}

std::string	Channel::getPassword()
{
	return this->_password;
}

bool	Channel::isPassword(std::string password)
{
	return this->_password == password;
}

void	Channel::setLimit(std::size_t limit)
{
	this->_limit = limit;
}

std::size_t	Channel::getLimit()
{
	return this->_limit;
}

bool		Channel::isFull()
{
	return this->_limit > 0 && this->_clients.size() >= this->_limit;
}

bool		Channel::canJoin(Client &client)
{
	bool	can_join = false;

	if (this->hasMode(Channel::I_INVITE) && !this->hasInvited(client))
		client.reply(ERR_INVITEONLYCHAN, this->getName().c_str());
	else if (this->hasMode(Channel::L_LIMIT) && this->isFull())
		client.reply(ERR_CHANNELISFULL, this->getName().c_str());
	else
		can_join = true;

	return can_join;
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
