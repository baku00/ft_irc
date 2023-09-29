#include "Nick.hpp"

Nick::Nick() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
}

Nick::~Nick() {}

std::string	Nick::getUsername(std::vector<std::string> args) const {
	return args[1];
}

void	Nick::execute(Client _client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return Client::sendMessage(_client.getFd(), "461 NICK :Not valid number of parameters");
	std::string username = this->getUsername(args);
	if (ServerInstance::getInstance()->getClientByUsername(username) != NULL)
		return Client::sendMessage(_client.getFd(), "462 NICK :Username already taken");
	ServerInstance::getInstance()->getClient(_client.getFd())->setUsername(username);
}
