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

void	Invite::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);	

	std::string nickname = this->getNickname(args);
	std::string channel_name = this->getChannel(args);

	Server	* server	= ServerInstance::getInstance();
	Channel	* channel	= server->getChannel(channel_name);
	Client	* invited	= server->getClientByNickname(nickname);

	if (!invited)
	{
		client.reply(ERR_NOSUCHNICK);
		return;
	}

	if (!channel)
	{
		channel = new Channel();
		channel->setName(channel_name);
		ServerInstance::getInstance()->addChannel(channel);
		channel->invite(*invited);
	}
}
