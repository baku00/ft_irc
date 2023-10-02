#include "Msg.hpp"

Msg::Msg() {
	this->_minArgsRequired = 2;
	this->_maxArgsRequired = -1;
	this->_commandName = "MSG";
}

Msg::~Msg() {}

std::string	Msg::getUsername(std::vector<std::string> args) const {
	std::string username = args[1];
	if (Nick::isValidNickname(username))
		return username;
	return username;
}

std::string	Msg::getMessage(std::vector<std::string> args) const {
	std::string message = "";
	for (size_t i = 2; i < args.size(); i++)
	{
		message += args[i];
		if (i < args.size() - 1)
			message += " ";
	}
	return message;
}

void	Msg::sendMessage(Client client, std::string username, std::string message) const {
	Client* user = ServerInstance::getInstance()->getClientByNickname(username);
	if (user == NULL)
		return Client::sendMessage(client.getFd(), "462 " + this->_commandName + " :User not found");
	Client::sendMessage(user->getFd(), this->_commandName + " " + client.getNickname() + " " + message);
}

void	Msg::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string username = this->getUsername(args);
	std::string message = this->getMessage(args);

	if (username == client.getUsername())
		return Client::sendMessage(client.getFd(), "462 " + this->_commandName + " :You can't send a message to yourself");

	this->sendMessage(client, username, message);
}
