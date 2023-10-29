#include "Mode.hpp"

Mode::Mode() {
	this->_minArgsRequired = 2;
	this->_maxArgsRequired = -1;
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
	return args[3];
}

void	Mode::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);	

	std::string channel_name = this->getChannel(args);
	std::string mode = this->getMode(args);
	bool		set_password = false;


	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);
	if (mode.length() != 2)
		return client.reply(ERR_NEEDMOREPARAMS, this->_commandName.c_str());
	if (!channel)
		return client.reply(ERR_NOSUCHCHANNEL, channel_name.c_str());
	if (mode[0] != '+' && mode[0] != '-')
		// TODO: Change ERR_UNKNOWNCOMMAND to correct error message
		return client.reply(ERR_UNKNOWNCOMMAND, mode.c_str());

	switch (mode[1])
	{
		case 'i':
			if (mode[0] == '+')
				channel->addMode(Channel::I_INVITE);
			else if (mode[0] == '-')
				channel->delMode(Channel::I_INVITE);
			break;
		case 't':
			if (mode[0] == '+')
				channel->addMode(Channel::T_TOPIC);
			else if (mode[0] == '-')
				channel->delMode(Channel::T_TOPIC);
			break;
		case 'k':
			if (mode[0] == '+')
				set_password = true;

			if (set_password)
				channel->addMode(Channel::K_PASSWORD);
			else
				channel->delMode(Channel::K_PASSWORD);

			channel->setPassword(set_password ? this->getValue(args) : "");

			break;
		case 'o':
			// std::string _operator = this->getValue(args);
			// Client *client_operator = ServerInstance::getInstance()->getClientByNickname(_operator);

			// if (!client_operator)
			// 	return client.reply(ERR_NOSUCHNICK, _operator.c_str());

			// if (mode[0] == '+')
			// 	channel->addOperator(*client_operator);
			// else
			// 	channel->delOperator(*client_operator);
			break;
		case 'l':
			// std::string limit = this->getValue(args);
			// bool	is_limited = limit.length() != 0;

			// if (is_limited < 0)
			// 	// TODO: Change ERR_NEEDMOREPARAMS to correct error message
			// 	return client.reply(ERR_NEEDMOREPARAMS, this->_commandName.c_str());

			// if (mode[0] == '+')
			// 	channel->addMode(Channel::L_LIMIT);
			// else
			// 	channel->delMode(Channel::L_LIMIT);
			// channel->setLimit(is_limited ? std::stoi(limit) : 0);
			break;
		default:
			// error
			break;
	}
}
