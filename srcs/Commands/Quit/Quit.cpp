#include "Quit.hpp"

Quit::Quit() {
	this->_minArgsRequired = 0;
	this->_maxArgsRequired = 0;
	this->_commandName = "USER";
}

Quit::~Quit() {}

void	Quit::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	ServerInstance::getInstance()->disconnectClientFromFD(client.getFd());
}
