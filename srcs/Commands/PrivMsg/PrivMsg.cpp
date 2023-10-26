#include "PrivMsg.hpp"
#include <rpl_errors.h>

PrivMsg::PrivMsg() {
	this->_minArgsRequired = 2;
	this->_maxArgsRequired = -1;
	this->_commandName = "PRIVMSG";
}

PrivMsg::~PrivMsg() {}

std::string	PrivMsg::getUsername(std::vector<std::string> args) const {
	std::string username = args[1];
	if (Nick::isValidNickname(username))
		return username;
	return username;
}

std::string	PrivMsg::getMessage(std::vector<std::string> args) const {
	std::string message = "";
	for (size_t i = 2; i < args.size(); i++)
	{
		message += args[i];
		if (i < args.size() - 1)
			message += " ";
	}
	return message;
}

void	PrivMsg::sendMessageClient(Client sender, std::string username, std::string message) const {
	Client *receiver = ServerInstance::getInstance()->getClientByNickname(username);
	if (receiver)
		receiver->sendPrivMsg(&sender, message);
	else
		sender.reply(ERR_NOSUCHNICK, username.c_str());
}

void	PrivMsg::sendMessageChannel(Client sender, std::string name, std::string message) const {
	Channel *channel = ServerInstance::getInstance()->getChannel(name);
	bool hasClient = channel->hasClient(sender.getFd());

	if (channel && hasClient)
	{
//		channel->showClients();
		channel->broadcastChanMsg(&sender, message);
	}
	else if (!hasClient)
		sender.reply(ERR_NOTONCHANNEL, name.c_str());
	else
		sender.reply(ERR_NOSUCHCHANNEL, name.c_str());	
}

bool	PrivMsg::isToChannel(std::string channel_name) const
{
	return (channel_name[0] == '#' || channel_name[0] == '&');
}

void	PrivMsg::execute(Client &sender, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(sender);

	std::string username = this->getUsername(args);
	std::string message = this->getMessage(args);

    std::cout << "Execute privmsg" << std::endl;

	if (username == sender.getUsername())
		// I don't think that this is the correct reply
		return sender.reply("462 ", this->_commandName + " :You can't send a message to yourself");

	if (this->isToChannel(username))
		this->sendMessageChannel(sender, username, message);
	else
		this->sendMessageClient(sender, username, message);
}
