#include "Join.hpp"
#include "../../Channel/Channel.hpp"

Join::Join() {
	this->_minArgsRequired = 1;
	this->_maxArgsRequired = 1;
	this->_commandName = "USER";
}

Join::~Join() {}

std::string	Join::getName(std::vector<std::string> args) const {
	return args[1];
}

void	Join::execute(Client client, std::vector<std::string> args) const {
	if (!this->isValidArgsNumber(args.size() - 1))
		return this->errorNumberArguments(client);

	std::string name = this->getName(args);
	Channel	*channel = ServerInstance::getInstance()->getChannel(name);
	if (channel)
	{
		std::cout << "Ajout du client" << std::endl;
		channel->addClient(client.getFd());
	}
	else
	{
		std::cout << "Création du channel" << std::endl;
		channel = new Channel(name, true);
		channel->addClient(client.getFd());
		ServerInstance::getInstance()->addChannel(channel);
	}
	std::string clients = "";
	for (std::vector<int>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); it++)
	{
		if (it != channel->getClients().begin())
			clients += " ";
		clients += ServerInstance::getInstance()->getClient(*it)->getNickname();
	}
	std::cout << "Clients: " << clients << std::endl;
	channel->sendMessage(Message(client.getFd(), "JOIN " + channel->getName()));
}
