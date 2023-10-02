#include "Nick.hpp"

Nick::Nick() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "NICK";
}

Nick::~Nick() {}

std::string	Nick::getNickname(std::vector<std::string> args) const {
	return args[1];
}

void	Nick::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string nickname = this->getNickname(args);

	if (ServerInstance::getInstance()->getClientByNickname(nickname) != NULL)
		return Client::sendMessage(client.getFd(), "462 " + this->_commandName + " :Nickname already taken");

	ServerInstance::getInstance()->getClient(client.getFd())->setNickname(nickname);
}
