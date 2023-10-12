#include "Kick.hpp"

Kick::Kick() {
	this->_minArgsRequired = 2;
	this->_maxArgsRequired = -1;
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

std::string	Kick::getClient(std::vector<std::string> args) const {
	return args[2];
}

void	Kick::execute(Client sender, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(sender);

	std::string channel_name = this->getChannel(args);
	std::string nickname = this->getNickname(args);
	std::string reason = this->getReason(args);

	Client *client_to_kick = ServerInstance::getInstance()->getClientByNickname(nickname);

	if(!client_to_kick)
		return Client::sendMessage(client.getFd(), "Client not found");

	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);

	if (!client)
		return Client::sendMessage(sender.getFd(), "Le client '" + client_name + "' n'existe pas");
	if (!channel)
		return Client::sendMessage(client.getFd(), "Channel not found");

	bool hasBeenEjected = channel->removeClient(client_to_kick->getFd());
	if (hasBeenEjected)
		Client::sendMessage(client_to_kick->getFd(), this->getCommandName() + " " + channel_name + " " + nickname + " " + reason + "\r\n");
}
