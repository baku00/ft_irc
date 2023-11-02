#include "Mode.hpp"
#include <rpl_errors.h>
#include <rpl_numeric.h>

Mode::Mode() {
	this->_minArgsRequired = 2;
	this->_maxArgsRequired = 3;
	this->_commandName = "MODE";
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
	if (mode[1] != 'i' && mode[1] != 'k' && mode[1] != 'o' && mode[1] != 'l' && mode[1] != 't')
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

	// Skip mode if not for channel
	if (channel_name[0] != '#')
		return;

	std::string mode = this->getMode(args);
	std::string value = this->getValue(args);

	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);
	if (!channel)
	{
		client.reply(ERR_NOSUCHCHANNEL, channel_name.c_str());
		return;
	}
	if (!channel->hasOperator(client))
	{
		client.reply(ERR_CHANOPRIVSNEEDED, channel_name.c_str());
		return;
	}
	if (!this->isValidMode(mode))
	{
		client.reply(ERR_UNKNOWNMODE, mode.c_str(), channel_name.c_str());
		return;
	}

	bool is_for_set = this->isForSet(mode);

	if (mode[1] == 'k')
	{
		if (is_for_set)
			channel->addMode(Channel::K_PASSWORD);
		else
			channel->delMode(Channel::K_PASSWORD);
		channel->setPassword(is_for_set ? value : "");
	}
	else if (mode[1] == 'l')
	{
		if (is_for_set)
			channel->addMode(Channel::L_LIMIT);
		else
			channel->delMode(Channel::L_LIMIT);
		try
		{
			channel->setLimit(is_for_set ? std::atoi(value.c_str()) : 0);
		}
		catch(const std::exception& e)
		{
			client.reply(ERR_NEEDMOREPARAMS, "MODE");
		}
		
	}
	else if (mode[1] == 'i')
	{
		if (is_for_set)
			channel->addMode(Channel::I_INVITE);
		else
			channel->delMode(Channel::I_INVITE);
	}
	else if (mode[1] == 't')
	{
		if (is_for_set)
			channel->addMode(Channel::T_TOPIC);
		else
			channel->delMode(Channel::T_TOPIC);
	}
	else if (mode[1] == 'o')
	{
		Client *client = ServerInstance::getInstance()->getClientByNickname(value);
		if (is_for_set)
			channel->addOperator(client->getFd());
		else
		{
			std::cout << "Client: " << client << std::endl;
			std::cout << "FD: " << client->getFd() << std::endl;
			channel->removeOperator(client->getFd());
		}
	}
	else
	{
		return client.reply(ERR_UNKNOWNMODE, &mode[1], channel_name.c_str());
	}

	channel->broadcastMessage(&client, "MODE " + channel_name + " " + mode + " " + value);
}
