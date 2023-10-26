#include "Auth.hpp"
#include <algorithm>

std::vector<std::string> Auth::getAuthorizedCommands() {
	std::vector<std::string> commands;

	commands.push_back("PASS");
	commands.push_back("NICK");
	commands.push_back("USER");
	commands.push_back("QUIT");

	return commands;
}

bool Auth::isAuthorized(const std::string &command, bool is_registered) {
	if (is_registered)
		return true;

	std::vector<std::string> allowed_commands = getAuthorizedCommands();
	std::vector<std::string>::iterator is_allowed = std::find(
			allowed_commands.begin(),
			allowed_commands.end(),
			command
	);
	if (is_allowed != allowed_commands.end())
		return true;

	return false;
}

bool Auth::authenticate(Client *client, std::string password) {
	client->login(password == ServerInstance::getInstance()->getPassword());
	return client->isAuthenticated();
}
