#include "User.hpp"

User::User() {
	this->_minArgsRequired = 3;
	this->_maxArgsRequired = 3;
	this->_commandName = "USER";
}

User::~User() {}

std::string	User::getUsername(std::vector<std::string> args) const {
	return args[1];
}

std::string	User::getFirstname(std::vector<std::string> args) const {
	return args[2];
}

std::string	User::getLastname(std::vector<std::string> args) const {
	return args[3];
}

void	User::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string username = this->getUsername(args);
	std::string firstname = this->getFirstname(args);
	std::string lastname = this->getLastname(args);

	ServerInstance::getInstance()->getClient(client.getFd())->setUserInfo(
		username,
		firstname,
		lastname
	);
}
