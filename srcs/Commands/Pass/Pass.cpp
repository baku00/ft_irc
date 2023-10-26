#include "Pass.hpp"
#include <rpl_errors.h>

Pass::Pass() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "PASS";
}

Pass::~Pass() {}

void	Pass::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	if (!Auth::authenticate(&client, args[1]))
		return client.reply(ERR_PASSWDMISMATCH);

	// There is nothing to send directly here but the Welcome message should only
	// be sent if the password success, so maybe not send it directly in the server
	// connection but only on successfull PASS command.
	// Client::sendPrivMsg(client.getFd(), "230 " + this->_commandName + " :Password correct");
}
