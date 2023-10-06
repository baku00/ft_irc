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

void	PrivMsg::sendMessage(Client client, std::string username, std::string message) const {
	Client* user = ServerInstance::getInstance()->getClientByNickname(username);
	printf("USER: %p\n", user);
	if (user == NULL)
		return Client::sendMessage(client.getFd(), "462 " + this->_commandName + " :User not found");
	std::cout << user << std::endl;
	user->sendMessage(&client, message);
}

bool	PrivMsg::isToChannel(std::string channel_name) const
{
	return (channel_name[0] == '#');
}

void	PrivMsg::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string username = this->getUsername(args);
	std::string message = this->getMessage(args);

	std::cout << "Client:" << std::endl;
	std::cout << &client << std::endl;

	if (username == client.getUsername())
		return Client::sendMessage(client.getFd(), "462 " + this->_commandName + " :You can't send a message to yourself");

	Client *receiver = ServerInstance::getInstance()->getClientByNickname(username);
	if (receiver)
		receiver->sendMessage(&client, message);
	else
		Client::sendMessage(client.getFd(), "462 " + this->_commandName + " :User not found");
}
