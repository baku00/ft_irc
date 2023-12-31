#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

#include <iostream>
#include <string>
#include <vector>
#include "../Client/Client.hpp"

class Client;

class ACommand {
	protected:
		int			_minArgsRequired;
		int			_maxArgsRequired;
		std::string	_commandName;

	public:
		ACommand();
		virtual ~ACommand();
		virtual void	execute(Client &client, std::vector<std::string> args) const = 0;
		bool			isValidArgsNumber(int nbArgs) const;
		std::string		getCommandName() const;
		void			errorNumberArguments(Client client) const;
};

#endif
