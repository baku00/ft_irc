#include "Kick.hpp"

Kick::Kick() {
	this->_minArgsRequired = 1;
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

	Client *client_to_kick = ServerInstance::getInstance()->getClientByNickname(nickname);

	if(!client_to_kick)
		// Here we should send the appropriate reply
		return client.sendPrivMsg(client_to_kick, "Client not found");

	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);
	if (!channel)
		// Here we should send the appropriate reply
		return client.sendPrivMsg(client_to_kick, "Channel not found");

	bool hasBeenEjected = channel->removeClient(client_to_kick->getFd());
	if (hasBeenEjected)
		client_to_kick->sendMessage(&client, this->getCommandName() + " " + channel_name + " " + nickname + " " + reason);
}
