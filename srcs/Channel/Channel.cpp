#include "Channel.hpp"

Channel::Channel()
{
	this->_name = "";
	this->_topic = "";
}

Channel::Channel(std::string name, bool by_name) {
	(void) by_name;
	this->_name = name;
	this->_topic = "";
}

Channel::Channel(const Channel &copy) {
	*this = copy;
}

Channel::~Channel() {}

Channel &Channel::operator=(const Channel &copy) {
	if (this != &copy) {
		this->_name = copy._name;
	}
	return *this;
}

std::string	Channel::getName() {
	return this->_name;
}

bool	Channel::isValidName(std::string name) {
	if (name[0] != '#' && name[0] != '&')
		return false;
	if (name.length() > 200)
		return false;
	if (name.find_first_not_of(" ,") != std::string::npos)
		return false;
	return true;
}

void	Channel::sendMessage(Message message) {
	if (message.getContent().empty())
		return ;
	if (!this->hasClient(message.getSender()))
		return ;

	this->_messages.push_back(message);

	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		Client	*sender = ServerInstance::getInstance()->getClient(message.getSender());
	
		Client::sendMessage(
			ServerInstance::getInstance()->getClient(*it)->getFd(),
			"Channel " + this->_name + " :" + sender->getNickname() + " : " + message.getContent() + "\r\n"
		);
	}
}

void	Channel::addClient(int client)
{
	if (!this->hasClient(client))
		this->_clients.push_back(client);
}

bool	Channel::hasClient(int client)
{
	for (std::vector<int>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		if (*it == client)
			return true;
	return false;
}

std::vector<int>	&Channel::getClients()
{
	return this->_clients;
}
