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

bool		Topic::containsTopic(std::vector<std::string> args) const {
	return args.size() - 1 > 1;
}

void		Topic::setTopic(Client client, Channel *channel, std::vector<std::string> args) const
{
	if (channel->hasMode(Channel::T_TOPIC) && !channel->hasOperator(client))
		return client.reply(ERR_CHANOPRIVSNEEDED, channel->getName().c_str());
	channel->setTopic(String::trim(this->getTopic(args), " \t\n\r\""));
	channel->sendTopic();
}

void	Topic::execute(Client & client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string channel_name = this->getChannel(args);
	Channel *channel = ServerInstance::getInstance()->getChannel(channel_name);

	if (!channel)
		return client.reply(ERR_NOSUCHCHANNEL, channel_name.c_str());
	if (!channel->hasClient(client.getFd()))
		return client.reply(ERR_NOTONCHANNEL, channel_name.c_str());

	if (this->containsTopic(args))
		this->setTopic(client, channel, args);
	else
		client.reply(RPL_TOPIC, channel_name.c_str(), channel->getTopic().c_str());
}
