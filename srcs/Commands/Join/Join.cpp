#include "Join.hpp"
#include <rpl_errors.h>
#include <rpl_numeric.h>

Join::Join() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 2;
	this->_commandName = "JOIN";
}

Join::~Join() {}

std::string	Join::getName(std::vector<std::string> args) const {
	std::string name = args[1];
	name = this->formatName(name);
	return name;
}

std::string	Join::getPassword(std::vector<std::string> args) const {
	if (args.size() < 3)
		return "";
	return args[2];
}

std::string Join::formatName(std::string name) const {
	if (name[0] != '#')
		return "#" + name;
	return name;
}

void	Join::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	// Get needed args
	Server * server = ServerInstance::getInstance();
	std::string channel_name = this->getName(args);
	std::string password = this->getPassword(args);

	// Create Channel if it doesn't exist
	Channel *channel = server->getChannel(channel_name);
	if (!channel)
	{
		channel = Channel::create(channel_name);
		channel->addOperator(client.getFd());
	}

	if (!channel->canJoin(client))
		return;

	if (channel->hasMode(Channel::K_PASSWORD) && !channel->isPassword(password))
	{
		client.reply(ERR_INVALIDKEY, channel_name.c_str());
		return;
	}

	// SUCCESS!

	// 1. Add the client to the channel
	channel->addClient(client.getFd());
	channel->removeInvited(client);

	// 2. Notify all channel members (including the client itself)
	channel->broadcastMessage(&client, "JOIN " + channel_name);

	// 3. RPL_TOPIC, RPL_NAMREPLY and RPL_ENDOFNAMES
	client.reply(RPL_TOPIC, channel_name.c_str(), channel->getTopic().c_str());
	client.reply(RPL_NAMREPLY, channel_name.c_str(), channel->getNicknames().c_str());
	client.reply(RPL_ENDOFNAMES, channel_name.c_str());

	std::cout << "Join command executed successfull" << std::endl;
}
