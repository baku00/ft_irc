#include "Quit.hpp"

Quit::Quit() {
	this->_minArgsRequired = 0;
	this->_maxArgsRequired = 0;
	this->_commandName = "QUIT";
}

Quit::~Quit() {}

void	Quit::execute(Client client, std::vector<std::string> args) const {
	(void) args;
	ServerInstance::getInstance()->disconnectClientFromFD(client.getFd());
}
