#include "ACommand.hpp"
#include <rpl_errors.h>

ACommand::ACommand() {
}

ACommand::~ACommand() {
}

bool	ACommand::isValidArgsNumber(int args) const
{
	if (_minArgsRequired == -1 && _maxArgsRequired == -1)
		return true;
	if (_minArgsRequired == -1 && args <= _maxArgsRequired)
		return true;
	if (_maxArgsRequired == -1 && args >= _minArgsRequired)
		return true;
	if (_minArgsRequired == _maxArgsRequired && args == _minArgsRequired)
		return true;
	if (args >= _minArgsRequired && args <= _maxArgsRequired)
		return true;
	return false;
}

std::string	ACommand::getCommandName() const {
	return this->_commandName;
}

void	ACommand::errorNumberArguments(Client client) const {
	client.reply(ERR_NEEDMOREPARAMS, this->_commandName.c_str());
}

void	ACommand::executeMaster(Client client, std::vector<std::string> args) {
	if (this->isValidArgsNumber(args.size() - 1))
		this->execute(client, args);
	else
		this->errorNumberArguments(client);
}
