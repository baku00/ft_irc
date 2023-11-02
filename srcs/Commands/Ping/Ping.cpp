#include "Ping.hpp"

Ping::Ping() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "PING";
}

Ping::~Ping() {}

void	Ping::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	client.sendMessage(&client, "PONG");
}
