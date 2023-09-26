#include "Auth.hpp"

bool	Auth::isAuthorized(Client client, std::string command) {
	if (client.isAuthenticated())
		return true;
	if (command == "PASS")
		return true;
	if (command == "NICK" || command == "USER")
		return true;
	if (client.isAuthenticated())
		return true;
	return false;
}