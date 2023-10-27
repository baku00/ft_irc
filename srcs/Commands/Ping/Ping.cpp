#include "Ping.hpp"

Ping::Ping() {
	this->_minArgsRequired = 0;
	this->_maxArgsRequired = 0;
	this->_commandName = "PING";
}

Ping::~Ping() {}

void	Ping::execute(Client client, std::vector<std::string> args) const {
	(void) args;
	// Isn't PING supposed to be sent from the server to a client ?
	client.sendPrivMsg(&client, "PONG");
}
