#include "Invite.hpp"

Invite::Invite() {
	this->_minArgsRequired = 2;
	this->_maxArgsRequired = 2;
	this->_commandName = "INVITE";
}

Invite::~Invite() {}

std::string	Invite::getNickname(std::vector<std::string> args) const {
	return args[1];
}

std::string	Invite::getChannel(std::vector<std::string> args) const {
	return args[2];
}

void	Invite::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);	

	std::string nickname = this->getNickname(args);
	std::string channel_name = this->getChannel(args);

	Server	* server	= ServerInstance::getInstance();
	Channel	* channel	= server->getChannel(channel_name);
	Client	* invited	= server->getClientByNickname(nickname);

	if (!channel)
	{
		// This is not in the RFC but some servers implement it
		// this way and it seems to be the simplest solution.
		client.reply(ERR_NOSUCHCHANNEL, channel_name.c_str());
		return;
	}

	if (!invited)
	{
		client.reply(ERR_NOSUCHNICK, nickname.c_str());
		return;
	}

	if (!channel->hasClient(client))
	{
		client.reply(ERR_NOTONCHANNEL, channel_name.c_str());
		return;
	}

	if (channel->hasMode(Channel::I_INVITE) && !channel->hasOperator(client))
	{
		client.reply(ERR_CHANOPRIVSNEEDED, channel_name.c_str());
		return;
	}

	if (channel->hasClient(*invited))
	{
		client.reply(ERR_USERONCHANNEL, nickname.c_str(), channel_name.c_str());
		return;
	}

	channel->invite(*invited);
	invited->sendMessage(&client, "INVITE " + nickname + " " + channel_name);
	client.reply(RPL_INVITING, channel_name.c_str(), nickname.c_str());
}
