#include "PrivMsg.hpp"

PrivMsg::PrivMsg() {
	this->_minArgsRequired = 2;
	this->_maxArgsRequired = -1;
	this->_commandName = "PRIVMSG";
}

PrivMsg::~PrivMsg() {}

std::string	PrivMsg::getUsername(std::vector<std::string> args) const {
	std::string username = args[1];
	if (Nick::isValidNickname(username))
		return username;
	return username;
}

std::string	PrivMsg::getMessage(std::vector<std::string> args) const {
	std::string message = "";
	for (size_t i = 2; i < args.size(); i++)
	{
		message += args[i];
		if (i < args.size() - 1)
			message += " ";
	}
	return message;
}

void	PrivMsg::sendMessageClient(Client sender, std::string username, std::string message) const {
	Client *receiver = ServerInstance::getInstance()->getClientByNickname(username);
	if (receiver)
		receiver->sendMessage(&sender, message);
	else
		Client::sendMessage(sender.getFd(), "462 " + this->_commandName + " :User not found");
}

void	PrivMsg::sendMessageChannel(Client sender, std::string name, std::string message) const {
	(void) sender;
	(void) name;
	(void) message;
	Channel *channel = ServerInstance::getInstance()->getChannel(name);
	if (channel)
	{
		channel->showClients();
		channel->sendMessage(&sender, message);
	}
	else
		Client::sendMessage(sender.getFd(), "Channel not found");
}

bool	PrivMsg::isToChannel(std::string channel_name) const
{
	return (channel_name[0] == '#');
}

void	PrivMsg::execute(Client sender, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(sender);

	std::string username = this->getUsername(args);
	std::string message = this->getMessage(args);

	std::cout << "Client:" << std::endl;
	std::cout << &sender << std::endl;

	if (username == sender.getUsername())
		return Client::sendMessage(sender.getFd(), "462 " + this->_commandName + " :You can't send a message to yourself");
	
	if (this->isToChannel(username))
		this->sendMessageChannel(sender, username, message);
	else
		this->sendMessageClient(sender, username, message);
}
