#include "Topic.hpp"

Topic::Topic() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "NICK";
}

Topic::~Topic() {}

std::string	Topic::getNickname(std::vector<std::string> args) const {
	return args[1];
}

void	Topic::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string nickname = this->getNickname(args);

	if (ServerInstance::getInstance()->getClientByNickname(nickname) != NULL)
		return Client::sendMessage(client.getFd(), "462 " + this->_commandName + " :Nickname already taken");

	ServerInstance::getInstance()->getClient(client.getFd())->setNickname(nickname);
}

bool	Topic::isValidNickname(std::string nickname) {
	if (!nickname.length())
		return false;
	if (nickname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
		return false;
	return true;
}
