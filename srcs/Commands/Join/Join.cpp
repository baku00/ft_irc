#include "Join.hpp"
#include <rpl_errors.h>

Join::Join() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "USER";
}

Join::~Join() {}

std::string	Join::getName(std::vector<std::string> args) const {
	return args[1];
}

void	Join::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string channel_name = this->getName(args);

	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);
	if (!channel)
		channel = Channel::create(channel_name);

	if (channel->hasMode(Channel::I_INVITE) && !channel->hasInvited(client))
	{
		client.reply(ERR_CHANOPRIVSNEEDED, channel_name.c_str());
		return;
	}
	
	channel->addClient(client.getFd());
}
