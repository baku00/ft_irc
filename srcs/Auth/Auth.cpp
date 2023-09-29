#include "Auth.hpp"

bool	Auth::isAuthorized(Client client, std::string command) {
	if (client.isAuthenticated())
		return true;
	if (command == "PASS")
		return true;
	return false;
}

bool	Auth::authenticate(Client *client, std::string password) {
	client->login(password == ServerInstance::getInstance()->getPassword());
	return client->isAuthenticated();
}
