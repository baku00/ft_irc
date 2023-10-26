#ifndef USER_HPP
# define USER_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class User : public ACommand {
	private:
		std::string		getUsername(std::vector<std::string> args) const;
		std::string		getHostname(std::vector<std::string> args) const;
		std::string		getServername(std::vector<std::string> args) const;
		std::string		getRealname(std::vector<std::string> args) const;

	public:
		User();
		virtual ~User();
		virtual void		execute(Client &client, std::vector<std::string> args) const;

		static bool			isValidUsername(std::string username);
		static bool			isValidHostname(std::string hostname);
		static bool			isValidServername(std::string servername);
		static bool			isValidRealname(std::string realname);
};

#endif