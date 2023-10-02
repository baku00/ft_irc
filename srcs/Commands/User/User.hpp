#ifndef USER_HPP
# define USER_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class User : public ACommand {
	private:
		std::string		getUsername(std::vector<std::string> args) const;
		std::string		getFirstname(std::vector<std::string> args) const;
		std::string		getLastname(std::vector<std::string> args) const;

	public:
		User();
		virtual ~User();
		virtual void		execute(Client client, std::vector<std::string> args) const;
};

#endif