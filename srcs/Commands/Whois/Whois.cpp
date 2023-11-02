#include "Whois.hpp"
#include <rpl_numeric.h>

Whois::Whois() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "PING";
}

Whois::~Whois() {}

void	Whois::execute(Client &client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	Client * target = ServerInstance::getInstance()->getClientByNickname(args[1]);
	if (target == NULL)
		return client.reply(ERR_NOSUCHNICK, args[1].c_str());

	client.reply(RPL_WHOISUSER,
				 target->getNickname().c_str(),
				 target->getUsername().c_str(),
				 target->getHostname().c_str(),
				 target->getRealname().c_str());
}
