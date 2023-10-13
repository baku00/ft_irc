#include "Invite.hpp"

Invite::Invite() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "INVITE";
}

Invite::~Invite() {}

std::string	Invite::getName(std::vector<std::string> args) const {
	return args[1];
}

void	Invite::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::vector<std::string>::iterator it = args.begin();
	for (; it != args.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	

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
