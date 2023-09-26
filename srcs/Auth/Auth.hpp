#ifndef AUTH_HPP
# define AUTH_HPP

# include <main.hpp>
# include "../Client/Client.hpp"

class Auth {
	public:
		static bool	isAuthorized(Client client, std::string command);
};

#endif