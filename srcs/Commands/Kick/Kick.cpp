#include "Kick.hpp"

Kick::Kick() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "USER";
}

Kick::~Kick() {}

std::string	Kick::getName(std::vector<std::string> args) const {
	return args[1];
}

void	Kick::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string channel_name = this->getName(args);

	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);
	if (!channel)
	{
		channel = new Channel();
		channel->setName(channel_name);
		ServerInstance::getInstance()->addChannel(channel);
	}
	channel->addClient(client.getFd());
}
