#include "Auth.hpp"

std::vector<std::string>	Auth::getAuthorizedCommands()
{
	std::vector<std::string> commands;

	commands.push_back("USER");
	commands.push_back("NICK");
	commands.push_back("QUIT");

	return commands;
}

bool	Auth::isAuthorized(Client client, std::string command) {
	if (command == "PASS")
		return true;
	if (!client.isValidate() && client.isAuthenticated())
	{
		std::vector<std::string> authorizedCommands = Auth::getAuthorizedCommands();
		for (std::vector<std::string>::iterator it = authorizedCommands.begin(); it != authorizedCommands.end(); it++)
			if (command == *it)
				return true;
	}
	if (client.isValidate())
		return true;
	return false;
}

bool	Auth::authenticate(Client *client, std::string password) {
	client->login(password == ServerInstance::getInstance()->getPassword());
	return client->isAuthenticated();
}
