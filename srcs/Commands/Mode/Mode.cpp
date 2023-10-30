#include "Mode.hpp"
#include <rpl_errors.h>
#include <rpl_numeric.h>

Mode::Mode() {
	this->_minArgsRequired = 2;
	this->_maxArgsRequired = 3;
	this->_commandName = "USER";
}

Mode::~Mode() {}

std::string	Mode::getChannel(std::vector<std::string> args) const {
	return args[1];
}

std::string	Mode::getMode(std::vector<std::string> args) const {
	return args[2];
}

std::string	Mode::getValue(std::vector<std::string> args) const {
	if (args.size() < 4)
		return "";
	return args[3];
}

bool	Mode::isForSet(std::string mode) const {
	if (mode[0] == '+')
		return true;
	return false;
}

bool	Mode::isValidMode(std::string mode) const {
	if (mode[0] != '+' && mode[0] != '-')
		return false;
	if (mode[1] != 'i' && mode[1] != 'k' && mode[1] != 'o')
		return false;
	if (mode.length() > 2)
		return false;
	return true;
}

void	Mode::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	// Get needed args
	std::string channel_name = this->getChannel(args);
	std::string mode = this->getMode(args);

	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);
	if (!channel)
	{
		client.reply(ERR_NOSUCHCHANNEL, channel_name.c_str());
		return;
	}
	if (!this->isValidMode(mode))
	{
		// TODO: Change ERR_UNKNOWNCOMMAND to unknown mode
		client.reply(ERR_UNKNOWNCOMMAND, mode.c_str());
		return;
	}

	bool is_for_set = this->isForSet(mode);
	std::string value = "";

	if (is_for_set)
		value = this->getValue(args);

	if (mode[1] == 'k')
	{
		if (is_for_set)
			channel->addMode(Channel::K_PASSWORD);
		else
			channel->delMode(Channel::K_PASSWORD);
		channel->setPassword(is_for_set ? value : "");
	}
	else if (mode[1] == 'i')
	{
		if (is_for_set)
			channel->addMode(Channel::I_INVITE);
		else
			channel->delMode(Channel::I_INVITE);
	}
	else if (mode[1] == 'o')
	{
		Client *client = ServerInstance::getInstance()->getClientByNickname(value);
		if (is_for_set)
			channel->addOperator(client->getFd());
		else
			channel->removeOperator(client->getFd());
	}
}
