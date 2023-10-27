#include "Me.hpp"

Me::Me() {
	this->_minArgsRequired = 0;
	this->_maxArgsRequired = 0;
	this->_commandName = "Me";
}

Me::~Me() {}

void	Me::execute(Client client, std::vector<std::string> args) const {
	(void) args;
	// What is this command ? Not specified in RFC...
	client.sendPrivMsg(&client, client.getInfo());
}
