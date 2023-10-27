#include "Nick.hpp"
#include <rpl_errors.h>

Nick::Nick() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "NICK";
}

Nick::~Nick() {}

std::string	Nick::getNickname(std::vector<std::string> args) const {
	return args[1];
}

void	Nick::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string nickname = this->getNickname(args);

	if (ServerInstance::getInstance()->getClientByNickname(nickname) != NULL)
		client.reply(ERR_NICKNAMEINUSE, nickname.c_str());

	ServerInstance::getInstance()->getClient(client.getFd())->setNickname(nickname);
}

bool	Nick::isValidNickname(std::string nickname) {
	if (!nickname.length())
		return false;
	if (nickname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
		return false;
	return true;
}
