#include "User.hpp"

User::User() {
	this->_minArgsRequired = 4;
	this->_maxArgsRequired = 4;
	this->_commandName = "USER";
}

User::~User() {}

std::string	User::getUsername(std::vector<std::string> args) const {
	return args[1];
}

std::string	User::getHostname(std::vector<std::string> args) const {
	return args[2];
}

std::string	User::getServername(std::vector<std::string> args) const {
	return args[3];
}

std::string	User::getRealname(std::vector<std::string> args) const {
	return args[4];
}

void	User::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string username = this->getUsername(args);
	std::string hostname = this->getHostname(args);
	std::string servername = this->getServername(args);
	std::string realname = this->getRealname(args);

	client.setUserInfo(
		username,
		hostname,
		servername,
		realname
	);
}

bool	User::isValidUsername(std::string username) {
	if (!username.length())
		return false;
	if (username.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
		return false;
	return true;
}

bool	User::isValidHostname(std::string hostname) {
	if (!hostname.length())
		return false;
	if (hostname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
		return false;
	return true;
}

bool	User::isValidServername(std::string servername) {
	if (!servername.length())
		return false;
	if (servername.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
		return false;
	return true;
}

bool	User::isValidRealname(std::string realname) {
	if (!realname.length())
		return false;
	if (realname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
		return false;
	return true;
}