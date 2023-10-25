#include "Join.hpp"
#include <rpl_errors.h>
#include <rpl_numeric.h>

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

    // Get needed args
    Server * server = ServerInstance::getInstance();
	std::string channel_name = this->getName(args);

    // Create Channel if it doesn't exist
	Channel *channel = server->getChannel(channel_name);
	if (!channel)
		channel = Channel::create(channel_name);

    // ERR_INVITEONLYCHAN if mode invite (+i) and not invited
	if (channel->hasMode(Channel::I_INVITE) && !channel->hasInvited(client))
	{
		client.reply(ERR_INVITEONLYCHAN, channel_name.c_str());
		return;
	}

    // SUCCESS!

    // 1. Add the client to the channel
    channel->addClient(client.getFd());

    // 2. Notify all channel members (including the client itself)
    channel->broadcastMessage(&client, "JOIN " + channel_name);

    // 3. RPL_TOPIC, RPL_NAMREPLY and RPL_ENDOFNAMES
    // TODO: here replace by topic
    client.reply(RPL_TOPIC, channel_name.c_str(), "");
    client.reply(RPL_NAMREPLY, channel_name.c_str(), channel->getNicknames().c_str());
}
