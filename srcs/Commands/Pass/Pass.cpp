#include "Pass.hpp"

Pass::Pass() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
}

Pass::~Pass() {}

void	Pass::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return Client::sendMessage(client.getFd(), "461 PASS :Not enough parameters");
	if (!Auth::authenticate(ServerInstance::getInstance()->getClient(client.getFd()), args[1]))
		return Client::sendMessage(client.getFd(), "462 PASS :Password incorrect");
	Client::sendMessage(client.getFd(), "230 PASS :Password correct");
}
