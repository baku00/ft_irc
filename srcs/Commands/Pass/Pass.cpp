#include "Pass.hpp"

Pass::Pass() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "PASS";
}

Pass::~Pass() {}

void	Pass::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	if (!Auth::authenticate(ServerInstance::getInstance()->getClient(client.getFd()), args[1]))
		return Client::sendMessage(client.getFd(), "462 " + this->_commandName + " :Password incorrect");
	
	Client::sendMessage(client.getFd(), "230 " + this->_commandName + " :Password correct");
}
