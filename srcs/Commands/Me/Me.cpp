#include "Me.hpp"

Me::Me() {
	this->_minArgsRequired = 0;
	this->_maxArgsRequired = 0;
	this->_commandName = "Me";
}

Me::~Me() {}

void	Me::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	Client::sendMessage(client.getFd(), client.getInfo());
}
