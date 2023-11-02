#include "Kick.hpp"

Kick::Kick() {
	this->_minArgsRequired = 2;
	this->_maxArgsRequired = 3;
	this->_commandName = "KICK";
}

Kick::~Kick() {}

std::string	Kick::getChannel(std::vector<std::string> args) const {
	return args[1];
}

std::string	Kick::getNickname(std::vector<std::string> args) const {
	return args[2];
}

std::string	Kick::getReason(std::vector<std::string> args) const {
	if (args.size() == 4)
		return args[3];
	return "";
}

void	Kick::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string channel_name = this->getChannel(args);
	std::string nickname = this->getNickname(args);
	std::string reason = this->getReason(args);

	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);
	if (!channel)
		return client.reply(ERR_NOSUCHCHANNEL, channel_name.c_str());

	if (!channel->hasClient(client))
		return client.reply(ERR_NOTONCHANNEL, channel_name.c_str());

	if (!channel->hasOperator(client))
		return client.reply(ERR_CHANOPRIVSNEEDED, channel_name.c_str());

	Client *client_to_kick = ServerInstance::getInstance()->getClientByNickname(nickname);
	if (client_to_kick == NULL || !channel->hasClient(*client_to_kick))
		return client.reply(ERR_USERNOTINCHANNEL, nickname.c_str(), channel_name.c_str());

	channel->broadcastMessage(&client, "KICK " + channel_name + " " + nickname + " " + reason);
	channel->removeClient(client_to_kick->getFd());
}
