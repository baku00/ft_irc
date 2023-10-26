#include "Topic.hpp"
#include "../../String/String.hpp"

Topic::Topic() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = -1;
	this->_commandName = "TOPIC";
}

Topic::~Topic() {}

std::string	Topic::getChannel(std::vector<std::string> args) const {
	return args[1];
}

std::string	Topic::getTopic(std::vector<std::string> args) const {
	return args[2];
}

void	Topic::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string channel_name = this->getChannel(args);
	std::string topic = this->getTopic(args);

	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);
	if (!channel)
		return client.reply(ERR_NOSUCHCHANNEL, channel_name.c_str());
	if (!channel->hasClient(client.getFd()))
		return client.reply(ERR_NOTONCHANNEL, channel_name.c_str());
	if (channel->hasMode(Channel::I_INVITE) && !channel->hasOperator(client))
		return client.reply(ERR_CHANOPRIVSNEEDED, channel_name.c_str());
	if (args.size() == 1)
		return client.reply(RPL_TOPIC, channel_name.c_str(), channel->getTopic().c_str());
	channel->setTopic(String::trim(topic, " \t\n\r\""));
	channel->sendTopic();
}
