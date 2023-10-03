#include "Join.hpp"
#include "../../Channel/Channel.hpp"

Join::Join() {
	this->_minArgsRequired = 4;
	this->_maxArgsRequired = 4;
	this->_commandName = "USER";
}

Join::~Join() {}

std::string	Join::getName(std::vector<std::string> args) const {
	return args[1];
}

void	Join::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string name = this->getName(args);

	Channel channel = Channel(name, true);

	ServerInstance::getInstance()->addChannel(channel);
}
